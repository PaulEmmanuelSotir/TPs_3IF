
----------------------------------------------------------------------
---  Processor
----------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.Numeric_Std.all;

entity processor is
  port (
    rst     : in  std_logic;
    ck      : in  std_logic;
    we      : out  std_logic;
    ma      : out  std_logic_vector(7 downto 0);
    mdi     : in  std_logic_vector(7 downto 0);
    mdo     : out std_logic_vector(7 downto 0)
  );
end entity;  


architecture rtl of processor is
  component reg8bits is
  port (
    rst     : in  std_logic;
    ck      : in  std_logic;
    ce      : in  std_logic;
    di      : in  std_logic_vector(7 downto 0);
    do      : out std_logic_vector(7 downto 0)
  );
  end component;  

  subtype state is std_logic_vector(3 downto 0);
  -- State encoding:
  constant LoadInstr: state    := "0000";
  constant InstrLoaded: state  := "0001";
  constant LoadCst  : state    := "0010";
  constant CstLoaded  : state  := "0011";
  constant WriteBack: state    := "0100";
  constant ReadMem   : state   := "0101";
  constant WriteMem  : state   := "0110";
  constant IllegalInstr: state := "1111";
	-- Registers to hold the current state and the next state
	signal currentState, nextState	   : state;

  --registers output and input
  signal instr, cst,
         a, b, aluOut, regABIn, arg1, arg2,
         pc, pcIn, pcOffset, nextPC    : std_logic_vector(7 downto 0);
  -- decomposition of input word
  signal destS, arg1S, arg2S, jr : std_logic;
  signal codeOp : std_logic_vector(3 downto 0);
  signal cond : std_logic_vector(1 downto 0);
  signal offset : std_logic_vector(4 downto 0);

  -- all the clock enable signale
  signal ceInstr, ceCst, ceA, ceB, ceDest, ceFlags, cePC, ja, progFetch : std_logic;

  -- other signals en vrac
  signal Z, C, N, aluZ, aluC, aluN, condTrue: std_logic;
  signal addResult, subResult: std_logic_vector(8 downto 0);
  
  -- for the FSM
  signal instrIsJA, instrIsJR, instrIsALU, instrIsCmp, instrIsNotOrCp, instrIsMem, oneWordInstr: std_logic;
  
begin

  -- All the registers in the design (except the control unit)
  regPC: reg8bits port map (rst=>rst, ck=>ck, ce=>cePC, di=>pcIn, do=>pc );
  regInstr: reg8bits port map (rst=>rst, ck=>ck, ce=>ceInstr, di=>mdi, do=>instr );
  regCst: reg8bits port map (rst=>rst, ck=>ck, ce=>ceCst, di=>mdi, do=>cst );
  regA: reg8bits port map (rst=>rst, ck=>ck, ce=>ceA, di=>regABIn, do=>a );
  regB: reg8bits port map (rst=>rst, ck=>ck, ce=>ceB, di=>regABIn, do=>b );

  -- The multiplexer on ma and PC
  ma <= pc when progFetch='1' else arg2;

  -- the input of regPC
  pcOffset <= "00000001" when jr='0'
            else  offset(4) & offset(4) & offset(4) & offset; -- sign extension 
  nextPC <= std_logic_vector(unsigned(pc) + unsigned(pcOffset));
  pcIn <= cst when ja='1' else nextPC;

  --the input of regA and regB
  regABIn <= mdi when codeOp="1101" else aluOut;
    
  --  Decomposition of the instruction word
  codeOp <= instr(6 downto 3);   
  destS <= instr(0);  
  arg1S <= instr(1);  
  arg2S <= instr(2);  
  offset <= instr(4 downto 0);
  cond <= instr(6 downto 5);
  -- the multiplexers selecting arg1 and arg2
  arg1 <= a when arg1S='0' else b;
  arg2 <= a when arg2S='0' else cst;

  -- ALU internals
  -- the adder/subtractor
  addResult <= std_logic_vector(signed('0' & arg1) + signed('0' & arg2));
  subResult <= std_logic_vector(signed('0' & arg1) - signed('0' & arg2));
  -- the following is the VHDL for a big multiplexer. Go draw it!
  with codeOp select
  aluOut <=
    addResult(7 downto 0)           when "0000",
    subResult(7 downto 0)           when "0001",
    arg1 and arg2                   when "0010",
    arg1 or  arg2                   when "0011",
    arg1 xor arg2                   when "0100",
    '0' & arg1(7 downto 1)          when "0101", -- lsr
    subResult(7 downto 0)           when "0110", -- cmp
    arg1 xor (7 downto 0 => arg2S)  when "1000",
    arg2                            when "1001",
    x"00" when others;

    -- flags
  aluC <= addResult(8) when codeOp="0000" else
          subResult(8) when codeOp="0001" or codeOp="0110" else
          arg1(0)  when codeOp="0101" else '0';
  aluZ <= '1' when aluOut = x"00" else '0'; 
  aluN <= aluOut(7);
  ceFlags <= instrIsALU and not codeOp(3);
  regFlags:  process(ck) is
  begin
    if rising_edge(ck) then
      if rst = '1' then
        C <= '0';
        Z <= '0';
        N <= '0';
      else
         if ceFlags = '1' then
           C <= aluC;
           Z <= aluZ;
           N <= aluN;
         end if;
      end if;
    end if;
  end process;
  
  ceA <= ceDest and not destS;
  ceB <= ceDest and destS;
  mdo <= arg1;

  -- The FSM register
  stateReg: process(ck) is
    begin  if rising_edge(ck) then
           if rst = '1' then  currentState <= "0000";
           else  currentState <= nextState; 
         end if;  end if;
    end process;
  -- A few intermediate signals to simplify the FSM, add more if you need to
  instrIsALU <= '1' when instrIsJR='0' and (codeOp="0000" or codeOp="0001" or codeOp="0010" or codeOp="0011" or codeOp="0100" or codeOp="0101" or codeOp="0110" or codeOp="1000" or codeOp="1001") else '0';
  instrIsJA <= '1' when instr(7 downto 3) = "01111" else '0';
  instrIsJR <= instr(7);
  condTrue <= '1' when (((	(instr(6 downto 5)="01" and Z='1'))
			or 	(instr(6 downto 5)="10" and C='1'))
			or	(instr(6 downto 5)="11" and N='1'))
			or 	(instr(6 downto 5)="00")
		else '0';
  instrIsMem <= '1'  when instrIsJR='0' and (codeOp="1101" or codeOp="1110") else '0';
  InstrIsNotOrCp <= '1' when (instr(7 downto 3) = "01000") else '0';
  InstrIsCmp <= '1' when (instr(7 downto 3) = "00110") else '0';
  -- Is the instruction coded on 1 byte or on two?
  oneWordInstr <= instrIsJR or InstrIsNotOrCp or ((instrIsALU or instrIsMem) and not arg2S);

  -- The FSM transition function: TODO
  nextState <=
    LoadInstr when currentState=WriteBack
		or ((instrIsJR='1' and currentState=InstrLoaded)
		or ((instrIsJA='1' and currentState=CstLoaded)
		or (currentState=ReadMem
		or currentState=WriteMem)))
    else
    InstrLoaded when currentState=LoadInstr
    else
    LoadCst when currentState=InstrLoaded and (((instrIsJR='0' and arg2S='1') and codeOp/="1000") or instrIsJA='1')
    else
    CstLoaded when currentState=LoadCst
    else
    ReadMem when codeOp="1101" and (currentState=CstLoaded or (currentState=InstrLoaded and arg2S='0'))
    else
    WriteMem when codeOp="1110" and (currentState=CstLoaded or (currentState=InstrLoaded and arg2S='0'))
    else
    WriteBack when (currentState=InstrLoaded or currentState=CstLoaded) and instrIsJR='0'
    else IllegalInstr;

  -- The FSM output function: TODO
  ceInstr <='1' when currentState=LoadInstr
             else '0';
  progFetch <= '1' when currentState=LoadInstr or currentState=LoadCst
                else '0';
  ceDest <='1' when currentState=WriteBack or currentState=ReadMem else '0';
  cePC <='1' when currentState=InstrLoaded or currentState=CstLoaded
          else '0';
  ceCst <='1' when currentState=LoadCst
          else '0';
  we <= '1' when currentState=WriteMem else '0';
  ja <= '1' when currentState=CstLoaded and instrIsJA='1'
          else '0';
  jr <= instrIsJR and condTrue;
  
end architecture rtl;


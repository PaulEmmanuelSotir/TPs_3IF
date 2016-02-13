
-- An 8-bit register entity to make the code smaller and closer to the drawing
library IEEE;
use IEEE.STD_LOGIC_1164.all;
entity reg8bits is
  port (
    rst     : in  std_logic;
    ck      : in  std_logic;
    ce      : in  std_logic;
    di      : in  std_logic_vector(7 downto 0);
    do      : out std_logic_vector(7 downto 0)
  );
end entity;  
-- This is a behaviorial description of a register. However, all
-- the synthesis tools will be able to infer a flip-flop with synchronous reset
-- and clock enable
architecture rtl of reg8bits is
begin
  reg: process(ck) is
  begin
    if rising_edge(ck) then
      if rst = '1' then
        do <= x"00";
      else
         if ce = '1' then
           do <= di;
         end if;
      end if;
    end if;
  end process;
end architecture rtl;



---------  Test bench -----------------
library ieee; 
use ieee.std_logic_1164.all;
library work;

entity testbench is
end entity;

architecture behaviorial of testbench is
  component memory256x8 is
  port (
    ck   : in  std_logic;
    we      : in  std_logic;
    address : in  std_logic_vector(7 downto 0);
    datain  : in  std_logic_vector(7 downto 0);
    dataout : out std_logic_vector(7 downto 0)
  );
  end component;

  component processor is
  port (
    rst      : in  std_logic;
    ck       : in  std_logic;
    we       : out  std_logic;
    ma       : out  std_logic_vector(7 downto 0);
    mdi      : in  std_logic_vector(7 downto 0);
    mdo      : out std_logic_vector(7 downto 0)
  );
  end component;
  
  signal ma,dp2m,dm2p : std_logic_vector(7 downto 0);
  signal ck, we, rst : std_logic;
begin 
  mem:  memory256x8
    port map ( ck => ck, we => we, address => ma, datain => dp2m, dataout => dm2p) ;

  proc:  processor
    port map ( ck => ck, rst => rst, we => we, ma => ma, mdi => dm2p, mdo => dp2m) ;

  clock_process : process 
   begin
     ck <= '1';
     wait for 0.5 ns; 
     ck <= '0';
     wait for 0.5 ns; 
   end process;

  rst_process : process 
   begin
     rst <= '1';
     wait for 1.1 ns; 
     rst <= '0';
     wait for 1 us; -- us is microsecond, because VHDL was invented before Unicode
   end process;



end;

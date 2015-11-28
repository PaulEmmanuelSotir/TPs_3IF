---------  Test bench for an n-bit adder -----------------
library ieee; 
use ieee.std_logic_1164.all;
library work;

entity testbench_adder8 is
end entity;

architecture behaviorial of testbench_adder8 is
  -- We need to redeclare adder, because it appears in testbench,
  -- but not fulladder
  component adder is
  generic (n: integer);
  port(x : in std_logic_vector(n-1 downto 0);
       y : in std_logic_vector(n-1 downto 0);
       cin : in std_logic;
       s : out std_logic_vector(n-1 downto 0);
       cout : out std_logic );
    end component;

  signal x,y,s : std_logic_vector(7 downto 0);
  signal cin, cout : std_logic;
begin 
  --  Instantiate the Unit Under Test (UUT)
  uut: adder
    generic map ( n => 8 )  -- at some point the size of the architecture must
                            -- be fixed
    port map (x => x, y => y, s => s, cin => cin,  cout => cout) ;

  -- A process is an infinite loop
   test_process :process 
   begin
     cin <= '0';
     x <= "00000000"; -- double quotes for bit vectors
     y <= "00000000"; 
     wait for 10 ns;  
     x <= "11111111"; 
     y <= "00000001"; 
     wait for 10 ns;  
     -- add more tests here
   end process;

end;

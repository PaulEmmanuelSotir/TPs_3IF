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

  signal testx, testy, tests : std_logic_vector(7 downto 0);
  signal testcin, testcout : std_logic;
begin 
  --  Instantiate the Unit Under Test (UUT)
  uut: adder
    generic map ( n => 8 )  -- at some point the size of the architecture must be fixed
    port map (x => testx, y => testy, s => tests, cin => testcin,  cout => testcout) ;

  -- A process is an infinite loop
   test_process :process 
   begin
     testcin <= '0';
     testx <= "00000000"; -- double quotes for bit vectors
     testy <= "00000000"; 
     wait for 10 ns;
     testx <= "01111111"; 
     testy <= "00000001"; 
     wait for 10 ns;  
     testx <= "11111111"; 
     testy <= "00000011"; 
     wait for 10 ns;  
     testx <= "11111111"; 
     testy <= "00000111"; 
     wait for 10 ns;  
     testx <= "11111111"; 
     testy <= "00001111"; 
     wait for 10 ns;  
     testx <= "11111111"; 
     testy <= "01001001"; 
     wait for 10 ns;  
     testcin <= '1';
     testx <= "11111111"; 
     testy <= "10000001"; 
     wait for 10 ns;  
     testx <= "11111111"; 
     testy <= "10010001"; 
     wait for 10 ns;  
     testx <= "11111111"; 
     testy <= "11110001"; 
     wait for 10 ns;  
     testx <= "11101011"; 
     testy <= "00000100"; 
     wait for 10 ns;  
     testx <= "11101111"; 
     testy <= "11010011"; 
     wait for 10 ns;  
     testx <= "00111011"; 
     testy <= "00000001"; 
     wait for 10 ns;  
     -- add more tests here
   end process;

end;

---------  An n-bit register ------------------
library ieee; 
use ieee.std_logic_1164.all;
library work;

entity testbench_nbitsregister is
end entity;

architecture behaviorial of testbench_nbitsregister is
  -- We need to redeclare adder, because it appears in testbench,
  -- but not fulladder
  component nbitsregister is
  generic (n: integer);
  port(d : in std_logic_vector(n-1 downto 0);
       q : out std_logic_vector(n-1 downto 0);
       enable : in std_logic);
    end component;

  signal testd, testq : std_logic_vector(7 downto 0);
  signal testenable : std_logic;
begin 
  --  Instantiate the Unit Under Test (UUT)
  uut: nbitsregister
    generic map ( n => 8 )  -- at some point the size of the architecture must be fixed
    port map (d => testd, q => testq, enable => testenable);

  -- A process is an infinite loop
  test_process :process 
  begin
     testenable <= '1';
     testd <= "00000000"; -- double quotes for bit vectors
     wait for 10 ns;
     testd <= "01111111";
     wait for 10 ns;  
     testd <= "11111111";
     wait for 10 ns;  
     testd <= "11111111";
     wait for 10 ns;  
     testd <= "11111111";
     wait for 10 ns;  
     testd <= "11111111"; 
     wait for 10 ns;  
     testd <= "11111111";
     wait for 10 ns;  
     testd <= "11111111"; 
     wait for 10 ns;  
     testd <= "11111111"; 
     wait for 10 ns;  
     testd <= "11101011";
     wait for 10 ns;  
     testd <= "11101111";
     wait for 10 ns;
     testd <= "00111011";
     wait for 10 ns;
   end process;

end;

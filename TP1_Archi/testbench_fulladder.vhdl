---------  A test bench for the full adder -----------------
library ieee; 
use ieee.std_logic_1164.all;
library work;

 -- the black box has no input and no output.
entity testbench_fulladder is
end entity;

architecture behaviorial of testbench_fulladder is
  -- We need to declare the sub-components used.
  component fulladder is
   port ( x, y, cin : in std_logic;
          cout, sum : out  std_logic );
    end component;

  -- Think of signals as wires inside the architecture.
  -- We give them a name. std_logic is the standard logic type.
  signal testx, testy, testcin, testcout, testsum: std_logic;
begin 

  --  Instantiate the Unit Under Test (UUT)
  uut: fulladder port map (
    x     => testx    , -- This => means: plugged to 
    y     =>   testy    ,
    cin   => testcin  ,
    sum   => testsum  , -- it works for inputs and outputs
    cout  => testcout 
    );      

  -- A process is an infinite loop
   test_process :process 
   begin
     testx <= '0';
     testy <= '0';
     testcin <= '0';
     wait for 1 ns;
     testx <= '0';
     testy <= '0';
     testcin <= '1';
     wait for 1 ns;
     testx <= '0';
     testy <= '1';
     testcin <= '0';
     wait for 1 ns;
     testx <= '0';
     testy <= '1';
     testcin <= '1';
     wait for 1 ns;
     testx <= '1';
     testy <= '0';
     testcin <= '0';
     wait for 1 ns;
     testx <= '1';
     testy <= '0';
     testcin <= '1';
     wait for 1 ns;
     testx <= '1';
     testy <= '1';
     testcin <= '0';
     wait for 1 ns;
     testx <= '1';
     testy <= '1';
     testcin <= '1';
     wait for 1 ns;
   end process;

end;

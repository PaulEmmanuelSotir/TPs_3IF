library ieee; 
use ieee.std_logic_1164.all;
library work;


entity clock_generator is
   port ( clk : out  std_logic );
end entity;


architecture behaviorial of clock_generator is
   constant clock_period : time := 1 ns;

   begin
   clock_process :process
   begin
     clk <= '0';
     wait for clk_period/2;  --for 0.5 ns signal is '0'.
     clk <= '1';
     wait for clk_period/2;  --for next 0.5 ns signal is '1'.
   end process;

end;

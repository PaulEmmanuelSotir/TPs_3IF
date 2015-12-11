---------  A D flip-flop ------------------
library ieee; 
use ieee.std_logic_1164.all;
library work;

entity dflipflop is
   port(d : in std_logic;
      clk : in std_logic;
      enable : in std_logic;
      q : out std_logic);
end entity;

architecture behaviorial of dflipflop is
   begin
   process(clk)
      begin
         if rising_edge(clk) then
            if enable = '1' then
               q <= d;
            end if;
         end if;
      end process;
end;


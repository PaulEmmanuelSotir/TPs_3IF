--- A good syntax for a mux
library ieee; 
use ieee.std_logic_1164.all;
library work;
entity mux4 is
   port ( sel: in std_logic_vector(1 downto 0);
          x0,x1,x2,x3 : in std_logic;
          s : out  std_logic );
end entity;

architecture arch of mux4 is
begin
  with (sel) select 
   s <=
    x0 when "00",
    x1 when "01",
    x2 when "10",
    x3 when "11",
    'U' when others;
 end architecture;


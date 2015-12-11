---------  An n-bit adder ------------------

library ieee; 
use ieee.std_logic_1164.all;
library work;

entity adder is
  generic (n: integer); -- generic means: architectural parameter
  port(x : in std_logic_vector(n-1 downto 0);
       y : in std_logic_vector(n-1 downto 0);
       cin : in std_logic;
       s : out std_logic_vector(n-1 downto 0);
       cout : out std_logic );
end entity;

architecture rtl of adder is
  component fulladder is
   port ( x, y, cin : in std_logic;
          cout, sum : out  std_logic );
    end component;
-- the vector of internal carries. Note that it is n+1 bits
  signal  c : std_logic_vector (n downto 0);
begin
    addloop: -- this is a label, mandatory on "for ... generate" loops
    for i in 0 to n-1 generate
      begin
        fulladderinstance:
          fulladder port map (
          x => x(i),
          y => y(i),
          cin => c(i),
          cout => c(i+1),
          sum => s(i)
          );
      end generate;
     cout <= c(n);
    c(0) <= cin;
end architecture;


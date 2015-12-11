---------  An n-bit register ------------------
library ieee; 
use ieee.std_logic_1164.all;
library work;

entity nbitsregister is
  generic (n: integer);
  port(d : in std_logic_vector(n-1 downto 0);
       enable : in std_logic;
       q : out std_logic_vector(n-1 downto 0));
end entity;

architecture dflipflops_arch of nbitsregister is
  -- D Flip-flop
  component dflipflop is
   port ( d, clk, enable : in std_logic;
          q : out  std_logic );
  end component;
  -- Clock generator
  component clock_generator is
   port ( clk : out std_logic );
  end component;
  signal clock : std_logic;
begin
    clock_instance: clock_generator port map ( clk => clock );

    flipfloploop: -- this is a label, mandatory on "for ... generate" loops
    for i in 0 to n-1 generate
      begin
        dflipflop_instance:
          dflipflop port map (
          d => d(i),
          clk => clock,
          q => q(i),
          enable => enable);
      end generate;
end architecture;


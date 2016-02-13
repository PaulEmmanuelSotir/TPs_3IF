

----------------------------------------------------------------------
---  An asynchronous memory
----------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.Numeric_Std.all;

entity memory256x8 is
  port (
    ck   : in  std_logic;
    we      : in  std_logic;
    address : in  std_logic_vector(7 downto 0);
    datain  : in  std_logic_vector(7 downto 0);
    dataout : out std_logic_vector(7 downto 0)
  );
end entity memory256x8;

architecture rtl of memory256x8 is
  type ram_array is array (0 to 255) of std_logic_vector(7 downto 0);
  signal ram : ram_array := (
-- on peut tester l'un des programmes qui suivent en le copiant au début de la RAM.
-- on peut tester l'un des programmes qui suivent en le copiant au début de la RAM.
    -- Voici un exemple de programme, à remplacer par les votres
    "01000100", -- not a -> a
    "00001011", -- b - a -> b
    "01001100", -- FF    -> a				-- "01111000", -- JA
    "11111111", -- FF 					-- "00000000", -- 0
    "00001011", -- b - a -> b
    "11111101", -- JR -3 IFN
    "01110100",	-- a -> 9*				--"01101100", -- *9 -> a
    "00001001", -- 9
    "10011101", -- JR -3
    "00000011", -- 03 (addr = 0x09)
    "00000100", -- 04
    "00001000", -- 08œ
  
    others => "UUUUUUUU");

begin
  dataout <= "UUUUUUUU" when address="UUUUUUUU"
             else ram(to_integer(unsigned(address))) after 0.2 ns ;

  ram_process: process(ck) is
  begin
    if rising_edge(ck) then
      if we = '1' then
        ram(to_integer(unsigned(address))) <= datain;
      end if;
    end if;
  end process ram_process;
end architecture rtl;



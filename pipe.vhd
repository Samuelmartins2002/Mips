library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity pipe is
  port(
    in1 : in std_logic_vector (7 downto 0);
    in2 : in std_logic_vector (7 downto 0);
    in3 : in std_logic_vector (7 downto 0);
    clock : in std_logic;
    reset : in std_logic;
    out1 : out std_logic_vector (7 downto 0)
  );
  
end entity;

architecture behavior of pipe is 
  signal FF_A : std_logic_vector (7 downto 0);
  signal FF_B : std_logic_vector (7 downto 0);
  signal FF_C : std_logic_vector (7 downto 0);
  signal FF_D : std_logic_vector (7 downto 0);
  signal FF_E : std_logic_vector (7 downto 0);
  signal FF_F : std_logic_vector (7 downto 0);
  
  begin
    
    process(clock, reset)
      
      begin 
        
      if(reset = '1') then
        FF_A <= (others => '0');
        FF_B <= (others => '0');
        FF_C <= (others => '0');
        FF_D <= (others => '0');
        FF_E <= (others => '0');
        FF_F <= (others => '0');
        
    elsif (clock = '1' and clock'event) then
      FF_A <= in1;
      FF_B <= in2;
      FF_C <= in3;
      FF_D <= FF_A + FF_B;
      FF_E <= FF_C;
      FF_F <= FF_D - FF_E;
      
  end if;
end process;
  out1 <= FF_F;
end behavior;
  
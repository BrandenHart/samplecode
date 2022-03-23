-- Simple ATM Banking System I designed in VHDL based on 5 generated events. The project was created on Intel Quartus and tested on an Altera FPGA board.

LIBRARY ieee;  

USE ieee.std_logic_1164.ALL;
--an ATM Printer Controller 
ENTITY state_atm IS
-------------------------------
PORT(clk,q,r,b: IN std_logic;
     t,s,e: OUT std_logic);
END state_atm;
ARCHITECTURE arc OF state_atm IS
TYPE state_type IS (idle, selftest, transmit, waiting, eject);
SIGNAL state: state_type;
BEGIN
PROCESS(clk)
BEGIN
IF (clk'EVENT and clk = '1') THEN // checks for the rising edge of the clock signal
CASE state IS
WHEN idle=>
IF q = '0' THEN
state <= idle;
t<='0'; 
s<='0';
e<='0';
ELSIF q = '1' THEN
state <= selftest; 
t<='0'; 
s<='1';
e<='0';
END IF;
WHEN selftest=> 
IF q = '0' THEN
state <= eject;
t<='0';
s<='0';
e<='1';
ELSIF q = '1' AND r = '0' THEN // loops back to itself because the r variable is not active yet
state <= selftest;
t<='0';
s<='1';
e<='0';
ELSIF q = '1' AND r = '1' THEN
state<= transmit;
t<='1';
s<='0';
e<='0';
END IF;
WHEN transmit=>
IF q = '0' THEN
state <= eject;
t<='0';
s<='0';
e<='1';
ELSIF q = '1' AND r = '0' THEN 
state<= selftest; // reverts to the previous state
t<='0';
s<='1';
e<= '0';
ELSIF q ='1' AND r = '1' THEN
IF b = '0' THEN
state<= transmit;
t<='1';
s<='0';
e<='0';
ELSE
state<= waiting;
t<='0';
s<='0';
END IF;
END IF;
WHEN waiting=>
IF q = '0' THEN
state <= eject;
t<='0';
s<='0';
e<='1';
ELSIF q = '1' AND r = '0' THEN
state<= selftest;
t<='0';
s<='1';
e<='1';
ELSIF q = '1' AND r = '1' THEN
IF b = '0' THEN
state<= transmit;
t<='1';
s<='0';
e<='0';
ELSE
state<= waiting;
t<='0';
s<='0';
e<='0';
END IF;
END IF;
WHEN eject=> 
if q = '0' then 
state <= eject;
t <= '0';
s <= '0';
e <= '1';
elsif q = '1' then 
state <= idle; // cycles back to the first state
t<='0';
s<='0';
e<= '0';
end if;


WHEN OTHERS =>
state <= idle;
t<='0';
s<='0';
e<='0';
END CASE;
END IF;
END PROCESS;
END arc;

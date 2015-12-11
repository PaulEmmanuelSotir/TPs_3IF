.PHONY: simulate_fulladder simulate_adder simulate_clock simulate_nbitsregister clean

testbench_fulladder: fulladder.o testbench_fulladder.o
	ghdl -e testbench_fulladder
testbench_fulladder.o: testbench_fulladder.vhdl fulladder.o
	ghdl -a testbench_fulladder.vhdl
fulladder.o: fulladder.vhdl
	ghdl -a fulladder.vhdl
simulate_fulladder: testbench_fulladder
	./testbench_fulladder --stop-time=20ns --vcd=testbench_fulladder.vcd
	gtkwave testbench_fulladder.vcd


testbench_adder8: adder.o testbench_adder.o fulladder.o
	ghdl -e testbench_adder8
testbench_adder.o: testbench_adder.vhdl adder.o 
	ghdl -a testbench_adder.vhdl
adder.o: adder.vhdl
	ghdl -a adder.vhdl
simulate_adder: testbench_adder8
	./testbench_adder8 --stop-time=100ns --vcd=testbench_adder8.vcd
	gtkwave testbench_adder8.vcd


clock.o: clock.vhdl
	ghdl -a clock.vhdl
clock_generator: clock.o
	ghdl -e clock_generator
simulate_clock: clock_generator
	./clock_generator --stop-time=100ns --vcd=clock_generator.vcd
	gtkwave clock_generator.vcd

nbitsregister.o: nbitsregister.vhdl
	ghdl -a nbitsregister.vhdl
dflipflop.o: dflipflop.vhdl
	ghdl -a dflipflop.vhdl
testbench_nbitsregister.o: testbench_nbitsregister.vhdl
	ghdl -a testbench_nbitsregister.vhdl
testbench_nbitsregister: testbench_nbitsregister.o nbitsregister.o clock.o dflipflop.o
	ghdl -e testbench_nbitsregister
simulate_nbitsregister: testbench_nbitsregister
	./testbench_nbitsregister --stop-time=100ns --vcd=testbench_nbitsregister.vcd
	gtkwave testbench_nbitsregister.vcd

clean:
	rm *.o
	rm *.vcd
	rm *.cf
	rm testbench_adder8 testbench_fulladder clock_generator testbench_nbitsregister

testbench.vcd: testbench.o memory256x8.o processor.o reg8bits.o
	ghdl -e testbench
	ghdl -r testbench --vcd=testbench.vcd --stop-time=50ns

%.o: %.vhdl
	ghdl -a $^

clean: 
	rm *.o testbench work-obj93.cf


default: help

help:
	@echo Useful targets:
	@echo "  small.txt medium.txt large.txt many.txt:  generate some input files "
	@echo "  question1 question2 question3: compile your programs"
	@echo "  run1 run2:  run your programs through the 'time' utility"
	@echo "  clean:  delete all generated files"

#########################
# workload generation

tiny.txt:
	./generator.cs 20 20 0 > $@

small.txt:
	./generator.cs 20 32 50 > $@

medium.txt:
	./generator.cs 20 50 50 > $@

large.txt:
	./generator.cs 20 64 50 > $@

many.txt:
	./generator.cs 1000 50 75 > $@

#########################
## program compilation

question1: question1.c
	gcc -Wall -pthread -g -o question1 question1.c 

question2: question2.c
	gcc -Wall -pthread -o question2 question2.c 

question3: question3.c
	gcc -Wall -pthread -g -o question3 question3.c 	
	
question5: question5.c
	gcc -Wall -pthread -g -o question5 question5.c 	
	
question7: question7.c
	gcc -Wall -pthread -g -o question7 question7.c 	
	
question10: question10.c
	gcc -Wall -pthread -g -o question10 question10.c 	

# add your own rules when you create new programs

#########################
## program execution

run1: question1
	time ./question1

run2: question2
	time ./question2
	
run3: question3
	time ./question3
	
run5: question5
	time ./question5
	
run7: question7
	time ./question7
	
run10: question10
	time ./question10

#########################
## utilities

clean:
	rm -f question1 question2 question3 question5 question7 tiny.txt small.txt medium.txt large.txt many.txt 


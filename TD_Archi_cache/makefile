.PHONY: clean cache_ex9 time_ex9

clean:
	rm cache_ex1
	rm cache_ex2
	rm cache_ex3
	rm cache_ex9_v1
	rm cache_ex9_v2
	rm cache_ex9_v3
	rm cache_ex9_v4
	rm cache_ex9_v5
	rm cache_ex9_v6
	
cache_ex1: TD_cache_ex1.c
	gcc TD_cache_ex1.c -std=c11 -o cache_ex1
	
cache_ex2: TD_cache_ex2.c
	gcc TD_cache_ex2.c -std=c11 -o cache_ex2
	
cache_ex3: TD_cache_ex3.c
	gcc TD_cache_ex3.c -std=c11 -o cache_ex3

cache_ex9_v1: cache_ex9_v1.c N.h
	gcc cache_ex9_v1.c -std=c11 -o cache_ex9_v1
	
cache_ex9_v2: cache_ex9_v2.c N.h
	gcc cache_ex9_v2.c -std=c11 -o cache_ex9_v2
	
cache_ex9_v3: cache_ex9_v3.c N.h
	gcc cache_ex9_v3.c -std=c11 -o cache_ex9_v3
	
cache_ex9_v4: cache_ex9_v4.c N.h
	gcc cache_ex9_v4.c -std=c11 -o cache_ex9_v4

cache_ex9_v5: cache_ex9_v5.c N.h
	gcc cache_ex9_v5.c -std=c11 -o cache_ex9_v5
	
cache_ex9_v6: cache_ex9_v6.c N.h
	gcc cache_ex9_v6.c -std=c11 -o cache_ex9_v6

cache_ex9:
	make cache_ex9_v1
	make cache_ex9_v2
	make cache_ex9_v3
	make cache_ex9_v4
	make cache_ex9_v5
	make cache_ex9_v6
	
time_ex9:
	time ./cache_ex9_v1
	@echo " "
	time ./cache_ex9_v2
	@echo " "
	time ./cache_ex9_v3
	@echo " "
	time ./cache_ex9_v4
	@echo " "
	time ./cache_ex9_v5
	@echo " "
	time ./cache_ex9_v6

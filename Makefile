all:
	gcc main.c -o main -lm

run:
	./main

clean:
	rm ./main *testdata.csv

faz:
	make clean; make; make run
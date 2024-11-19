all:
	gcc main.c -o main -lm

run:
	./main

clean:
	rm ./main *.csv

faz:
	make clean; make; make run
all: main.cpp a1task2_mkl.o a1task2_openblas.o a1task2_pthread.o a1task2_naive.o
	g++ a1task2_naive.o a1task2_pthread.o a1task2_openblas.o a1task2_mkl.cpp main.cpp -I /opt/OpenBLAS/include -I /usr/include/mkl -L /opt/OpenBLAS/lib -lopenblas -lpthread -lgfortran -o yourcode.out
	
a1task2_openblas.o: a1task2_openblas.cpp a1task2_openblas.h
	g++ -c a1task2_openblas.cpp -I /opt/OpenBLAS/include -L /opt/OpenBLAS/lib -lopenblas -lpthread -lgfortran 
		
a1task2_mkl.o: a1task2_mkl.cpp a1task2_mkl.h
	g++ -c a1task2_mkl.cpp -I /usr/include/mkl -lgfortran 
	
a1task2_pthread.o: a1task2_pthread.cpp a1task2_pthread.h a1task2_naive.o
	g++ -c a1task2_pthread.cpp -lpthread

a1task2_naive.o: a1task2_naive.cpp a1task2_naive.h 
	g++ -c a1task2_naive.cpp 
	
clean:
	rm -rf *o yourcode.out

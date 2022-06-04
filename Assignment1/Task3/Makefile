all: main.cpp libaudio.so 
	g++ -o yourcode.out -L. main.cpp -laudio -lopenblas -lpthread -lgfortran

libaudio.so: libaudio.o
	g++ -shared -o libaudio.so libaudio.o  

libaudio.o: libaudio.cpp libaudio.h
	g++ -c -fpic libaudio.cpp -I $(MKL_BLAS_PATH)/include -L $(MKL_BLAS_PATH)/lib -lopenblas -lpthread -lgfortran
	
clean:
	rm -rf *o yourcode.out
	
	
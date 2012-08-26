GPP=g++
GCC=gcc
FLAGS=  -g2 -Wall -O0  -D_DEBUG 
LIBS=  
OBJS=Debug/main.o Debug/Perceptron.o 

all: Debug Debug/ejercicio1.bin

clean:
	rm -rf ${OBJS} Debug/ejercicio1.bin

Debug/ejercicio1.bin: ${OBJS}
	${GPP} ${OBJS} ${LIBS} -o $@

Debug:
	mkdir Debug

Debug/main.o: main.cpp Perceptron.h GNUplot.h
	${GPP} ${FLAGS} -c main.cpp -o $@

Debug/Perceptron.o: Perceptron.cpp Perceptron.h GNUplot.h func.h utils.h
	${GPP} ${FLAGS} -c Perceptron.cpp -o $@


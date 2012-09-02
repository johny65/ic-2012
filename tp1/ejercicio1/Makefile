GPP=g++
GCC=gcc
FLAGS=  -g2 -Wall -O0  -D_DEBUG 
LIBS=  
OBJS=Debug/main.o Debug/Perceptron.o Debug/func.o Debug/utils.o 

all: Debug bin/ejercicio1

clean:
	rm -rf ${OBJS} Debug/ejercicio1.bin

bin/ejercicio1: ${OBJS}
	${GPP} ${OBJS} ${LIBS} -o $@

Debug:
	mkdir Debug bin

Debug/main.o: main.cpp Perceptron.h GNUplot.h
	${GPP} ${FLAGS} -c main.cpp -o $@

Debug/Perceptron.o: Perceptron.cpp Perceptron.h GNUplot.h utils.h func.h wait.h
	${GPP} ${FLAGS} -c Perceptron.cpp -o $@

Debug/func.o: func.cpp func.h
	${GPP} ${FLAGS} -c func.cpp -o $@

Debug/utils.o: utils.cpp utils.h GNUplot.h
	${GPP} ${FLAGS} -c utils.cpp -o $@


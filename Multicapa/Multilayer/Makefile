GPP=g++
GCC=gcc
FLAGS=  -g2 -Wall -O0 -larmadillo -D_DEBUG 
LIBS=  
OBJS=Debug/main.o Debug/Network.o Debug/func.o Debug/Perceptron.o Debug/utils.o 

all: Debug Debug/Multilayer

clean:
	rm -rf ${OBJS} Debug/Multilayer

Debug/Multilayer: ${OBJS}
	${GPP} ${OBJS} ${LIBS} -o $@

Debug:
	mkdir Debug

Debug/main.o: main.cpp Network.h Perceptron.h GNUplot.h utils.h
	${GPP} ${FLAGS} -c main.cpp -o $@

Debug/Network.o: Network.cpp Network.h Perceptron.h GNUplot.h utils.h func.h
	${GPP} ${FLAGS} -c Network.cpp -o $@

Debug/func.o: func.cpp
	${GPP} ${FLAGS} -c func.cpp -o $@

Debug/Perceptron.o: Perceptron.cpp Perceptron.h GNUplot.h utils.h func.h wait.h
	${GPP} ${FLAGS} -c Perceptron.cpp -o $@

Debug/utils.o: utils.cpp GNUplot.h
	${GPP} ${FLAGS} -c utils.cpp -o $@


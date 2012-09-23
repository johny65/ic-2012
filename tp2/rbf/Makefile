GPP=g++
GCC=gcc
FLAGS=  -g2 -Wall -O0 -D_DEBUG 
LIBS=  
OBJS=Debug/main.o Debug/RBFNetwork.o Debug/func.o Debug/Perceptron.o Debug/utils.o Debug/rbf.o

all: Debug bin/rbfnn

clean:
	rm -rf ${OBJS} Debug/rbfnn
	rm *.dat
	rm red.gv; rm red.png

bin/rbfnn: ${OBJS}
	${GPP} ${OBJS} ${LIBS} -o $@

Debug:
	mkdir Debug

Debug/main.o: main.cpp RBFNetwork.h Perceptron.h GNUplot.h utils.h
	${GPP} ${FLAGS} -c main.cpp -o $@

Debug/RBFNetwork.o: RBFNetwork.cpp RBFNetwork.h Perceptron.h GNUplot.h utils.h func.h rbf.h
	${GPP} ${FLAGS} -c RBFNetwork.cpp -o $@

Debug/rbf.o: rbf.cpp rbf.h func.h
	${GPP} ${FLAGS} -c $< -o $@

Debug/func.o: func.cpp func.h
	${GPP} ${FLAGS} -c func.cpp -o $@

Debug/Perceptron.o: Perceptron.cpp Perceptron.h GNUplot.h utils.h func.h wait.h
	${GPP} ${FLAGS} -c Perceptron.cpp -o $@

Debug/utils.o: utils.cpp GNUplot.h
	${GPP} ${FLAGS} -c utils.cpp -o $@

.PHONY: clean


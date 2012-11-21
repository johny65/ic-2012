GPP=g++
GCC=gcc
FLAGS= -g2 -Wall -O0  -D_DEBUG 
LIBS=  
OBJS=Debug/genetic.o Debug/main.o Debug/func.o Debug/utils.o Debug/argparser.o

all: Debug bin/GA.bin bin/grad.bin

clean:
	rm -rf ${OBJS} bin/GA.bin

Debug/grad.o: grad.cpp func.h genetic.h GNUplot.h argparser.h
	${GPP} ${FLAGS} -c $< -o $@
	
bin/grad.bin: Debug/grad.o Debug/argparser.o Debug/func.o
	${GPP} $^ -o $@

bin/GA.bin: ${OBJS}
	${GPP} ${OBJS} ${LIBS} -o $@

Debug:
	mkdir Debug

Debug/genetic.o: genetic.cpp genetic.h
	${GPP} ${FLAGS} -c $< -o $@

Debug/main.o: main.cpp genetic.h func.h
	${GPP} ${FLAGS} -c $< -o $@

Debug/func.o: func.cpp func.h
	${GPP} ${FLAGS} -c $< -o $@

Debug/utils.o: utils.cpp utils.h
	${GPP} ${FLAGS} -c $< -o $@

Debug/argparser.o: argparser.cpp argparser.h
	${GPP} ${FLAGS} -c $< -o $@

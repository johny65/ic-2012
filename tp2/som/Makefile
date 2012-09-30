GPP=g++
GCC=gcc
FLAGS=  -g2 -Wall -O0 -D_DEBUG 
LIBS= -lGL -lGLU -lglut
OBJS=Debug/main.o Debug/SOM.o Debug/func.o Debug/Neurona.o Debug/utils.o

all: Debug bin/som

clean:
	rm -rf ${OBJS} Debug/som
	rm *.dat
	rm red.gv; rm red.png

bin/som: ${OBJS}
	${GPP} ${OBJS} ${LIBS} -o $@

Debug:
	mkdir Debug

Debug/main.o: main.cpp SOM.h Neurona.h
	${GPP} ${FLAGS} -c main.cpp -o $@

Debug/SOM.o: SOM.cpp SOM.h func.h Neurona.h
	${GPP} ${FLAGS} -c $< -o $@

Debug/Neurona.o: Neurona.cpp Neurona.h func.h
	${GPP} ${FLAGS} -c $< -o $@

Debug/func.o: func.cpp func.h
	${GPP} ${FLAGS} -c func.cpp -o $@

Debug/utils.o: utils.cpp utils.h GNUplot.h
	${GPP} ${FLAGS} -c utils.cpp -o $@

.PHONY: clean

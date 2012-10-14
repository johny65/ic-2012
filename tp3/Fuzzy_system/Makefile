GPP=g++
GCC=gcc
FLAGS= -g2 -Wall -O0 -D_DEBUG 
LIBS=
OBJS=obj/main.o obj/Sistema.o obj/utils.o 

all: Debug obj Debug/fuzzy

clean:
	rm -rf ${OBJS} Debug/Fuzzy_system.bin

Debug/fuzzy: ${OBJS}
	${GPP} ${OBJS} ${LIBS} -o $@

Debug:
	mkdir Debug

obj:
	mkdir obj

obj/main.o: main.cpp Sistema.h utils.h GNUplot.h
	${GPP} ${FLAGS} -c main.cpp -o $@

obj/Sistema.o: Sistema.cpp Sistema.h utils.h GNUplot.h
	${GPP} ${FLAGS} -c Sistema.cpp -o $@

obj/utils.o: utils.cpp utils.h GNUplot.h
	${GPP} ${FLAGS} -c utils.cpp -o $@


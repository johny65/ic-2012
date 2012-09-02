#!bin/sh

mkdir particiones

#tabla 1 desv. 10%:
./generar.py -i tabla1.csv -o salida1.csv -n 1000 -d 0.1
./particionar.py -i salida1.csv -o particiones/ -p t1_10 -n 5 -e 80


#tabla 2 desv. 10%:
./generar.py -i tabla2.csv -o salida2.csv -n 5000 -d 0.1
./particionar.py -i salida2.csv -o particiones/ -p t2_10 -n 50 -e 80


#tabla 2 desv. 50%:
./generar.py -i tabla2.csv -o salida2.csv -n 5000 -d 0.5
./particionar.py -i salida2.csv -o particiones/ -p t2_50 -n 50 -e 80


#tabla 2 desv. 70%:
./generar.py -i tabla2.csv -o salida2.csv -n 5000 -d 0.7
./particionar.py -i salida2.csv -o particiones/ -p t2_70 -n 50 -e 80

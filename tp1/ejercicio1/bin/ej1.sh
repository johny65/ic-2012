#!bin/sh

mkdir or-xor
./generar.py -i tabla_OR.csv -o or-xor/datos_or.csv -n 500 -d 0.05
./particionar.py -i or-xor/datos_or.csv -o or-xor/ -p or -n 1 -e 80

./generar.py -i tabla_XOR.csv -o or-xor/datos_xor.csv -n 500 -d 0.05
./particionar.py -i or-xor/datos_xor.csv -o or-xor/ -p xor -n 1 -e 80

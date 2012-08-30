# -*- coding: utf-8 -*- #para que se puedan escribir acentos :p

from math import *
import random
import sys
import argparse

def generar_nuevo_punto(punto, var, deseada):
	"""
	Genera aleatoriamente un nuevo punto a partir de uno de origen con una
	desviación dada por 'var'. El nuevo punto queda dentro de una esfera
	centrada en 'punto' con radio no mayor a 'var'. Además inserta como
	último elemento la salida deseada para la entrada representada por el
	punto.
	"""
	r = random.randrange(0, var, int=float) #radio
	tita1 = random.randrange(0, 2*pi, int=float) #ángulo para x-y
	tita2 = random.randrange(0, 2*pi, int=float) #ángulo para z
	xy = r*cos(tita1)
	x = punto[0] + xy*cos(tita2)
	y = punto[1] + xy*sin(tita2)
	z = punto[2] + r*sin(tita1)
	nuevo_punto = [x, y, z]
	nuevo_punto.append(deseada)
	return nuevo_punto


def generar_datos(nombre, var, n, salida):
	"""
	Genera una serie de datos ('n' patrones) a partir de los valores de una
	tabla dada en el archivo 'nombre' en formato CSV, con una desviación
	aleatoria dada por 'var'. Los patrones generados se guardan en formato CSV
	en el archivo 'salida'.
	"""
	
	#leer archivo de entrada:
	tabla = []
	f = open(str(nombre), "r") #str(nombre) no debería hacer falta
	for line in f.readlines():
		x = [float(s) for s in line.split(',')] #el maxsplit no hace falta
		tabla.append(x) #tabla contiene las salidas deseadas también
	f.close()

	#generar datos:
	datos = []
	cant_por_clase = n/len(tabla) - 1
	for i in range(len(tabla)):
		punto = tabla[i][:-1] #cada entrada en la tabla es un punto 3D (sacando la salida deseada)
		for k in range(cant_por_clase):
			deseada = tabla[i][-1]
			nuevo_punto = generar_nuevo_punto(punto, var, deseada)
			datos.append(nuevo_punto)
		datos.append(tabla[i]) #agrego la entrada sin variaciones
	
	#completar hasta n, eligiendo aleatoriamente la clase:
	for i in range(n - len(datos)):
		entrada = random.choice(tabla)
		punto = entrada[:-1] #no tomo la salida deseada
		deseada = entrada[-1]
		nuevo_punto = generar_nuevo_punto(punto, var, deseada)
		datos.append(nuevo_punto)

	#guardar archivo de salida:
	f = open(salida, 'w')
	for d in datos:
		for j in range(len(d)-1):
			f.write(str(d[j]) + ", ")
		f.write(str(d[-1]) + "\n")
		#para que el archivo se pueda graficar en gnuplot, comentar la línea de
		#arriba y en vez de ',' poner ' ' en la anterior.
	f.close()


def main():
	"""
	Función principal. Revisa si hay parámetros pasados.
	"""

	#agregar las opciones que se pueden pasar por parámetro, con sus valores
	#por defecto si no se pasan:
	parser = argparse.ArgumentParser()
	parser.add_argument("-i", "--input", help="Archivo de entrada",
						default="entrada.csv", dest="entrada")
	
	parser.add_argument("-o", "--output", help="Archivo de salida",
						default="salida.csv", dest="salida")

	parser.add_argument("-d", "--desviacion", help="Desviación",
						default=0.1, type=float, dest="var")

	parser.add_argument("-n", "--cantidad", help="Cantidad de datos a generar",
						default=1000, type=int, dest="cant")
	
	p = parser.parse_args()

	generar_datos(p.entrada, p.var, p.cant, p.salida)


if __name__ == "__main__":
	main()

# -*- coding: utf-8 -*- #para que se puedan escribir acentos :p

import random
import argparse

def particionar(archivo, destino, prefijo, porc_entr, cant):
	"""
	Crea particiones de entrenamiento-prueba a partir de un archivo de entrada,
	con relación dada por 'porc_entr' (porcentaje para entrenamiento, el resto
	queda para prueba).
	Crea 'cant' cantidad de particiones, y son guardadas en distintos archivos
	dentro de la carpeta 'destino' con el siguiente formato:

	'prefijo'{i}_e.csv para el conjunto de entrenamiento
	'prefijo'{i}_p.csv para el conjunto de prueba

	donde {i} es el número de partición y 'prefijo' se puede configurar.
	"""
	
	#leer archivo de entrada:
	datos = []
	f = open(archivo, 'r')
	for line in f.readlines():
		datos.append(line)
	f.close()

	#'datos' contiene las líneas del archivo, desordenarlas directamente:
	n = len(datos)
	for i in range(cant):
		random.shuffle(datos)
		#separar:
		entrenamiento = datos[0:int(n*porc_entr)]
		prueba = datos[len(entrenamiento):]
		#guardar:
		e = open("{}/{}{}_e.csv".format(destino, prefijo, i+1), 'w')
		e.writelines(entrenamiento)
		e.close()
		p = open("{}/{}{}_p.csv".format(destino, prefijo, i+1), 'w')
		p.writelines(prueba)
		p.close()


def main():
	"""
	Función principal. Revisa si hay parámetros pasados.
	"""

	#agregar las opciones que se pueden pasar por parámetro, con sus valores
	#por defecto si no se pasan:
	parser = argparse.ArgumentParser()
	parser.add_argument("-i", "--input", help="Archivo de entrada",
						default="entrada.csv", dest="entrada")
	
	parser.add_argument("-o", "--output", help="Carpeta de salida (debe existir)",
						default=".", dest="salida")

	parser.add_argument("-p", "--prefijo", help="Prefijo para los archivos de salida",
						default="particion", dest="pre")
	
	parser.add_argument("-e", "--porcentaje", help="Porcentaje para entrenamiento",
						default=80, type=int, dest="porc")

	parser.add_argument("-n", "--cantidad", help="Cantidad de particiones a generar",
						default=2, type=int, dest="cant")
	
	p = parser.parse_args()

	particionar(p.entrada, p.salida, p.pre, p.porc/100.0, p.cant)


if __name__ == "__main__":
	main()

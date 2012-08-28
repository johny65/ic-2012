import math
import random

def generar_datos(tabla, var, n):

	datos = []
	cant_por_tabla = n/len(tabla)
	for i in tabla:
		for k in range(cant_por_tabla):
			fila = []
			for j in i:
				a = j*(1-var); b = j*(1+var)
#				if a < b:
#					d = random.randrange(a, b, int=float)
#				else:
#					d = random.randrange(b, a, int=float)
				d = random.gauss(j, var)
				fila.append(d)
			datos.append(fila)
	
	#completar n!
	print datos
	f = open("salida.txt", 'w')
	for i in datos:
		for j in i:
			f.write(str(j) + " ")
		f.write('\n')
	f.close()


t = [[1, -1], [-1, 1]]
generar_datos(t, 0.05, 500)


		


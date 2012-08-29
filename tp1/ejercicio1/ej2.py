import math
import random

def generar_datos(nombre,var, n):
	tabla=[]	
	f = open(str(nombre), "r")
	for line in f.readlines():
    		x=[float(s) for s in line.split(',',700)] #lo ideal seria poner la len(linea) pero no me lo toma
    		x=x[0:len(x)-1]
    		tabla.append(x)
	f.close()
	
	datos = []
	cant_por_tabla = n/len(tabla)
	for i in tabla:
		for k in range(cant_por_tabla):
			fila = []
			for j in i:
				r = random.randrange(0, var, int=float)
				tita=random.randrange(0,2*math.pi, int=float)
				d=random.randrange(-1,1, int=float)
				if d > 0:
					a=r*math.cos(tita)-j
				else:
					a=r*math.sin(tita)-j
				fila.append(a)
			datos.append(fila)
	
	#completar n! hay que ver el resto de n/len(tabla)
	print datos
	f = open("salida.txt", 'w')
	for i in datos:
		for j in i:
			f.write(str(j) + " ")
		f.write('\n')
	f.close()


generar_datos("entradas.txt", 0.05, 500)

#Esta funcion genera los datos aletorios con un desvio dado, faltaria agregar a "salidas.txt" los datos 
#de entradas.txt, y luego si hacer la funcion de las particiones
		


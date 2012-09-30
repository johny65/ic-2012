# -*- coding: utf-8 -*-

import random
import math
import sys

def generar_circulo(n):
    """
    Genera n puntos aleatorios contenidos en un círculo de radio 1 centrado en
    el origen.
    """
    contador = 0
    patrones = []
    while contador < n:
        x = random.randrange(-1, 1, int=float)
        y = random.randrange(-1, 1, int=float)
        if (math.sqrt(x**2.0 + y**2.0)) < 1.0:
            patrones.append([x, y, 0])
            contador += 1
    return patrones

def generar_rectangulo(n):
    """
    Genera n puntos aleatorios contenidos en un rectángulo de vértices
    (1,1), (-1,1), (-1,-1) y (1,-1) (eso es un cuadrado).
    """
    patrones = []
    for i in range(n):
        x = random.randrange(-1, 1, int=float)
        y = random.randrange(-1, 1, int=float)
        patrones.append([x, y, 0])
    return patrones

def generar_T(n):
    """
    Genera n puntos aleatorios contenidos en una T.
    """
    contador = 0
    patrones = []
    while contador < n:
        x = random.randrange(-1, 1, int=float)
        y = random.randrange(-1, 1, int=float)
        if y >= 0.5:
            patrones.append([x, y, 0])
            contador += 1
        elif x >= -0.25 and x <= 0.25:
            patrones.append([x, y, 0])
            contador += 1
    return patrones

def guardar(datos, salida):
	f = open(salida, 'w')
	for d in datos:
		for j in range(len(d)-1):
			f.write(str(d[j]) + ", ")
		f.write(str(d[-1]) + "\n")
		#para que el archivo se pueda graficar en gnuplot, comentar la línea de
		#arriba y en vez de ',' poner ' ' en la anterior.
	f.close()


#------------------------------

if __name__ == "__main__":
    if (sys.argv[1:]):
        N = int(sys.argv[1])
        print "Generando %d datos..." % (N)
        p = generar_circulo(N)
        guardar(p, "circulo.csv")
        p = generar_rectangulo(N)
        guardar(p, "rectangulo.csv")
        p = generar_T(N)
        guardar(p, "t.csv")


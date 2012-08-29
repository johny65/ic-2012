def funcion(fila): #funcion logica que agrega la salida esperada en el archivo salida.txt
	fila_n=[]	
	for i in fila:
		if i>0: 
			fila_n.append(1)
		else:
			fila_n.append(0);
	d=(not(fila_n[0]) and (fila_n[2])) or (fila_n[0] and fila_n[1] and not(fila_n[2])) or (not(fila_n[0]) and not(fila_n[1]))
	if d: return 1
	else: return -1
	
t=[-1.5, 1, -1]
j=funcion(t)
print j


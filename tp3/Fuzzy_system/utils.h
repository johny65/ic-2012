#ifndef UTILS_H
#define UTILS_H
	struct triangulo{
		double left;
		double center;
		double right;
		void calcular_centro();
		bool pertenece(double);
	};
	
	struct trapezoide:triangulo{
		double b,c; //b y c puntos donde el grado de membresia corta al triangulo
		//determinar_bc(double degree); //degree:grado de membresia, A: triangulo de pertenencia
	};
	
	
#endif

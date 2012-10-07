#ifndef UTILS_H
#define UTILS_H
struct trapezoide{
	double b,c; // b y c cortes que produce el grado de activacion del conjunto difuso
};	
struct triangulo{
		double left;
		double center;
		double right;
		trapezoide A;
		void calcular_bc(double degree);
		void calcular_centro();
		bool pertenece(double);
	};
	
	
	
	
#endif

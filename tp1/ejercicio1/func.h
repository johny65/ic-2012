#ifndef FUNC_H
#define FUNC_H
#include <vector>
using namespace std;

vector<double> init_weight(int nd){
	double w;
	vector<double> pesos;
	srand(time(NULL));
	for(int i=0;i<nd+1;i++){ //hasta nd+1 xq el sesgo tambien tiene peso aletorio
		w=(0+rand()%100)/100.0;
		pesos.push_back(w);
	}
	return pesos;
}

vector<double> sum(vector<double> y,vector<double> x){
	vector<double> r;
	for(int i=0;i<y.size()-1;i++){
		r.push_back(y[i]+x[i]);
	}
	r.push_back(y.back());
	return r;
}

vector<double> dif(vector<double> y,vector<double> x){
	vector<double> r;
	for(int i=0;i<y.size()-1;i++){
		r.push_back(y[i]-x[i]);
	}
	r.push_back(y.back());
	return r;
}

vector<double> prod_escalar(vector<double> x,double nu){
	vector<double> y;
	for(int i=0;i<x.size();i++){
		y.push_back(nu*x[i]);
	}
	return y;
}


double dot(vector<double> &x, vector<double> &y){
	if(x.size()!=y.size()){
		cout<<"vectores de diferente dimension"<<endl;
		return 0;
	}
	double p=0;
	//vector de pesos sin sesgo
	for(int i=0;i<x.size();i++){
		p+=x[i]*y[i];
	}
	return p;
}


double signo(int valor){
	//segun la funcion de activacion:
	if(valor>=0) return 1;
	else return -1;
	
}
vector<double> recalcular_pesos(vector<double> pv,double tasa,double s,double se,vector<double> datos){
	//np=pv+2*tasa*[se-s]*datos
	vector<double> np;
	np=sum(pv,prod_escalar(datos,2*tasa*(se-s)));
	return np;
}

#endif

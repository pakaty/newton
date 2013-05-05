#include<iostream>
#include<functional>
#include<unistd.h>
#include<fstream>
#include<vector>
#include<cmath>
#include "gppp/gnuplot.hpp"


using std::cout;
using std::endl;
using std::function;
using std::vector;

function<double(double)> f = [](double x){
	return exp(x) - 2;
};
double d_dx(function<double(double)> f,double x)
{
	const double h = 1e-10;
	return (f(x+h)-f(x))/h;
}

double root(double eps,double x0, double l, double r,function<double(double)> f)
{
	vector<double> xs;
	double x1 = x0;// = x0-f(x0)/d_dx(f,x0);
	do
	{
		x0=x1;
		xs.push_back(x0);
		x1 = x0-f(x0)/d_dx(f,x0);
	}
	while(fabs(x1-x0)>eps && x1 <= r && x1 >= l);
	ofstream of("plot.gp"), dof("data.dat");
	for (double x : xs){
		gp_setVline(x, -10,10, of);
	}
	gp_setVline(x1, -10,10, of, 0x0000FF);
	of << "set term gif" << endl;
	of << "set output 'pic.gif'" << endl;
	my_f_gnuplot(f, l, r , 100, dof, of);
	dof.close();
	of.close();
	return x1;
};

int main()
{
	cout << root(0.000001, 1 , -1, 4 , f)<<endl;
	sleep(2);
	system("gnuplot -p 'plot.gp'");
}






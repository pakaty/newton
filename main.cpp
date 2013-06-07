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
function<double(double)> f1 = [](double x){
	return sin(x);
};
function<double(double)> f2 = [](double x){
	return x*x*x*x;
};
double d_dx(function<double(double)> f,double x)
{
	const double h = 1e-10;
	return (f(x+h)-f(x))/h;
}

double root(double eps,double x0, double l, double r,function<double(double)> f, const char *picname)
{
	vector<double> xs;
	int i = 0;
	double x1 = x0;// = x0-f(x0)/d_dx(f,x0);
	do
	{
		i++;
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
	of << "set output '" << picname << "'"<< endl;
	cout << "Iterations: " << i << endl;
	my_f_gnuplot(f, l, r , 100, dof, of);
	dof.close();
	of.close();
	return x1;
};

int main()
{
	char picname[20];
	int i = 0;
	double l = -5,r = 5;
	cout << "exp" << endl;
	for (double x0 = l; x0 <= r; x0 += (r-l)/5){
		sprintf(picname, "exp%d.gif",i++);
		cout << "xo: " << x0 << " " << root(0.000001, x0 , l,r , f,picname )<<endl;
		sleep(1);
		system("gnuplot -p 'plot.gp'");
	}
	l = -M_PI_2+0.2;r =M_PI_2-0.2;
	cout << "sin" << endl;
	for (double x0 = l; x0 <= r; x0 += (r-l)/5){
		sprintf(picname, "sin%d.gif",i++);
		cout << "xo: " << x0 << " " << root(0.000001, x0 , l,r , f1,picname )<<endl;
		sleep(1);
		system("gnuplot -p 'plot.gp'");
	}
	l = -1;r = 1;
	cout << "x4" << endl;
	for (double x0 = l; x0 <= r; x0 += (r-l)/5){
		sprintf(picname, "x4%d.gif",i++);
		cout << "xo: " << x0 << " " << root(0.000001, x0 , l,r , f2,picname )<<endl;
		sleep(1);
		system("gnuplot -p 'plot.gp'");
	}
}






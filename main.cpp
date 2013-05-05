#include<iostream>
#include<functional>
#include<cmath>

using std::cout;
using std::endl;
using std::function;

function<double(double)> f = [](double x){
return exp(x)-2;
};
double d_dx(function<double(double)> f,double x)
{
const double h = 1e-10;
return (f(x+h)-f(x))/h;
}

double root(double eps,double x0,function<double(double)> f)
{
 double x1 = x0-f(x0)/d_dx(f,x0);
 do
 {
  x0=x1;
  x1 = x0-f(x0)/d_dx(f,x0);
 }
 while(fabs(x1-x0)>eps);
 
 return x1;
};

int main()
{
	cout << root(0.000001,1,f)<<endl;
}






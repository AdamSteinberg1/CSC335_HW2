//Program to solve problem 2c and 2d in section 2.4

#include <functional>
#include <cmath>
#include <iostream>
using namespace std;

const int MAX_ITERATIONS = 100;

//if two numbers differ by less than TOLERANCE, they are considered equal.
const double TOLERANCE =   0.00001; //problem stated tolerance = 10^-5

//given a function f, it's derivative fPrime, and an initial approximation p0, return f's root
auto newtonsMethod(function<double(double)> f, function<double(double)> fPrime, double p0)
{
  for (int i = 1; i <= MAX_ITERATIONS; i++)
  {
    double p = p0 - f(p0)/fPrime(p0);
    if(fabs(p - p0) < TOLERANCE)
    {
      return make_pair(p, i);
    }
    p0 = p;
  }
  return make_pair(p0, MAX_ITERATIONS);
}

int main()
{
  cout.precision(16);

  //part c
  cout << "Part c:" << endl;

  function<double(double)> f = [&](double x){
    return sin(3*x) + 3*exp(-2*x)*sin(x) - 3*exp(-x)*sin(2*x) - exp(-3*x);
  };

  function<double(double)> fPrime = [&](double x){
    return 3*cos(3*x) + 3*exp(-2*x)*(-2*sin(x) + cos(x)) + 3*exp(-x)*(sin(2*x) - 2*cos(2*x)) - 3*exp(-3*x);
  };

  auto result = newtonsMethod(f, fPrime, 3.5);
  cout << "\tx = " << result.first << " after " << result.second << " iterations" << endl;

  //part d
  cout << "Part d:" << endl;

  function<double(double)> g = [&](double x){
    return exp(3*x) - 27*pow(x, 6) + 27*pow(x, 4)*exp(x) - 9*pow(x,2)*exp(2*x);
  };

  function<double(double)> gPrime = [&](double x){
    return 3*exp(3*x) - 162*pow(x,5) + 27*pow(x,3)*exp(x)*(4+x) - 18*x*exp(2*x)*(1+x);
  };

  result = newtonsMethod(g, gPrime, 4);
  cout << "\tx = " << result.first << " after " << result.second << " iterations" << endl;

  return 0;
}

//Program to solve problem 4c and 4d in section 2.4

#include <functional>
#include <cmath>
#include <iostream>
using namespace std;

const int MAX_ITERATIONS = 100;

//if two numbers differ by less than TOLERANCE, they are considered equal.
const double TOLERANCE =   0.00001; //problem stated tolerance = 10^-5

//given a function f, its derivative fPrime, its second derivative fPrimePrime, and an initial approximation p0, return f's root
auto modifiedNewtonsMethod(function<double(double)> f, function<double(double)> fPrime, function<double(double)> fPrimePrime, double p0)
{
  for (int i = 1; i <= MAX_ITERATIONS; i++)
  {
    double p = p0 - (f(p0)*fPrime(p0)) / (pow(fPrime(p0),2) - f(p0)*fPrimePrime(p0));
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

  //f's first derivative
  function<double(double)> fPrime = [&](double x){
    return 3*cos(3*x) + 3*exp(-2*x)*(-2*sin(x) + cos(x)) + 3*exp(-x)*(sin(2*x) - 2*cos(2*x)) - 3*exp(-3*x);
  };

  //f's second derivative
  function<double(double)> fPrimePrime = [&](double x){
    return -9*sin(3*x) + 3*(3*exp(-2*x)*sin(x) - 4*exp(-2*x)*cos(x)) + 3*(3*exp(-x)*sin(2*x) + 4*exp(-x)*cos(2*x)) + 9*exp(-3*x);
  };

  auto result = modifiedNewtonsMethod(f, fPrime, fPrimePrime, 3.5);
  cout << "\tx = " << result.first << " after " << result.second << " iterations" << endl;

  //part d
  cout << "Part d:" << endl;

  function<double(double)> g = [&](double x){
    return exp(3*x) - 27*pow(x, 6) + 27*pow(x, 4)*exp(x) - 9*pow(x,2)*exp(2*x);
  };

  //g's first derivative
  function<double(double)> gPrime = [&](double x){
    return 3*exp(3*x) - 162*pow(x,5) + 27*pow(x,3)*exp(x)*(4+x) - 18*x*exp(2*x)*(1+x);
  };

  //g's second derivative
  function<double(double)> gPrimePrime = [&](double x){
    return 9*exp(3*x) - 810*pow(x,4) + 27*exp(x)*(pow(x,4) + 8*pow(x,3) + 12*pow(x,2)) - 18*exp(2*x)*(2*pow(x,2) + 4*x + 1);
  };

  result = modifiedNewtonsMethod(g, gPrime, gPrimePrime, 4);
  cout << "\tx = " << result.first << " after " << result.second << " iterations" << endl;

  return 0;
}

//Program to solve problem 16 in section 2.1
//Uses bisection algorithm

#include <functional>
#include <cmath>
#include <iostream>
using namespace std;

const int MAX_ITERATIONS = 100;

//if two numbers differ by less than TOLERANCE, they are considered equal.
const double TOLERANCE =   0.0000000000000005;
const double G = 32.17;

//the function we're going to find the root of
double f(double w)
{
  return -1.7 - G / (2*w*w) * ((exp(w)-exp(-w))/2 - sin(w));
}


//given a function f on the interval [a,b], return it's root
double bisection(function<double(double)> f, double a, double b)
{
   double p;
   double f_a = f(a);
   for (int i = 1; i <= MAX_ITERATIONS; i++)
   {
     p = a + (b-a)/2.0;
     double f_p = f(p);
     if(f_p == 0 || (b-a)/2.0 < TOLERANCE)
     {
       return p;
     }
     else if (signbit(f_p) == signbit(f_a))
     {
       a = p;
       f_a = f_p;
     }
     else
     {
       b = p;
     }
   }
   return p;
}

int main()
{
  cout.precision(16);

  //the depth must be between 0 and 1
  double w = bisection(f, -10, 0);
  cout << "w = " << w << endl;

  return 0;
}

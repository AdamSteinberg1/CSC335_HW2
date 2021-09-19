//Program to solve problem 28 in section 2.3

#include <functional>
#include <cmath>
#include <iostream>
using namespace std;

const int MAX_ITERATIONS = 100;

//if two numbers differ by less than TOLERANCE, they are considered equal.
const double TOLERANCE =   0.0000000000000005;

//given a function f, it's derivative fPrime, and an initial approximation p0, return f's root
double newtonsMethod(function<double(double)> f, function<double(double)> fPrime, double p0)
{
  for (int i = 1; i <= MAX_ITERATIONS; i++)
  {
    double p = p0 - f(p0)/fPrime(p0);
    if(fabs(p - p0) < TOLERANCE)
    {
      return p;
    }
    p0 = p;
  }
  return p0;
}

//given a function f and two inital approximations, p0 and p1, return f's root
double secantMethod(function<double(double)> f, double p0, double p1)
{
  double q0 = f(p0);
  double q1 = f(p1);
  for (int i = 2; i <= MAX_ITERATIONS; i++)
  {
    double p = p1 - q1 * (p1 - p0) / (q1 - q0);
    if(fabs(p - p1) < TOLERANCE)
    {
      return p;
    }
    p0 = p1;
    q0 = q1;
    p1 = p;
    q1 = f(p);
  }
  return p1;
}

int main()
{
  cout.precision(16);

  //part b
  const double A = M_E/3; //the amount of drugs to be injected
                          //calulated by hand in part a

  //the function we're going to find the root of for part b
  function<double(double)> f = [&](double t){
    return A*t*exp(-t/3) - 0.25;
  };

  //f's derivative
  function<double(double)> fPrime = [&](double t){
    return A*exp(-t/3)*(1-t/3);
  };

  double t2 = newtonsMethod(f, fPrime, 4); //time of the second injection
                                           //this is needed for part c, arbitruarily picked the Newton's method result
  cout << "Time of second injection:" << endl;
  cout << "\tNewton's Method:\tt = " << t2 << endl;
  cout << "\tSecant Method:\t\tt = " << secantMethod(f, 4, 5) << endl;


  //part c

  //the function we're going to find the root of for part c
  function<double(double)> g = [&](double t){
    return -0.25 + A*t*exp(-t/3) + 0.75*A*(t-t2)*exp(-(t-t2)/3);
  };

  //g's derivative
  function<double(double)> gPrime = [&](double t){
    return A*exp(-t/3)*(1-t/3) + 0.75*A*exp(-(t-t2)/3)*(1-(t-t2)/3);
  };

  cout << "Time of third injection:" << endl;
  cout << "\tNewton's Method:\tt = " << newtonsMethod(g, gPrime, 15) << endl;
  cout << "\tSecant Method:\t\tt = " << secantMethod(g, 15, 20) << endl;


  return 0;
}

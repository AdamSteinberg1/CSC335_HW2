#include <functional>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_ITERATIONS = 100;

//the actual root of f provided by Dr. Pounds
const double ACTUAL_ROOT = 1.839286755214161;

//if two numbers differ by less than TOLERANCE, they are considered equal.
const double TOLERANCE =   0.0000000000000005;

//the function we're going to find the root of
double f(double x)
{
  return x*x*x - x*x - x - 1.0;
}

//f's derivative
double fPrime(double x)
{
  return 3.0*x*x - 2.0*x - 1.0;
}

//g is a function that has a fixed point at f's root
double g(double x)
{
  return cbrt(x*x + x + 1.0);
}

//prints the first three lines of a table
void printHeader(string title)
{
  cout << endl << endl;
  cout << title << endl;
  cout << "┏━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
  cout << endl;
  cout << "┃ ";
  cout << setw(9) << "Iteration" << " ┃ ";
  cout << setw(25) << "x" << " ┃ ";
  cout << setw(25) << "f(x)" << " ┃ ";
  cout << setw(25) << "Absolute Error" << " ┃ ";
  cout << setw(25) << "Relative Error" << " ┃ " << endl;
  cout << "┣━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━━━━━━━━┫";
  cout << endl;
}

//prints 1 row of the table
void printRow(int iteration, double x)
{
    double f_x = f(x);
    double absError = fabs(x-ACTUAL_ROOT);
    double relativeError = absError/ACTUAL_ROOT;

    cout << "┃ ";
    cout << setw(9) << iteration << " ┃ ";
    cout << setw(25) << x << " ┃ ";
    cout << setw(25) << f_x << " ┃ ";
    cout << setw(25) << absError << " ┃ ";
    cout << setw(25) << relativeError << " ┃ " << endl;
}

//given a function f on the interval [a,b], return it's root
double bisection(function<double(double)> f, double a, double b)
{
   printHeader("Bisection");
   double p;
   double f_a = f(a);
   for (int i = 1; i <= MAX_ITERATIONS; i++)
   {
     p = a + (b-a)/2.0;
     double f_p = f(p);
     printRow(i, p);
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

//given a function f, it's derivative fPrime, and an initial approximation p0, return f's root
double newtonsMethod(function<double(double)> f, function<double(double)> fPrime, double p0)
{
  printHeader("Newton's Method");
  printRow(0, p0);
  for (int i = 1; i <= MAX_ITERATIONS; i++)
  {
    double p = p0 - f(p0)/fPrime(p0);
    printRow(i, p);
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
  printHeader("Secant Method");
  double q0 = f(p0);
  double q1 = f(p1);
  printRow(0, p0);
  printRow(1, p1);
  for (int i = 2; i <= MAX_ITERATIONS; i++)
  {
    double p = p1 - q1 * (p1 - p0) / (q1 - q0);
    printRow(i, p);
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

//given a function g and an inital approximation p0, return g's fixed point
double fixedPointMethod(function<double(double)> g, double p0)
{
  printHeader("Fixed Point Method");
  printRow(0, p0);
  for (int i =1; i <= MAX_ITERATIONS; i++)
  {
    double p = g(p0);
    printRow(i, p);
    if(fabs(p - p0) < TOLERANCE)
    {
      return p;
    }
    p0 = p;
  }
  return p0;
}

//given a function g and an inital approximation p0, return g's fixed point
double steffensensMethod(function<double(double)> g, double p0)
{
  printHeader("Steffensen's Method");
  printRow(0, p0);
  for (int i = 1; i <= MAX_ITERATIONS; i++)
  {
    double p1 = g(p0);
    double p2 = g(p1);
    double p = p0 - (p1-p0)*(p1-p0)/(p2 - 2*p1 + p0);
    printRow(i, p);
    if(fabs(p - p0) < TOLERANCE)
    {
      return p;
    }
    p0 = p;
  }
  return p0;
}

int main()
{
  //print the values with the same precision as the given root
  cout.precision(16);

  //arbituarily pick [0.0, 2.0] as range to search in
  bisection(f, 0.0, 2.0);

  //arbitruarily pick 1.5 as initial approximation
  newtonsMethod(f, fPrime, 1.5);

  //arbitruarily pick 1.5 and 2.0 as initial approximations
  secantMethod(f, 1.5, 2.0);

  //arbitruarily pick 1.5 as initial approximation
  fixedPointMethod(g, 1.5);

  //arbitruarily pick 1.5 as initial approximation
  steffensensMethod(g, 1.5);

  return 0;
}

//Program to solve problem 29 in section 2.3

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

  //part a
  cout << "Part a" << endl;

  double l = 89.0;
  double h = 49.0;
  double D = 55.0;
  double beta_d = 11.5; //beta in degrees
  double beta_r = beta_d * M_PI / 180.0; //beta in radians

  double A = l * sin(beta_r);
  double B = l * cos(beta_r);
  double C = (h+0.5*D)*sin(beta_r) - 0.5*D*tan(beta_r);
  double E = (h+0.5*D)*cos(beta_r) - 0.5*D;

  function<double(double)> f = [&](double alpha){
    return A*sin(alpha)*cos(alpha) + B*pow(sin(alpha), 2) - C*cos(alpha) - E*sin(alpha);
  };

  function<double(double)> fPrime = [&](double alpha){
    return A*(pow(cos(alpha), 2) - pow(sin(alpha), 2)) + B*2*sin(alpha)*cos(alpha) + C*sin(alpha) - E*cos(alpha);
  };

  double alpha1 =  newtonsMethod(f, fPrime, 0.5);
  cout << "Newton's Method:\talpha = " << alpha1 * 180/M_PI << " degrees" << endl;
  alpha1 = secantMethod(f, 0.5, 1.0);
  cout << "Secant Method:\t\talpha = " << alpha1 * 180/M_PI << " degrees" << endl;

  //part b
  cout << endl << "Part b" << endl;

  D = 30.0;
  //recalculate anything that depends on D
  C = (h+0.5*D)*sin(beta_r) - 0.5*D*tan(beta_r);
  E = (h+0.5*D)*cos(beta_r) - 0.5*D;

  double alpha2 =  newtonsMethod(f, fPrime, 0.5);
  cout << "Newton's Method:\talpha = " << alpha2 * 180/M_PI << " degrees" << endl;
  alpha2 = secantMethod(f, 0.5, 1.0);
  cout << "Secant Method:\t\talpha = " << alpha2 * 180/M_PI << " degrees" << endl;

  return 0;
}

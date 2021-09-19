//Program to solve problem 6 in section 2.2
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

const int MAX_ITERATIONS = 25;


//computes the next term of sequence a, given current term x
double a(double x)
{
  return x * pow((1.0 + (7.0-pow(x, 5.0))/(x*x)), 3.0);
}

//computes the next term of sequence b, given current term x
double b(double x)
{
  return x - (pow(x, 5.0) - 7.0)/pow(x, 2.0);
}

//computes the next term of sequence c, given current term x
double c(double x)
{
  return x - (pow(x, 5.0) - 7.0)/(5.0*pow(x, 4.0));
}

//computes the next term of sequence d, given current term x
double d(double x)
{
  return x - (pow(x, 5.0) - 7.0)/12;
}

int main()
{
  cout.precision(16);

  const double ACTUAL_VAL = pow(7.0, 0.2);
  const double p0 = 1.0;

  double p_a = 1.0;
  double p_b = 1.0;
  double p_c = 1.0;
  double p_d = 1.0;

  cout << setw(25) << "a" << setw(25) << "b" << setw(25) << "c" << setw(25) << "d" << setw(25) << "actual" << endl;

  for(int i = 0; i < MAX_ITERATIONS; i++)
  {
    cout << setw(25) << p_a <<
    setw(25) << p_b <<
    setw(25) << p_c <<
    setw(25) << p_d <<
    setw(25) << ACTUAL_VAL << endl;

    p_a = a(p_a);
    p_b = b(p_b);
    p_c = c(p_c);
    p_d = d(p_d);
  }
  return 0;
}

//Program to solve problem 12 in section 2.5

#include <functional>
#include <cmath>
#include <iostream>
using namespace std;

const int MAX_ITERATIONS = 100;

//if two numbers differ by less than TOLERANCE, they are considered equal.
const double TOLERANCE = 0.00001; //problem statement gave TOLERANCE = 10^-5

double g_a(double x)
{
  return 2+sin(x);
}

double g_b(double x)
{
  return cbrt(2*x+5);
}

double g_c(double x)
{
  return log(3*x*x);
}

double g_d(double x)
{
  return cos(x);
}

//given a function g and an inital approximation p0,
//return a pair of g's fixed point and the number iterations performed
auto steffensensMethod(function<double(double)> g, double p0)
{
  for (int i = 1; i <= MAX_ITERATIONS; i++)
  {
    double p1 = g(p0);
    double p2 = g(p1);
    double p = p0 - (p1-p0)*(p1-p0)/(p2 - 2*p1 + p0);
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

  auto result = steffensensMethod(g_a, 2.5);
  cout << "a) x = " << result.first << " after " << result.second << " iterations" << endl;

  result = steffensensMethod(g_b, 2.5);
  cout << "b) x = "  << result.first << " after " << result.second << " iterations" << endl;

  result = steffensensMethod(g_c, 1.0);
  cout << "c) x = " << result.first << " after " << result.second << " iterations" << endl;

  result = steffensensMethod(g_d, 1.0);
  cout << "d) x = " << result.first << " after " << result.second << " iterations" << endl;
  return 0;
}

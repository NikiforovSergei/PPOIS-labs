#include "../../include/polynominal/polynominal.hpp"

// ! Polynominal utils
/*
 * Solve polynominal equasion
 */
double Polynominal::__calculate_polynominal(double x) {
  int n = this->__cooficients.size() - 1;
  double res = this->__cooficients[n];
  for (int i = n - 1; i >= 0; i--) {
    res = x * res + this->__cooficients[i];
  }

  return res;
}

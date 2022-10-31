#include "utils/polynominal/polynominal_utils.cpp"

Polynominal::Polynominal(std::vector<double> cooficients) {
  this->__cooficients = cooficients;
}

double Polynominal::operator [] (int i) {
  return this->__cooficients[i];
}

double Polynominal::operator () (double x) {
  return this->__calculate_polynominal(x);
}

Polynominal Polynominal::operator + (Polynominal& other) {
  int n = std::max(this->__cooficients.size(), other.__cooficients.size()); 
  std::vector<double> res (n);
  
  for (int i = 0; i < n; i++) {
    double a = 0, b = 0;
    if (i < this->__cooficients.size()) {
      a = this->__cooficients[i]; // REFACTOR: change to this
    }
    if (i < other.__cooficients.size()) {
      b = other.__cooficients[i];
    }
    res[i] = a + b;

  }

  return Polynominal(res);
}

Polynominal& Polynominal::operator += (Polynominal& other) {
  return *this = *this + other;
}

Polynominal Polynominal::operator - (Polynominal& other) {
  int n = std::max(this->__cooficients.size(), other.__cooficients.size()); 
  std::vector<double> res (n);
  
  for (int i = 0; i < n; i++) {
    double a = 0, b = 0;
    if (i < this->__cooficients.size()) {
      a = this->__cooficients[i]; // REFACTOR: change to this
    }
    if (i < other.__cooficients.size()) {
      b = other.__cooficients[i];
    }
    res[i] = a - b;
  }

  return Polynominal(res);
}

Polynominal& Polynominal::operator -= (Polynominal& other) {
  return *this = *this - other;
}

Polynominal Polynominal::operator * (Polynominal& other) {
  int n = this->__cooficients.size() + other.__cooficients.size() - 1;
  std::vector<double> res (n);

  for (int i = 0; i < this->__cooficients.size(); i++) {
    for (int j = 0; j < other.__cooficients.size(); j++) {
      res[i+j] += this->__cooficients[i] * other.__cooficients[j]; // REFACTOR: Change to []
    }
  }

  return Polynominal(res);
}

Polynominal& Polynominal::operator *= (Polynominal& other) {
  return *this = *this * other;
}

bool Polynominal::operator == (const Polynominal& other) const {
  if (this->__cooficients.size() != other.__cooficients.size()) {
    return false;
  }

  for (int i = 0; i < this->__cooficients.size(); i++) {
    if (this->__cooficients[i] != other.__cooficients[i]) {
      return false;
    }
  }

  return true;
}

bool Polynominal::operator != (const Polynominal& other) const {
  return !(*this == other);
}

#include <iostream>
#include <algorithm>
#include <vector>

// !Polynominal class 
/*
 * A more detailed class description
 */
class Polynominal {
private:
  // Cooficients of polynominal
  std::vector<double> __cooficients;
  // Private method to solve Polynominal
  double __calculate_polynominal(double x);
public:
   // Constructor of a Polynominal class
   /* 
   * @param cooficients Polynominal cooficients
   */
  Polynominal(std::vector<double> cooficients);
  
  // Get cooficient of index i
  /*
   * @param i index of cooficient
   */
  double operator [] (int i);
  // Solve polynominal
  /*
   * @param x variable 
   */
  double operator () (double x);
  
  Polynominal operator + (Polynominal& other);
  Polynominal& operator += (Polynominal& other);

  Polynominal operator - (Polynominal& other);
  Polynominal& operator -= (Polynominal& other);
  
  Polynominal operator * (Polynominal& other);
  Polynominal& operator *= (Polynominal& other);
  
  bool operator == (const Polynominal& other) const;
  bool operator != (const Polynominal& other) const;
};

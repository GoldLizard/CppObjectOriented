// Author:  Keith A. Shomper
// Date:    Jan 7, 2020
// Purpose: Starter code for HW#2


#include <iostream>

using namespace std;

class ComplexNumber {
 public:
   // constructors (copy constructor not necessary, included for illustration)
   ComplexNumber(float real = 0.0, float imag = 0.0);
   ComplexNumber(const ComplexNumber &rhs);
   // add new construtor here ...
   ComplexNumber(const char *copy); //

   // assignment operator (not necessary, included for illustration)
   ComplexNumber& operator=(const ComplexNumber &rhs);

   // the multiplication operation is a member function
   // add new mult op here ...
   ComplexNumber operator*(const ComplexNumber &rhs); //




   // equality operator needed for unit test in HW2
   bool operator==(const ComplexNumber &rhs) const;

   // friend operator functions
   friend ComplexNumber operator+(const ComplexNumber &, const ComplexNumber &);
   friend ComplexNumber operator-(const ComplexNumber &, const ComplexNumber &);
   friend ostream&      operator<<(ostream &,            const ComplexNumber &);
   // add new input operator here ...

   friend istream&       operator>>(istream &in,             ComplexNumber &a); //



   // data members
 private:
   float r;
   float i;
};



//ComplexNumber::ComplexNumber(const ComplexNumber &rhs) : r(ths.r), i(rhs.i) {}

/*
Modify the file ComplexNumber.h by adding function prototypes for the three functions
listed below:

1. A ComplexNumber constructor which takes a single C-sytle string (i.e., const char *)
as its only parameter

2. A multiplication operator as a member function returning a ComplexNumber and taking
two parameters:
  An implicit constant this parameter and
  An explicit parameter which is a constant reference to a ComplexNumber

3. An input operator as a friend function returning a reference to an istream and taking
two parameters
  A reference to an istream and
  A reference to a ComplexNumber
*/
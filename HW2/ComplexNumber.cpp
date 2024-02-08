// Author:  Keith A. Shomper
// Date:    Jan 7, 2020
// Purpose: Starter code for HW#2

/*
Modify the file ComplexNumber.cpp file to add stub implementations
for the three functions which you specified in Part2.
*/

#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>
#include "ComplexNumber.h"

ComplexNumber::ComplexNumber(float real, float imag) {
   r = real;
   i = imag;
}

ComplexNumber::ComplexNumber(const ComplexNumber &rhs) {
   r = rhs.r;
   i = rhs.i;
}

//new constructor here
ComplexNumber::ComplexNumber(const char *copy){
   
   string copyString = copy;
   stringstream temp;
   temp << copy;

   if(    copyString.find('+') < copyString.size()
      || ((copyString.find('-') < copyString.size()
      && copyString.find('-') != 0) // != 0 stops inputs like -2i from being stored as r = -2, i = 0
      && copyString.find('i') < copyString.size())){ //stops inputs like =3.4e-1 from having garbage data in i
      //both real and imaginary parts exist
      temp >> r;
      if(copyString.find("+i") < copyString.size()){
         //real exists, covers i=1 case
         i = 1;
      }   
      else if(copyString.find("-i") < copyString.size()){
         //real exists, covers i=-1 case
         i = -1;
      }
      else{
         //real exists, r+Ai case
         temp >> i;
      }
   }
   else if(copyString.find('i') < copyString.size()){
      //only imaginary part exists
      r = 0;
   
      if(copyString.find("-i") < copyString.size()){
         //real does not exist, covers i=-1 case
         i = -1;
      }
      else if(copyString.find('i') == 0){
         //real does not exist, covers i=1 case
         i = 1;
      }
      else{
         //real does not exist, covers +Ai case
         temp >> i;
      }
   }
   else{
      //only real part exists
      temp >> r;
      i = 0;
   }
}

ComplexNumber& ComplexNumber::operator=(const ComplexNumber &rhs){
   r = rhs.r;
   i = rhs.i;
   return *this;
}

//mult op stud here
ComplexNumber ComplexNumber::operator* (const ComplexNumber &rhs){
   ComplexNumber result;
   result.r = (r * rhs.r) - (i * rhs.i);
   result.i = (r * rhs.i) + (i * rhs.r);
   return result;
}


bool ComplexNumber::operator==(const ComplexNumber &rhs) const {
   return (r == rhs.r && i == rhs.i);
}

ComplexNumber operator+ (const ComplexNumber &a, const ComplexNumber &b) {
   ComplexNumber result;

   result.r = a.r + b.r;
   result.i = a.i + b.i;

   return result;
}

ComplexNumber operator- (const ComplexNumber &a, const ComplexNumber &b) {
   ComplexNumber result;

   result.r = a.r - b.r;
   result.i = a.i - b.i;

   return result;
}

ostream& operator<< (ostream &out, const ComplexNumber &b) {
   bool rPrinted = false;

   if (b.r != 0 || (b.r == 0 && b.i == 0)) {
      out << b.r;
      rPrinted = true;
   }
   
   if (b.i > 0) {
      if (rPrinted) {
         out << "+";
      }
      if (b.i != 1) {
         out << b.i;
      }
      out << "i";
   } else if (b.i < 0) {
      if (b.i == -1) {
         out << "-";
      } else {
         out << b.i;
      }
      out << "i";
   }

   return out;
}

//new input operator here
istream& operator>> (istream &in, ComplexNumber &a) {
   string userInput;
   in >> userInput;
   char* inputPointer = &userInput.at(0); //converts string to char* so that ComplexNumber(char* copy) can be used
   a = ComplexNumber(inputPointer);
   return in;
}
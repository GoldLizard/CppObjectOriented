#ifndef GATEH
#define GATEH

#include "Wire.h"
#include <vector>
using namespace std;

class Gate{
public:
    Gate(); //default constructor
    Gate(string gateType, string gateDelayString, string gateInput1, string gateInput2, string gateOutput); //constructor with 5 parameters
    int getDelay() const;
    Wire* getInput(int inputNumber) const;
    Wire* getOutput() const;
    int Evaluate(int time) const;
    
    Wire* outputWire;
    string gateType;
    int gateDelay;
    Wire *input1, *input2;
private:
};

#endif
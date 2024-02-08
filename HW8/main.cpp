#include <iostream>
#include <queue>
#include <vector>

#include "Circuit.h"
#include "Circuit.cpp"
#include "Gate.h"
#include "Gate.cpp"
#include "Wire.h"
#include "Wire.cpp"
using namespace std;

int main(){
    string fileName;
    cout << "What is the name of the circuit test file (base name only)" << endl;
    cin >> fileName;
    //fileName = "circuit6";

    ReadCircuitDescription(fileName);
    cout << "circuit read" << endl;

    ReadVectorFile(fileName + "_v");
    cout << "vector read" << endl;
    
    while(!eventQueue.empty() && timeElapsed <= 60){
        SimulateEvent();
        //cout << "timeElapsed: " << timeElapsed << endl;
    }
    //cout << "finished simulation" << endl;

    Print();
    cout << endl << "finished printing" << endl;
    system("Pause");
    return 0;
}
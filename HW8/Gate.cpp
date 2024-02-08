#include "Gate.h"
#include "Circuit.h"
#include <fstream>
#include <string>
using namespace std;

Gate::Gate() : gateType(""), gateDelay(0), input1(nullptr), input2(nullptr), outputWire(nullptr){ //default constructor
}


//constructor with 5 parameters
Gate::Gate(string gateType, string gateDelayString, string gateInput1, string gateInput2, string gateOutput){
    Gate* tempGate = new Gate; //create a new Gate and populate class data
    tempGate->gateType = gateType;
    tempGate->gateDelay = stoi(gateDelayString);
    tempGate->input1 = allWires.at(stoi(gateInput1));
    
    allWires.at(stoi(gateInput1))->addDrive(tempGate); //input1 drives gate
    //cout << "drive added: " << gateInput1 << endl;

    if(gateInput2 != ""){
        tempGate->input2 = allWires.at(stoi(gateInput2));
        allWires.at(stoi(gateInput2))->addDrive(tempGate); //input2 drives gate
    }
    if(gateInput2 == ""){
        tempGate->input2 = nullptr; //gateInput2 == "" only when NOT gate
    }
    tempGate->outputWire = allWires.at(stoi(gateOutput)); //links gate to output wire
    allGates.push_back(tempGate); //adds gate to allGates
}

int Gate::getDelay() const{
    return gateDelay;
}

Wire* Gate::getInput(int inputNumber) const {
    if(inputNumber == 1){
        return input1;
    }
    else if(inputNumber == 2){
        return input2;
    }
    return nullptr;
}

Wire* Gate::getOutput() const {
    return outputWire;
}

int Gate::Evaluate(int time) const { //removed string gateType
    vector<vector<int>> allSolutions;
    int firstInput, secondInput;
    firstInput = input1->getLastKnownValue(time); //replace with getLastKnownValue
    if(input2 != nullptr){ secondInput = input2->getLastKnownValue(time); } //messy here to deal with NOT gate case
    else{ secondInput = 2; }
    
    if(gateType == "AND"){
        allSolutions = {{0,0,0}, {0,1,0}, {0,2,0}, {1,1,1}, {1,2,2}, {2,2,2}}; //{firstInput, SecondInput, output}
    }
    else if(gateType == "NAND"){
        allSolutions = {{0,0,1}, {0,1,1}, {0,2,1}, {1,1,0}, {1,2,2}, {2,2,2}}; //{firstInput, SecondInput, output}
    }
    else if(gateType == "OR"){
        allSolutions = {{0,0,0}, {0,1,1}, {0,2,2}, {1,1,1}, {1,2,1}, {2,2,2}}; //{firstInput, SecondInput, output}
    }
    else if(gateType == "NOR"){
        allSolutions = {{0,0,1}, {0,1,0}, {0,2,2}, {1,1,0}, {1,2,0}, {2,2,2}}; //{firstInput, SecondInput, output}
    }
    else if(gateType == "XOR"){
        allSolutions = {{0,0,0}, {0,1,1}, {0,2,2}, {1,1,0}, {1,2,2}, {2,2,2}}; //{firstInput, SecondInput, output}
    }
    else if(gateType == "XNOR"){
        allSolutions = {{0,0,1}, {0,1,0}, {0,2,2}, {1,1,1}, {1,2,2}, {2,2,2}}; //{firstInput, SecondInput, output}
    }
    else if(gateType == "NOT"){
        allSolutions = {{0,2,1}, {1,2,0}, {2,2,2}}; //{firstInput, SecondInput, output}
    }
    else{
        printf("\033[1;31m"); //text color red
        cout << "Error: gate type does not exist" << endl;
        cout << "gateType: " << gateType << endl;
        system("Pause");
    }
    for(vector<int> eachSolution : allSolutions){ //if the first/second inputs match {firstInput, SecondInput, X}, return X
        if(eachSolution.at(0) == firstInput && eachSolution.at(1) == secondInput
        || eachSolution.at(0) == secondInput && eachSolution.at(1) == firstInput){ //both input orders 02 and 20 will use {0,2,X}
            return eachSolution.at(2);
        }
    } 
    printf("\033[1;31m"); //text color red
    cout << "Error: no evaluation returned" << endl;
    cout << "gateType: " << gateType << "\t" << "Inputs: " << firstInput << secondInput << endl;
    system("Pause");
    return 3; //compiler doesnt like reaching end of function without return
}
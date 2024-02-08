#ifndef WIREH
#define WIREH

#include "Gate.h"
#include <vector>
using namespace std;

class Gate;

vector<int> addV(vector<int> v1, vector<int> v2){
    vector<int> addedV = v1;
    for(int i = 0; i < v2.size(); i++){
        addedV.push_back(v2.at(i));
    }
    return addedV;
}

class Wire{
public:
    Wire();
    Wire(string wireType, string wireName, string wireNumber);
    void PopulateWireHistory(int time); //once an event changes a wire's value, it fills in data between the last known state and new value
    void PopulateWireHistory(); //after _v.txt is read or , it fills in the remaining history. Ex. _____-ZZZZZ -> _____------

    int getHistory(int time);
    string getHistoryString(int time); //returns wire's vector history as a single string to output
    int getLastKnownValue(int time);
    void setHistory(int value, int time); //add value to history
    void addDrive(Gate* toBeDriven); //adds a gate to the output wire


    vector<Gate*> drives; //this wire is the input of these gates
    string wireName;    //A, B, C, 3, 4, etc
    string wireType;    //INPUT, OUTPUT, or Between
    vector<int> wireHistory  = addV({2}, vector<int>(60, 3)); //time 0-16, print out
                            //0 == off, 1 == on, 2 == NULL, 3 == to be generated
private:
};

#endif
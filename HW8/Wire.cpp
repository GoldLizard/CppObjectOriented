#include "Wire.h"
using namespace std;

Wire::Wire(){
    vector<Gate*> drives = {};
    string wireName = "";
    vector<int> wireHistory = addV({2}, vector<int>(60, 3)); //declared weird because C++11 doesnt like overloaded vector declaration directly in class
    wireHistory.at(0) = 2;
    //int currentState = 2;
}

Wire::Wire(string wireType, string wireName, string wireNumber){
    Wire* tempWire = new Wire;
    tempWire->wireType = wireType;
    tempWire->wireName = wireName;
    allWires.at(stoi(wireNumber)) = tempWire;
}

void Wire::PopulateWireHistory(){ //fills input wires until the end of 16s Ex. _____-ZZZZZ -> _____------
    int lastKnownValue, lastKnownTime;
    if(wireType == "INPUT"){
        for(int i = 0; wireHistory.at(i) != 3; i++){
            if(wireHistory.at(i+1) == 3){
                lastKnownValue = wireHistory.at(i);
                lastKnownTime = i;
            }
        }
        for(int i = lastKnownTime+1; i < wireHistory.size(); i++){
            setHistory(lastKnownValue, i);
        }
    }
}

void Wire::PopulateWireHistory(int time){ //fills wireHistory between time and last known value, Ex. _ZZZZ-ZZZZ -> _____-ZZZZ
    if(time > 1){ //stops error from trying to access wireHistory.at(-1)
        int lastKnownValue, lastKnownTime;

        lastKnownValue = wireHistory.at(time-1); //could replace section below, but glitched because lastKnownTime isnt calculated
        lastKnownTime = time-1;
        for(int i = time-1; wireHistory.at(i) == 3; i--){
            lastKnownTime = i;
            lastKnownValue = wireHistory.at(i-1); //maybe -2
        }
        cout << "last value: " << lastKnownValue << " last time: " << lastKnownTime << endl;
        //system("Pause");
        for(int i = lastKnownTime; wireHistory.at(i) == 3; i++){//moves forward
            wireHistory.at(i) = lastKnownValue; //fills in all data between
        }
    }
}

int Wire::getHistory(int time){
    return wireHistory.at(time);
}

string Wire::getHistoryString(int time){
    string history = "";
    for(int i = 0; i <= time; i++){ //prints up to time parameter
        if(getHistory(i) == 0){
            history += "_";
        }
        else if(getHistory(i) == 1){
            history += "-";
        }
        else if(getHistory(i) == 2){
            history += "X";
        }
        else{
            history += "Z"; //should not happen
        }
    }
    return history;
}

int Wire::getLastKnownValue(int time){ //retrieves last known value before time parameter
    int lastKnownValue = 2;
    if(this->getHistory(time) != 3){
        lastKnownValue = this->getHistory(time);
    }
    if(time != 0){
        if(this->getHistory(time) == 3){
            for(int i = time-1; this->getHistory(i) == 3; i--){ //backtrack until the last known value is found, 3 is default
                if(i-1 == 0 && this->getHistory(i-1) == 3){
                    lastKnownValue = 2;
                }
                else if(this->getHistory(i-1) != 3){
                    lastKnownValue = this->getHistory(i-1);
                }
            }
        }
    }
    return lastKnownValue;
}

void Wire::setHistory(int value, int time){
    wireHistory.at(time) = value;
}

void Wire::addDrive(Gate* toBeDriven){ //adds drive to wire
    bool driveAlreadyExists = false;
    for(Gate* &eachGate : this->drives){ //checks all drives to avoid adding the same drive twice
        if(eachGate == toBeDriven){
            driveAlreadyExists = true;
        }
    }
    if(driveAlreadyExists == false){
        drives.push_back(toBeDriven);
    }

}
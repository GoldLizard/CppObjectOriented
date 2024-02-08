#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>

#include "Circuit.h"
#include "Gate.h"
#include "Wire.h"
using namespace std;

void ReadCircuitDescription(string fileName){
    ifstream TXT;
    string trash, line, wireType, wireName, wireNumber, gateType, gateDelayString, gateInput1, gateInput2, gateOutput;

    TXT.open(fileName + ".txt");
    if(!TXT.is_open()){
        printf("\033[1;31m"); //text color red
        cout << "Error: cannot open circuit file" << endl;
        system("Pause");
    }
    getline(TXT, line); //eats first line "Circuit SampleCircuit"
    istringstream CircuitTitle(line);
    CircuitTitle >> trash >> circuitName; //trashes "Circuit", saves "SampleCircuit" to CircuitName in main
    while(!TXT.eof()){
        getline(TXT, line);
        if(line != ""){
            istringstream TXTline(line);
            if(line.find("INPUT") < line.size() || line.find("OUTPUT") < line.size()){ //wire description
                TXTline >> wireType >> wireName >> wireNumber; //INPUT A 1
                if(allWires.size() < stoi(wireNumber)+1){allWires.resize(stoi(wireNumber)+1);} //resizes
                Wire(wireType, wireName, wireNumber);
            }
            else if (!(line.find("NOT") == 0)){ //gate description, except NOT
                TXTline >> gateType >> gateDelayString >> gateInput1 >> gateInput2 >> gateOutput;
                //cout << "input: " << line << endl;
                //system("Pause");
                //shorten this later. creates in between wires that are neither input or output
                //make sure print function is compatible with new wire type
                
                //resizes vector if needed, remove from create wire code
                if(allWires.size() < stoi(gateInput1)+1){allWires.resize(stoi(gateInput1)+1);}
                if(allWires.size() < stoi(gateInput2)+1){allWires.resize(stoi(gateInput2)+1);}
                if(allWires.size() < stoi(gateOutput)+1){allWires.resize(stoi(gateOutput)+1);}

                //creates wire if it doesn't exist
                if(allWires.at(stoi(gateInput1)) == nullptr){
                    allWires.at(stoi(gateInput1)) = new Wire("Between", gateInput1, gateInput1);
                }
                if(allWires.at(stoi(gateInput2)) == nullptr){
                    allWires.at(stoi(gateInput2)) = new Wire("Between", gateInput2, gateInput2);
                }
                if(allWires.at(stoi(gateOutput)) == nullptr){
                    allWires.at(stoi(gateOutput)) = new Wire("Between", gateOutput, gateOutput); //possible problem here
                }
                

                Gate(gateType, gateDelayString, gateInput1, gateInput2, gateOutput);
            }
            else if(line.find("NOT") == 0){ //NOT description
                TXTline >> gateType >> gateDelayString >> gateInput1 >> gateOutput;
                string gateInput2 = ""; //program kills itself if I try passing nullptr as a parameter
                //may want to add a wire size check
            
                if(allWires.at(stoi(gateInput1)) == nullptr){
                    allWires.at(stoi(gateInput1)) = new Wire("Between", gateInput1, gateInput1);
                }
                if(allWires.at(stoi(gateOutput)) == nullptr){
                    allWires.at(stoi(gateOutput)) = new Wire("Between", gateOutput, gateOutput);
                }

                //cout << "NOT output: " << gateOutput << endl;

                Gate(gateType, gateDelayString, gateInput1, gateInput2, gateOutput);
            }
            else{
                printf("\033[1;31m"); //text color red
                cout << "Error: bad input line in circuit file" << endl;
                cout << "Input line: " << line << endl;
                system("Pause");
            }
        }
    }
    TXT.close();
}

void ReadVectorFile(string fileName){
    ifstream TXT;
    string trash, line, wireName, valueString;
    int time, value;
    TXT.open(fileName + ".txt");
    if(!TXT.is_open()){
        printf("\033[1;31m"); //text color red
        cout << "Error: cannot open vector file" << endl;
        system("Pause");
    }
    getline(TXT, trash); //eats "VECTOR SimpleCircuit" and "INPUT"
    while(!TXT.eof()){
        getline(TXT, line);
        if(line != ""){
            if(line.find("INPUT") != 0){
                printf("\033[1;31m"); //text color red
                cout << "Error: bad input line in vector file" << endl;
                cout << "Input: " << line << endl;
                system("Pause");
            }
            istringstream TXTline(line);
            TXTline >> trash >> wireName >> time >> valueString; //parse data from line, trashes "INPUT"
            if(valueString == "X"){value = 2;} //deals with bad parsing stoi() conversion
            else{value = stoi(valueString);}

           //cout << "vector: " << wireName << time << value << endl;
            for(Wire* eachWire : allWires){
                if(eachWire != nullptr && eachWire->wireName == wireName){ // != nullptr prevents errors from unused wire numbers          
                    eachWire->setHistory(value, time);
                    //cout << "attempted populate time: " << time << endl;
                    eachWire->PopulateWireHistory(time); //glitch here for circuit4
                    //cout << "done populate" << endl;
                    for(Gate* eachGate : eachWire->drives){ //for all gates connected to the updated wire
                        CreateEvent(eachGate, time);
                        //cout << "event created." << "time elapsed: " << timeElapsed << endl;
                        //cout << "drives size: " << eachWire->drives.size() << endl;
                    }
                }
            }
        }
    }
    for(Wire* eachWire : allWires){
        if(eachWire != nullptr){
            eachWire->PopulateWireHistory();
        }
    }
    TXT.close();
}

void CreateEvent(Gate* eventGate, int timeGenerated){
    event* tempEvent = new event;
    tempEvent->eventGate = eventGate;
    tempEvent->timeGenerated = timeGenerated;
    tempEvent->timeToUpdate = timeGenerated + tempEvent->eventGate->gateDelay;
    eventQueue.push(tempEvent); //replace with function that adds events in right order
}

void SimulateEvent(){
    bool anyEventSimulated = false;
    int eventsChecked = 0;
    while(anyEventSimulated == false && timeElapsed <= 60){ //loops until it finds valid event to execute
        event* currentEvent = eventQueue.front();
        //cout << endl << currentEvent->eventGate->gateType << " " << currentEvent->timeGenerated << endl;
        //below print line breaks if the circuit has a NOT gate
        //cout << "gate inputs: " << currentEvent->eventGate->input1->getHistory(currentEvent->timeGenerated) << currentEvent->eventGate->input2->getHistory(currentEvent->timeGenerated) << endl;
        eventQueue.pop();
        if(currentEvent->timeToUpdate > timeElapsed){
            //cout << "event pushed back" << endl;
            //cout << "Time generated: " << currentEvent->timeGenerated << " Time elapsed: " << timeElapsed << endl; 
            eventQueue.push(currentEvent); //just keep recycling events
            eventsChecked++;
        }
        else{ //this is an event that can be evaluated
            Gate* currentGate = currentEvent->eventGate;
            int currentTimeToUpdate = currentEvent->timeToUpdate;
            int currentTimeGenerated = currentEvent->timeGenerated;
            int currentInput1 = currentGate->input1->getLastKnownValue(currentTimeGenerated);
            int currentInput2;
            if(currentGate->input2 != nullptr){ //messy because of NOT
                currentInput2 = currentGate->input2->getLastKnownValue(currentTimeGenerated);
            }
            else{
                currentInput2 = 2;
            }

            Wire* currentOutput = currentGate->outputWire;

            //if(currentOutput == nullptr){
                //cout << "null" << endl;
            //}
    
            if((currentInput1 == 3) || (currentInput2 == 3)){
                printf("\033[1;31m"); //text color red
                cout << "Error: tried evaluating gate with ungenerated inputs" << endl;
                cout << "gateType: " << currentGate->gateType << endl;
                cout << "wires: " << currentGate->input1->wireName << " " << currentGate->input2->wireName << endl;
                cout << "Time generated: " << currentEvent->timeGenerated << endl;
                cout << "Inputs: " << currentInput1 << " " << currentInput2 << endl;
                system("Pause");
            }

            //evaluate
            int newEvaluation = currentGate->Evaluate(currentTimeGenerated);
            currentOutput->setHistory(newEvaluation, currentTimeToUpdate); //update wire's history
            currentOutput->PopulateWireHistory(currentTimeToUpdate); //broke here lol. //not anymore
            if(newEvaluation != currentOutput->getLastKnownValue(currentTimeGenerated) || (currentOutput->getLastKnownValue(currentTimeGenerated) == 2)){
                for(Gate* eachGate : currentOutput->drives){ //for all gates connected to the updated wire
                    CreateEvent(eachGate, timeElapsed);
                    //cout << "event created." << "time elapsed: " << timeElapsed << endl;
                    //cout << "drives size: " << currentOutput->drives.size() << endl;
                }
            } //else, do not create new events. Nothing changes

            if(eventQueue.empty()){
                //cout << "queue empty: " << currentGate->gateDelay << endl;
                timeElapsed = currentTimeToUpdate;
            }

            delete currentEvent; //free both queue item and memory
            //cout << "event deleted" << endl;
            //cout << "queue size: " << eventQueue.size() << endl;
            //cout << "events checked " << eventsChecked << endl;
            //cout << "event read" << endl;
            anyEventSimulated = true;
        }

        if(eventsChecked >= eventQueue.size() && !eventQueue.empty()){ //if all events have been checked for that time, check next timeElapsed
            timeElapsed++;
            eventsChecked = 0;
            //cout << "time elapsed increased" << endl;
        }
    }
}


void Print(){
    printf("\033[1;37m"); //text color white

    if(timeElapsed > 60){timeElapsed = 60;}

    for(Wire* eachWire : allWires){
        if(eachWire != nullptr && eachWire->wireName != ""){ //allWires may contain empty wires, only print wires that exist
            cout << "  |" << endl;                                                                  //  |
            cout << eachWire->wireName << " | " << eachWire->getHistoryString(timeElapsed) << endl; //A | ____----
        }
    }
    cout << "  |_" ;
    for(int i = 0; i <= timeElapsed; i++){ //prints x axis
        cout << "_";
    }
    cout << endl;
    string timeAxis1, timeAxis2;
    for(int i = 0; i <= timeElapsed; i++){
        if((i % 5 == 0) && (i % 10 != 0)){
            timeAxis1 += to_string((i-5) / 10); //0   1   2   3   4 //fix, broken
            timeAxis2 += "5";                   //5   5   5   5   5
        }
        else if(i % 10 == 0){
            timeAxis1 += to_string(i / 10); //0   1   2   3   4
            timeAxis2 += "0";               //0   0   0   0   0
        }
        else{
            timeAxis1 += "-"; //all times that arent multiples of 5
            timeAxis2 += "-";
        }
    }
    printf("\033[1;36m"); //text color blue
    cout << "    " << timeAxis1 << endl << "    " << timeAxis2 << endl << endl;

    printf("\033[1;0m"); //text color white
    cout << "Circuit Name: " << circuitName << endl;
    cout << "Time elapsed: " << timeElapsed << "ns" << endl;
}
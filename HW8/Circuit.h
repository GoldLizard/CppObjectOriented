#ifndef CIRCUITH
#define CIRCUITH

#include <iostream>
#include <sstream>
#include <vector>

#include "Gate.h"
#include "Wire.h"
using namespace std;

struct event{
    Gate* eventGate;
    int timeGenerated;
    int timeToUpdate;
};

void ReadVectorFile(string fileName); //add read circuit description
void ReadCircuitDescription(string fileName); //add read vector file
void SimulateEvent();
void CreateEvent(Gate* eventGate, int timeGenerated);
void Print(); //print function

vector<Wire*> allWires = {};
vector<Gate*> allGates = {};
queue<event*> eventQueue;
int timeElapsed = 0;
string circuitName = "";


#endif
#include <iostream>
#include <vector>
using namespace std;

int Evaluate(string gateType, Wire* input1, Wire* input2, int time);

int main(){

    cout << Evaluate("NOR", 1,1) << endl;

    system("Pause");
    return 0;
}


int Evaluate(string gateType, Wire* input1, Wire* input2, int time){
    vector<vector<int>> allSolutions;
    int input3, input4;
    input3 = input1->wireHistory.at(time);
    if(input2 != nullptr){ input4 = input2->wireHistory.at(time); } //messy here to deal with NOT gate case
    else{ input4 = 2; }

    if(input3 > input4){ //orders inputs so theres only 6 comparisons
        int temp = input3;
        input3 = input4;
        input4 = temp;
    }
    
    if(gateType == "AND"){
        allSolutions = {{0,0,0}, {0,1,0}, {0,2,0}, //{input1, input2, output}
                        {1,1,1}, {1,2,2}, {2,2,2}};
    }
    else if(gateType == "NAND"){
        allSolutions = {{0,0,1}, {0,1,1}, {0,2,1}, //{input1, input2, output}
                        {1,1,0}, {1,2,2}, {2,2,2}};
    }
    else if(gateType == "OR"){
        allSolutions = {{0,0,0}, {0,1,1}, {0,2,2}, //{input1, input2, output}
                        {1,1,1}, {1,2,1}, {2,2,2}};
    }
    else if(gateType == "NOR"){
        allSolutions = {{0,0,1}, {0,1,0}, {0,2,2}, //{input1, input2, output}
                        {1,1,0}, {1,2,0}, {2,2,2}};
    }
    else if(gateType == "XOR"){
        allSolutions = {{0,0,0}, {0,1,1}, {0,2,2}, //{input1, input2, output}
                        {1,1,0}, {1,2,2}, {2,2,2}};
    }
    else if(gateType == "XNOR"){
        allSolutions = {{0,0,1}, {0,1,0}, {0,2,2}, //{input1, input2, output}
                        {1,1,1}, {1,2,2}, {2,2,2}};
    }
    else if(gateType == "NOT"){ //go back and make input2 = 2 upon declaration
        allSolutions = {{0,2,1}, {1,2,0}, {2,2,2}}; //{input1, input2, output}
    }

    for(vector<int> eachSolution : allSolutions){
        if(eachSolution.at(0) == input3 && eachSolution.at(1) == input3){
            return eachSolution.at(2);
        }
    } 
    cout << "Evaluation error: gate returned nothing." << endl;
    cout << "gateType: " << gateType << "\t" << "Inputs: " << input1 << input2 << endl;
    return 3; //because compiler doesnt like reaching end of function without return
}

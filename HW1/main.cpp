#include <iostream>
using namespace std;

int zymain(int, char**);
void reverse(char*, char*);

int main(int argc, char **argv) {
    return zymain(argc, argv);
}

int zymain(int argc, char** argv) {
    //checks argv[1]'s size by null terminator
    int strSize = 0;
    for(char* i = argv[1]; *i != '\0'; i++){
        strSize++;
    }

    //checks that 4 commands are present
    if(argc != 4){
        cout << "expected 4 commands, recieved " << argc << " commands" << endl;
        return 1;
    }
    //checks that argv[2] and argv[3] are only digits
    for(int i = 2; i <= 3; i++){
        for(char* j = argv[i]; *j != '\0'; j++){    //loops through all characters
            if(!isdigit(*j)){
                cout << "argv[" << i << "] can only contain digits" << endl;
                return 2;
            }
        }
    }

    //converting argument str to int
    //awkwardly placed in the middle to avoid stoi() crash when arvc<4
    int frontIndex = stoi(argv[2]);
    int rearIndex = stoi(argv[3]);

    //checks 0 < frontIndex <= rearIndex
    if(!(frontIndex >= 0)  ||  !(frontIndex <= rearIndex)){
        cout << "frontIndex cannot be negative. rearIndex cannot be smaller than frontIndex" << endl;
        return 3;
    }
    //rearIndex cannot be larger than strSize
    if(!(rearIndex < strSize)){
        cout << "rearIndex cannot be larger than strSize" << endl;
        return 4;
    }

    //gets memory address of string at Index's location
    char* front = argv[1] + frontIndex;
    char* rear = argv[1] + rearIndex;
    reverse(front, rear);
    cout << '\"' << argv[1] << '\"' << endl;
    system("Pause");
    return 0;
}

void reverse (char *front, char *rear){
    //keeps swapping characters until *(front+i) and *(rear-i) meet in the middle
    for(int i = 0; (front+i) < (rear-i); i++){
        char temp = *(front+i);
        *(front+i) = *(rear-i);
        *(rear-i) = temp;
    }
}
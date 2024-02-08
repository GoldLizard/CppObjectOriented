// Author:  Keith A. Shomper
// Date:     2/13/20
// Purpose: To implement a simple, sorted linked-list of positive integers

#include "LLSortedPosInt.h"

// The linked-list is constructed of Node elements
struct Node {
    int    key;
    Node *next;
};

static NodePtr createNode(int key, NodePtr p) {
    NodePtr n = new Node;   // allocate a new Node for storing the given key value
    n->key  = key;          // store the key value and the next pointer
    n->next = p;
    return n;               // return the new Node to the caller
}   

// Constructors
LLSortedPosInt::LLSortedPosInt() {
    this->head = createNode(HEAD_OF_LIST, nullptr);     // create the sentinal Node at the head of the list
}  

LLSortedPosInt::LLSortedPosInt(int key) {
    this->head = createNode(HEAD_OF_LIST, nullptr);     // create the sentinal Node at the head of the list
    if(key > 0){                                        // add the single element key, as long as it is positive
        insert(key);
        }
}

LLSortedPosInt::LLSortedPosInt(int *keys,     int n) {
    this->head =  createNode(HEAD_OF_LIST, nullptr);    // create the sentinal node at the head of the list
    for(int i = 0; i < n; i++){                         // add new Nodes for each positive value in keys
        if(keys[i] > 0){
            insert(keys[i]);
        }
    }
}

LLSortedPosInt::LLSortedPosInt(const LLSortedPosInt &l) {
    this->head = createNode(HEAD_OF_LIST, nullptr);     //create a deep copy of the input list l
    NodePtr newList = this->head;                       //creates a pointer to deep copy too
    NodePtr originalList = l.head->next;                //deep copy source
    while(originalList != nullptr){
        newList->next = createNode(originalList->key, nullptr); //adds key to the list
        newList = newList->next;
        originalList = originalList->next;
    }
}

// Destructor
LLSortedPosInt::~LLSortedPosInt() {
    while(this->head != nullptr){
        NodePtr toBeDeleted = this->head;
        this->head = this->head->next;
        delete toBeDeleted;   //free the Nodes in *this, including the sentinal
    }
    delete this->head; //prevents memory leak, since this->head==nullptr wont delete the last node inside the loop
}

// Assignment Operator
LLSortedPosInt&  LLSortedPosInt::operator=(const LLSortedPosInt &l) {
    if (this == &l) {   // handle self assignment
        return *this;
    }
    // free old elements of the list before the new elements from l are assigned
    this->~LLSortedPosInt();
    this->head = createNode(HEAD_OF_LIST, nullptr); //rebuild the sentinal
    NodePtr temp1 = this->head;                     //2 pointers to walk both lists
    NodePtr temp2 = l.head->next;

    while(temp2 != nullptr){       //loops to deep copy each element
        temp1->next = createNode(temp2->key, nullptr);
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return *this;
}

// Print Operator (a non-member function)
ostream&  operator<<  (ostream &out, const LLSortedPosInt &l) {
    // an empty list will be printed as <>
    // a singleton list (a list having one key value k) will be
    //   printed as <k>
    // a list having multiple keys such as 2, 5, 7 will be printed
    //   as <2, 5, 7>

    // print the left angle bracket
    out << '<';
    // print the keys in the list 1
    NodePtr toBePrinted = l.head->next; //added ->next to not print -1  <2, 4, 6, 8>
    while(toBePrinted != nullptr){
        out << toBePrinted->key;
        if(toBePrinted->next != nullptr){
            out << ", ";
        }
        toBePrinted = toBePrinted->next;
    }

    // print the right angle bracket
    out << '>';

    return out;
}

// Boolean Functions
bool LLSortedPosInt::isEmpty            (         ) const {
    // return true if only the sentinal is in the list; return false otherwise
    if(this->head->next == nullptr){return true;}   //if the first node is null, must be empty
    else{return false;}                             //if its not null, must contain a second node and not empty
}

bool LLSortedPosInt::containsElement (int key) const {
    NodePtr toBeSearched = this->head;      //NodePtr to walk the list
    while(toBeSearched != nullptr){         //repeat until last node
        if(toBeSearched->key == key){return true;}       //return true if that node contains the right key
        else{toBeSearched = toBeSearched->next;}         //else, move to the next node and repeat check
    }
    return false;                           //only returns false if the whole list is checked and never returns true
}

// Other Operator Member Functions
bool LLSortedPosInt::operator==(const LLSortedPosInt &l) const {
    NodePtr lhs = this->head;       //declare NodePtrs for this and l as lhs and rhs, for readability
    NodePtr rhs = l.head;
    while(true){                    //just repeat. Its gotta return one of them eventually
        if((lhs->key != rhs->key)                                   //handles nonequal keys
        || ((lhs->next == nullptr) + (rhs->next == nullptr) == 1)){ //handles comparison of nonequal sized lists by XORing a boolean nullptr check 
            return false;
        }
        else if(lhs->key == rhs->key){ //checks equality of keys
            if((lhs->next == nullptr) && (rhs->next == nullptr)){ //checks if final node
                return true;
            }
            else if((lhs->next != nullptr) && (rhs->next != nullptr)){ //checks that neither are last node
                lhs = lhs->next; //move forward both pointers to check the next pointer
                rhs = rhs->next;
            }
        }
    }
    // if all Node key values in *this match the cooresponding
    //  Node key values in l, then the lists are equivalent
}

bool LLSortedPosInt::operator!=(const LLSortedPosInt &l) const {
    return !(*this == l);  //reuses == operator, but returns the inverse
}   

// Other Operator Functions (non-member functions)
LLSortedPosInt  operator+ (const LLSortedPosInt &l1, 
                                        const LLSortedPosInt &l2)  {
    // create a copy of l1 and add each element of l2 to it in 
    // the correct (sorted ascending) order, allow duplicates
    LLSortedPosInt addedList(l1);                       //creates new list by copying l1
    NodePtr toBeAdded = l2.head->next;                  //create NodePtr to walk through the list to be added
    while (toBeAdded != nullptr) {
        addedList.insert(toBeAdded->key);               //adds l2's key to 1l's copy
        toBeAdded = toBeAdded->next;                    //moves to the next element to be added to l1's copy
    }
    return addedList;
}

LLSortedPosInt  operator- (const LLSortedPosInt &l1,
                                        const LLSortedPosInt &l2)  {
    //// reclaim any storage -- do not to remove the sentinal Node
    LLSortedPosInt subtractedList(l1);                  //creates new list by copying l1
    NodePtr toBeSubtracted = l2.head->next;             //create NodePtr to walk through the list to be subtracted
    while (toBeSubtracted != nullptr) {     //repeat until at the end of l2
        subtractedList.remove(toBeSubtracted->key);     //removes l2's key from l1's copy
        toBeSubtracted = toBeSubtracted->next;          //moves to the next element to be removed from l1's copy
    }
    return subtractedList;  
}

// The following helper functions are provide to assist you in
// building the class--these helper functions are useful in
// several places among the functions you will write--take time
// to learn what they do

void LLSortedPosInt::insert(int key) {

    NodePtr npp = head;     // setup pointers to walk the list
    NodePtr npc = head->next;           
    while (npc != NULL && npc->key <= key) {// walk the list, searching until the given key value is exceeded
        npp = npc;
        npc = npc->next;
    }
    npp->next = createNode(key, npc);   // insert the new value into the list
}

// remove() removes an element from the list (if it is present)
void LLSortedPosInt::remove(int key) {
    if (key <= 0) {return;}     // negative values should not be stored in the list
    NodePtr npp = head; // setup pointers to walk the list
    NodePtr npc = head->next;
    while (npc != NULL) {
        if (npc->key == key) {      //if the key value is found
            npp->next = npc->next;  //splice this Node from the list
            delete npc;             // reclaim its storage
            break;
        }
        npp = npc;  // walk the pointers to the next Node
        npc = npc->next;
    }
}
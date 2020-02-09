#include "Hanoi.h"

#include <sstream>

using namespace std;

// TODO: Define any private helper functions you need
/* Type your code here */
string Hanoi::solveHanoi(int nDiscs, int a, int b, int c) const {
    if(nDiscs <= 0) {
        return "";
    }
    if(nDiscs == 1) {
        return to_string(a) + "->" + to_string(b) + "\n";
    }
    string tempHanoi = solveHanoi(nDiscs - 1, a, c, b);
    tempHanoi += to_string(a) + "->" + to_string(b) + "\n";
    tempHanoi += solveHanoi(nDiscs - 1, c, b, a);
    return tempHanoi;
}

// Solve the N pole, M disc Towers of Hanoi problem and return a sequence of
// moves as a string in the form:
//  # Below, A->B means 'move the top disc on pole A to pole B'
//  1->2
//  1->3
//  2->3
//  ...
// solve() always means move all discs from pole 1 to pole 2 using 3 as a temp.
string Hanoi::solve() const {
   // TODO
   /* Type your code here */
    
    return "# Below, A->B means 'move the top disc on pole A to pole B'\n" + this->solveHanoi(nDiscs, 1, 2, 3);
}

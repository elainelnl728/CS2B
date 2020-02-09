//
//  main.cpp
//  Queue
//
//  Created by Elaine on 8/3/19.
//  Copyright © 2019 Elaine. All rights reserved.
//


#include <iostream>
#include <sstream>

#include "Simulation.h"

using namespace std;

int main(int argc, const char * argv[]) {
    // Fill in reasonable values for your simulation
    int meanTimeToNextCustomer = 60 * 1;
    int meanTransactionTime = 60 * 1;
    int numCashiers = 5;
    int simDuration = 60 * 60 * 10;
    int qJoinThreshold = -1;
    
    srand((unsigned) time(0L));       // Comment out while testing
    
    Simulation sim(simDuration, numCashiers, qJoinThreshold,
                   meanTransactionTime, meanTimeToNextCustomer);
    sim.setCashierEfficiency(0, 100);
    sim.setCashierEfficiency(1, 90);
    sim.setCashierEfficiency(2, 70);
    sim.setCashierEfficiency(3, 60);
    sim.setCashierEfficiency(4, 40);
    sim.setVerbose();
    
//    sim.setQJoinThreshold(0); // Fry's style
//    stringstream ss1;
//    sim.run(ss1);
//    cout << ss1.str() <<endl;
//    cout << "------------------------------------------------------\n";
    
    sim.setQJoinThreshold(qJoinThreshold); // Walmart Style
    stringstream ss2;
    sim.run(ss2);
    cout << ss2.str() <<endl;
    cout << "------------------------------------------------------\n";

    return 0;
}


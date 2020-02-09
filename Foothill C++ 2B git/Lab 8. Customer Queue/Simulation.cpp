//
//  Simulation.cpp
//  Queue
//
//  Created by Elaine on 8/3/19.
//  Copyright © 2019 Elaine. All rights reserved.
//


#include <iostream>
#include <vector>
#include <queue>

#include "Simulation.h"

#include <random>

using namespace std;

// Global helper friend
ostream& operator<<(ostream& os, const Customer& cust) {
    // TODO - type your code here
    os << "Customer info:" << endl;
    os << "  Walk in time: " << cust.inTime << endl;
    os << "  Serving duration: " << cust.svcDuration << endl;
    return os << endl;
}

// Global helper friend. Dump simulation parameters.
ostream& operator<<(ostream& os, const Simulation& sim) {
    os
    << "Simulation properties:" << endl
    << "  Number of cashiers: " << sim.getNumCashiers() << endl
    << "  Simulation duration: " << sim.getSimDuration() << endl
    << "  Queue joining threshold: " << sim.getQJoinThreshold() << endl
    << endl
    << "  Mean time between successive customers set to: " << sim.getMeanTimeToNextCustomer() << endl
    << "  Mean customer service time set to: " << sim.getMeanSvcTime() <<endl
    ;
    
    os << "  Cashier efficiencies:";
    for (size_t n = 0; n < sim.cashiers.size(); n++)
        os << " " << sim.cashiers[n].getEfficiencyPct();
    
    return os << endl;
}

// Private helper: find the shortest queue and if its length is at most
// qJoinThreshold, return its index. Else return -1
int Simulation::findViableQueue() const {
    // TODO - type your code here
    int queueNum = -1;
    int min = -1;
    for (size_t i = 0; i < cashiers.size(); ++i) {
        if ((qJoinThreshold < 0 || (int)(cashiers[i].q.size()) <= qJoinThreshold) &&
            (min == -1 || min > (int)(cashiers[i].q.size()))) {
            min = (int)cashiers[i].q.size();
            queueNum = int(i);
        }
    }
    return queueNum;
}

// Private helper
// Return if the current wall clock reading indicates peak time. To keep the
// simulation as comprehensive as possible, we'll take the total simulation time
// and divide it up into NUM_PEAK_PERIODS chunks of time. The odd numbered chunks
// are "peak" times
bool Simulation::isPeakTime() const {
    static int numSecondsPerPeriod = simDuration/NUM_PEAK_TIMES;
    int period = wallClock / numSecondsPerPeriod;
    return (period % 2 == 0);
}

// Private helper
// During peak times, meanTimeToNextCustomer is shorter (/= PEAK_TO_NORMAL_RATIO)
int Simulation::getNextCustomerArrivalInterval(default_random_engine& gen) const {
    static double x = meanTimeToNextCustomer;
    static double peakX = meanTimeToNextCustomer/PEAK_TO_NORMAL_RATIO;
    
    static normal_distribution<double> distroEntry(x, x/2.0);
    static normal_distribution<double> distroEntryPeak(peakX, peakX/2.0);
    
    int nextAt = isPeakTime() ? distroEntryPeak(gen) : distroEntry(gen);
    
    return (nextAt >= 0 ? nextAt : 0); // Clip and return
}

// Advance the wall clock by the given number of seconds. When that happens
// both timeToNextCustomer and the individual svc times of customers
// already at a cashier will be decreased by nSecs
void Simulation::advanceWallClock(int nSecs) {
    if (verbose) cout << wallClock << ": Advancing wall clock by " << nSecs <<endl;
    
    // TODO: Type your code here
    wallClock += nSecs;
    
    if (wallClock < simDuration) {
        timeToNextCustomer -= nSecs;
        if (verbose)
            cout << wallClock << ": " << "Time to customer is now " <<timeToNextCustomer <<endl;
    }
    
    for (size_t n = 0; n < cashiers.size(); n++) {
        if (cashiers[n].q.size() > 0) {
            if (verbose)
                cout << wallClock << ": Cashier #" << n << ": " << cashiers[n].q.front();
            cashiers[n].q.front().svcDuration -= nSecs;
            if (verbose) cout  << " updated to " << cashiers[n].q.front() <<endl;
        }
    }
}

// ---- Public API ------------------------------------------

Simulation::Simulation(int theSimDuration, int theNumCashiers,
                       int theQJoinThreshold, int theMeanSvcTime,
                       int theMeanTimeToNextCustomer) {
    
    // Silently default to sensible values in the ctr
    setSimDuration(theSimDuration);
    setNumCashiers(theNumCashiers);
    setQJoinThreshold(theQJoinThreshold);
    setMeanSvcTime(theMeanSvcTime);
    setMeanTimeToNextCustomer(theMeanTimeToNextCustomer);
    
    cashiers.resize(numCashiers);
}

bool Simulation::setSimDuration(int n) {
    // TODO - type your code here
    if (n <= 0) {
        simDuration = DEFAULT_SIM_DURATION;
        return false;
    }
    simDuration = n;
    return true;
}

bool Simulation::setNumCashiers(int n) {
    // TODO - type your code here
    if (n <= 0) {
        numCashiers = DEFAULT_NUM_CASHIERS;
        return false;
    }
    numCashiers = n;
//    cashiers = std::vector<Cashier>(n, Cashier());
    cashiers.resize(numCashiers);
    
    return true;
}

// 0 represents case 2, -1 represents case 1.
bool Simulation::setQJoinThreshold(int n) {
    if (n < -1) {
        qJoinThreshold = 0; // Case 2 (Fry's style)
        return false;
    }
    qJoinThreshold = n;
    return true;
}

bool Simulation::setMeanSvcTime(int n) {
    // TODO - type your code here
    if (n < MIN_MEAN_SVC_TIME) {
        meanSvcTime = MIN_MEAN_SVC_TIME;
        return false;
    }
    meanSvcTime = n;
    return true;
}

bool Simulation::setMeanTimeToNextCustomer(int n) {
    // TODO - type your code here
    if (n < MIN_MEAN_TIME_TO_NEXT_CUSTOMER) {
        meanTimeToNextCustomer = MIN_MEAN_TIME_TO_NEXT_CUSTOMER;
        return false;
    }
    meanTimeToNextCustomer = n;
    return true;
}

bool Simulation::setCashierEfficiency(size_t n, int eff) {
    // TODO - type your code here
    if (n >= cashiers.size()) {
        return false;
    }
    return cashiers[n].setEfficiencyPct(eff);
}

// TODO: Complete this function in your own way if you like. I won't be testing it this week, but
// it must be a compiling stub. It shouldn't break my compilation of your code. Next week, you will
// have my model solution which you can use to flesh this method out, if you didn't do so yourself.
// Individual TODO points have been marked with TODO below
void Simulation::run(ostream& os) {
    unsigned long numCustomers = 0, numCustomersProcessed = 0;
    unsigned long totalCustomerTime = 0;
    
    // You're free to ignore the next three lines - It is a way to generate
    // random numbers that are Normally distributed (like in real life)
    // instead of uniformly (which is what rand() provides)
    unsigned seed = (unsigned)(time(0L));  // 10; // I'll use a diff value when testing
    
    default_random_engine generator(seed);
    normal_distribution<double> distroSvc(meanSvcTime, meanSvcTime/2.0);
    
    // We will increment wallClock and stop the simulation when it rolls past
    // simDuration secs.
    this->wallClock = 0;
    
    // All cashier queues start off at length 0
    cashiers.resize(numCashiers);
    
    // The next customer will arrive in this many seconds
    timeToNextCustomer = getNextCustomerArrivalInterval(generator);
    
    if (verbose)
        cout << wallClock << ": Next customer will arrive in " << timeToNextCustomer <<endl;
    
    // We loop until the global queue has been emptied. When wallClock >
    // simDuration, new user creation (and enqueueing) will stop, and so
    // at some finite time after that the global queue will deplete to 0.
    while(wallClock < simDuration || numCustomersProcessed < numCustomers) {
        if (verbose) {
            cout << "--- TOP OF LOOP : " << (isPeakTime() ? "PEAK TIME" : "OFF-PEAK TIME")
            << " ---------------------------------------------------------\n";
        }
        // At the beginning of each iteration, move as many customers as
        // possible from the global queue into the cashier queues. Typically
        // this will move no more than 1 customer.
        while (globalQueue.size() > 0) {
            int n = findViableQueue();
            if (n < 0) // No viable queues
                break;
            if (verbose) {
                cout << wallClock << ": " << globalQueue.front()
                << " joined cashier #" << n << " at pos #" << cashiers[n].q.size() <<endl;
            }
            // Update the customer record with the actual service duration
            // which we now know because we know the cashier's efficiency.
            globalQueue.front().svcDuration *= 100;
            globalQueue.front().svcDuration /= cashiers[n].getEfficiencyPct();
            cashiers[n].q.push(globalQueue.front());
            globalQueue.pop();
        }
        
        // Is the next event a customer arrival or exit? Let's find out.
        // Determine the shortest svc time of all the non-empty cashier queues
        int minSvcDur = std::numeric_limits<int>::max();
        size_t cNdx = 0;
        for (size_t n = 0; n < cashiers.size(); n++) {
            if (cashiers[n].q.size() == 0) continue;
            if (cashiers[n].q.front().svcDuration < minSvcDur) {
                minSvcDur = cashiers[n].q.front().svcDuration;
                cNdx = n; // remember the first cashier to become free
            }
        }
        if (minSvcDur < timeToNextCustomer || wallClock > simDuration) {
            if (verbose)
                cout << wallClock << ": CHECKOUT " << cashiers[cNdx].q.front() << endl;
            advanceWallClock(minSvcDur);
            totalCustomerTime += (wallClock - cashiers[cNdx].q.front().inTime);
            cashiers[cNdx].q.pop();
            ++numCustomersProcessed;
        } else {
            if (verbose) cout << wallClock << ": ENTRY" << endl;
            advanceWallClock(timeToNextCustomer);
            // Add the new customer to global queue, but don't create a
            // new customer if the simulation has ended (Still need to empty
            // the queue of existing customers)
            if (wallClock < simDuration) {
                int svcTime = distroSvc(generator);
                if (svcTime < 0) svcTime = 0; // Clip
                globalQueue.push(Customer(svcTime, wallClock));
                ++numCustomers;
                // Set the time the next customer will arrive
                timeToNextCustomer = getNextCustomerArrivalInterval(generator);
                
                if (verbose) {
                    cout << wallClock << ": " << globalQueue.back() << " joined global queue" << endl;
                    if (wallClock < simDuration)
                        cout << "\tNext customer will arrive in " << timeToNextCustomer <<endl;
                } }
        }
        
        if (verbose) {
            cout << "\tGlobal queue length = " << globalQueue.size() <<endl;
            cout << "\tNum customers: " << numCustomers << " (" << numCustomersProcessed << "processed)\n";
            cout << "\tCashier queue lengths:";
            for (size_t n = 0; n < cashiers.size(); n++) cout << " " << cashiers[n].q.size();
            cout << endl;
        }
    }
    os << *this << "\n\n"
    << "Final wall clock reading: " <<wallClock << endl
    <<"Total number of customers served: " << numCustomers <<endl
    <<"Total customer time: " << totalCustomerTime <<endl
    <<"Average wait time per customer: " << totalCustomerTime / numCustomers <<endl;
}

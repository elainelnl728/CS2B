//
//  Automaton.cpp
//  Cellular Automaton
//
//  Created by Elaine Lu on 7/21/19.
//  Copyright © 2019 Elaine. All rights reserved.
//

#include "Automaton.h"

#include <stdio.h>

constexpr int On = 1;
constexpr int Off = 0;
constexpr int ruleSize = 8;

Automaton::Automaton(int rule) {
    this->displayWidth = DEFAULT_DISPLAY_WIDTH;
    // Initialize rule.
    setRule(rule);
    
    this->extremeBit = Off;
    resetToFirstGen();
}

bool Automaton::setDisplayWidth(int width) {
    if (width % 2 == 0) {
        return false;
    }
    if (width < 1) {
        this->displayWidth = 1;
        return false;
    }
    if (width > MAX_DISPLAY_WIDTH) {
        this->displayWidth = MAX_DISPLAY_WIDTH;
        return false;
    }
    this->displayWidth = width;
    return true;
}

bool Automaton::setRule(int rule) {
    if (rule < MIN_RULE || rule > MAX_RULE) {
        return false;
    }
    int mask = 1;  // 0000 0001
    for (int i = 0; i < 8; ++i) {
        this->rules[i] = (rule & mask) > 0?true:false;
        mask = mask << 1;
    }
    return true;
}

void Automaton::resetToFirstGen() {
    long int max_size = 10000;
    if (max_size % 2 == 0) {
        max_size -= 1;
    }
    this->thisGen = vector<int>(max_size, Off);
    this->thisGen[max_size / 2] = On;
}

void Automaton::propagateNewGen() {
    int preCell = this->extremeBit;
    for (int i = 0; i < int(this->thisGen.size()); ++i) {
        int parent = 0;
        // Rightmost cell.
        if (i == int(this->thisGen.size()) - 1) {
            parent = (preCell << 2) | (this->thisGen[i] << 1) | (this->extremeBit);
        } else {
            parent = (preCell << 2) | (this->thisGen[i] << 1) | (this->thisGen[i + 1]);
        }
        // Update cell.
        preCell = this->thisGen[i];
        this->thisGen[i] = this->rules[parent]? On : Off;
    }
    // Update extreme bit.
    int parentExtremeBit = (preCell << 2) | (this->extremeBit << 1) | (this->extremeBit);
    this->extremeBit = this->rules[parentExtremeBit]? On : Off;
}

string Automaton::toStringCurrentGen(char charFor0, char charFor1) const {
    string generation = "";
    int array_size = int(this->thisGen.size());
    for (int i = (array_size - this->displayWidth) / 2; i < (array_size - this->displayWidth) / 2 + this->displayWidth; ++i) {
        generation.push_back(this->thisGen[i] == On?charFor1:charFor0);
    }
    return generation;
}

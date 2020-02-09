//
//  main.cpp
//  Screen Tester
//
//  Created by Anand Venkataraman on 1/2/19.
//  Copyright © 2019 Anand Venkataraman. All rights reserved.
//  This file won't be tested by me
//

#include <iostream>

using namespace std;

#include "Shapes.h"

int main(int argc, const char * argv[]) {
    Screen scr(100, 100);
    StickMan obj;
    
    StickMan stickMan(96,10, 4,1);
    stickMan.draw(scr, '*');
    
    cout <<"Screen:\n" <<scr <<endl;
    
    return 0;
}

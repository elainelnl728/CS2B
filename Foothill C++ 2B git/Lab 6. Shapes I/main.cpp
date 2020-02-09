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
    
    Line line1(22,180, 47,11); line1.draw(scr);
//    Line line1(10,0, 5,5); line1.draw(scr);
//    Line line2(5,5, 15,15); line2.draw(scr);
//    Line line3(15,15, 20,11); line3.draw(scr);
//    Line line4(20,11, 20,29); line4.draw(scr);
//    Line line5(20,29, 30,6); line5.draw(scr);
//
//    Line line6(90,20, 40,0); line6.draw(scr);
//
//    Line(0,0, 10,0).draw(scr);
    
    cout <<"Screen:\n" <<scr <<endl;
    
    return 0;
}

//
//  Shapes.cpp
//  Screen
//
//  Created by Anand Venkataraman on 1/5/19.
//  Copyright © 2019 Anand Venkataraman. All rights reserved.
//
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

#include "Shapes.h"

// --------- Screen methods -----------------------------
Screen::Screen(int w, int h) : width(w), height(h) {
    // TODO - Complete this Constructor
    /* Type your code here */
    for (int i = 0; i < height; ++i) {
        pixels.push_back(vector<char>(width, '.'));
    }
}

void Screen::fill(char ch) {
    // TODO - Complete this method
    /* Type your code here */
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            pixels[i][j] = ch;
        }
    }
}

// Output the screen on the given stream.
ostream& operator<<(ostream& os, const Screen& scr) {
    // TODO - Complete this function
    /* Type your code here */
    for (int i = scr.height - 1; i >= 0; --i) {
        for (int j = 0; j < scr.width; ++j) {
            cout << scr.pixels[i][j];
        }
        cout << endl;
    }
    return os;
}

string Screen::toString() const {
    string output;
    for (int i = height - 1; i >= 0; --i) {
        for (int j = 0; j < width; ++j) {
            output.push_back(pixels[i][j]);
        }
        output.push_back('\n');
    }
    return output;
}
// --------- Point methods -----------------------------

// @override virtual shape method - Public API call.
bool Point::draw(Screen& scr, char ch) {
    // TODO - Complete this method
    /* Type your code here */
    return scr.setPixel(x, y, ch);
}

// --------- Line methods -----------------------------

// TODO - Private helpers. Implement as necessary

/* Type your code here */


// @override virtual shape method - Public API call.
// Draw this line on the given screen. Always draw left to right,
// and bottom to top if vertical. Use the supplied char ch as the
// pixel char
bool drawLine(int x_from, int y_from, int x_to, int y_to, Screen& scr, char ch) {
    bool status = true;
    if (abs(y_to - y_from) >= abs(x_to - x_from)) {
        int sign = y_from < y_to?1:-1;
        int dy = sign;
        double dx = dy * (double)(x_to - x_from) / (double)(y_to - y_from);
        double x = x_from;
        for (int y = y_from; sign * y <= sign * y_to; y += dy, x += dx) {
            status = scr.setPixel((int)x, (int)y, ch) && status;
        }
    } else {
        int sign = x_from < x_to?1:-1;
        int dx = sign;
        double dy = dx * (double)(y_to - y_from) / (double)(x_to - x_from);
        double y = y_from;
        for (int x = x_from; sign * x <= sign * x_to; x += dx, y += dy) {
            status = scr.setPixel((int)x, (int)y, ch) && status;
        }
    }
    return status;
}

bool Line::draw(Screen& scr, char ch) {
    // TODO: Complete this method
    /* Type your code here */
    if (x1 == x2 && y1 == y2) {
        return scr.setPixel(x1, y1, ch);
    }

    if (x2 > x1 || (x2 == x1 && y2 > y1)) {
        return drawLine(x1, y1, x2, y2, scr, ch);
    }
    return drawLine(x2, y2, x1, y1, scr, ch);
}


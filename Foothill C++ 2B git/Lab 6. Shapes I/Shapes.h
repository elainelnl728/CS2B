//
//  Shapes.h
//  Project name: Screen
//
//  Created by Anand Venkataraman on 1/3/19.
//  Copyright © 2019 Anand Venkataraman. All rights reserved.
//
// A Screen object and various shapes that can be drawn on it. Search for
// TODO items below and complete the open tasks.

#ifndef Shapes_h
#define Shapes_h

#include <iostream>
#include <vector>

// -------------- Screen -------------------
// A virtual screen with pixels x: 0-(w-1) and y: 0-(h-1)
// NOTE: (0,0) is the bottom left - Pixels can be any character, determined
// by each Point.

class Screen {
    friend class Shape;
    
private:
    int width, height;
    std::vector<std::vector<char>> pixels;
    
public:
    static const char DEFAULT_FG_CH = '*', DEFAULT_BG_CH = '.';
    
    Screen(int w = 100, int h = 100);
    
    // TODO
    /* Type your code here */
    std::vector<std::vector<char>>& getPixels() {
        return pixels;
    }
    bool setPixel(int x, int y, char ch) {
        if (x < width && y < height) {
            pixels[y][x] = ch;
            return true;
        }
        return false;
    }
    
    void clear() { fill(DEFAULT_BG_CH);}
    void fill(char c);
    string toString() const;
    
    friend std::ostream& operator<<(std::ostream& os, const Screen& scr);
};

// --------- Shape ---------------------------------

// Base class for Point, Line, etc.
// Abstract.
class Shape {
private:
    // empty
    
public:
    // TODO
    /* Type your code here */
    virtual bool draw(Screen& scr, char ch = Screen::DEFAULT_FG_CH) = 0;
};

// --------- Point ---------------------------------
class Point : public Shape {
private:
    int x, y;
    
public:
    Point(int x1, int y1) : x(x1), y(y1) {}
    // TODO
    /* Type your code here */
    bool draw(Screen& scr, char ch = Screen::DEFAULT_FG_CH) override;
};

// ----------- Line --------------------------------
// Line in two point notation
class Line : public Shape {
private:
    int x1, y1, x2, y2;
    
    // Helpers
    // TODO
    /* Type your code here */
    
public:
    // TODO
    /* Type your code here */
    Line(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
    bool draw(Screen& scr, char ch = Screen::DEFAULT_FG_CH) override;
};

#endif /* Shape_h */


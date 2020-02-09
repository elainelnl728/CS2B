//
//  Shape2.h
//  Shape2
//
//  Created by Elaine on 8/3/19.
//  Copyright © 2019 Elaine. All rights reserved.
//

#ifndef Shape2_h
#define Shape2_h

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
    virtual bool draw(Screen& scr, char ch = Screen::DEFAULT_FG_CH) const = 0;
    virtual ~Shape() {}
};

// --------- Point ---------------------------------
class Point : public Shape {
private:
    int x, y;
    
public:
    Point(int x1, int y1) : x(x1), y(y1) {}
    // TODO
    /* Type your code here */
    bool draw(Screen& scr, char ch = Screen::DEFAULT_FG_CH) const override;
    ~Point() {}
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
    bool draw(Screen& scr, char ch = Screen::DEFAULT_FG_CH) const override;
    ~Line() {}
};


// TODO - Import, and adapt as necessary, your code from the previous lab
// Enter your code here

// ----------- Quadrilateral -----------------
// A general quadrilateral with points (x1,y1) ... (x4,y4), clockwise
// from bottom left. Don't do sophisticated checks to make sure the points
// form a single closed shape.

// TODO - Complete this class
// Type your code here

class Quadrilateral : public Shape {
public:
    Quadrilateral(int x1, int y1, int x2, int y2,
                  int x3, int y3, int x4, int y4) : x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3), x4(x4), y4(y4) {}
    ~Quadrilateral() {};
    bool draw(Screen& scr, char ch = Screen::DEFAULT_FG_CH) const override;
    
private:
    int x1, y1, x2, y2, x3, y3, x4, y4;
};

// ----------- UprightRectangle, a special Quadrilateral -----------------

// An UprightRectangle is a special upright Quadrilateral so we don't have to
// parameterize the constructor with a ton of numbers

class UprightRectangle : public Quadrilateral {
public:
    UprightRectangle(int x1, int y1, int x2, int y2) : Quadrilateral(x1, y1, x1, y2, x2, y2, x2, y1) {}
    ~UprightRectangle() {}
};

// TODO - Complete this class
// Type your code here

// ----------- StickMan, a composite Shape -----------------

class StickMan : public Shape {
public:
    static const int DEFAULT_W = 20, DEFAULT_H = 40;
    // TODO - Complete this class
    // Type your code here
    StickMan() : x(0), y(0), w(DEFAULT_W), h(DEFAULT_H) {}
    
    StickMan(int x, int y, int w = DEFAULT_W, int h = DEFAULT_H) : x(x), y(y), w(w), h(h) {
        if (w <= 1) {
            this->w = DEFAULT_W;
        }
        if (h <= 1) {
            this->h = DEFAULT_H;
        }
        
        // Head.
        parts.push_back(new UprightRectangle(x, y + this->h / 2, x + this->w - 1, y + this->h - 1));
        // Torso.
        parts.push_back(new Line(x + this->w / 2, y + this->h / 4, x + this->w / 2, y + this->h / 2));
        // Legs.
        parts.push_back(new Line(x, y, x + this->w / 2, y + this->h / 4));
        parts.push_back(new Line(x + this->w / 2, y + this->h / 4, x + this->w - 1, y));
        // Arms
        parts.push_back(new Line(x + this->w / 4, y + this->h / 4, x + this->w / 2, y + this->h / 2));
        parts.push_back(new Line(x + this->w / 2, y + this->h / 2, x + 3 * this->w / 4, y + this->h / 4));
    }

    ~StickMan() {
        for (Shape* ptr : parts) {
            delete ptr;
        }
    }
    
    bool draw(Screen& scr, char ch = Screen::DEFAULT_FG_CH) const override;
    const std::vector<Shape *>& getParts() const;
    
private:
    int x, y, w, h;
    std::vector<Shape*> parts;
};



#endif /* Shape2_h */

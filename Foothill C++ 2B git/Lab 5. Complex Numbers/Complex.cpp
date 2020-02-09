#include "Complex.h"
#include <stdio.h>
using namespace std;

// TODO: Type your code here

namespace {
    string removeTrailingZero(string str) {
        while (!str.empty() && str.back() == '0') {
            str.pop_back();
        }
        if (str.back() == '.') {
            str.pop_back();
        }
        return str;
    }
}

string Complex::toString() const {
    string real = to_string(this->real);
    string imag = to_string(this->imag);
    return "(" + removeTrailingZero(real) + ", " + removeTrailingZero(imag) + ")";
}

double Complex::norm() const {
    return this->real * this->real + this->imag * this->imag;
}

Complex Complex::reciprocal() const {
    const double currNorm = this->norm();
    if (currNorm < 1e-10) {
        throw DivByZeroException();
    }
    return Complex(this->real/currNorm, -this->imag/currNorm);
}

const Complex& Complex::operator=(const Complex& rhs) {
    this->real = rhs.real;
    this->imag = rhs.imag;
    return *this;
}

string Complex::DivByZeroException::toString() {
    return "Divide by zero exception";
}
string Complex::DivByZeroException::what() {
    return toString();
}

// operators (the first one's signature is below for reference)
Complex operator+(const Complex& a, const Complex& b) {
    return Complex(a.real + b.real, a.imag + b.imag);
}
Complex operator-(const Complex& a, const Complex& b) {
    return Complex(a.real - b.real, a.imag - b.imag);
}
Complex operator*(const Complex& a, const Complex& b) {
    return Complex(a.real * b.real - a.imag * b.imag, a.real * b.imag + b.real * a.imag);
}
Complex operator/(const Complex& a, const Complex& b) {
    return a * b.reciprocal();
}
bool operator<(const Complex& a, const Complex& b) {
    return a.norm() < b.norm();
}
bool operator==(const Complex& a, const Complex& b) {
    return a.norm() == b.norm();
}
ostream& operator<<(ostream& os, const Complex& a) {
    os << a.toString();
    return os;
}


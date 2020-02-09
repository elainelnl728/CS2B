#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <stack>
using namespace std;

class Complex {
private:
      double real, imag;
      
public:
   // TODO: Type your code here;
    Complex() : real(0), imag(0) {}
    Complex(double realNum, double imagNum=0.0) : real(realNum), imag(imagNum) {}
    
    const Complex& operator=(const Complex& rhs);
    template <typename T>
    const Complex& operator=(const T rhs);

    double getReal() const { return this->real; }
    double getImag() const { return this->imag; }
    void setReal(const double real) { this->real = real; }
    void setImag(const double imag) { this->imag = imag; }
    
    string toString() const;
    double norm() const;
    Complex reciprocal() const;
    
    class DivByZeroException {
        public:
        // TODO: Type your code here
        string toString();
        string what();
    };
    
    // operators (the first one's signature is below for reference)
    friend Complex operator+(const Complex& a, const Complex& b);
    template <typename T>
    friend Complex operator+(const Complex& a, const T b);
    template <typename T>
    friend Complex operator+(const T a, const Complex& b);
    
    // TODO: Type your code here
    friend Complex operator-(const Complex& a, const Complex& b);
    template <typename T>
    friend Complex operator-(const Complex& a, const T b);
    template <typename T>
    friend Complex operator-(const T a, const Complex& b);
    
    friend Complex operator*(const Complex& a, const Complex& b);
    template <typename T>
    friend Complex operator*(const Complex& a, const T b);
    template <typename T>
    friend Complex operator*(const T a, const Complex& b);
    
    friend Complex operator/(const Complex& a, const Complex& b);
    template <typename T>
    friend Complex operator/(const Complex& a, const T b);
    template <typename T>
    friend Complex operator/(const T a, const Complex& b);
    
    friend bool operator<(const Complex& a, const Complex& b);
    friend bool operator==(const Complex& a, const Complex& b);
    friend ostream& operator<<(ostream& os, const Complex& a);
};

// Templates.
template <typename T>
const Complex& Complex::operator=(const T rhs) {
    this->real = rhs;
    this->imag = 0.0;
    return * this;
}

template <typename T>
Complex operator+(const Complex& a, const T b) {
    return Complex(a.real + b, a.imag);
}
template <typename T>
Complex operator+(const T a, const Complex& b) {
    return Complex(a + b.real, b.imag);
}

template <typename T>
Complex operator-(const Complex& a, const T b) {
    return Complex(a.real - b, a.imag);
}
template <typename T>
Complex operator-(const T a, const Complex& b) {
    return Complex(a - b.real, -b.imag);
}

template <typename T>
Complex operator*(const Complex& a, const T b) {
    return Complex(a.real * b, a.imag * b);
}
template <typename T>
Complex operator*(const T a, const Complex& b) {
    return Complex(a * b.real, a * b.imag);
}

template <typename T>
Complex operator/(const Complex& a, const T b) {
    return Complex(a.real / b, a.imag / b);
}
template <typename T>
Complex operator/(const T a, const Complex& b) {
    return a * b.reciprocal();
}


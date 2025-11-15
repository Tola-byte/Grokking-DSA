#include <iostream>
#include <string>

/*
OPERATOR OVERLOADING - COMPLETE GUIDE
=====================================

WHAT IS OPERATOR OVERLOADING?
- Allows you to define how operators work with your custom types
- Makes your classes behave like built-in types
- Can overload most operators (+, -, *, /, ==, !=, <, >, [], (), etc.)

RULES:
1. Cannot create new operators (only overload existing ones)
2. Cannot change operator precedence or associativity
3. Cannot change number of operands (binary operators stay binary)
4. Some operators must be member functions, others can be free functions
5. Some operators come in pairs (== and !=, < and >, etc.)

TYPES OF OPERATORS:
1. Arithmetic: +, -, *, /, %
2. Assignment: =, +=, -=, *=, /=
3. Comparison: ==, !=, <, >, <=, >=
4. Logical: &&, ||, !
5. Bitwise: &, |, ^, ~, <<, >>
6. Unary: +, -, ++, --
7. Subscript: []
8. Function call: ()
9. Stream: <<, >>
10. Memory: new, delete

MEMBER vs FREE FUNCTIONS:
- Member functions: have access to private members
- Free functions: need to be friends or use public interface
- Some operators MUST be member functions: =, [], (), ->
- Stream operators are usually free functions (friend functions)
*/

class Complex {
private:
    double real, imag;

public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
    // ARITHMETIC OPERATORS (Binary operators)
    // - Return new object (don't modify this object)
    // - const member functions (don't modify this object)
    // - Called when: c1 + c2, c1 - c2, c1 * c2
    
    // Addition operator: c1 + c2
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    
    // Subtraction operator: c1 - c2
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }
    
    // Multiplication operator: c1 * c2
    // Formula: (a+bi)(c+di) = (ac-bd) + (ad+bc)i
    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag,
                      real * other.imag + imag * other.real);
    }
    
    // ASSIGNMENT OPERATORS (Compound assignment)
    // - Modify this object and return reference to this
    // - Called when: c1 += c2, c1 -= c2
    // - More efficient than c1 = c1 + c2 (avoids temporary object)
    
    // Compound addition: c1 += c2
    Complex& operator+=(const Complex& other) {
        real += other.real;
        imag += other.imag;
        return *this;  // Return reference for chaining
    }
    
    // Assignment operator: c1 = c2
    // - Must be member function
    // - Handle self-assignment
    // - Return reference for chaining
    Complex& operator=(const Complex& other) {
        if (this != &other) {  // Self-assignment check
            real = other.real;
            imag = other.imag;
        }
        return *this;
    }
    
    // COMPARISON OPERATORS
    // - Return bool
    // - const member functions
    // - Usually come in pairs (== and !=, < and >)
    
    // Equality operator: c1 == c2
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }
    
    // Inequality operator: c1 != c2
    // - Can be implemented as !(c1 == c2) or separately
    bool operator!=(const Complex& other) const {
        return !(*this == other);  // Reuse == operator
    }
    
    // STREAM OPERATORS (Friend functions)
    // - Must be free functions (not member functions)
    // - Need friend access to private members
    // - Return reference to stream for chaining
    
    // Output operator: cout << c
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real;
        if (c.imag >= 0) os << "+";
        os << c.imag << "i";
        return os;  // Return stream reference for chaining
    }
    
    // Input operator: cin >> c
    friend std::istream& operator>>(std::istream& is, Complex& c) {
        std::cout << "Enter real part: ";
        is >> c.real;
        std::cout << "Enter imaginary part: ";
        is >> c.imag;
        return is;  // Return stream reference for chaining
    }
    
    // UNARY OPERATORS
    // - Operate on single operand (this object)
    // - Return new object (don't modify this)
    
    // Unary minus: -c
    Complex operator-() const {
        return Complex(-real, -imag);
    }
    
    // PRE-INCREMENT: ++c (modify then return)
    Complex& operator++() {
        ++real;  // Increment real part
        return *this;  // Return reference to modified object
    }
    
    // POST-INCREMENT: c++ (return copy then modify)
    // - int parameter distinguishes from pre-increment
    // - Parameter is not used, just for distinction
    Complex operator++(int) {
        Complex temp = *this;  // Save current value
        ++real;  // Increment real part
        return temp;  // Return old value
    }
    
    // FUNCTION CALL OPERATOR (Functor)
    // - Makes object callable like a function
    // - Can have any number of parameters
    // - Called when: c() or c(1, 2, 3)
    // - Returns magnitude squared of complex number
    double operator()() const {
        return real * real + imag * imag;  // magnitude squared
    }
    
    // SUBSCRIPT OPERATOR
    // - Must be member function
    // - Allows array-like access: c[0] = real, c[1] = imag
    // - Return reference to allow modification
    double& operator[](int index) {
        return index == 0 ? real : imag;
    }
    
    // Const version for const objects
    const double& operator[](int index) const {
        return index == 0 ? real : imag;
    }
};

int main() {
    Complex c1(3, 4);
    Complex c2(1, 2);
    
    std::cout << "c1 = " << c1 << std::endl;
    std::cout << "c2 = " << c2 << std::endl;
    
    // Arithmetic operations
    Complex c3 = c1 + c2;
    std::cout << "c1 + c2 = " << c3 << std::endl;
    
    Complex c4 = c1 - c2;
    std::cout << "c1 - c2 = " << c4 << std::endl;
    
    Complex c5 = c1 * c2;
    std::cout << "c1 * c2 = " << c5 << std::endl;
    
    // Assignment
    c1 += c2;
    std::cout << "c1 after += c2: " << c1 << std::endl;
    
    // Comparison
    std::cout << "c1 == c2: " << (c1 == c2) << std::endl;
    
    // Unary operators
    std::cout << "-c2 = " << (-c2) << std::endl;
    
    // Increment
    std::cout << "++c2 = " << (++c2) << std::endl;
    std::cout << "c2++ = " << (c2++) << std::endl;
    
    // Function call operator
    std::cout << "Magnitude squared of c1: " << c1() << std::endl;
    
    // Subscript operator
    std::cout << "c1[0] = " << c1[0] << ", c1[1] = " << c1[1] << std::endl;
    
    return 0;
}

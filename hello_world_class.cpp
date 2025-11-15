#include <iostream>
#include <string>

/*
HELLO WORLD CLASS - Practical C++ Exercise
==========================================

FEATURES DEMONSTRATED:
1. Constructor with parameters
2. Operator overloading (<<)
3. Member functions
4. const correctness
5. Friend functions for stream operators
*/

class HelloWorld {
private:
    unsigned int repeatCount;
    std::string message;

public:
    // PARAMETERIZED CONSTRUCTOR
    // Takes unsigned int for repeat count and string for message
    HelloWorld(unsigned int count, const std::string& msg) 
        : repeatCount(count), message(msg) {
        std::cout << "HelloWorld object created\n";
    }

    // DEFAULT CONSTRUCTOR
    HelloWorld() : repeatCount(1), message("Hello World") {
        std::cout << "HelloWorld object created with defaults\n";
    }

    // COPY CONSTRUCTOR
    HelloWorld(const HelloWorld& other) 
        : repeatCount(other.repeatCount), message(other.message) {
        std::cout << "HelloWorld copy constructor called\n";
    }

    // DESTRUCTOR
    ~HelloWorld() {
        std::cout << "HelloWorld object destroyed\n";
    }

    // STREAM OUTPUT OPERATOR (<<)
    // Allows: cout << helloWorldObject;
    // Must be friend function to access private members
    friend std::ostream& operator<<(std::ostream& os, const HelloWorld& hw) {
        for (unsigned int i = 0; i < hw.repeatCount; ++i) {
            os << hw.message;
            if (i < hw.repeatCount - 1) {
                os << " ";  // Add space between repetitions
            }
        }
        return os;
    }

    // GETTER METHODS
    unsigned int getRepeatCount() const {
        return repeatCount;
    }

    std::string getMessage() const {
        return message;
    }

    // SETTER METHODS
    void setRepeatCount(unsigned int count) {
        repeatCount = count;
    }

    void setMessage(const std::string& msg) {
        message = msg;
    }

    // MEMBER FUNCTION to print
    void print() const {
        for (unsigned int i = 0; i < repeatCount; ++i) {
            std::cout << message;
            if (i < repeatCount - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    // OPERATOR OVERLOADING: Addition
    // Combines two HelloWorld objects
    HelloWorld operator+(const HelloWorld& other) const {
        return HelloWorld(repeatCount + other.repeatCount, 
                         message + " " + other.message);
    }

    // OPERATOR OVERLOADING: Multiplication
    // Multiplies repeat count
    HelloWorld operator*(unsigned int multiplier) const {
        return HelloWorld(repeatCount * multiplier, message);
    }

    // COMPARISON OPERATORS
    bool operator==(const HelloWorld& other) const {
        return repeatCount == other.repeatCount && message == other.message;
    }

    bool operator!=(const HelloWorld& other) const {
        return !(*this == other);
    }
};

int main() {
    std::cout << "=== HelloWorld Class Demo ===\n\n";

    // Create HelloWorld object with 3 repetitions of "Hello"
    HelloWorld hw1(3, "Hello");
    std::cout << "hw1: " << hw1 << std::endl;

    // Create HelloWorld object with 5 repetitions of "C++"
    HelloWorld hw2(5, "C++");
    std::cout << "hw2: " << hw2 << std::endl;

    // Using default constructor
    HelloWorld hw3;
    std::cout << "hw3 (default): " << hw3 << std::endl;

    // Using member function to print
    std::cout << "\nUsing print() method:\n";
    hw1.print();

    // Operator overloading examples
    std::cout << "\n=== Operator Overloading ===\n";
    
    // Addition
    HelloWorld hw4 = hw1 + hw2;
    std::cout << "hw1 + hw2: " << hw4 << std::endl;

    // Multiplication
    HelloWorld hw5 = hw1 * 2;
    std::cout << "hw1 * 2: " << hw5 << std::endl;

    // Comparison
    HelloWorld hw6(3, "Hello");
    std::cout << "\nhw1 == hw6: " << (hw1 == hw6 ? "true" : "false") << std::endl;
    std::cout << "hw1 == hw2: " << (hw1 == hw2 ? "true" : "false") << std::endl;

    // Using setters
    std::cout << "\n=== Using Setters ===\n";
    hw3.setRepeatCount(4);
    hw3.setMessage("Mako");
    std::cout << "hw3 after setters: " << hw3 << std::endl;

    // Copy constructor
    std::cout << "\n=== Copy Constructor ===\n";
    HelloWorld hw7 = hw1;
    std::cout << "hw7 (copy of hw1): " << hw7 << std::endl;

    std::cout << "\n=== End of Demo ===\n";
    return 0;
}



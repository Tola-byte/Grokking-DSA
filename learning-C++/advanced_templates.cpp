#include <iostream>
#include <vector>
#include <string>

/*
TEMPLATES - COMPLETE GUIDE
==========================

WHAT ARE TEMPLATES?
- Generic programming feature that allows code to work with different types, 
-more like blue-prints that takes in different types and generates code for each type. Happens at compile time.
- Zero runtime overhead
- Type safety, compiler checks types at compile time.
- Performance, no runtime overhead.
- Code reuse, write once, use with many types.


TYPES OF TEMPLATES:
1. Function Templates: Generic functions that work with any type
2. Class Templates: Generic classes that work with any type
3. Template Specialization: Special behavior for specific types
4. Variadic Templates: Templates with variable number of parameters

DISADVANTAGES:
- Compile time: Templates increase compilation time
- Code bloat: Each type generates separate code
- Error messages: Template errors can be cryptic
- Debugging: Harder to debug template code

TEMPLATE SYNTAX:
- template <typename T> or template <class T>
- typename and class are equivalent in template parameters
- T is a placeholder for the actual type
- Can have multiple template parameters: template <typename T, typename U>
*/

// FUNCTION TEMPLATE
// - Generic function that works with any type
// - Compiler generates specific version for each type used
template <typename T>
T max_of(T x, T y) {
    return x > y ? x : y;
}

// CLASS TEMPLATE
// - Generic class that works with any type
// - All member functions are implicitly templates
// - Must specify type when creating objects: Stack<int> myStack;
template <typename T>
class Stack {
private:
    std::vector<T> elements;  // Container to store elements

public:
    // Push element onto stack
    void push(const T& element) {
        elements.push_back(element);
    }
    
    // Pop element from stack

    void pop(){
        if(!elements.empty()){
            elements.pop_back()
        }
        throw std::error("Stack is empty");
    }
    // get top element

    T top() const {
        if(!elements.empty()){
            elements.back()
        }
    }
    // check if stack is empty
    bool empty() const {
        if(elements.empty()){
            return true;
        }
        return false;
    }
    // get stack size
    size_t size() const {
        return elements.size();
    }
};

// TEMPLATE SPECIALIZATION
// - Special behavior for specific types
// - Override generic template for specific type
// - template <> indicates full specialization
// - This version has special behavior for std::string
template <>
class Stack<std::string> {
private:
    std::vector<std::string> elements;

public:
    // Special push with logging for strings
    void push(const std::string& element) {
        elements.push_back(element);
        std::cout << "String pushed: " << element << std::endl;
    }
    
    // Special pop with logging for strings
    void pop() {
        if (!elements.empty()) {
            std::cout << "String popped: " << elements.back() << std::endl;
            elements.pop_back();
        }
    }
    
    std::string top() const {
        if (!elements.empty()) {
            return elements.back();
        }
        throw std::runtime_error("String stack is empty");
    }
    
    bool empty() const {
        return elements.empty();
    }
    
    size_t size() const {
        return elements.size();
    }
};

// TEMPLATE WITH MULTIPLE PARAMETERS
// - Can have multiple template parameters
// - Each parameter can be different types
// - Useful for containers that hold pairs of different types
template <typename T, typename U>
class Pair {
private:
    T first;
    U second;

public:
    // Constructor
    Pair(T f, U s) : first(f), second(s) {}
    
    // Getters
    T getFirst() const { return first; }
    U getSecond() const { return second; }
    
    // Setters
    void setFirst(T f) { first = f; }
    void setSecond(U s) { second = s; }
    
    // Display method
    void display() const {
        std::cout << "(" << first << ", " << second << ")" << std::endl;
    }
};

// TEMPLATE WITH DEFAULT PARAMETERS
// - Template parameters can have default values
// - Similar to function default parameters
// - Allows: Array<> (uses defaults) or Array<double, 5> (custom values)
template <typename T = int, int SIZE = 10>
class Array {
private:
    T data[SIZE];  // Fixed-size array

public:
    // Constructor initializes all elements to default value
    Array() {
        for (int i = 0; i < SIZE; ++i) {
            data[i] = T{};  // Default initialization
        }
    }
    
    // Subscript operator for element access
    T& operator[](int index) {
        return data[index];
    }
    
    // Const version for const objects
    const T& operator[](int index) const {
        return data[index];
    }
    
    // Get array size
    int getSize() const {
        return SIZE;
    }
};

// VARIADIC TEMPLATES (C++11)
// - Templates that accept variable number of parameters
// - Uses ... syntax for parameter packs
// - Recursive template instantiation
// - Used in std::make_unique, std::make_shared, etc.

// Base case: single parameter
template <typename T>
void print(T&& t) {
    std::cout << t << std::endl;
}

// Recursive case: multiple parameters
template <typename T, typename... Args>
void print(T&& t, Args&&... args) {
    std::cout << t << " ";
    print(std::forward<Args>(args)...);  // Recursive call with remaining args
}

int main() {
    std::cout << "=== Template Examples ===\n";
    
    // Function template
    std::cout << "max_of(5, 10) = " << max_of(5, 10) << std::endl;
    std::cout << "max_of(3.14, 2.71) = " << max_of(3.14, 2.71) << std::endl;
    
    // Class template
    Stack<int> intStack;
    intStack.push(1);
    intStack.push(2);
    intStack.push(3);
    
    std::cout << "Top of int stack: " << intStack.top() << std::endl;
    intStack.pop();
    std::cout << "Top after pop: " << intStack.top() << std::endl;
    
    // Template specialization
    Stack<std::string> stringStack;
    stringStack.push("Hello");
    stringStack.push("World");
    stringStack.pop();
    
    // Multiple template parameters
    Pair<int, std::string> pair1(42, "Answer");
    pair1.display();
    
    Pair<double, char> pair2(3.14, 'A');
    pair2.display();
    
    // Default template parameters
    Array<> defaultArray;  // int array of size 10
    Array<double, 5> customArray;  // double array of size 5
    
    defaultArray[0] = 100;
    customArray[0] = 3.14;
    
    std::cout << "Default array[0] = " << defaultArray[0] << std::endl;
    std::cout << "Custom array[0] = " << customArray[0] << std::endl;
    
    // Variadic templates
    print("Hello", "World", 42, 3.14);
    
    return 0;
}

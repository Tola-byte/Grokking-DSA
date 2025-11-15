#include <iostream>
#include <string>
#include <memory>

/*
RULE OF 3/5 EXPLAINED:

Rule of 3: If you implement any of these 3, you usually need all 3:
1. Destructor
2. Copy Constructor  
3. Copy Assignment Operator

Rule of 5: With C++11, add these 2 more:
4. Move Constructor
5. Move Assignment Operator

WHEN DO YOU NEED THEM?
- When your class manages resources (memory, files, network connections)
- When you have raw pointers, file handles, or other resources
- When default behavior would be wrong (shallow copy vs deep copy)

WHEN DON'T YOU NEED THEM?
- When your class only contains simple data types
- When you use smart pointers (unique_ptr, shared_ptr)
- When you follow Rule of 0 (let compiler generate everything)
*/

// BAD EXAMPLE: Violates Rule of 3/5
class BadResourceManager {
private:
    int* data;
    size_t size;

public:
    BadResourceManager(size_t s) : size(s) {
        data = new int[size];
        std::cout << "BadResourceManager: Allocated " << size << " integers\n";
    }
    
    // Only destructor - VIOLATES RULE OF 3!
    ~BadResourceManager() {
        delete[] data;
        std::cout << "BadResourceManager: Freed memory\n";
    }
    
    // No copy constructor or assignment operator!
    // This will cause DOUBLE DELETE bugs!
};

// GOOD EXAMPLE: Follows Rule of 5
class GoodResourceManager {
private:
    int* data;
    size_t size;

public:
    // Constructor
    GoodResourceManager(size_t s) : size(s) {
        data = new int[size];
        std::cout << "GoodResourceManager: Allocated " << size << " integers\n";
    }
    
    // 1. Destructor
    ~GoodResourceManager() {
        delete[] data;
        std::cout << "GoodResourceManager: Freed memory\n";
    }
    
    // 2. Copy Constructor (Rule of 3)
    GoodResourceManager(const GoodResourceManager& other) : size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        std::cout << "GoodResourceManager: Copy constructor\n";
    }
    
    // 3. Copy Assignment Operator (Rule of 3)
    GoodResourceManager& operator=(const GoodResourceManager& other) {
        if (this != &other) {  // Self-assignment check
            delete[] data;      // Clean up old resources
            size = other.size;
            data = new int[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
            std::cout << "GoodResourceManager: Copy assignment\n";
        }
        return *this;
    }
    
    // 4. Move Constructor (Rule of 5)
    GoodResourceManager(GoodResourceManager&& other) noexcept 
        : data(other.data), size(other.size) {
        other.data = nullptr;  // Transfer ownership
        other.size = 0;
        std::cout << "GoodResourceManager: Move constructor\n";
    }
    
    // 5. Move Assignment Operator (Rule of 5)
    GoodResourceManager& operator=(GoodResourceManager&& other) noexcept {
        if (this != &other) {
            delete[] data;      // Clean up old resources
            data = other.data;  // Transfer ownership
            size = other.size;
            other.data = nullptr;
            other.size = 0;
            std::cout << "GoodResourceManager: Move assignment\n";
        }
        return *this;
    }
    
    // Access methods
    int& operator[](size_t index) { return data[index]; }
    const int& operator[](size_t index) const { return data[index]; }
    size_t getSize() const { return size; }
};

// RULE OF 0: Let compiler handle everything
class SimpleClass {
private:
    std::string name;
    int value;
    
public:
    SimpleClass(const std::string& n, int v) : name(n), value(v) {}
    
    // No destructor, copy constructor, or assignment operator needed!
    // Compiler-generated versions work fine for simple data types
    
    void display() const {
        std::cout << "SimpleClass: " << name << " = " << value << std::endl;
    }
};

// SMART POINTERS: Follow Rule of 0
class ModernResourceManager {
private:
    std::unique_ptr<int[]> data;
    size_t size;

public:
    ModernResourceManager(size_t s) : size(s) {
        data = std::make_unique<int[]>(size);
        std::cout << "ModernResourceManager: Allocated " << size << " integers\n";
    }
    
    // No destructor needed! unique_ptr handles cleanup
    // No copy constructor/assignment needed! unique_ptr is non-copyable
    // Move constructor/assignment are automatically generated
    
    int& operator[](size_t index) { return data[index]; }
    const int& operator[](size_t index) const { return data[index]; }
    size_t getSize() const { return size; }
};

// WHEN TO USE EACH RULE:

/*
RULE OF 0: Use when possible
- Only simple data types (int, string, vector, etc.)
- Use smart pointers instead of raw pointers
- Let compiler generate everything

RULE OF 3: Use when you have resources but no move semantics
- Legacy C++ code
- When you need deep copying
- When move semantics aren't beneficial

RULE OF 5: Use in modern C++ with resources
- When you have expensive-to-copy resources
- When move semantics provide performance benefits
- When you want to avoid unnecessary copies
*/

void demonstrateRuleViolations() {
    std::cout << "=== Demonstrating Rule Violations ===\n";
    
    // This will cause problems:
    BadResourceManager bad1(5);
    // BadResourceManager bad2 = bad1;  // SHALLOW COPY! Both point to same memory
    // When bad1 and bad2 go out of scope, same memory gets deleted twice!
}

void demonstrateRuleFollowing() {
    std::cout << "\n=== Demonstrating Rule Following ===\n";
    
    // Rule of 5 in action
    GoodResourceManager good1(3);
    good1[0] = 10; good1[1] = 20; good1[2] = 30;
    
    // Copy constructor
    GoodResourceManager good2 = good1;
    std::cout << "good2[0] = " << good2[0] << std::endl;
    
    // Copy assignment
    GoodResourceManager good3(2);
    good3 = good1;
    std::cout << "good3[0] = " << good3[0] << std::endl;
    
    // Move constructor
    GoodResourceManager good4 = std::move(good1);
    std::cout << "good4[0] = " << good4[0] << std::endl;
    
    // Move assignment
    GoodResourceManager good5(1);
    good5 = std::move(good2);
    std::cout << "good5[0] = " << good5[0] << std::endl;
}

void demonstrateRuleOfZero() {
    std::cout << "\n=== Demonstrating Rule of Zero ===\n";
    
    SimpleClass simple1("test", 42);
    SimpleClass simple2 = simple1;  // Compiler-generated copy constructor
    simple2 = simple1;              // Compiler-generated assignment operator
    
    ModernResourceManager modern1(3);
    modern1[0] = 100;
    // ModernResourceManager modern2 = modern1;  // ERROR! unique_ptr is non-copyable
    ModernResourceManager modern2 = std::move(modern1);  // Move is fine
}

int main() {
    demonstrateRuleViolations();
    demonstrateRuleFollowing();
    demonstrateRuleOfZero();
    
    std::cout << "\n=== Rule Summary ===\n";
    std::cout << "Rule of 0: Use smart pointers, let compiler handle everything\n";
    std::cout << "Rule of 3: Destructor + Copy Constructor + Copy Assignment\n";
    std::cout << "Rule of 5: Rule of 3 + Move Constructor + Move Assignment\n";
    std::cout << "Choose Rule of 0 when possible, Rule of 5 when you have resources\n";
    
    return 0;
}

#include <iostream>
#include <string>

/*
CONSTRUCTORS AND DESTRUCTORS - COMPLETE GUIDE
============================================

CONSTRUCTORS:
- Special member functions that initialize objects
- Same name as the class
- No return type (not even void)
- Called automatically when object is created
- Can be overloaded (multiple constructors with different parameters)

TYPES OF CONSTRUCTORS:
1. Default Constructor: No parameters, creates object with default values
2. Parameterized Constructor: Takes parameters to initialize object
3. Copy Constructor: Creates new object as copy of existing object
4. Move Constructor: Transfers resources from temporary object (C++11)

DESTRUCTORS:
- Special member function that cleans up resources
- Same name as class with ~ prefix
- No parameters, no return type
- Called automatically when object goes out of scope
- Only one destructor per class

RULE OF 3/5:
- If you implement any of: destructor, copy constructor, copy assignment
- You usually need all three (Rule of 3)
- With C++11, add move constructor and move assignment (Rule of 5)
- This is because if you need custom destructor, you're managing resources
- And if you're managing resources, you need custom copy/move behavior
*/

class BankAccount {
private:
    std::string accountHolder;
    double balance;
    int* transactionCount; // Dynamic memory for RAII demo

public:
    // 1. DEFAULT CONSTRUCTOR
    // - No parameters
    // - Initializes object with default values
    // - Called when: BankAccount account; (no parentheses)
    BankAccount() : accountHolder("Unknown"), balance(0.0), transactionCount(new int(0)) {
        std::cout << "Default constructor called\n";
    }

    // 2. PARAMETERIZED CONSTRUCTOR
    // - Takes parameters to initialize object
    // - Uses member initializer list (after :)
    // - Called when: BankAccount account("Alice", 1000.0);
    BankAccount(const std::string name, double initialBalance) 
        : accountHolder(std::move(name)), balance(initialBalance) {
        transactionCount = new int(0);
        std::cout << "Parameterized constructor called for " << name << "\n";
    }

    // 3. COPY CONSTRUCTOR (Rule of 3/5)
    // - Creates new object as copy of existing object
    // - Takes const reference to another object of same type
    // - Called when: BankAccount account2 = account1; or BankAccount account2(account1);
    // - Must do DEEP COPY for resources (not shallow copy)
    BankAccount(const BankAccount& other) 
        : accountHolder(other.accountHolder), balance(other.balance) {
        transactionCount = new int(*other.transactionCount);  // Deep copy!
        std::cout << "Copy constructor called\n";
    }

    // 4. MOVE CONSTRUCTOR (C++11)
    // - Transfers resources from temporary object
    // - Takes rvalue reference (&&) - indicates temporary object
    // - Called when: BankAccount account = std::move(other); or returning from function
    // - TRANSFERS ownership (doesn't copy), source becomes empty
    BankAccount(BankAccount&& other) noexcept 
        : accountHolder(std::move(other.accountHolder)), balance(other.balance) {
        transactionCount = other.transactionCount;
        other.transactionCount = nullptr;  // Transfer ownership!
        std::cout << "Move constructor called\n";
    }

    // 5. COPY ASSIGNMENT OPERATOR (Rule of 3/5)
    // - Assigns one object to another (both already exist)
    // - Called when: account1 = account2;
    // - Must handle self-assignment (account1 = account1)
    // - Returns reference to allow chaining (account1 = account2 = account3)
    BankAccount& operator=(const BankAccount& other) {
        if (this != &other) {  // Self-assignment check!
            accountHolder = other.accountHolder;
            balance = other.balance;
            delete transactionCount;  // Clean up old resources
            transactionCount = new int(*other.transactionCount);  // Deep copy!
            std::cout << "Copy assignment called\n";
        }
        return *this;  // Return reference for chaining
    }

    // 6. MOVE ASSIGNMENT OPERATOR (Rule of 5)
    // - Transfers resources from temporary object to existing object
    // - Called when: account1 = std::move(account2);
    // - TRANSFERS ownership, source becomes empty
    BankAccount& operator=(BankAccount&& other) noexcept {
        if (this != &other) {  // Self-assignment check!
            accountHolder = std::move(other.accountHolder);
            balance = other.balance;
            delete transactionCount;  // Clean up old resources
            transactionCount = other.transactionCount;  // Transfer ownership!
            other.transactionCount = nullptr;  // Source becomes empty
            std::cout << "Move assignment called\n";
        }
        return *this;  // Return reference for chaining
    }

    // DESTRUCTOR (Rule of 3/5)
    // - Cleans up resources when object goes out of scope
    // - Same name as class with ~ prefix
    // - No parameters, no return type
    // - Called automatically when object is destroyed
    // - Only one destructor per class
    ~BankAccount() {
        delete transactionCount;  // Clean up dynamic memory
        std::cout << "Destructor called for " << accountHolder << "\n";
    }

    // Methods
    void deposit(double amount) {
        balance += amount;
        (*transactionCount)++;
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            (*transactionCount)++;
        }
    }

    void displayInfo() const {
        std::cout << "Account: " << accountHolder 
                  << ", Balance: $" << balance 
                  << ", Transactions: " << *transactionCount << "\n";
    }
};


class SimpleCounter{
    private:
    int* value;

    public:
        SimpleCounter() : value(new int(0)){} // constructor
        SimpleCounter(const SimpleCounter& other): value(new int(*other.value)){} // copy constructor
        SimpleCounter& operator=(const SimpleCounter& other){
            if(this != &other) *value = *other.value;
            return *this;
         }
        ~SimpleCounter(){
            delete value;
        }

};
int main() {
    std::cout << "=== Constructor/Destructor Demo ===\n";
    
    // Default constructor
    BankAccount account1;
    account1.displayInfo();
    
    // Parameterized constructor
    BankAccount account2("Alice", 1000.0);
    account2.displayInfo();
    
    // Copy constructor
    BankAccount account3 = account2;  // Copy constructor
    account3.displayInfo();
    
    // Assignment operator
    account1 = account2;  // Copy assignment
    account1.displayInfo();
    
    // Move constructor
    BankAccount account4 = std::move(account3);
    account4.displayInfo();
    
    std::cout << "\n=== End of scope - destructors called ===\n";
    return 0;
}


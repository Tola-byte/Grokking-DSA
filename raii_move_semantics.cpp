#include <iostream>
#include <memory>
#include <vector>
#include <string>

/*
RAII & MOVE SEMANTICS - COMPLETE GUIDE
======================================

RAII (Resource Acquisition Is Initialization):
- C++ programming technique where resource management is tied to object lifetime
- Resources are acquired in constructors and released in destructors
- Ensures automatic cleanup even when exceptions occur
- Prevents memory leaks and resource leaks

MOVE SEMANTICS (C++11):
- Allows transferring ownership of resources without copying
- Uses rvalue references (&&) to identify temporary objects
- Avoids expensive deep copies
- Improves performance by eliminating unnecessary copies

SMART POINTERS:
- RAII wrappers around raw pointers
- Automatic memory management
- unique_ptr: exclusive ownership, non-copyable
- shared_ptr: shared ownership, reference counting
- weak_ptr: non-owning reference, breaks cycles

KEY CONCEPTS:
1. Rvalue References (&&): Identify temporary objects
2. std::move(): Converts lvalue to rvalue reference
3. Move Constructor: Transfers resources from temporary object
4. Move Assignment: Transfers resources to existing object
5. noexcept: Indicates function won't throw exceptions
*/

// RAII EXAMPLE: Resource Manager
// - Constructor acquires resource (memory)
// - Destructor releases resource (memory)
// - Copy constructor does deep copy
// - Move constructor transfers ownership
class ResourceManager {
private:
    int* data;
    size_t size;

public:
    // CONSTRUCTOR: Acquires resource (RAII)
    // - Allocates memory when object is created
    // - Resource is tied to object lifetime
    ResourceManager(size_t s) : size(s) {
        data = new int[size];
        std::cout << "Resource acquired: " << size << " integers\n";
    }
    
    // DESTRUCTOR: Releases resource (RAII)
    // - Automatically called when object goes out of scope
    // - Ensures memory is always freed, even if exceptions occur
    ~ResourceManager() {
        delete[] data;
        std::cout << "Resource released\n";
    }
    
    // COPY CONSTRUCTOR: Deep copy
    // - Creates independent copy of resources
    // - Both objects have their own memory
    ResourceManager(const ResourceManager& other) : size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        std::cout << "Copy constructor called\n";
    }
    
    // MOVE CONSTRUCTOR: Transfer ownership
    // - Takes rvalue reference (&&) - indicates temporary object
    // - Transfers resources without copying
    // - Source object becomes empty (nullptr)
    // - noexcept indicates this won't throw exceptions
    ResourceManager(ResourceManager&& other) noexcept 
        : data(other.data), size(other.size) {
        other.data = nullptr;  // Transfer ownership
        other.size = 0;
        std::cout << "Move constructor called\n";
    }
    
    // COPY ASSIGNMENT: Deep copy assignment
    // - Assigns one object to another (both already exist)
    // - Must handle self-assignment
    // - Cleans up old resources before copying new ones
    ResourceManager& operator=(const ResourceManager& other) {
        if (this != &other) {  // Self-assignment check
            delete[] data;      // Clean up old resources
            size = other.size;
            data = new int[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
            std::cout << "Copy assignment called\n";
        }
        return *this;
    }
    
    // MOVE ASSIGNMENT: Transfer ownership assignment
    // - Transfers resources from temporary object to existing object
    // - Source object becomes empty
    // - noexcept indicates this won't throw exceptions
    ResourceManager& operator=(ResourceManager&& other) noexcept {
        if (this != &other) {  // Self-assignment check
            delete[] data;      // Clean up old resources
            data = other.data;  // Transfer ownership
            size = other.size;
            other.data = nullptr;  // Source becomes empty
            other.size = 0;
            std::cout << "Move assignment called\n";
        }
        return *this;
    }
    
    // Access methods
    int& operator[](size_t index) {
        return data[index];
    }
    
    const int& operator[](size_t index) const {
        return data[index];
    }
    
    size_t getSize() const { return size; }
};

// FUNCTION THAT RETURNS BY VALUE (triggers move semantics)
// - When returning local object, compiler uses move semantics
// - Avoids expensive copy operation
ResourceManager createResource(size_t size) {
    ResourceManager rm(size);
    for (size_t i = 0; i < size; ++i) {
        rm[i] = i * i;
    }
    return rm;  // This will use move semantics automatically
}

// FUNCTION DEMONSTRATING RVALUE REFERENCES
// - Takes rvalue reference parameter
// - Indicates function expects temporary object
void processResource(ResourceManager&& rm) {
    std::cout << "Processing resource with " << rm.getSize() << " elements\n";
    // rm will be destroyed when function ends
}

int main() {
    std::cout << "=== RAII & Move Semantics Demo ===\n";
    
    // RAII in action
    {
        ResourceManager rm1(5);
        rm1[0] = 10;
        rm1[1] = 20;
        std::cout << "rm1[0] = " << rm1[0] << std::endl;
    } // rm1 destructor called here automatically
    
    std::cout << "\n=== Move Semantics ===\n";
    
    // Move constructor
    ResourceManager rm2 = createResource(3);  // Move constructor
    std::cout << "rm2[0] = " << rm2[0] << std::endl;
    
    // Move assignment
    ResourceManager rm3(2);
    rm3 = createResource(4);  // Move assignment
    std::cout << "rm3[0] = " << rm3[0] << std::endl;
    
    // Rvalue reference
    processResource(createResource(2));
    
    std::cout << "\n=== Smart Pointers ===\n";
    
    // UNIQUE_PTR: Exclusive ownership
    // - Only one unique_ptr can own the object
    // - Non-copyable (prevents multiple ownership)
    // - Automatically deletes object when unique_ptr goes out of scope
    std::unique_ptr<ResourceManager> uniquePtr = 
        std::make_unique<ResourceManager>(3);
    (*uniquePtr)[0] = 100;
    std::cout << "unique_ptr[0] = " << (*uniquePtr)[0] << std::endl;
    
    // Transfer ownership with std::move
    std::unique_ptr<ResourceManager> anotherPtr = std::move(uniquePtr);
    std::cout << "uniquePtr is now " << (uniquePtr ? "valid" : "null") << std::endl;
    
    // SHARED_PTR: Shared ownership
    // - Multiple shared_ptr can own the same object
    // - Uses reference counting
    // - Object is deleted when last shared_ptr is destroyed
    std::shared_ptr<ResourceManager> sharedPtr1 = 
        std::make_shared<ResourceManager>(2);
    std::shared_ptr<ResourceManager> sharedPtr2 = sharedPtr1;  // Share ownership
    
    std::cout << "Reference count: " << sharedPtr1.use_count() << std::endl;
    
    // WEAK_PTR: Non-owning reference
    // - Doesn't affect object lifetime
    // - Breaks reference cycles
    // - Can check if object still exists
    std::weak_ptr<ResourceManager> weakPtr = sharedPtr1;
    std::cout << "Weak ptr expired: " << weakPtr.expired() << std::endl;
    
    if (auto locked = weakPtr.lock()) {
        std::cout << "Successfully locked weak_ptr\n";
    }
    
    std::cout << "\n=== End of scope ===\n";
    return 0;
}

/*
INTERVIEW TALKING POINTS FOR MAKO C++ POSITION

These are the exact points you should memorize and be able to explain clearly.
Practice explaining these concepts out loud - that's what will impress them.
*/

/*
1. RAII (Resource Acquisition Is Initialization)
================================================

WHAT IT IS:
- A C++ programming technique where resource management is tied to object lifetime
- Resources are acquired in constructors and released in destructors
- Ensures automatic cleanup even when exceptions occur

WHY IT MATTERS:
- Prevents memory leaks
- Exception-safe resource management
- Makes code more robust and maintainable

EXAMPLE EXPLANATION:
"RAII is C++'s way of managing resources automatically. When I create an object,
it acquires resources in its constructor. When the object goes out of scope,
the destructor automatically cleans up those resources. This prevents memory
leaks and makes my code exception-safe."

KEY POINTS TO MENTION:
- Constructor acquires, destructor releases
- Automatic cleanup on scope exit
- Exception safety
- Smart pointers are RAII wrappers
*/

/*
2. MOVE SEMANTICS
=================

WHAT IT IS:
- C++11 feature that allows transferring ownership of resources without copying
- Uses rvalue references (&&) to identify temporary objects
- Avoids expensive deep copies

WHEN TO USE:
- When returning large objects from functions
- When passing temporary objects
- When implementing containers or resource managers

EXAMPLE EXPLANATION:
"Move semantics solve the performance problem of expensive copies. Instead of
copying a large object, I can transfer its ownership using std::move. The
source object becomes empty, and the destination gets the resources. This is
especially useful for containers and when returning objects from functions."

KEY POINTS TO MENTION:
- Transfers ownership, doesn't copy
- Uses rvalue references (&&)
- Source object becomes empty
- Performance optimization
- std::move() function
*/

/*
3. ITERATOR INVALIDATION RULES
==============================

WHAT IT IS:
- Rules about when iterators become invalid after container modifications
- Critical for avoiding crashes and undefined behavior

CONTAINER-SPECIFIC RULES:

VECTOR:
- Insert/erase at any position invalidates all iterators
- push_back/pop_back only invalidates end() iterator
- Reserve doesn't invalidate iterators

MAP/UNORDERED_MAP:
- Insert/erase only invalidates iterators to erased elements
- Other iterators remain valid
- unordered_map rehashing invalidates all iterators

EXAMPLE EXPLANATION:
"Iterator invalidation is crucial for safe container manipulation. For vectors,
any insert or erase invalidates all iterators because elements might move in memory.
For maps, only the erased element's iterator becomes invalid. For unordered_map,
rehashing invalidates everything. I always check these rules before modifying
containers while iterating."

KEY POINTS TO MENTION:
- Vector: insert/erase invalidates all
- Map: only erased element invalidated
- Unordered_map: rehashing invalidates all
- Always check rules before modifying while iterating
*/

/*
4. RULE OF 3/5
==============

WHAT IT IS:
- Rule of 3: If you implement destructor, copy constructor, or copy assignment,
  you usually need all three
- Rule of 5: With C++11, add move constructor and move assignment operator

WHEN YOU NEED THEM:
- When managing resources (memory, files, network connections)
- When default behavior would be wrong
- When you have raw pointers or other resources

WHEN YOU DON'T:
- When using smart pointers
- When class only contains simple data types
- Rule of 0: let compiler generate everything

EXAMPLE EXPLANATION:
"The Rule of 3/5 guides when I need to implement special member functions.
If I'm managing resources like raw pointers, I need custom destructor, copy
constructor, and copy assignment. With C++11, I also implement move constructor
and move assignment for performance. But if I use smart pointers, I follow
Rule of 0 and let the compiler generate everything."

KEY POINTS TO MENTION:
- Rule of 3: destructor + copy constructor + copy assignment
- Rule of 5: Rule of 3 + move constructor + move assignment
- Rule of 0: use smart pointers, let compiler handle everything
- Choose based on resource management needs
*/

/*
5. TEMPLATES
============

WHAT IT IS:
- Generic programming feature that allows code to work with different types
- Compile-time polymorphism
- Function templates and class templates

ADVANTAGES:
- Code reuse
- Type safety
- Performance (no runtime overhead)
- STL is built on templates

EXAMPLE EXPLANATION:
"Templates allow me to write generic code that works with any type. The compiler
generates specific versions for each type I use. This gives me code reuse,
type safety, and zero runtime overhead. The entire STL is built on templates,
which is why it's so efficient and flexible."

KEY POINTS TO MENTION:
- Generic programming
- Compile-time code generation
- Type safety
- No runtime overhead
- STL foundation
*/

/*
6. SMART POINTERS
==================

WHAT THEY ARE:
- RAII wrappers around raw pointers
- Automatic memory management
- unique_ptr, shared_ptr, weak_ptr

WHEN TO USE:
- unique_ptr: exclusive ownership, non-copyable
- shared_ptr: shared ownership, reference counting
- weak_ptr: non-owning reference, breaks cycles

EXAMPLE EXPLANATION:
"Smart pointers are RAII wrappers that automatically manage memory. unique_ptr
provides exclusive ownership and is non-copyable, perfect for single ownership.
shared_ptr uses reference counting for shared ownership. weak_ptr breaks
reference cycles. I use them instead of raw pointers for automatic cleanup."

KEY POINTS TO MENTION:
- Automatic memory management
- unique_ptr: exclusive ownership
- shared_ptr: shared ownership with reference counting
- weak_ptr: breaks cycles
- Prefer over raw pointers
*/

/*
INTERVIEW STRATEGY:
==================

1. START WITH THE PROBLEM: "RAII solves the memory leak problem by..."
2. EXPLAIN THE SOLUTION: "It works by tying resource lifetime to object lifetime..."
3. GIVE A CONCRETE EXAMPLE: "For example, when I create a vector..."
4. MENTION BENEFITS: "This gives me automatic cleanup and exception safety..."
5. CONNECT TO BIGGER PICTURE: "This is why C++ is so powerful for systems programming..."

PRACTICE THESE EXPLANATIONS OUT LOUD!
*/

int main() {
    std::cout << "=== Interview Talking Points Summary ===\n";
    std::cout << "1. RAII: Constructor acquires, destructor releases\n";
    std::cout << "2. Move Semantics: Transfer ownership, avoid expensive copies\n";
    std::cout << "3. Iterator Invalidation: Know the rules for each container\n";
    std::cout << "4. Rule of 3/5: When to implement special member functions\n";
    std::cout << "5. Templates: Generic programming with compile-time generation\n";
    std::cout << "6. Smart Pointers: RAII wrappers for automatic memory management\n";
    std::cout << "\nPractice explaining these concepts out loud!\n";
    return 0;
}

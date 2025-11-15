#include <vector>
#include <iostream>
int main() {
 
    std::vector<std::string> students={"SpongeBob", "Patrick", "Bob"} ;
    std::string name = "SpongeBob";
    bool doesNameExists;
    // for loop
    // for(int i=0 ; i < students.size(); ++i){
    //     std::cout << students[i] << std::endl;
    // }

    // for each

    // Use const std::string& when you’re just reading.
//Use std::string& when you need to change the elements.
// Use a plain value (no &) only when you want a copy.

    for (const std::string& i : students){
      //  std::cout << i << std::endl;

        if (i == name) {
        std::cout <<name << "\n";
        
        break;
    } else {
        std::cout << "Not found" << '\n';
    }
    
    }

    // to sort, just use two nested loops. and use ur head sha. or do std::sort(begins, ends)
    // std::fill : fills a range of elements with a specified value, fill(begin, end, value)

    // also for pass by value vs pass by reference, say you want to swap values,
    //  in pass by value, just makes copy of those values, but pass by reference makes a reference to the memory addresses and swaps.
    // so one just make copies, the other references their addresses in memory

    //const parameters = parameter that are effectively read-only. code is more secure and conveys intent.

    //pointers = variable that stores a memory address of another variable ,
    // & address-of operator
    // * dereference operator.

    int age = 31;
    int *pAge = &age;

    // for an array, just do *arrayName = arrayName

    // null value pointer, a pointer that means something has no value.
    // be care so as not to deference a nullptr, would throw errors. 
     
    // dynamic memory, memory that is allocated after the program is already compiled and running. 
    // use the 'new' operator to allocate memory in the heap rather than the stack.
    // useful when we don't know how much memory we will need. makes our program more flexible.
    // especially when accepting user input


    //RECURSION: a programming technique where a function invokes itself from within
    // break a complex concept into repeatable small steps.

    // iterative vs recursive.
    // advantages = less code and is cleaner, useful for searching and sorting algorithms.
    // disadvantages = uses more memory, and slower. 

    // WHEN YOU ENCOUNTER AN INFINITE LOOP, STACK OVERFLOW HAPPENS.
    // A STACK OVERFLOW OCCURS IF THE CALL STACK POINTER EXCEEDS THE STACK BOUND.
    // CALL STACK IS A LIMITED SPACE, SIZE OF CALL STACK DEPENDS ON FACTORS LIKE MACHINE ARCHITECTURE, PROGRAMMING LANGUAGE, MULTI-THREADING ETC. 
    // WHEN A PROGRAM ATTEMPTS TO USE MORE SPACE THAN IS AVAILABLE ON THE CALL STACK , A BUFFER OVERFLOW OR STACK OVERFLOW HAPPENS. 
    // RESULTING IN A PROGRAM CRASH.

    // also learn how recursion causes stack overflow.

    // function templates:  describes what a function looks like,

    // struct

    struct student{
        std::string studentName;
        bool isStudent;
        int age;
    };

    // enums are user-defined data type that consists of paired named integrer constants. 

    enum Day {
        monday = 0,
        tuesday = 1,
        wednesday = 2
    };

    // OBJECT ORIENTED PROGRAMMING
    // object - a collection of attributes and methods. they have characteristics and can perform actions. created 
    // from a class which acts as a blueprint.

    class Human {
        public:
            std::string name;
            std::string occupation;
            int age;

            void eat(){
                std::cout << " dawg is eating \n";
            }
            void drink(){
                std::cout << " dawg is drinking \n";
            }
            void sleep(){
                std::cout << " dawg is sleeping \n";
            }

    };

    Human human1;
    human1.name = "Tola";
    // now you can then call methods.

    human1.drink();

    // CONSTRUCTORS
    // special method that is automatically called when an object is instantiated/
    // useful for assigning values to attributes as arguments.

     class Human {
        public:
            std::string name;
            std::string occupation;
            int age;

            Human(std::string name, std::string occupation, int age){
                this->name = name;
                this->occupation = occupation;
                this->age = age;
            };

    };

    // Abstraction: hiding unnecessary data from outside a class.
    // getter: function that makes the private attribute readable.
    //setter: function that makes the private attribute writeable.

     class Stove{
        // instead of public, do private
        private:
        int temperature = 0;

        public:
        int getTemperature(){
            return temperature;
        }

        void setTemp(int temperature){
            this->temperature = temperature;
        }
     };

      // INHERITANCE: A class can receive attributes and methods from another class.
      // children classes inherit from a parent class
      // helps to reuse similar code found within multiple classes.
     class Animal{
        public:
            bool alive = true;
        void eat(){
            std::cout << "This animal is eating";
        }
     };

      class Dog : public Animal{
        public:

      };

    
    return 0;
}


// “C++ is ideal for low-latency because it gives predictable, tiny, and stable response times: 
//no garbage collector or JIT pauses, ahead-of-time optimized native code, precise control of memory/layout, and direct access to hardware/OS features 
//(SIMD, atomics, thread pinning, kernel-bypass I/O). With RAII and preallocation, we eliminate hot-path allocations and locks, which reduces jitter and
// keeps p99/p99.9 tight.”


//Clearing the term: “GIC/JIT” → you probably mean GC/JIT
//GC = Garbage Collection (garbage-collected languages).
//Some languages automatically reclaim unused memory in the background. That’s convenient, but the collector occasionally pauses parts of your program (modern GCs try to make pauses tiny, but not zero).
//Examples: Java, C#, Go (GC yes, JIT no—see below).
//JIT = Just-In-Time compilation (JIT-compiled languages).
//Code is compiled at runtime (often after the program starts), which allows powerful optimizations—but also means warm-up time and occasional de-optimizations that can add jitter.
//Examples: Java (HotSpot), .NET (C#), JavaScript engines (V8), PyPy.

//p50 + p95/p99 + p99.9: together they show the whole story (median, fast tail, extreme tail).
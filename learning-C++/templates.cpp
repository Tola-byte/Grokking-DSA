#include <iostream>

// C++ Templates:

// Templates are blue-prints that generates code for different types. 
// Codes are generated at compile time and hence zero overhead line. 
//so I keep type safety and usually pay zero runtime overhead

// examples are function, class, template specialization and variadic templates.

// Function templates. 

template <class T>
int max_sum(T x, T y ){
    return x + y
}

// Class template.

template <class T>
class Stack {
    private:
    std::vector<T> elements;

    public:
    bool empty() const{
        elements.empty() ? return true : return false;
    }
    void push(const T& element){
            elements.push_back(element);
    }
    void pop(){
        if(!elements.empty()){
            elements.pop_back();
        }
        throw std::error("Stack is empty, nothing to pop")
    }
    T top() {
         if(!elements.empty()){
            elements.back();
        }
    }
    size_t size()const{
       return elements.size();
    }


}

//C++ (Mako maintenance): 60–90m/day. Pick one micro-topic per day:
//Day 1: references vs pointers, const correctness (10-line examples).
//Day 2: STL iterators + std::sort with custom comparator.
// Day 3: move semantics + unique_ptr/shared_ptr.
// Day 4: unordered_map pitfalls (rehash, iterator invalidation).
// Day 5: priority_queue (top-k) small exercise.
// Day 6: RAII + rule of 0/3/5 quick demo.
// Day 7: std::thread, mutex, lock_guard tiny producer/consumer.
// Day 8: 45-min timed C++ medium + review.


// Have 3 crisp tech bullets ready:
// RAII & move semantics (what problem they solve).
// Iterator invalidation rules for vector, deque, unordered_map.
// When to pick map vs unordered_map vs vector + binary_search.

// VERY IMPORTANT:
// 90-sec intro: who you are → strongest coding win → why C++ → why Mako.
// 3 crisp C++ bullets: RAII & move semantics; iterator invalidation rules; map vs unordered_map trade-offs.
// 1 bug story + 1 concurrency note (mutex + condition_variable).
// Close with: “What are the next steps and what should I prepare for the technical rounds?”
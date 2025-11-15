

// What is the “Rule of 0 / 3 / 5” in C++?
// Rule of Zero:
// If your class doesn’t own a resource (memory, file, socket), or it stores ownership in RAII members (e.g., std::vector, std::string, std::unique_ptr), then write none of the special members. Let the compiler generate them.
// Rule of Three (pre-C++11):
// If you need any of these because you own a raw resource, you probably need all three:
// destructor, copy constructor, copy assignment (to implement deep copy & cleanup).
// Rule of Five (C++11+):
// With move semantics, if Rule of Three applies, you also need:
// move constructor and move assignment (for efficient moves, avoiding extra allocations).
// “Special members” = dtor, copy/move ctors, copy/move assignments.



// totally fair—and yes, some of what we covered is *beyond* what most grads are expected to code cold. 
//For a **graduate** role (with a 12-month training plan), interviewers mainly want solid **fundamentals**, clear thinking,
// and signs you can learn fast—not a walking C++ encyclopedia.

// Here’s a realistic prep map 👇

// # What you actually need (for a 20-min screen)

// * **C++ basics:** values vs references vs pointers, `const`, scopes.
// * **RAII (in words):** constructor acquires, destructor releases; no leaks.
// * **Smart pointers:** `unique_ptr` (owning, move-only), `shared_ptr` (shared), `weak_ptr` (non-owning).
// * **Templates (light):** function template + class template idea; maybe a non-type param; know `std::vector<T>` is a class template.
// * **STL essentials:** `std::vector`, `std::string`, range-for, `<algorithm>` (`sort`, `find_if`).
// * **Concurrency (one-liner):** C++ uses **OS threads + atomics/locks**; Go has goroutines; Java has threads + **virtual threads**.

// # Nice-to-have (only if time allows)

// * `if constexpr`, variadic templates (just the idea), `std::lock_guard`, `std::chrono`.
// * High-level “why C++ is good for low latency” (no GC/JIT, control, AOT).

// # 5 one-line answers (memorize)

// * **RAII:** “Tie resource lifetime to object lifetime—ctor gets it, dtor frees it—so cleanup is automatic and exception-safe.”
// * **Smart pointers:** “`unique_ptr` = single owner; `shared_ptr` = ref-counted shared owner; `weak_ptr` breaks cycles / non-owning.”
// * **Templates:** “Compile-time generics: one blueprint, compiler generates versions per type/constant; zero runtime cost.”
// * **p99 vs average:** “Percentiles reveal tail latency; p99/p99.9 matter when spikes hurt more than the median.”
// * **Why C++ for low latency:** “No GC/JIT pauses, precise memory/layout control, AOT native code, direct hardware/OS tuning.”

// # Tiny code you can type under pressure (covers basics)

// ```cpp
// #include <iostream>
// #include <memory>
// #include <vector>
// #include <algorithm>
// #include <string>

// // 1) function template
// template <class T>
// T my_max(T a, T b) { return a < b ? b : a; }

// // 2) class template + RAII-containing members
// template <class T>
// struct Box {
//     T value;
//     void print() const { std::cout << value << "\n"; }
// };

// int main() {
//     // vector/string are RAII; no manual delete
//     std::vector<int> v{3,1,4};
//     std::sort(v.begin(), v.end());
//     std::cout << "max=" << my_max(5, 9) << "\n";

//     Box<std::string> b{"hello"};
//     b.print();

//     // smart pointer (unique ownership)
//     auto p = std::make_unique<int>(42);
//     std::cout << *p << "\n";   // frees automatically at scope end
// }
// ```

// # If you get asked something you don’t know

// Say: **“I’m not fully sure, but my understanding is … [best effort]. If I had 10 minutes, I’d confirm by [tool/experiment].”**
// This shows honesty + problem-solving, which matters more than trivia.

// # Reality check

// For a grad role, they’re judging:

// * your **grasp of fundamentals** (the bullets above),
// * **clarity** in explaining them,
// * and your **learning attitude**.
//   You don’t need coroutines/ranges/DPDK mastery on day one. If you can explain RAII, smart pointers, and basic templates clearly—and write a small, clean snippet—you’re in great shape.



// Minimal prep plan (you can do this in ~2 hours)
// Revisit one past code task (20–30 min): be ready to explain problem → approach → trade-offs.
// C++ core refresh (30–40 min):
// RAII & smart pointers (unique/shared/weak)
// Templates: function + class + a tiny NTTP example
// Concurrency: “C++ uses OS threads/atomics; Go has goroutines; Java has virtual threads.”
// Latency vs throughput, p99/p99.9 one-liners
// Type a tiny demo (20 min): your “Greeter<Formatter, Bangs>” hello-world with variadic greet_all.
// 60-second intro (10 min): who you are, what you’ve built, why Mako.
// Logistics check (10 min): camera/mic, IDE/compiler ready (g++ -std=c++20), quiet room.
// Lightning answers (memorize)
// RAII: constructor acquires, destructor releases → automatic, deterministic cleanup.
// Smart pointers: unique_ptr = single owner; shared_ptr = shared owner; weak_ptr = non-owning.
// Templates: compile-time generics; one blueprint → many instantiations; zero runtime overhead.
// Why C++ for low latency: no GC/JIT pauses, precise memory/layout control, AOT native code, hardware/OS tuning.
// Latency vs throughput: latency = time per request; throughput = requests per second; watch p99/p99.9 for tails.
// Good questions to ask them (pick 1–2)
// “What does success look like for grads by month 3 and month 12?”
// “Where is C++ used most in your stack (market data, gateways, matching)?”
// “How do you measure and reduce tail latency (p99+) in production?”
// You’ve got this. Send the nudge now, then do the light prep—if they reply with a slot, you’ll be ready on the spot.
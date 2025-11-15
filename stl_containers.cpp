#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <iterator>

void demonstrateVectorIterators() {
    std::cout << "=== Vector Iterator Rules ===\n";
    
    std::vector<int> vec = {1, 2, 3, 4, 5};
    
    // Safe iteration
    std::cout << "Vector contents: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Iterator invalidation example
    auto it = vec.begin() + 2;  // Points to element 3
    std::cout << "Iterator points to: " << *it << std::endl;
    
    vec.insert(vec.begin() + 1, 99);  // Insert at position 1
    std::cout << "After insert, iterator points to: " << *it << std::endl;
    // Iterator is still valid but now points to different element!
    
    // Range-based for loop (C++11)
    std::cout << "Range-based for: ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

void demonstrateMapOperations() {
    std::cout << "\n=== Map vs Unordered Map ===\n";
    
    // std::map - ordered, O(log n) operations
    std::map<std::string, int> orderedMap;
    orderedMap["apple"] = 5;
    orderedMap["banana"] = 3;
    orderedMap["cherry"] = 8;
    
    std::cout << "Ordered map (sorted by key):\n";
    for (const auto& pair : orderedMap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    
    // std::unordered_map - hash table, O(1) average operations
    std::unordered_map<std::string, int> hashMap;
    hashMap["apple"] = 5;
    hashMap["banana"] = 3;
    hashMap["cherry"] = 8;
    
    std::cout << "\nUnordered map (hash table):\n";
    for (const auto& pair : hashMap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    
    // Iterator invalidation in unordered_map
    auto it = hashMap.find("banana");
    if (it != hashMap.end()) {
        std::cout << "Found: " << it->first << " = " << it->second << std::endl;
    }
    
    hashMap["grape"] = 12;  // This might rehash and invalidate iterators
    // it might be invalid now!
}

void demonstrateSTLAlgorithms() {
    std::cout << "\n=== STL Algorithms ===\n";
    
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3};
    
    // Sort with custom comparator
    std::sort(numbers.begin(), numbers.end(), std::greater<int>());
    std::cout << "Sorted (descending): ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << std::endl;
    
    // Find element
    auto it = std::find(numbers.begin(), numbers.end(), 8);
    if (it != numbers.end()) {
        std::cout << "Found 8 at position: " << std::distance(numbers.begin(), it) << std::endl;
    }
    
    // Count elements
    int count = std::count(numbers.begin(), numbers.end(), 5);
    std::cout << "Count of 5: " << count << std::endl;
    
    // Transform
    std::vector<int> doubled(numbers.size());
    std::transform(numbers.begin(), numbers.end(), doubled.begin(),
                   [](int x) { return x * 2; });
    
    std::cout << "Doubled: ";
    for (int n : doubled) std::cout << n << " ";
    std::cout << std::endl;
}

void demonstrateContainerPerformance() {
    std::cout << "\n=== Container Performance Trade-offs ===\n";
    
    // When to use each container:
    std::cout << "Vector:\n";
    std::cout << "  - Use for: Random access, sequential access\n";
    std::cout << "  - Avoid: Frequent insertions/deletions in middle\n";
    std::cout << "  - Time: O(1) access, O(n) insert/delete\n\n";
    
    std::cout << "Map:\n";
    std::cout << "  - Use for: Sorted data, range queries\n";
    std::cout << "  - Avoid: When order doesn't matter\n";
    std::cout << "  - Time: O(log n) all operations\n\n";
    
    std::cout << "Unordered Map:\n";
    std::cout << "  - Use for: Fast lookups, order doesn't matter\n";
    std::cout << "  - Avoid: When you need sorted iteration\n";
    std::cout << "  - Time: O(1) average, O(n) worst case\n\n";
    
    std::cout << "Set vs Vector + Binary Search:\n";
    std::cout << "  - Set: O(log n) insert/find, sorted\n";
    std::cout << "  - Vector + binary_search: O(log n) find, O(n) insert\n";
    std::cout << "  - Choose vector if: Few inserts, many searches\n";
    std::cout << "  - Choose set if: Many inserts, need sorted data\n";
}

int main() {
    demonstrateVectorIterators();
    demonstrateMapOperations();
    demonstrateSTLAlgorithms();
    demonstrateContainerPerformance();
    
    return 0;
}

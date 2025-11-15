#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <chrono>
#include <iomanip>

// Template for different account types
template <typename T>
class Account {
private:
    std::string accountNumber;
    std::string accountHolder;
    T balance;
    std::vector<std::string> transactionHistory;
    mutable std::map<std::string, int> accessCount; // mutable for const methods

public:
    // Constructors (Rule of 5)
    Account() : accountNumber(""), accountHolder(""), balance(T{}) {
        std::cout << "Default Account constructor\n";
    }
    
    Account(const std::string& number, const std::string& holder, T initialBalance)
        : accountNumber(number), accountHolder(holder), balance(initialBalance) {
        addTransaction("Account created with initial balance: " + std::to_string(initialBalance));
        std::cout << "Account constructor for " << holder << "\n";
    }
    
    // Copy constructor
    Account(const Account& other) 
        : accountNumber(other.accountNumber), accountHolder(other.accountHolder),
          balance(other.balance), transactionHistory(other.transactionHistory),
          accessCount(other.accessCount) {
        std::cout << "Account copy constructor\n";
    }
    
    // Move constructor
    Account(Account&& other) noexcept
        : accountNumber(std::move(other.accountNumber)),
          accountHolder(std::move(other.accountHolder)),
          balance(std::move(other.balance)),
          transactionHistory(std::move(other.transactionHistory)),
          accessCount(std::move(other.accessCount)) {
        std::cout << "Account move constructor\n";
    }
    
    // Copy assignment
    Account& operator=(const Account& other) {
        if (this != &other) {
            accountNumber = other.accountNumber;
            accountHolder = other.accountHolder;
            balance = other.balance;
            transactionHistory = other.transactionHistory;
            accessCount = other.accessCount;
            std::cout << "Account copy assignment\n";
        }
        return *this;
    }
    
    // Move assignment
    Account& operator=(Account&& other) noexcept {
        if (this != &other) {
            accountNumber = std::move(other.accountNumber);
            accountHolder = std::move(other.accountHolder);
            balance = std::move(other.balance);
            transactionHistory = std::move(other.transactionHistory);
            accessCount = std::move(other.accessCount);
            std::cout << "Account move assignment\n";
        }
        return *this;
    }
    
    // Destructor
    ~Account() {
        std::cout << "Account destructor for " << accountHolder << "\n";
    }
    
    // Operator overloading
    bool operator==(const Account& other) const {
        return accountNumber == other.accountNumber;
    }
    
    bool operator<(const Account& other) const {
        return accountNumber < other.accountNumber;
    }
    
    Account& operator+=(T amount) {
        deposit(amount);
        return *this;
    }
    
    Account& operator-=(T amount) {
        withdraw(amount);
        return *this;
    }
    
    // Stream operators
    friend std::ostream& operator<<(std::ostream& os, const Account& account) {
        os << "Account: " << account.accountNumber 
           << ", Holder: " << account.accountHolder
           << ", Balance: " << account.balance;
        return os;
    }
    
    // Methods
    void deposit(T amount) {
        if (amount > 0) {
            balance += amount;
            addTransaction("Deposit: +" + std::to_string(amount));
        }
    }
    
    bool withdraw(T amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            addTransaction("Withdrawal: -" + std::to_string(amount));
            return true;
        }
        addTransaction("Failed withdrawal attempt: -" + std::to_string(amount));
        return false;
    }
    
    T getBalance() const {
        accessCount["balance"]++;
        return balance;
    }
    
    const std::string& getAccountNumber() const { return accountNumber; }
    const std::string& getAccountHolder() const { return accountHolder; }
    
    void displayHistory() const {
        std::cout << "\nTransaction History for " << accountHolder << ":\n";
        for (const auto& transaction : transactionHistory) {
            std::cout << "  " << transaction << "\n";
        }
    }
    
    void displayAccessStats() const {
        std::cout << "\nAccess Statistics for " << accountHolder << ":\n";
        for (const auto& pair : accessCount) {
            std::cout << "  " << pair.first << ": " << pair.second << " times\n";
        }
    }

private:
    void addTransaction(const std::string& transaction) {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        std::string timestamp = std::ctime(&time_t);
        timestamp.pop_back(); // Remove newline
        transactionHistory.push_back(timestamp + " - " + transaction);
    }
};

// Banking System using STL containers
class BankingSystem {
private:
    std::map<std::string, std::unique_ptr<Account<double>>> accounts;
    std::unordered_map<std::string, std::vector<std::string>> customerAccounts;
    
public:
    // RAII - constructor acquires resources, destructor cleans up
    BankingSystem() {
        std::cout << "Banking System initialized\n";
    }
    
    ~BankingSystem() {
        std::cout << "Banking System shutting down\n";
    }
    
    // Move semantics for account creation
    void createAccount(std::string accountNumber, std::string holder, double initialBalance) {
        auto account = std::make_unique<Account<double>>(accountNumber, holder, initialBalance);
        
        // Move the account into the map
        accounts[accountNumber] = std::move(account);
        customerAccounts[holder].push_back(accountNumber);
        
        std::cout << "Account " << accountNumber << " created for " << holder << "\n";
    }
    
    // Iterator safety demonstration
    void displayAllAccounts() const {
        std::cout << "\n=== All Accounts ===\n";
        for (auto it = accounts.begin(); it != accounts.end(); ++it) {
            std::cout << *it->second << std::endl;
        }
    }
    
    // Safe iterator usage
    void processAccounts() {
        std::cout << "\n=== Processing Accounts ===\n";
        
        // Create a copy of account numbers to avoid iterator invalidation
        std::vector<std::string> accountNumbers;
        for (const auto& pair : accounts) {
            accountNumbers.push_back(pair.first);
        }
        
        // Process accounts safely
        for (const auto& accountNumber : accountNumbers) {
            auto it = accounts.find(accountNumber);
            if (it != accounts.end()) {
                // Safe to modify account through iterator
                it->second->deposit(10.0); // Interest payment
            }
        }
    }
    
    // Template specialization for different account types
    template<typename T>
    void createTypedAccount(const std::string& number, const std::string& holder, T balance) {
        if constexpr (std::is_same_v<T, double>) {
            createAccount(number, holder, balance);
        } else if constexpr (std::is_same_v<T, int>) {
            createAccount(number, holder, static_cast<double>(balance));
        }
    }
    
    // STL algorithms demonstration
    void findHighBalanceAccounts(double threshold) const {
        std::cout << "\n=== High Balance Accounts (>" << threshold << ") ===\n";
        
        std::vector<std::string> highBalanceAccounts;
        std::copy_if(accounts.begin(), accounts.end(),
                    std::back_inserter(highBalanceAccounts),
                    [threshold](const auto& pair) {
                        return pair.second->getBalance() > threshold;
                    });
        
        for (const auto& accountNumber : highBalanceAccounts) {
            auto it = accounts.find(accountNumber);
            if (it != accounts.end()) {
                std::cout << *it->second << std::endl;
            }
        }
    }
    
    // Smart pointer usage
    std::shared_ptr<Account<double>> getAccount(const std::string& accountNumber) const {
        auto it = accounts.find(accountNumber);
        if (it != accounts.end()) {
            // Return a shared_ptr (though this is a bit artificial for this example)
            return std::shared_ptr<Account<double>>(it->second.get(), [](Account<double>*){});
        }
        return nullptr;
    }
    
    // Operator overloading for banking operations
    BankingSystem& operator+=(const std::pair<std::string, double>& deposit) {
        auto it = accounts.find(deposit.first);
        if (it != accounts.end()) {
            it->second->deposit(deposit.second);
        }
        return *this;
    }
    
    BankingSystem& operator-=(const std::pair<std::string, double>& withdrawal) {
        auto it = accounts.find(withdrawal.first);
        if (it != accounts.end()) {
            it->second->withdraw(withdrawal.second);
        }
        return *this;
    }
    
    // Function object for sorting
    struct AccountComparator {
        bool operator()(const std::pair<std::string, std::unique_ptr<Account<double>>>& a,
                       const std::pair<std::string, std::unique_ptr<Account<double>>>& b) const {
            return a.second->getBalance() > b.second->getBalance();
        }
    };
    
    void displayAccountsByBalance() const {
        std::cout << "\n=== Accounts Sorted by Balance ===\n";
        
        std::vector<std::pair<std::string, std::unique_ptr<Account<double>>>> sortedAccounts;
        for (auto& pair : accounts) {
            sortedAccounts.push_back(std::move(pair));
        }
        
        std::sort(sortedAccounts.begin(), sortedAccounts.end(), AccountComparator{});
        
        for (const auto& pair : sortedAccounts) {
            std::cout << *pair.second << std::endl;
        }
    }
};

int main() {
    std::cout << "=== Comprehensive Banking System Demo ===\n";
    
    BankingSystem bank;
    
    // Create accounts using templates
    bank.createAccount("ACC001", "Alice Johnson", 1000.0);
    bank.createAccount("ACC002", "Bob Smith", 2500.0);
    bank.createAccount("ACC003", "Charlie Brown", 500.0);
    bank.createAccount("ACC004", "Alice Johnson", 1500.0); // Same customer, different account
    
    // Display all accounts
    bank.displayAllAccounts();
    
    // Demonstrate operator overloading
    bank += std::make_pair("ACC001", 200.0);  // Deposit
    bank -= std::make_pair("ACC002", 300.0);  // Withdrawal
    
    // Process accounts (demonstrates iterator safety)
    bank.processAccounts();
    
    // Find high balance accounts using STL algorithms
    bank.findHighBalanceAccounts(1000.0);
    
    // Display accounts sorted by balance
    bank.displayAccountsByBalance();
    
    // Demonstrate smart pointers
    auto account = bank.getAccount("ACC001");
    if (account) {
        std::cout << "\nRetrieved account: " << *account << std::endl;
        account->displayHistory();
        account->displayAccessStats();
    }
    
    // Demonstrate move semantics
    std::cout << "\n=== Move Semantics Demo ===\n";
    Account<double> account1("TEMP001", "Temp User", 100.0);
    Account<double> account2 = std::move(account1);  // Move constructor
    std::cout << "After move: " << account2 << std::endl;
    
    // Demonstrate Rule of 5
    std::cout << "\n=== Rule of 5 Demo ===\n";
    Account<double> account3("TEMP002", "Another User", 200.0);
    Account<double> account4 = account3;  // Copy constructor
    account4 = account2;  // Copy assignment
    
    std::cout << "\n=== End of Demo ===\n";
    return 0;
}

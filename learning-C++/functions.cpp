#include <iostream>
#include <iomanip>
 // it is fine for dunctions to share same name, but must have different params
 // function name + parameters = function signature. each one must have a specific signature. 

 // do a banking program, allows user to deposit, withdraw and showbalance


// do this later, to_lower that converts string to lowercase
// std::string to_lower(std::string s){
//    for( char& ch: s){

//    }
// }



double addBalance(std::string name, double userBalance, double amountToBeAdded){
   std::cout<< "/nHi " << name << "\n Your balance has been credited with " << amountToBeAdded << "and your balance is " << userBalance+amountToBeAdded << std::endl;
   return userBalance += amountToBeAdded;
    
   
}

double subtractBalance(std::string name, double userBalance, double amountToBeSubtracted){
   std::cout<< "Hi " << name << ", your balance has been credited with " << amountToBeSubtracted << "and your balance is " << userBalance-amountToBeSubtracted << std::endl;
   return userBalance -= amountToBeSubtracted;
   
   
}

double bankBalance(std::string name, double userBalance){
   std::cout<< "Hi " << name << "\n Your balance is " << std::fixed << std::setprecision(2) << userBalance << std::endl;
   return userBalance;
   
}
int main(){

   std::string name;
   double amount;
   double userBalance = 0.0;
   char userActionType;  // use '' for char, use "" for string
   std::cout << "************ Welcome to GTBANK *************\n";
   std::cout << "Enter your name\n";
   std::cin >> name;

   // That error means: switch only works on integral or enum types (e.g., int, char, enum). 
   // You’re trying to switch on a string, and case "" is a string literal, which isn’t allowed.
   
   std::cout << "Do you want to deposit money, withdraw or show balance?" << std::endl;
   std::cout << "d for deposit, w for withdraw, b for balance \n";
   std::cin >> userActionType;

   // if(d){

   // }
   switch(userActionType){
      case 'd':
         std::cout << "How much do you want to deposit";
         std::cin >> amount;
         addBalance(name, userBalance, amount);
         break;
      case 'b':
         bankBalance(name, userBalance);
         break;
      case 'w': 
         std::cout << "How much do you want to withdraw";
         std::cin >> amount;
         subtractBalance(name, userBalance, amount);
         break;
      default:
        std::cout<<"You put in wrong response \n";
         break;
   }

   std::cout <<  "****Thanks for banking with us **********" ;

   return 0;
}
#include <iostream>
 // its an header file that contains functions for basic i/o operations.
using namespace std;

namespace first{
    int x= 1;
}

namespace second {
    int x = 2;
}

int main(){
    
    // there are two means of declaring variables, decoration and assignment. 

    int x;  // declaration, determine its type first
    x = 5;  // assignment

    // integers
    int age = 21;
    int number = 5;
    // double number including decimal

    double temperature = 23.7;

    // single character or char, char can only store one data type, if you add two
    // there'd be an overflow. e.g doing char value = "BX" would cause an overflow.  
    char grade = 'A';
    char initial = 'B';

    // boolean, can only have two states.
    bool student = true;

    // string, contains sequence of characters
    string name = "Tola";

    // const keyword, tells the compiler that a value can't be modified. read-only

    double pi = 22.7;

   // :: is known as a scope resolution operator, so in the namespace above, first::x returns value of x in namespace first.
   // namespaces allows you to be able to give different values to same variable so far namespaces are different.



    // type defs
    // typedef = reserved keyword used to create an additional name for another data type.
    //           new identifier for an existing type, helps with readability and reduces type.

    // it basically types. gives you a new identifier for an operation, but use USING now. 

    // with typedef:
    typedef std::string text_t;
    // the above two mean same thing.


    //Arithmetic operations. they both mean same thing.
    //Addition
    int students = 30;
    students++; // to add one
    students += 40; // add 40 to initial students

    // SUBTRACTION works same way too.
    //Multiplication works same way too, just use the * symbol.
    //Division, works same way too, just use / symbol, forward slash.

    // to get remainder too, just use % operator, modulo operator. 
    // in summary, Arithmetic operators in C++ uses PEMDAS math operation.

    // type conversion: converts a value of one data type to another,
    // implicit: automatic, and explicit: specify the new data type prior
    // to cast type, do (double) or (char), put in parenthesis
    

    // use getline function if you want your name to have spaces.
    // now if you accept an input before getline, it doesnt allow u to fill in an input in the getline part.
    // to solve this, do this: getline(cin >> ws, name)
    string myName;
    int myAge;

    cout<< "What's your age dawgski"<<'\n';
    cin >> myAge;


    cout << "What is your name"<<'\n';
    getline(cin >> ::ws, myName);

   
    cout << "Oh hi, welcome " << myName << endl << "you are quite matured for your age " << myAge << endl;

    // Useful math functions
    // to get max and min, do max(x,y) and min(x,y), 
    // for power, import c.math and do pow(x,y) where y is number to be raised to,
    // for root, do sqrt. for absolute value, abs
    // to round, do round(x)
    // to round up, do ceil(x)
    // to round down, do floor(x)

    cout<<"I like Pizza "<< endl;
    cout << " its a nice snack";
    return 0; // if ran successfully

}
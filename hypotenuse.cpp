// a function to calculate hypotenuse of a triangle

#include <iostream>
#include <cmath>
using namespace std;

int main(){

    // program for pythagoras theorem.
    double opposite;
    double adjacent;
    double hypotenuse;


    // std::cout << "Hello, Welcome to the hypotenuse calculator" << std::endl;

    // std::cout << "I'd be collecting some values fom you, adjacent and hypotenuse" << std::endl;

    // cout << "Now input your adjacent value" << endl;
    // cin >> adjacent;

    // cout << "Opposite value is" << "\n";
    // cin >> opposite;

    // cout << "Your hypotenuse is: " << endl << ceil(sqrt(pow(opposite,2) + pow(adjacent, 2)))<< "units"<< endl;

    int month;
    // if, else if and else statements work as same as js. 
    // switch alternative to writing many else ifs

    switch(month){
        case 1:
            cout<<"this is january"<<endl;
            break;
        case 2:
            cout << "this is February" << endl;
            break;
        case 3:
            cout << "This is March" << endl;
            break;
        case 4:
            cout << "This is April" << endl;
            break;
        case 5:
            cout << "This is May" << endl;
            break;
        default:
            cout<< "only 5 months are specified here";

    };

    // ternary operator, exact same as JS , ? and then :

    //Logical operators. && , || and !
    // you should be able to build a basic calculator or converter with this stuff.

    // now, useful strings in C++;
    // say we have a string. we can do name.length() , boolean name.empty returns true or false

    string name;
    cout << "Your name is "<< endl;
    getline(cin, name);
   // name.empty() ? cout<< "Name is empty" : 
   // cout<< "Name is " << name << " has length " << name.length()<< endl;
    

    // also name.clear() clears name, and .append('x') , adds something to the name
    name.append("@gmail.com");
   // cout << "Now your email is " << name;

    // name.at(0), returns char at index 0, name.at(1) returns char at index 1, and so on. 
    // name.insert(index,letter), it inserts at position specified

    // name.find(item), as the name implies. 
    // name.erase(startingIndex, endingIndex) cuts a string based on parameters put in.


    //WHILE LOOPS
    // while is technically an if statement that runs infinitely

    // DO-WHILE loops
    // do some block of code first, and then repeat again if condition is true

    // do {
    //    // cin >> name;
    //     cout << "Name must be Agunbiade" << endl;
    // }
    // while(name != "Agunbiade");

    //FOR LOOPS, work same way in JS, for(int i=0; i < a limit; i++){}


    // break keyword: break out of a loop, continue keyword: skip current iteration

    // generating random numbers , we need to initialize a starting point, or a seed
    // srand(time(0)) or srand(time(NULL)), IMPORT <ctime> as headers 

    srand(time(NULL));

    int randomNumber = rand() % 5 + 1;

    switch(randomNumber){
        case 1:
            cout << "You won a lucky pencil" << endl;
            break;
        case 2:
            cout << "You won a lucky book" << endl;
            break;
        case 3:
            cout << "You won a free hen" << endl;
            break;
        case 4:
            cout << "You won a free iphone" << endl;
            break;
        case 5:
            cout << "You won a new HOUSE!!" << endl;
            break;
        default:
            cout<<"You can only get between numbers 0-4";
            break;
        
    }

   // cout << randomNumber ;
    return 0;
}
#include <iostream>

class HelloWorld{
    public:
    int number;
    std::string words;

    HelloWorld(std::string message, int numberOfTimesToPrint){
        this->words = message;
        this->number = numberOfTimesToPrint;
        
    }
    void printMessage(){
        for(int i = 0; i < number; i++){
            std::cout << this->words << std::endl;
        }
    }
    ~HelloWorld(){
        std::cout<<"memoy clear" << std::endl;
    };
};

int main (){
   // HelloWorld values;
    HelloWorld greetings("hiii", 5);
    greetings.printMessage();
    
    return 0;
}
// simple average calculator

#include <iostream>


class Student{
    public:
     std::vector<int> scores;

        void addScores(int score){
           
            scores.push_back(score);
        }

        double returnAverage(){
            int sum = 0;
            for(int i = 0; i < scores.size(); i++){
                 sum = sum + scores[i];
            }
            return sum / scores.size();    

        }

};

int main(){
    Student student;
    int amount;
    int score;

    std::cout << "How many subjects do you want to submit?" << std::endl;
    std::cin >> amount;

    for(int i=0; i < amount; ++i){
        std::cout << "What's course score for course "<< i << std::endl;
        std::cin >> score;
        student.addScores(score);
    }
    
    std::cout << "average is " << student.returnAverage() << std::endl;
    return 0;
}
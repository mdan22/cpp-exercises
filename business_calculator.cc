#include <iostream>
#include <string>

    int counter = 0;

    double calculateProfit(double capital, double earnings, int years) {
        std::cout<<counter<<". year: ";
        std::cout<<"capital = "<<capital<<std::endl;
        capital += capital*0.1+ earnings;
        years--;
        counter++;
        return years >= 0 ? calculateProfit(capital, earnings, years) : capital;
    }
    
    int main() {
        double in1;
        double in2;
        double in3;
        
        std::cout << "Enter capital: ";
        std::cin >> in1;

        std::cout << "Enter yearly earnings: ";
        std::cin >> in2;

        std::cout << "Enter years: ";
        std::cin >> in3;

        std::cout<<"capital = "<<calculateProfit(in1, in2, in3)<<std::endl;
        return 0;
    }

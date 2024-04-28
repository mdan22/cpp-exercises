#include <iostream>
#include <string>
#include <vector>

std::string intToRoman(int num) {
    std::vector<int> values = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    std::vector<std::string> symbols = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX","V", "IV", "I"};
    std::string result = "";
    size_t i = 0;
        while ( i < values.size())
        {
            if (num/values[i] >= 1)
            {
                result += symbols[i];
                num -= values[i];
            }
            else {
                i++;
            }
        }
    return result;
}

int main(int argc, char const *argv[])
{
    std::cout<<"num = 1994, roman = "<<intToRoman(1994)<<std::endl;
    return 0;
}

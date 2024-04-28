#include <iostream>
#include <string>
    bool isPalindrome(int x) {
        std::string numStr = std::to_string(x);
        for (size_t i = 0; i < numStr.length()/2; i++)
        {
            if (numStr[i] != numStr[numStr.length()-1-i])
            {
                return false;
            }            
        }
        return true;
    }
    int main(int argc, char const *argv[])
    {
        std::cout << isPalindrome(121);
        std::cout << isPalindrome(122);
        std::cout << isPalindrome(13431);
        std::cout << isPalindrome(1221);
        std::cout << isPalindrome(12112);

        return 0;
    }
    
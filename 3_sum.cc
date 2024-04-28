#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

class Solution {
public:
    int threeSumClosest(std::vector<int>& nums, int target) {
        int num1 = 0;
        int num2 = 0;
        int num3 = 0;
        int sum = 0;
        int minDiff = INT_MAX;
        for (size_t i = 0; i < nums.size(); i++)
        {
            num1 = nums[i];
            for (size_t j = i+1; j < nums.size(); j++)
            {
                num2 = nums[j];
                for (size_t k = j+1; k < nums.size(); k++)
                {
                    num3 = nums[k];
                    int tempSum = num1 + num2 + num3 ;
                    int diff = std::abs(tempSum - target);
                    if (diff < minDiff)
                    {
                        minDiff = diff;
                        sum = tempSum;
                        if (minDiff == 0)
                        {
                            return sum;
                        }
                    }
                }
            }         
        }
        return sum;
    }
};

int main(int argc, char const *argv[])
{
    std::vector<int> v = {-1,2,1,-4};
    Solution s = Solution();
    int result = s.threeSumClosest(v,1);
    std::cout<<"result = "<<result<<std::endl;
    return 0;
}
    
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>


class Solution {
public:
    int threeSumClosest(std::vector<int>& nums, int target) {
        size_t n = nums.size();
        int minDiff = INT_MAX;
        int closestSum;

        std::sort(nums.begin(), nums.end());

        for (size_t i = 0; i < n-2; i++)
        {
            int left = i + 1;
            int right = n-1;
            while (left<right)
            {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum < target)
                {
                    left++;
                }
                else if (sum > target)
                {
                    right++;
                }
                else
                {
                    return sum;
                }
                
                int diff = std::abs(sum - target);
                if (diff < minDiff)
                {
                    minDiff = diff;
                    closestSum = sum;
                }               
                
            }
            
  
        }
        return closestSum;
    }
};

int main(int argc, char const *argv[])
{
    std::vector<int> v = {-1,2,1,-4};
    Solution s = Solution();
    int ex1 = s.threeSumClosest(v,1);
    std::cout<<"ex1 = "<<ex1<<std::endl;

    std::vector<int> v2 = {0,0,0};
    int ex2 = s.threeSumClosest(v2,1);
    std::cout<<"ex2 = "<<ex2<<std::endl;

    return 0;
}
    
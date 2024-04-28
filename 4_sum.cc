#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {
    std::vector<std::vector<int>> result;
    int n = nums.size();
    
    if (n < 4) {
        return result;
    }
    
    std::sort(nums.begin(), nums.end());
    
    for (int i = 0; i < n - 3; ++i) {
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }
        
        for (int j = i + 1; j < n - 2; ++j) {
            if (j > i + 1 && nums[j] == nums[j - 1]) {
                continue;
            }
            
            int left = j + 1;
            int right = n - 1;
            
            while (left < right) {
                long sum = static_cast<long>(nums[i]) + nums[j] + nums[left] + nums[right];
                
                if (sum == target) {
                    result.push_back({nums[i], nums[j], nums[left], nums[right]});
                    while (left < right && nums[left] == nums[left + 1]) {
                        ++left;
                    }
                    while (left < right && nums[right] == nums[right - 1]) {
                        --right;
                    }
                    ++left;
                    --right;
                } else if (sum < target) {
                    ++left;
                } else {
                    --right;
                }
            }
        }
    }
    
    return result;
}

int main() {
    std::vector<int> nums1 = {1, 0, -1, 0, -2, 2};
    int target1 = 0;

    std::cout << "Input: nums = [1, 0, -1, 0, -2, 2], target = " << target1 << "\n";
    std::vector<std::vector<int>> result1 = fourSum(nums1, target1);
    for (const auto& quadruplet : result1) {
        std::cout << "[";
        for (int num : quadruplet) {
            std::cout << num << " ";
        }
        std::cout << "]";
    }
    std::cout << "\n";

    std::vector<int> nums2 = {2, 2, 2, 2, 2};
    int target2 = 8;

    std::cout << "Input: nums = [2, 2, 2, 2, 2], target = " << target2 << "\n";
    std::vector<std::vector<int>> result2 = fourSum(nums2, target2);
    for (const auto& quadruplet : result2) {
        std::cout << "[";
        for (int num : quadruplet) {
            std::cout << num << " ";
        }
        std::cout << "]";
    }
    std::cout << "\n";

    return 0;
}

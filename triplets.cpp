#include <vector>
#include <iostream>
#include <map>
#include <algorithm>

// Given an integer array nums, return all the triplets 
// [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

// Notice that the solution set must not contain duplicate triplets.
    
class Solution 
{
public:
    using triplet = std::vector<int>;
    using triplets = std::vector<triplet>;

    triplets threeSum(std::vector<int> nums_copy) 
    {        
        triplets result;
        
        if(nums_copy.size() == 1 || nums_copy.size() == 0)
            return result;
        
        std::sort(std::begin(nums_copy), std::end(nums_copy));

        for(int i = 0; i < nums_copy.size() - 2; ++i) 
        {
            if(i > 0 && nums_copy[i] == nums_copy[i - 1])
                continue;
            
            int left = i + 1;
            int right = nums_copy.size() - 1;
            while(left < right) 
            {
                if(nums_copy[i] + nums_copy[left] + nums_copy[right] == 0) 
                {
                    triplet out = { nums_copy[i], nums_copy[left], nums_copy[right] };

                    while(left < right && nums_copy[left] == nums_copy[left + 1])
                        left++;
                    while(left < right && nums_copy[right] == nums_copy[right - 1])
                        right--;

                    result.emplace_back(std::move(out));

                    left++;
                    right--;
                } 
                else if(nums_copy[i] + nums_copy[left] + nums_copy[right] < 0) 
                {
                    left++;
                } 
                else 
                {
                    right--;
                }
            }
        }
        return result;
    }
};

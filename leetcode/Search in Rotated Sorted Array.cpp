#include <tuple>
#include <vector>
#include <cstddef>
#include <iostream>

/*
    Search in Rotated Sorted Array

    There is an integer array nums sorted in ascending order (with distinct values).

    Prior to being passed to your function, nums is possibly rotated at an unknown pivot index k (1 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].

    Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.

    You must write an algorithm with O(log n) runtime complexity.
*/

/*
    Решение:
    1. Если левый край меньше правого края, то список без вращения - выполнить бинарный поиск и вернуть индекс (exit)
    2. Ищем точку поворота, попутно сравнивая значения с целевым.
    2.1. Целевое значение совпало до точки поворота - вернуть индекс (exit)
    3. Выполнить бинарный поиск начиная с точки поворота и вернуть индекс (exit)
*/

class Solution {
public:
    using numbers = std::vector<int>;
    
    std::tuple<int, bool> find_rotated_pos(const numbers& nums, int target) {
        for (size_t i = 0; i < nums.size() - 1; ++i) {
            if (nums[i] == target) {
                return {i, true};
            }
            
            auto next = i + 1;
           
            if (nums[next] == target) {
                return {next, true};
            }
            
            if (nums[i] > nums[next]) {
               return {next, false}; 
            }
        }
        return {0, false};
    }
    
    int binary_search(const numbers& nums, size_t pos, int target) {
        size_t left = pos;
        size_t right = nums.size();

        while (left <= right) {
            int mid = (left + right) / 2; 

            if(mid < nums.size()) {
                if(nums[mid] == target) return mid;
                
                if(nums[mid] > target)
                    right = mid - 1;
                else
                    left = mid + 1;
            }
            else
                return -1;
        }
        return -1;
    }
    
    int search(const numbers& nums, int target) {
        if (nums.size() == 0)
            return -1;
        
        if (nums.size() == 1)
            return nums[0] == target ? 0 : -1;
        
        if (nums[0] < nums[nums.size() - 1])
            return binary_search(nums, 0, target);
        
        const auto [pos, found] = find_rotated_pos(nums, target);
        if(found)
            return pos;
        
        return binary_search(nums, pos, target);
    }
};
int main()
{
    Solution s;
    std::cout << s.search({4,5,6,7,0,1,2}, 0) << "\n"; 
    std::cout << s.search({1,3}, 0) << "\n"; 
    std::cout << s.search({4,5,6,7,0,1,2}, 3) << "\n"; 
    std::cout << s.search({0}, 3) << "\n"; 
    std::cout << s.search({}, 3) << "\n"; 
    std::cout << s.search({1,3}, 3) << "\n"; 
}

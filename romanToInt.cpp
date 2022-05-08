#include <unordered_map>
#include <cstdint>
#include <iostream>
#include <string>

class Solution {
public:
    int romanToInt(std::string s) {
        int result = 0;
        
        std::unordered_map<char, std::int16_t> romain = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}
        };
        
        std::int16_t prev = 0;
        for(auto rit = s.rbegin(); rit != s.rend(); ++rit)
        {
            auto value = romain[*rit];
            if(value >= prev)
            {
                result += value;
            }
            else
            {
                result -= value;
            }

            prev = value;
        }

        return result;
    }
};

int main()
{
    Solution s;

    std::cout << s.romanToInt("III") << "\n"; // 1994

    return 0;
}

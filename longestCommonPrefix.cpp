#include <string>
#include <vector>
#include <iostream>

// Write a function to find the longest common prefix string amongst an array of strings.
// If there is no common prefix, return an empty string "".

class Solution {
public:
    std::string longestCommonPrefix(const std::vector<std::string>& items) {
        std::string result;
                
        std::size_t index = 0;
        while(true)
        {
            char prefix = 0;
            std::size_t count = 0;
            for(std::size_t i = 0; i < items.size(); ++i)
            {
                const auto& item = items[i];
                if(item.size() > index)
                {
                    if(prefix == 0)
                        prefix = item[index];  

                    if(item[index] == prefix)
                        ++count;
                }
            }

            ++index;
            if(count == items.size())
                result += prefix;
            else
                return result;
        }
        return {};
    }
};

int main()
{
    Solution s;
    std::cout << s.longestCommonPrefix({"flower","flow","flight"}) << "\n"; // fl
    return 0;
}

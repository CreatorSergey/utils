#include <string>
#include <iostream>

/**
    Largest Substring Between Two Equal Characters

    Given a string s, return the length of the longest substring between two equal characters, excluding the two characters. If there is no such substring return -1.

    A substring is a contiguous sequence of characters within a string.
*/

int maxLengthBetweenEqualCharacters(const std::string& s) {
    int v[26] = {};
    int ans = -1;

    for (int i = 0; i < s.size(); i++) {

        // запоминаем первую встречную позицию
        if (!v[s[i] - 'a'])
            v[s[i] - 'a'] = i + 1;
        
        // вычитаем из текущей первую встречную позицию
        // чем раньше элемент был встречен, тем меньше будет вычтено
        // это и обеспечивает поиск максимального расстояния
        ans = std::max(ans, i - v[s[i] - 'a']);
    }

    std::cout << "\n";
    return ans;
}

int main()
{
    std::cout << maxLengthBetweenEqualCharacters("bxfra") + "\n";
    std::cout << maxLengthBetweenEqualCharacters("aa") + "\n";
    std::cout << maxLengthBetweenEqualCharacters("asdgaa") + "\n";
    return 0;
}

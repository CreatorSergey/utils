#include <string>
#include <iostream>

namespace rabin_karp
{
    const int BASE = (1 << 8);
    const int MOD = 104729;
    
    int soloHash(const std::string& s, int startIdx, int endIdx) 
    {
        int base = 1;
        int out = 0;

        for (int i = startIdx; i <= endIdx; i++) 
        {
            out *= BASE;
            out = out + s[i] * base;
            out = out % MOD;
        }
        return out;
    }

    int rollHash(const std::string& s, int startIdx, int endIdx, int prevHash) 
    {
        int leftBaseOffset = s[startIdx - 1];
        for (int i = startIdx; i < endIdx; i++) 
        {
            leftBaseOffset *= BASE;
            leftBaseOffset %= MOD;
        }

        int out = ((prevHash + MOD - leftBaseOffset) * BASE + s[endIdx]) % MOD;
        return out;
    }

    // сравнине строк
    bool stringsMatch(const std::string& needle, const std::string& haystack, std::size_t haystackOffset) 
    {
        for (std::size_t i = 0; i < needle.size(); i++) 
        {
            if(needle[i] != haystack[i + haystackOffset]) 
                return false;
        }
        return true;
    }
    
    // поиск подстроки
    int search_substring(const std::string& haystack, const std::string& needle) 
    {
        const auto haystackLen = haystack.size();
        const auto needleLen = needle.size();
        
        if(needleLen == 0) 
            return 0;

        if(needleLen > haystackLen) 
            return -1;
        
        const auto needleHash = soloHash(needle, 0, needleLen - 1);
        auto substrHash = soloHash(haystack, 0, needleLen - 1);

        if(needleHash == substrHash) 
        {
            if(stringsMatch(needle, haystack, 0)) 
                return 0;
        }
        
        for(int i = 1; i <= haystackLen - needleLen; i++) 
        {
            substrHash = rollHash(haystack, i, i + needleLen - 1, substrHash);

            if(needleHash != substrHash) 
                continue;

            if(stringsMatch(needle, haystack, i))
                return i;
        }
        
        return -1;
    }
}

int main()
{
    std::cout << "found " << rabin_karp::search_substring("Hello World", "lo World");
}

#include <cstring>
#include <iostream>

int hash(const char* text, std::size_t length) 
{
    int hash = 0;

    int d = 52;     // Константа из формулы
    int p = 65713;  // Вычисления производятся по модулю простого числа

    for(std::size_t i = 0; i < length; i++) 
        hash += (d * hash + (int)text[i]) % p;
    
    if(hash < 0)
        hash += p;

    return hash;
}

// Алгоритм Рабина — Карпа
int rabin_karp_substring_search(const char* text, const char* search) 
{
    std::size_t search_length = strlen(search);
    std::size_t text_length = strlen(text);

    // Хэш подстроки для поиска
    int search_hash = hash(search, search_length);
    for(std::size_t k = 0; k <= (text_length - search_length); k++) 
    {
        // Хэш окна
        int window_hash = hash(&text[k], search_length);
        if(search_hash == window_hash) 
        {
            // Если хэши совпали, проверяем посимвольно
            for(std::size_t i = 0; (i < search_length); i++) 
            {
                if(search[i] == text[k + i])
                {
                    if(i == (search_length - 1))
                        return k;
                }
            }
        }
    }

    // Строка не найдена
    return -1;
}

int main()
{
    std::cout << "found: " << rabin_karp_substring_search("Hello World", "World");
    return 0;
}

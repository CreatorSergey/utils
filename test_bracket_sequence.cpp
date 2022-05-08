#include <iostream>
#include <stack>

bool balanced(const std::string &s) {
    std::stack<char> stack;
    for (char c : s) {
        switch (c) {

        case '(': stack.push(')'); break;
        case '[': stack.push(']'); break;
        case '{': stack.push('}'); break;
        case '<': stack.push('>'); break;

        case ')':
        case ']':
        case '}':
        case '>':
            if (stack.empty() || stack.top() != c) {
                return false;
            }
            stack.pop();
            break;
        default:
            break;
        }
    }
    return stack.empty();
}

// проврка скобочной последовательности
void test_bracket_sequence(const std::string& s) {
    std::cout << '"' << s << "\" " << (balanced(s) ? "yes" : "no") << '\n';
}

int main() {
    test_bracket_sequence("");
    test_bracket_sequence("([()])");
    test_bracket_sequence("((())([(]))");
    test_bracket_sequence("a(b[c)d]e");
    test_bracket_sequence("a(b[c]d");
    test_bracket_sequence("b[c]d)e");
}

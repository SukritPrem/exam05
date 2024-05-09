#include <iostream>
#include <string>
#include <stack>
void calculator(std::string input, int index)
{
    std::stack<int> stack;
    int num = 0;

    while(index < input.size())
    {
        if(std::isdigit(input[index]))
        {
            num = num * 10 + (input[index] - '0');
        }
        
    }
}

int main(void)
{
    std::string input;
    int index = 0;
    calculator(input, index);
}

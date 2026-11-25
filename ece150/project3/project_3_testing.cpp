#include <iostream>
#include "project_3.cpp"

int main();

int main()
{
    int data[10] = { 5, 4, 2, 2, 2, 4, 5, 1, 4, 3 };
    std::size_t result = shift_duplicates(data, 10);
    for (std::size_t i = 0; i < 10; i++)
    {
        std::cout << data[i] << " ";
    }
    return 0;
}
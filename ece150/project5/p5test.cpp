#include <iostream>
#include "project_5.cpp"
#include <cassert>

int main();

int main()
{
    Set my_set{1, 2, 3, 7, 8, 9};
    // int array[12]{6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 7, 6};
    Set other_set{3, 4, 5, 7, 9, 11};
    std::cout << my_set << std::endl;
    //<< other_set << std::endl;
    // my_set.insert(array, 3, 11);
    my_set.merge(other_set);
    std::cout << my_set << std::endl;
    std::cout << "my set size: " << my_set.size() << std::endl;
    std::cout << "other set size: " << other_set.size() << std::endl;
    return 0;
}
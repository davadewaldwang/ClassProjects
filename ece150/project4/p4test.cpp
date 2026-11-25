#include <iostream>
#include "project_4.cpp"

int main();

int main()
{
    char a[20]{"aardvark"};
    char b[20]{"baboon"};
    char c[20]{"chipmunk"};
    char d[20]{"dino"};
    char e[20]{"elephant"};
    char *words[5]{b, c, d, e, a};
    // std::cout << compare(d, a);
    // std::cout << is_sorted(words, 5) << std::endl;
    // // std::cout << length(a) << std::endl; // Should print 5
    // // std::cout << compare(a, b) << std::endl; // Should print a negative number
    // // assign(a, b);
    // // std::cout << a << std::endl; // Should print the assigned string
    // for (std::size_t i = 0; i < 5; i++) {
    //     std::cout << words[i] << " ";
    // }
    // std::cout << std::endl;
    // std::size_t num = remove_duplicates(words, 5);
    for (std::size_t i = 0; i < 5; i++)
    {
        std::cout << words[i] << std::endl;
    }
    std::cout << std::endl;
    insert(words, 5);
    for (std::size_t i = 0; i < 5; i++)
    {
        std::cout << words[i] << std::endl;
    }
    std::cout << std::endl;
    // std::cout << std::endl;
    // std::cout << num << std::endl; // Should print the number of unique strings
    // std::cout << distance(a, b) << std::endl;

    // insertion_sort(words, 5);
    //  for (std::size_t i = 0; i < 5; i++)
    //  {
    //      std::cout << words[i] << std::endl;
    //  }
    //  std::cout << std::endl;
    return 0;
}
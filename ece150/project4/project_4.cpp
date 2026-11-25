#include "p_4_header.hpp"
#include <iostream>

std::size_t length(char const *a);
int compare(char const *str1, char const *str2);
void assign(char *str1, char const *str2);
unsigned int distance(char const *str1, char const *str2);
std::size_t is_sorted(char *array[], std::size_t capacity);
void insert(char *array[], std::size_t capacity);
void insertion_sort(char *array[], std::size_t capacity);
std::size_t remove_duplicates(char *array[], std::size_t capacity);
std::size_t find(char *array[], std::size_t capacity, char const *str);
void free_word_array(char **word_array);

std::size_t length(char const *a)
{
    std::size_t len = 0;
    while (*a != '\0')
    {
        len++;
        a++;
    }
    return len;
}

int compare(char const *str1, char const *str2)
{
    while (*str1 != '\0' && *str2 != '\0')
    {
        if (*str1 < *str2)
            return -1;
        else if (*str1 > *str2)
            return 1;
        str1++;
        str2++;
    }
    if (*str1 == '\0' && *str2 == '\0')
        return 0;
    else if (*str1 == '\0')
        return -1;
    else
        return 1;
}

void assign(char *str1, char const *str2)
{
    while (*str2 != '\0')
    {
        *str1 = *str2;
        str1++;
        str2++;
    }
    *str1 = '\0';
}

unsigned int distance(char const *str1, char const *str2)
{
    if (*str1 == '\0')
        return length(str2);

    if (*str2 == '\0')
        return length(str1);

    if (*str1 == *str2)
        return distance(str1 + 1, str2 + 1);

    return 1 + std::min({distance(str1 + 1, str2 + 1), distance(str1, str2 + 1), distance(str1 + 1, str2)});
}

std::size_t is_sorted(char *array[], std::size_t capacity)
{
    for (std::size_t i = 0; i < capacity - 1; i++)
    {
        if (compare(array[i], array[i + 1]) > 0)
        {
            return i + 1;
        }
    }
    return capacity;
}

void insert(char *array[], std::size_t capacity)
{
    char *temp = new char[length(array[capacity - 1]) + 1];
    assign(temp, array[capacity - 1]);
    std::size_t i = capacity - 1;
    while (i > 0 && compare(array[i - 1], temp) > 0)
    {
        assign(array[i], array[i - 1]);
        i--;
    }
    assign(array[i], temp);
    delete[] temp;
}

void insertion_sort(char *array[], std::size_t capacity)
{
    if (capacity <= 1)
        return;
    insertion_sort(array, capacity - 1);
    insert(array, capacity);
}

std::size_t remove_duplicates(char *array[], std::size_t capacity)
{
    if (capacity == 1)
        return 1;
    int count_unique{0};
    for (std::size_t i = 1; i < capacity; i++)
    {
        if (compare(array[i], array[i - 1]) != 0)
        {
            count_unique++;
            array[count_unique] = array[i];
        }
    }
    return count_unique + 1;
}

std::size_t find(char *array[], std::size_t capacity, char const *str)
{
    unsigned int result{distance(str, array[0])};
    for (int i = 0; i < capacity; i++)
    {
        if (compare(array[i], str) == 0)
            return i;
        if (distance(str, array[i]) < result)
            result = distance(str, array[i]);
    }
    return result;
}

void free_word_array(char **word_array)
{
    delete[] *word_array;
    delete[] word_array;
}
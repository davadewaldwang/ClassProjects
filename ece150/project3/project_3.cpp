#include <iostream>
#include <cassert>

double *geometric(double a, double ratio, std::size_t cap);
double *cross_correlation(double array0[], std::size_t cap0, double array1[], std::size_t cap1);
std::size_t shift_duplicates(int array[], std::size_t capacity);
void deallocate(double *&ptr, bool is_array, std::size_t capacity = 0);

double *geometric(double a, double ratio, std::size_t cap)
{
    double *ptr_array = new double[cap];
    for (std::size_t i = 0; i < cap; i++) // iterate through each cell
    {
        double r{1};
        for (int j = 0; j < i; j++) // determine r^i
        {
            r *= ratio;
        }
        ptr_array[i] = a * r;
    }
    return ptr_array;
}

double *cross_correlation(double array0[], std::size_t cap0, double array1[], std::size_t cap1)
{
    assert(cap0 + cap1 >= 1);

    double *ptr_array = new double[cap0 + cap1 - 1]{};

    for (std::size_t i = 0; i < cap0; i++)
    {
        for (std::size_t j = 0; j < cap1; j++)
        {
            ptr_array[i + j] += array0[i] * array1[j];
        }
    }

    return ptr_array;
}

std::size_t shift_duplicates(int array[], std::size_t capacity)
{
    std::size_t count_dupe{0};

    for (std::size_t i = 0; i < capacity - count_dupe; i++) // iterate through cells in array
    {
        for (std::size_t j = i + 1; j < capacity - count_dupe; j++) // compare every other cell until dupe of i is found
        {
            if (array[i] == array[j])
            {
                int temp = array[j];
                for (std::size_t k = j; k < capacity - count_dupe - 1; k++) // shift all elements after j to the left
                {
                    array[k] = array[k + 1];
                }
                array[capacity - count_dupe - 1] = temp; // place the duplicate at the end of the array
                count_dupe++; // increment the count of duplicates found
                j--; // decrement j to check the new value at index j in the next iteration
            }
        }
    }
    return capacity - count_dupe;
}

void deallocate(double *&ptr, bool is_array, std::size_t capacity)
{
    if (is_array)
    {
        for (std::size_t i = 0; i < capacity; i++)
        {
            ptr[i] = 0;
        }
        delete[] ptr;
    }
    else
    {
        *ptr = 0;
        delete ptr;
    }
    ptr = nullptr;
}
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cassert>


void resizeArray(double*& arr, int& capacity) 
{
    int newCapacity = capacity * 2;
    double* newArr = new double[newCapacity];
    
    for (int i = 0; i < capacity; i++)
    {
        newArr[i] = arr[i];
    }
    
    delete[] arr;
    arr = newArr;
    capacity = newCapacity;
    
    std::cout << "New capacity = " << newCapacity << std::endl;
}

void bubbleSort(double arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                double tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}


double findMin(double arr[], int size)
{
    double minVal = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] < minVal)
        {
            minVal = arr[i];
        }
    }

    return minVal;
}

double findMax(double arr[], int size)
{
    double maxVal = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > maxVal)
        {
            maxVal = arr[i];
        }
    }

    return maxVal;
}


double calculateMean(double arr[], int size)
{
    double sum = 0.0;
    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    return sum / size;
}


double calculateMedian(double arr[], int size)
{
    double* sortedArray = new double[size];
    for (int i = 0; i < size; i++)
    {
        sortedArray[i] = arr[i];
    }
    
    bubbleSort(sortedArray, size);
    
    double median;
    if (size % 2 == 0)
    {
        median = (sortedArray[size / 2 - 1] + sortedArray[size / 2]) / 2.0;
    }
    else
    {
        median = sortedArray[size / 2];
    }
    
    delete[] sortedArray;
    return median;
}


double calculateStandardDeviation(double arr[], int size, double mean)
{
    double sumSquaredDiff = 0.0;

    for (int i = 0; i < size; i++)
    {
        double difference = arr[i] - mean;
        sumSquaredDiff += difference * difference;
    }

    double variance = sumSquaredDiff / size;
    return std::sqrt(variance);
}

int main()
{
    int capacity = 5;
    double* numbers = new double[capacity];

    int size = 0;
    double number;
    
    std::cout << "Emter the collection:" << std::endl;
    
    while (std::cin >> number) {
        if (size >= capacity) {
            resizeArray(numbers, capacity);
        }
        
        numbers[size] = number;
        size++;
    }

    std::cout << "Size = " << size << std::endl;
    std::cout << "Capacity = " << capacity << std::endl;
    
    double minValue = findMin(numbers, size);
    double maxValue = findMax(numbers, size);
    double meanValue = calculateMean(numbers, size);
    double medianValue = calculateMedian(numbers, size);
    double stdDeviation = calculateStandardDeviation(numbers, size, meanValue);
    
    std::cout << "\nResults:" << std::endl;
    std::cout << "Min = " << minValue << std::endl;
    std::cout << "Max = " << maxValue << std::endl;
    std::cout << "Average = " << meanValue << std::endl;
    std::cout << "Median = " << medianValue << std::endl;
    std::cout << "Std = " << stdDeviation << std::endl;
    
    return 0;
}
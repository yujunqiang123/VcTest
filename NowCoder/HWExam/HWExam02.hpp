#pragma once
#include <iostream>

using namespace std;

int HWExam02()
{
    int number = 0;
    while (cin >> number) {
        int* data = new int[number]();

        for (int index = 0; index < number; index++) {
            cin >> data[index];
        }
        int windowSize = 0;
        cin >> windowSize;

        int maxSum = 0;
        for (int index = 0; index < number && index < windowSize; index++) {
            maxSum += data[index];
        }

        int lastSum = maxSum;
        for (int index = windowSize; index < number; index++) {
            lastSum += data[index] - data[index - windowSize];
            maxSum = maxSum > lastSum ? maxSum : lastSum;
        }
        cout << maxSum << endl;

        if (data != nullptr) {
            delete[] data;
            data = nullptr;
        }
    }
    return 0;
}
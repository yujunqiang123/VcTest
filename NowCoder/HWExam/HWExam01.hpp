#pragma once

#include <iostream>
#include <set>

using namespace std;

int HWExam01()
{
    long long number = 0;
    while (cin >> number) {
        set<long long> data;

        long long temp;
        long long index = 0;
        while(index < number) {
            cin >> temp;
            auto iter = data.find(temp);
            if (iter == data.end()) {
                data.insert(temp);
            }
            index++;
        }
        long long N = 0;
        cin >> N;

        if (N > data.size() / 2) {
            cout << -1 << endl;
            continue;
        }

        long long sum = 0;
        auto iterBegin = data.begin();
        for (long long index = 0; index < N; index++) {
            sum += *iterBegin;
            iterBegin++;
        }
        auto iterRbegin = data.rbegin();
        for (long long index = 0; index < N; index++) {
            sum += *iterRbegin;
            iterRbegin++;
        }
        cout << sum << endl;
    }
    return 0;
}
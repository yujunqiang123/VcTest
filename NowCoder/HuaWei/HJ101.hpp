#pragma once
/*
题目描述
输入整型数组和排序标识，对其元素按照升序或降序进行排序（一组测试用例可能会有多组数据）

本题有多组输入，请使用while(cin>>)处理

输入描述:
第一行输入数组元素个数
第二行输入待排序的数组，每个数用空格隔开
第三行输入一个整数0或1。0代表升序排序，1代表降序排序

输出描述:
输出排好序的数字

示例1
输入
8
1 2 4 9 3 55 64 25
0
5
1 2 3 4 5
1
输出
1 2 3 4 9 25 55 64
5 4 3 2 1
*/

#include <iostream>
#include <set>

using namespace std;

int HJ101()
{
    int numCount;
    while (cin >> numCount) {
        multiset<int> numSet;

        int temp;
        for (int index = 0; index < numCount; index++) {
            cin >> temp;
            numSet.insert(temp);
        }

        int order = 0;
        cin >> order;
        if (order == 0) {
            cout << *numSet.begin();
            for (auto iter = ++numSet.begin(); iter != numSet.end(); iter++) {
                cout << ' ' << *iter;
            }
        } else if (order == 1) {
            cout << *numSet.rbegin();
            for (auto iter = ++numSet.rbegin(); iter != numSet.rend(); iter++) {
                cout << ' ' << *iter;
            }
        }
        cout << endl;
    }
    return 0;
}
#pragma once
/*
题目描述
从输入任意个整型数，统计其中的负数个数并求所有非负数的平均值，结果保留一位小数，如果没有非负数，则平均值为0
本题有多组输入数据，输入到文件末尾，请使用while(cin>>)读入
数据范围小于1e6
输入描述:
输入任意个整数，每行输入一个。

输出描述:
输出负数个数以及所有非负数的平均值

示例1
输入
-13
-4
-7
输出
3
0.0
*/

#include <iostream>

using namespace std;

int HJ105()
{
    long long temp;
    long long numN = 0;
    long long numP = 0;
    long long sum = 0;
    while (cin >> temp) {
        if (temp == 0) {
            break;
        }

        if (temp < 0) {
            numN++;
        } else {
            numP++;
            sum += temp;
        }
    }
    printf("%d\n%.1f\n", numN, (float)sum / numP);
    return 0;
}

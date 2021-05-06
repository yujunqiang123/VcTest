#pragma once
/*
题目描述
输入一个字符串和一个整数k，截取字符串的前k个字符并输出
本题输入含有多组数据
输入描述:
1.输入待截取的字符串
2.输入一个正整数k，代表截取的长度

输出描述:
截取后的字符串

示例1
输入
abABCcDEF
6
输出
abABCc

示例2
输入
ffIKEHauv
1
bdxPKBhih
6
输出
f
bdxPKB
*/

#include <iostream>
#include <string>
using namespace std;

int HJ046()
{
    int num;
    string str;
    while (cin >> str >> num) {
        cout << str.substr(0, num) << endl;
    }

    return 0;
}
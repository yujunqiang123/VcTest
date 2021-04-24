#pragma once
/*
题目描述
计算字符串最后一个单词的长度，单词以空格隔开。

输入描述 :
输入一行，代表要计算的字符串，非空，长度小于5000。

输出描述 :
输出一个整数，表示输入字符串最后一个单词的长度。

示例1
输入
hello nowcoder
输出
8
*/

#include <iostream>
#include <string>
using namespace std;

int HJ001()
{
    string str;
    while (getline(cin, str)) {
        int pos = str.find_last_of(' ');
        if (pos != string::npos) {
            cout << str.length() - pos - 1 << endl;
        } else {
            cout << str.length() << endl;
        }
    }
    return 0;
}
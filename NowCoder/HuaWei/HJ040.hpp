#pragma once
/*
题目描述
输入一行字符，分别统计出包含英文字母、空格、数字和其它字符的个数。
本题包含多组输入。

输入描述:
输入一行字符串，可以有空格

输出描述:
统计其中英文字符，空格字符，数字字符，其他字符的个数

示例1
输入
1qazxsw23 edcvfr45tgbn hy67uj m,ki89ol.\\/;p0-=\\][
输出
26
3
10
12
*/
#include <iostream>
#include <string>
using namespace std;

enum charType
{
    CHAR_ENGLISH,
    CHAR_BLANK,
    CHAR_NUMBER,
    CHAR_OTHER,
    CHAR_TYPE_MAX
};

int HJ040()
{
#define ENGLISH_CHAR
    string str;
    while (getline(cin, str)) {
        int len = str.length();
        int number[CHAR_TYPE_MAX] = { 0 };
        for (int index = 0; index < len; index++) {
            char tempChar = str[index];
            if ('a' <= tempChar && tempChar <= 'z' ||
                'A' <= tempChar && tempChar <= 'Z') {
                number[CHAR_ENGLISH]++;
            } else if (' ' == tempChar) {
                number[CHAR_BLANK]++;
            } else if ('0' <= tempChar && tempChar <= '9') {
                number[CHAR_NUMBER]++;
            } else {
                number[CHAR_OTHER]++;
            }
        }

        for (int index = 0; index < CHAR_TYPE_MAX; index++) {
            cout << number[index] << endl;
        }
    }
    return 0;
}
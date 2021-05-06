#pragma once
/*
题目描述
一个DNA序列由A / C / G / T四个字母的排列组合组成。
G和C的比例（定义为GC - Ratio）是序列中G和C两个字母的总的出现次数除以总的字母数目（也就是序列长度）。
在基因工程中，这个比例非常重要。因为高的GC - Ratio可能是基因的起始点。

给定一个很长的DNA序列，以及要求的最小子序列长度，研究人员经常会需要在其中找出GC - Ratio最高的子序列。

本题含有多组样例输入。

输入描述 :
输入一个string型基因序列，和int型子串的长度

输出描述 :
找出GC比例最高的子串, 如果有多个输出第一个的子串

示例1
输入
AACTGTGCACGACCTGA
5
输出
GCACG
*/

#include <iostream>
#include <string>
using namespace std;

int HJ063()
{
    int len = 0;
    string str;
    while (cin >> str >> len) {
        int numGCMax = 0;
        string subStr;
        int strLen = str.length();
        for (int index = 0; index < strLen && index < len; index++) {
            if (str[index] == 'G' || str[index] == 'C') {
                ++numGCMax;
            }
        }
        subStr = str.substr(0, len);

        int numGCLast = numGCMax;
        for (int index = len; index < strLen; index++) {
            int tempNumGC = numGCLast;
            char tempCharEnd = str[index];
            char tempCharBegin = str[index-len];

            bool begin = tempCharEnd == 'G' || tempCharEnd == 'C';
            bool end = tempCharBegin == 'G' || tempCharBegin == 'C';
            if (begin == true && end == false) {
                ++tempNumGC;
            } else if (begin == false && end == true) {
                --tempNumGC;
            }

            if (tempNumGC > numGCMax) {
                numGCMax = tempNumGC;
                subStr = str.substr(index - len + 1, len);
            }
            numGCLast = tempNumGC;
        }

        cout << subStr << endl;
    }
    return 0;
}

#pragma once
/*
题目描述
Jessi初学英语，为了快速读出一串数字，编写程序将数字转换成英文：
如22：twenty two，123：one hundred and twenty three。


说明：
数字为正整数，长度不超过九位，不考虑小数，转化结果为英文小写；
输出格式为twenty two；

非法数据请返回“error”；

关键字提示：and，billion，million，thousand，hundred。

本题含有多组输入数据。

输入描述:
输入一个long型整数

输出描述:
输出相应的英文写法

示例1
输入
2356
输出
two thousand three hundred and fifty six
*/

#include <iostream>
#include <string>
using namespace std;

const string ones[] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
const string tens[] = { "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nighteen" };
const string twenties[] = { "zero", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" };
const string hundreds[] = { "hundred", "thousand", "million", "billion" };
const int ihundreds[] = { (int)1e2, (int)1e3, (int)1e6, (int)1e9, (int)1e12 };

string itoe(long long n)
{
    if (0 <= n && n <= 9) {
        return ones[n];
    } else if (10 <= n && n < 20) {
        return tens[n % 10];
    } else if (20 <= n && n < 1e2) {
        return twenties[n / 10] + (n % 10 ? " " + ones[n % 10] : "");
    }

    for (int index = 0; index < 4; index++) {
        if (n < ihundreds[index + 1]) {
            return itoe(n / ihundreds[index]) + " " + hundreds[index]
                + (n%ihundreds[index] ? (index ? " " : " and ") + itoe(n%ihundreds[index]) : "");
        }
    }
    return "";
}

int HJ042()
{
    long long N = 0;
    while (cin >> N) {
        cout << itoe(N) << endl;
    }
    return 0;
}

#pragma once
/*
题目描述
原理：ip地址的每段可以看成是一个0-255的整数，把每段拆分成一个二进制形式组合起来，然后把这个二进制数转变成
一个长整数。
举例：一个ip地址为10.0.3.193
每段数字             相对应的二进制数
10                   00001010
0                    00000000
3                    00000011
193                  11000001

组合起来即为：00001010 00000000 00000011 11000001,转换为10进制数就是：167773121，即该IP地址转换后的数字就是它了。

本题含有多组输入用例，每组用例需要你将一个ip地址转换为整数、将一个整数转换为ip地址。

输入描述:
输入
1 输入IP地址
2 输入10进制型的IP地址

输出描述:
输出
1 输出转换成10进制的IP地址
2 输出转换后的IP地址

示例1
输入
10.0.3.193
167969729
输出
167773121
10.3.3.193
*/

#include <iostream>
#include <string>
using namespace std;

int HJ033()
{
    unsigned intIp;
    string strIp;
    while (cin >> strIp >> intIp) {
        int value[4] = { 0 };
        //strIP to intIp
        for (int index = 0; index < 3; index++) {
            int dotIndex = strIp.find_first_of('.');
            if (dotIndex == string::npos) {
                break;
            }

            string subStr = strIp.substr(0, dotIndex);
            value[index] = atoi(subStr.c_str());

            strIp = strIp.substr(dotIndex + 1);
        }
        value[3] = atoi(strIp.c_str());

        unsigned res = 0;
        for (int index = 0; index < 4; index++) {
            res = value[index] | (res << 8);
        }
        cout << res << endl;

        //intIp to strIp

        for (int index = 3; index >= 0; index--) {
            value[index] = 0xFF & intIp;
            intIp = intIp >> 8;
        }
        string resStr = "";
        for (int index = 0; index < 3; index++) {
            resStr += to_string(value[index]) + '.';
        }
        resStr += to_string(value[3]);
        cout << resStr << endl;
    }

    return 0;
}
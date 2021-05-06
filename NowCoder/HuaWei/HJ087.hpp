#pragma once
/*
题目描述
密码按如下规则进行计分，并根据不同的得分为密码进行安全等级划分。

一、密码长度:
5 分: 小于等于4 个字符
10 分: 5 到7 字符
25 分: 大于等于8 个字符

二、字母:
0 分: 没有字母
10 分: 全都是小（大）写字母
20 分: 大小写混合字母

三、数字:
0 分: 没有数字
10 分: 1 个数字
20 分: 大于1 个数字

四、符号:
0 分: 没有符号
10 分: 1 个符号
25 分: 大于1 个符号

五、奖励:
2 分: 字母和数字
3 分: 字母、数字和符号
5 分: 大小写字母、数字和符号

最后的评分标准:
>= 90: 非常安全
>= 80: 安全（Secure）
>= 70: 非常强
>= 60: 强（Strong）
>= 50: 一般（Average）
>= 25: 弱（Weak）
>= 0:  非常弱

对应输出为：
VERY_SECURE
SECURE,
VERY_STRONG,
STRONG,
AVERAGE,
WEAK,
VERY_WEAK,

请根据输入的密码字符串，进行安全评定。

注：
字母：a-z, A-Z
数字：0-9

符号包含如下： (ASCII码表可以在UltraEdit的菜单view->ASCII Table查看)
!"#$%&'()*+,-./     (ASCII码：x21~0x2F)
:;<=>?@             (ASCII码：x3A~0x40)
[\]^_`              (ASCII码：x5B~0x60)
{|}~                (ASCII码：x7B~0x7E)

输入描述:
本题含有多组输入样例。
每组样例输入一个string的密码

输出描述:
每组样例输出密码等级

示例1
输入
38$@NoNoNo
123
输出
VERY_SECURE
WEAK
说明
第一组样例密码强度为95分。
第二组样例密码强度为25分。
*/

#include <iostream>
#include <string>

using namespace std;

int AnalysisPassword(const string &password)
{
    int score = 0;
    if (password.empty() == true) {
        return score;
    }

    int lenght = password.length();
    if (lenght <= 4) {
        score += 5;
    } else if (lenght <= 7) {
        score += 10;
    } else {
        score += 25;
    }

    int lowerCharNum = 0;   //小写字母数量
    int upperCharNum = 0;   //大写字母数量
    int digitNum = 0;       //数字数量
    int figureNum = 0;      //符号数量
    for (int index = 0; index <= lenght; index++) {
        char tempChar = password[index];
        if ('a' <= tempChar && tempChar <= 'z') {
            lowerCharNum++;
        } else if ('A' <= tempChar && tempChar <= 'Z') {
            upperCharNum++;
        } else if ('0' <= tempChar && tempChar <= '9') {
            digitNum++;
        } else if (('!' <= tempChar && tempChar <= '/') ||
            (':' <= tempChar && tempChar <= '@') ||
            ('[' <= tempChar && tempChar <= '`') ||
            ('{' <= tempChar && tempChar <= '~')) {
            figureNum++;
        }
    }

    if (lowerCharNum != 0 && upperCharNum != 0) {
        score += 20;
    } else if (lowerCharNum != 0 || upperCharNum != 0) {
        score += 10;
    }

    if (digitNum > 1) {
        score += 20;
    } else if (digitNum == 1) {
        score += 10;
    }

    if (figureNum > 1) {
        score += 25;
    } else if (figureNum == 1) {
        score += 10;
    }

    if (lowerCharNum != 0 && upperCharNum != 0 && digitNum != 0 && figureNum != 0) {
        score += 5;
    } else if ((lowerCharNum + upperCharNum != 0) && digitNum != 0 && figureNum != 0) {
        score += 3;
    } else if ((lowerCharNum + upperCharNum != 0) && digitNum != 0) {
        score += 2;
    }

    return score;
}

int HJ087()
{
    string password;
    while (cin>>password) {
        int score = AnalysisPassword(password);
        if (score >= 90) {
            cout << "VERY_SECURE" << endl;
        } else if (score >= 80) {
            cout << "SECURE" << endl;
        } else if (score >= 70) {
            cout << "VERY_STRONG" << endl;
        } else if (score >= 60) {
            cout << "STRONG" << endl;
        } else if (score >= 50) {
            cout << "AVERAGE" << endl;
        } else if (score >= 25) {
            cout << "WEAK" << endl;
        } else {
            cout << "VERY_WEAK" << endl;
        }
    }
    return 0;
}

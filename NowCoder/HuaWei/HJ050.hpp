#pragma once
/*
题目描述
输入一个表达式（用字符串表示），求这个表达式的值。
保证字符串中的有效字符包括[‘0’-‘9’],‘+’,‘-’, ‘*’,‘/’ ,‘(’， ‘)’,‘[’, ‘]’,‘{’ ,‘}’。且表达式一定合法。



输入描述:
输入一个算术表达式

输出描述:
得到计算结果

示例1
输入
3+2*{1+2*[-4/(8-6)+7]}
输出
25
*/

#include <iostream>
#include <string.h>

using namespace std;

int char_i = 0;//使用全局变量，防止递归产生的无线循环
int calculate(char *character)
{
    int num[100] = { 0 };
    int num_i = 0;
    char flag = '+';
    int result = 0;
    int len = strlen(character);

    while (char_i < len) {
        int num_m = 0;

        if (character[char_i] == '{' || character[char_i] == '[' || character[char_i] == '(')//先算括号里的
        {
            char_i++;
            num_m = calculate(character);
        }

        while (1) {
            if (character[char_i] >= '0' && character[char_i] <= '9') {
                num_m = num_m * 10 + character[char_i] - '0';
                char_i++;
            } else
                break;
        }

        switch (flag)//如果是加减num_i++，如果是乘除直接计算num_i不变        最后再将num[]里的所有元素相加
        {
        case '+':
            num[num_i] = num_m;
            num_i++;
            break;
        case '-':
            num[num_i] = -num_m;
            num_i++;
            break;
        case '*':
            num[num_i - 1] *= num_m;
            break;
        case '/':
            num[num_i - 1] /= num_m;
            break;
        default:
            break;
        }

        flag = character[char_i];
        if (character[char_i] == '}' || character[char_i] == ']' || character[char_i] == ')') {//结束本次递归，返回括号内运算的结果
            char_i++;
            break;
        }
        char_i++;
    }


    for (int i = 0; i < num_i; i++) {
        result += num[i];
    }

    return result;
}


int HJ050()
{
    char character[100] = { 0 };
    int result = 0;
    cin >> character;

    result = calculate(character);

    cout << result << endl;
    return 0;
}
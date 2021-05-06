#pragma once
/*
题目描述
Catcher是MCA国的情报员，他工作时发现敌国会用一些对称的密码进行通信，比如像这些ABBA，ABA，A，123321，
但是他们有时会在开始或结束时加入一些无关的字符以防止别国破解。比如进行下列变化 ABBA->12ABBA,ABA->ABAKK,123321->51233214。
因为截获的串太长了，而且存在多种可能的情况（abaaab可看作是aba,或baaab的加密形式），Cathcer的工作量实在是太大了，
他只能向电脑高手求助，你能帮Catcher找出最长的有效密码串吗？

本题含有多组样例输入。

输入描述:
输入一个字符串

输出描述:
返回有效密码串的最大长度

示例1
输入
ABBA
输出
4
*/

#include <iostream>
#include <string>

using namespace std;

//返回以 (indexL + indexR) / 2 为中心的回文子串的半长
int PalindromicLengthHalf(int indexL, int indexR, int strLen, const char * const str)
{
    int length = 0;
    while (indexL >= 0 && indexR <= strLen - 1) {
        if (str[indexL--] == str[indexR++]) {
            length++;
        } else {
            break;
        }
    }

    return length;
}

int HJ032()
{
    string password;
    while (cin >> password) {
        int maxLength = 0;
        int passwordLen = password.length();
        const char* const passwordTemp = password.c_str();
        for (int indexL = 0, indexR = 0; indexR < passwordLen; ) {
            int tempLength = PalindromicLengthHalf(indexL, indexR, passwordLen, passwordTemp);
            if (indexL < indexR) {
                tempLength = 2 * tempLength;
                indexL++;
            } else {
                tempLength = 2 * tempLength - 1;
                indexR++;
            }
            maxLength = maxLength > tempLength ? maxLength : tempLength;
        }

        cout << maxLength << endl;
    }
    return 0;
}

//Manacher 算法详解
//http://www.cxyxiaowu.com/2869.html
int HJ032_Manacher()
{
    string password;
    while (cin >> password) {
        int maxLength = 0;
        int passwordTempLen = password.length() * 2 + 1;

        int* arrayP = new int[passwordTempLen];
        char* passwordTemp = new char[passwordTempLen];
        memset(arrayP, 0, sizeof(int) * passwordTempLen);
        memset(passwordTemp, 0, sizeof(char) * passwordTempLen);

        for (int index = 0; index < passwordTempLen; index++) {
            if (index % 2) {
                passwordTemp[index] = password[index / 2];
            } else {
                passwordTemp[index] = '#';
            }
        }

        int centerIndex = 0;
        int maxRightIndex = 0;
        for (int index = 0; index < passwordTempLen; index++) {
            if (index >= maxRightIndex) {
                int valueP = PalindromicLengthHalf(index, index, passwordTempLen, passwordTemp);
                arrayP[index] = valueP;
                if (maxRightIndex < (index + valueP)) {
                    centerIndex = index;
                    maxRightIndex = index + valueP;
                }
            } else {
                int mirrorIndex = 2 * centerIndex - index;
                int delta = maxRightIndex - index;
                if (delta < arrayP[mirrorIndex]) {
                    arrayP[index] = delta;
                } else if (delta > arrayP[mirrorIndex]) {
                    arrayP[index] = arrayP[mirrorIndex];
                } else {
                    int temp = PalindromicLengthHalf(index - arrayP[mirrorIndex], index + arrayP[mirrorIndex], passwordTempLen, passwordTemp);
                    int maxRightIndexTemp = index + arrayP[mirrorIndex] + temp;
                    if (maxRightIndexTemp > maxRightIndex) {
                        maxRightIndex = maxRightIndexTemp;
                        centerIndex = index;
                    }
                    arrayP[index] = arrayP[mirrorIndex] + temp;
                }
            }
        }

        //for (int index = 0; index < passwordTempLen; index++) {
        //    cout << passwordTemp[index];
        //}
        //cout << endl;

        for (int index = 0; index < passwordTempLen; index++) {
            //cout << arrayP[index];
            maxLength = maxLength > arrayP[index] ? maxLength : arrayP[index];
        }
        //cout << endl;

        delete[] arrayP;
        arrayP = nullptr;

        delete[] passwordTemp;
        passwordTemp = nullptr;
        cout << maxLength - 1 << endl;
    }
    return 0;
}
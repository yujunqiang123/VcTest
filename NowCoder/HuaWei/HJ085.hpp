#pragma once
/*
题目描述
给定一个仅包含小写字母的字符串，求它的最长回文子串的长度。
所谓回文串，指左右对称的字符串。
所谓子串，指一个字符串删掉其部分前缀和后缀（也可以不删）的字符串
（注意：记得加上while处理多个测试用例）

输入描述:
输入一个仅包含小写字母的字符串

输出描述:
返回最长回文子串的长度

示例1
输入
cdabbacc
输出
4
说明
abba为最长的回文子串
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

int HJ085()
{
    string password;
    while (cin>> password) {
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
int HJ085_Manacher()
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
#pragma once
/*
题目描述
计算最少出列多少位同学，使得剩下的同学排成合唱队形

说明：

N位同学站成一排，音乐老师要请其中的(N-K)位同学出列，使得剩下的K位同学排成合唱队形。
合唱队形是指这样的一种队形：设K位同学从左到右依次编号为1，2…，K，他们的身高分别为T1，T2，…，TK，
则他们的身高满足存在i（1<=i<=K）使得T1<T2<......<Ti-1<Ti>Ti+1>......>TK。

你的任务是，已知所有N位同学的身高，计算最少需要几位同学出列，可以使得剩下的同学排成合唱队形。

注意不允许改变队列元素的先后顺序
请注意处理多组输入输出！

输入描述:
整数N

输出描述:
最少需要几位同学出列

示例1
输入
8
186 186 150 200 160 130 197 200
输出
4
*/

#include <iostream>

using namespace std;

int HJ024()
{
    int studentNum = 0;
    while (cin >> studentNum) {
        int* studentHight = new int[studentNum];
        for (int index = 0; index < studentNum; index++) {
            cin >> studentHight[index];
        }

        //寻找每一个学生左边的最长递增子序列
        int* studentHightAdd = new int[studentNum];
        for (int index = 0; index < studentNum; index++) {
            int max = 0;
            for (int indexL = 0; indexL < index; indexL++) {
                if (studentHight[index] > studentHight[indexL] &&
                    max < studentHightAdd[indexL]) {
                    max = studentHightAdd[indexL];
                }
            }
            studentHightAdd[index] = max + 1;
        }

        //寻找每一个学生右边边的最长递减子序列
        int* studentHightDec = new int[studentNum];
        for (int index = studentNum-1; index >= 0; index--) {
            int max = 0;
            for (int indexR = studentNum - 1; indexR > index; indexR--) {
                if (studentHight[index] > studentHight[indexR] &&
                    max < studentHightDec[indexR]) {
                    max = studentHightDec[indexR];
                }
            }
            studentHightDec[index] = max + 1;
        }

        //for (int index = 0; index < studentNum; index++) {
        //    cout << studentHightAdd[index] << ' ';
        //}
        //cout << endl;
        //for (int index = 0; index < studentNum; index++) {
        //    cout << studentHightDec[index] << ' ';
        //}
        //cout << endl;
        int min = studentNum + 1;
        for (int index = 0; index < studentNum; index++) {
            int delNum = studentNum - (studentHightAdd[index] + studentHightDec[index] - 1);
            min = min < delNum ? min : delNum;
        }
        cout << min << endl;

        if (studentHightDec != nullptr) {
            delete[] studentHightDec;
            studentHightDec = nullptr;
        }
        if (studentHightAdd != nullptr) {
            delete[] studentHightAdd;
            studentHightAdd = nullptr;
        }
        if (studentHight != nullptr) {
            delete[] studentHight;
            studentHight = nullptr;
        }
    }
    return 0;
}


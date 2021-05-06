﻿#pragma once
/*
题目描述
问题描述：数独（Sudoku）是一款大众喜爱的数字逻辑游戏。玩家需要根据9X9盘面上的已知数字，
推算出所有剩余空格的数字，并且满足每一行、每一列、每一个粗线宫内的数字均含1-9，并且不重复。
输入：
包含已知数字的9X9盘面数组[空缺位以数字0表示]
输出：
完整的9X9盘面数组

输入描述:
包含已知数字的9X9盘面数组[空缺位以数字0表示]

输出描述:
完整的9X9盘面数组

示例1
输入
0 9 2 4 8 1 7 6 3
4 1 3 7 6 2 9 8 5
8 6 7 3 5 9 4 1 2
6 2 4 1 9 5 3 7 8
7 5 9 8 4 3 1 2 6
1 3 8 6 2 7 5 9 4
2 7 1 5 3 8 6 4 9
3 8 6 9 1 4 2 5 7
0 4 5 2 7 6 8 3 1

输出
5 9 2 4 8 1 7 6 3
4 1 3 7 6 2 9 8 5
8 6 7 3 5 9 4 1 2
6 2 4 1 9 5 3 7 8
7 5 9 8 4 3 1 2 6
1 3 8 6 2 7 5 9 4
2 7 1 5 3 8 6 4 9
3 8 6 9 1 4 2 5 7
9 4 5 2 7 6 8 3 1
*/

#include <iostream>
#include <set>
using namespace std;
#define SIZE 9

void InitOption(set<int> &option)
{
    option.insert(1);
    option.insert(2);
    option.insert(3);
    option.insert(4);
    option.insert(5);
    option.insert(6);
    option.insert(7);
    option.insert(8);
    option.insert(9);
}

void CheckH(int row, int col, int* sudo, set<int> &option)
{

}

int HJ044()
{
    set<int> option[SIZE][SIZE];//备选数字
    int sudo[SIZE][SIZE] = { 0 };
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            cin >> sudo[row][col];
        }
    }

    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (sudo[row][col] == 0) {
                InitOption(option[row][col]);
                //横向查看

                //纵向查看
                //子方框查看
            }
        }
    }
    return 0;
}
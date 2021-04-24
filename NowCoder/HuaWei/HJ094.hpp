#pragma once
/*
题目描述
请实现一个计票统计系统。你会收到很多投票，其中有合法的也有不合法的，请统计每个候选人得票的数量以及不合法的票数。
本题有多组样例输入。
输入描述:
输入候选人的人数n，第二行输入n个候选人的名字（均为大写字母的字符串），第三行输入投票人的人数，第四行输入投票。

输出描述:
按照输入的顺序，每行输出候选人的名字和得票数量，最后一行输出不合法的票数。

示例1
输入
4
A B C D
8
A D E CF A GG A B
输出
A : 3
B : 1
C : 0
D : 1
Invalid : 3
*/

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int HJ094()
{
    int peopleNum;
    while (cin >> peopleNum) {
        if (peopleNum == -1) {
            break;
        }

        vector<string> peopleName;
        unordered_map<string, int> peopleVolite;

        string name;
        for (int index = 0; index < peopleNum; index++) {
            cin >> name;
            peopleName.push_back(name);
            peopleVolite[name] = 0;
        }

        int invalidNum = 0;
        int voliteNum = 0;
        cin >> voliteNum;
        for (int index = 0; index < voliteNum; index++) {
            cin >> name;
            auto iter = peopleVolite.find(name);
            if (iter != peopleVolite.end()) {
                iter->second++;
            } else {
                invalidNum++;
            }
        }

        for (auto iter = peopleName.begin(); iter != peopleName.end(); iter++) {
            cout << *iter << " : " << peopleVolite[*iter] << endl;
        }
        cout << "Invalid : " << invalidNum << endl;
    }
    return 0;
}
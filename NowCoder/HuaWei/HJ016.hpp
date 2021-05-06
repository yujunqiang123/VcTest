#pragma once
/*
题目描述
王强今天很开心，公司发给N元的年终奖。王强决定把年终奖用于购物，
他把想买的物品分为两类：主件与附件，附件是从属于某个主件的，下表就是一些主件与附件的例子：

主件      附件
电脑      打印机，扫描仪
书柜      图书
书桌      台灯，文具
工作椅     无

如果要买归类为附件的物品，必须先买该附件所属的主件。每个主件可以有 0 个、 1 个或 2 个附件。
附件不再有从属于自己的附件。王强想买的东西很多，为了不超出预算，他把每件物品规定了一个重要度，
分为 5 等：用整数 1 ~ 5 表示，第 5 等最重要。他还从因特网上查到了每件物品的价格（都是 10 元的整数倍）。
他希望在不超过 N 元（可以等于 N 元）的前提下，使每件物品的价格与重要度的乘积的总和最大。
    设第 j 件物品的价格为 v[j] ，重要度为 w[j] ，共选中了 k 件物品，编号依次为 j1 ， j2 ，……， jk ，则所求的总和为：
    v[j1]*w[j1]+v[j2]*w[j2]+ … +v[jk]*w[jk] 。（其中 * 为乘号）

请你帮助王强设计一个满足要求的购物单。

输入描述:
输入的第 1 行，为两个正整数，用一个空格隔开：N m
（其中 N （ <32000 ）表示总钱数， m （ <60 ）为希望购买物品的个数。）

从第 2 行到第 m+1 行，第 j 行给出了编号为 j-1 的物品的基本数据，每行有 3 个非负整数 v p q
（其中 v 表示该物品的价格（ v<10000 ）， p 表示该物品的重要度（ 1 ~ 5 ）， q 表示该物品是主件还是附件。
如果 q=0 ，表示该物品为主件，如果 q>0 ，表示该物品为附件， q 是所属主件的编号）

输出描述:
输出文件只有一个正整数，为不超过总钱数的物品的价格与重要度乘积的总和的最大值（ <200000 ）。
示例1
输入
1000 5
800 2 0
400 5 1
300 5 1
400 3 0
500 2 0
输出
2200
*/

#include <iostream>
#include <vector>
#include <map>
#include <string.h>
using namespace std;

struct Obj
{
    int price;      //价格
    int importance; //重要性
};

struct MasterObj
{
    Obj obj;
    vector<Obj> belongs;     //所属的附件物品
};

int HJ016()
{
    int money, objNum;
    while (cin >> money >> objNum) {
        map<int, MasterObj> masterObjs;

        money = money / 10; //物品价格都是10元的整数倍，因此除以10，减少动态规划占用内存
        int price, importance, belongTo;     //所属主件(0:为主件 other:所属主件编号)
        for (int index = 0; index < objNum; index++) {
            cin >> price >> importance >> belongTo;
            if (belongTo == 0) {
                MasterObj masterObj;
                masterObj.obj.price = price / 10;
                masterObj.obj.importance = importance;
                masterObjs[index + 1] = masterObj;
            } else {
                Obj belongObj;
                belongObj.price = price / 10;
                belongObj.importance = importance;
                masterObjs[belongTo].belongs.push_back(belongObj);
            }
        }

        int masterObjNum = masterObjs.size();
        int rowTotal = masterObjNum + 1;
        int colTotal = money + 1;
        int* dynamicArray = new int[rowTotal * colTotal];
        memset(dynamicArray, 0, sizeof(int) * rowTotal * colTotal);

        auto masterObj = masterObjs.begin();
        for (int row = 1; row < rowTotal; row++, masterObj++) {
            for (int col = 1; col < colTotal; col++) {
                int notBuyThisObj = dynamicArray[(row - 1) * colTotal + col];
                if (col < masterObj->second.obj.price) {
                    //当前金额买不起当前主物品
                    dynamicArray[row * colTotal + col] = notBuyThisObj;
                } else {
                    int buyThisObj[4] = { 0 };
                    //只买主物品
                    buyThisObj[0] = masterObj->second.obj.price * masterObj->second.obj.importance +
                        dynamicArray[(row - 1) * colTotal + (col - masterObj->second.obj.price)];
                    
                    //主物品 + 附件1
                    if (masterObj->second.belongs.size() >= 1 &&
                        masterObj->second.belongs[0].price <= col - masterObj->second.obj.price) {
                        buyThisObj[1] = masterObj->second.obj.price * masterObj->second.obj.importance +
                            masterObj->second.belongs[0].price * masterObj->second.belongs[0].importance +
                            dynamicArray[(row - 1) * colTotal + (col - masterObj->second.obj.price - masterObj->second.belongs[0].price)];
                    }
                    //主物品 + 附件2
                    if (masterObj->second.belongs.size() >= 2 &&
                        masterObj->second.belongs[1].price <= col - masterObj->second.obj.price) {
                        buyThisObj[2] = masterObj->second.obj.price * masterObj->second.obj.importance +
                            masterObj->second.belongs[1].price * masterObj->second.belongs[1].importance +
                            dynamicArray[(row - 1) * colTotal + (col - masterObj->second.obj.price - masterObj->second.belongs[1].price)];
                    }
                    //主物品 + 附件1 + 附件2
                    if (masterObj->second.belongs.size() >= 2 &&
                        masterObj->second.belongs[0].price + masterObj->second.belongs[1].price <= col - masterObj->second.obj.price) {
                        buyThisObj[3] = masterObj->second.obj.price * masterObj->second.obj.importance +
                            masterObj->second.belongs[0].price * masterObj->second.belongs[0].importance +
                            masterObj->second.belongs[1].price * masterObj->second.belongs[1].importance +
                            dynamicArray[(row - 1) * colTotal + (col - masterObj->second.obj.price - masterObj->second.belongs[0].price - masterObj->second.belongs[1].price)];
                    }

                    int maxValue = 0;
                    for (int index = 0; index < 4; index++) {
                        maxValue = maxValue > buyThisObj[index] ? maxValue : buyThisObj[index];
                    }

                    dynamicArray[row * colTotal + col] = maxValue > notBuyThisObj ? maxValue : notBuyThisObj;
                }
            }
        }
        cout << dynamicArray[rowTotal * colTotal - 1] * 10;

        for (int row = 0; row < rowTotal; row++) {
            for (int col = 0; col < colTotal; col++) {
                cout << col << ':' << dynamicArray[row * colTotal + col] << ' ';
            }
            cout << endl;
        }

        if (dynamicArray != nullptr) {
            delete[] dynamicArray;
            dynamicArray = nullptr;
        }
    }
    return 0;
}

/*
#include <iostream>
#include <algorithm>
int main1()
{
    int N, m;
    while (std::cin >> N >> m) {
        int val[60][3] = { 0 }, cos[60][3] = { 0 }, total[3200] = { 0 };
        for (int i = 1; i <= m; ++i) {
            int cost, p, q;
            std::cin >> cost >> p >> q;
            if (q != 0) {
                if (val[q][1] == 0) {
                    val[q][1] = cost * p;
                    cos[q][1] = cost;
                } else {
                    val[q][2] = cost * p;
                    cos[q][2] = cost;
                }
            } else {
                val[i][0] = cost * p;
                cos[i][0] = cost;
            }
        }

        for (int i = 1; i <= m; ++i) { // 遍历所有物件
            for (int j = N / 10; j >= cos[i][0] / 10; --j) { // 每个钱数
                // 只选主件
                if (j >= cos[i][0] / 10) {
                    total[j] = std::max(total[j], val[i][0] + total[j - cos[i][0] / 10]);
                }

                // 选主件和一个附件
                int tmp = (cos[i][0] + cos[i][1]) / 10;
                if (cos[i][1] != 0 && j >= tmp) {
                    total[j] = std::max(total[j], val[i][0] + val[i][1] + total[j - tmp]);
                }

                // 选主件和两个附件
                tmp = (cos[i][0] + cos[i][1] + cos[i][2]) / 10;
                if (cos[i][2] != 0 && j >= tmp) {
                    total[j] = std::max(total[j], val[i][0] + val[i][1] + val[i][2] + total[j - tmp]);
                }
            }
        }

        std::cout << total[N / 10] << std::endl;
    }

    return 0;
}
*/
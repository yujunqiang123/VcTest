#pragma once

#include <iostream>

using namespace std;

#define MAX_R 20
int channelBits[MAX_R] = {
    1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048,
    4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288
};

//寻找一个与 delta 最接近的 R 阶信道
//return 所求 R阶信道的 索引 -1：未找到
int bestRChennel(int delta, const int* const channelNum, int indexCurrent)
{
    int minIndex = -1;
    int minDleta = 5242880;
    for (int index = indexCurrent; index >= 0; index--) {
        if (channelNum[index] > 0) {
            int temp = channelBits[index] - delta;
            temp = temp > 0 ? temp : -temp;
            if (minDleta >= temp) {
                minDleta = temp;
                minIndex = index;
            }
        }
    }

    return minIndex;
}

int HWExam03()
{
    int channelR;
    while (cin >> channelR) {
        int* channelNum = new int[channelR + 1]();//每阶信道的数量
        int* channelNum2 = new int[channelR + 1]();//每阶信道的数量
        int* channelNum3 = new int[channelR + 1]();//每阶信道的数量
        for (int index = 0; index <= channelR; index++) {
            cin >> channelNum[index];
            channelNum2[index] = channelNum[index];
            channelNum3[index] = channelNum[index];
        }
        int userD = 0;
        cin >> userD;

        int userNum = 0;//能够支持的用户的数量
        for (int index = channelR; index >= 0;) {
            if (channelBits[index] >= userD) {
                //信道容量大于用户使用量,一个信道支持一个用户
                userNum += channelNum[index];
                index--;
            } else if (channelNum[index] != 0) {
                int delta = userD;
                while (delta >= 0) {
                    //寻找一个与 delta 最接近的 存在的 信道
                    int bestIndex = bestRChennel(delta, channelNum, index);
                    if (bestIndex != -1) {
                        delta -= channelBits[bestIndex];
                        channelNum[bestIndex]--;
                    } else {
                        break;
                    }
                }
                if (delta <= 0) {
                    userNum++;
                }
            } else {
                index--;
            }
        }

        int userNum2 = 0;//能够支持的用户的数量
        for (int index = channelR; index >= 0;) {
            if (channelBits[index] >= userD) {
                //信道容量大于用户使用量,一个信道支持一个用户
                userNum2 += channelNum2[index];
                index--;
            } else {
                //贪最大 不是最优解
                int sumBits = 0;
                while (sumBits < userD && index >= 0) {
                    if (channelNum2[index] == 0) {
                        index--;
                    } else {
                        sumBits += channelBits[index];
                        channelNum2[index]--;
                    }
                }
                if (index >= 0) {
                    userNum++;
                }
            }
        }

        int userNum3 = 0;//能够支持的用户的数量
        for (int index = 0; index <= channelR;) {
            if (channelBits[index] >= userD) {
                //信道容量大于用户使用量,一个信道支持一个用户
                userNum3 += channelNum3[index];
                index++;
            } else {
                //贪最小不是最优解
                int sumBits = 0;
                while (sumBits < userD && index <= channelR) {
                    if (channelNum3[index] == 0) {
                        index++;
                    } else {
                        sumBits += channelBits[index];
                        channelNum3[index]--;
                    }
                }
                if (index <= channelR) {
                    userNum3++;
                }
            }
        }

        int res = userNum > userNum2 ? userNum : userNum2;
        res = res > userNum3 ? res : userNum3;
        cout << res << endl;

        if (channelNum != nullptr) {
            delete[] channelNum;
            channelNum = nullptr;
        }
        if (channelNum2 != nullptr) {
            delete[] channelNum2;
            channelNum2 = nullptr;
        }
        if (channelNum3 != nullptr) {
            delete[] channelNum3;
            channelNum3 = nullptr;
        }
    }
    return 0;
}

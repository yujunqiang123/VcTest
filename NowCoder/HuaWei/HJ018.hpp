#pragma once
/*
题目描述
请解析IP地址和对应的掩码，进行分类识别。要求按照A/B/C/D/E类地址归类，不合法的地址和掩码单独归类。

所有的IP地址划分为 A,B,C,D,E五类

A类地址1.0.0.0~126.255.255.255;

B类地址128.0.0.0~191.255.255.255;

C类地址192.0.0.0~223.255.255.255;

D类地址224.0.0.0~239.255.255.255；

E类地址240.0.0.0~255.255.255.255


私网IP范围是：

10.0.0.0～10.255.255.255

172.16.0.0～172.31.255.255

192.168.0.0～192.168.255.255


子网掩码为二进制下前面是连续的1，然后全是0。（例如：255.255.255.32就是一个非法的掩码）
注意二进制下全是1或者全是0均为非法

注意：
1. 类似于【0.*.*.*】和【127.*.*.*】的IP地址不属于上述输入的任意一类，也不属于不合法ip地址，计数时可以忽略
2. 私有IP地址和A,B,C,D,E类地址是不冲突的

输入描述:
多行字符串。每行一个IP地址和掩码，用~隔开。

输出描述:
统计A、B、C、D、E、错误IP地址或错误掩码、私有IP的个数，之间以空格隔开。

示例1
输入
10.70.44.68~255.254.255.0   (A\私有~非法)  =>  错误
1.0.0.1~255.0.0.0           (A\公有~合法)  =>  正确
192.168.0.2~255.255.255.0   (C\私有~合法)  =>  正确
19..0.~255.255.255.0        (错误~合法)    =>  错误
输出
1 0 1 0 0 2 1
*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

enum typeIP
{
    IP_A = 0,
    IP_B,
    IP_C,
    IP_D,
    IP_E,
    IP_A_PRIVATE,
    IP_B_PRIVATE,
    IP_C_PRIVATE,
    IP_IGNORE,
    IP_ERROR,
};

typeIP AnalysisIP(string IP)
{
    int dataIP[4] = { 0 };

    int dotNum = count(IP.begin(), IP.end(), '.');
    if (dotNum != 3) {
        return IP_ERROR;
    }
    for (int index = 0; index < dotNum; index++) {
        int pos = IP.find_first_of('.');
        if (pos == string::npos) {
            break;
        }
        string subStr = IP.substr(0, pos);
        if (subStr.empty() == true) {
            return IP_ERROR;
        }
        dataIP[index] = atoi(subStr.c_str());
        if (dataIP[index] < 0 || 255 < dataIP[index]) {
            return IP_ERROR;
        }
        IP = IP.substr(pos+1, IP.length() - pos -1);
    }
    if (IP.empty() == true) {
        return IP_ERROR;
    }
    dataIP[3] = atoi(IP.c_str());
    if (dataIP[3] < 0 || 255 < dataIP[3]) {
        return IP_ERROR;
    }

    if (dataIP[0] == 0 || dataIP[0] == 127) {
        return IP_IGNORE;
    } else if (1 <= dataIP[0] && dataIP[0] <= 126) {
        if (dataIP[0] == 10) {
            return IP_A_PRIVATE;
        } else {
            return IP_A;
        }
    } else if (128 <= dataIP[0] && dataIP[0] <= 191) {
        if (dataIP[0] == 172 && (16 <= dataIP[1] && dataIP[1] <= 31)) {
            return IP_B_PRIVATE;
        } else {
            return IP_B;
        }
    } else if (192 <= dataIP[0] && dataIP[0] <= 223) {
        if (dataIP[0] == 192 && 168 == dataIP[1]) {
            return IP_C_PRIVATE;
        } else {
            return IP_C;
        }
    } else if (224 <= dataIP[0] && dataIP[0] <= 239) {
        return IP_D;
    } else if (240 <= dataIP[0] && dataIP[0] <= 255) {
        return IP_E;
    }

    return IP_ERROR;
}

bool AnalysisMask(string mask)
{
    int dataMask[4] = { 0 };

    int dotNum = count(mask.begin(), mask.end(), '.');
    if (dotNum != 3) {
        return false;
    }
    for (int index = 0; index < dotNum; index++) {
        int pos = mask.find_first_of('.');
        if (pos == string::npos) {
            break;
        }
        dataMask[index] = atoi(mask.substr(0, pos).c_str());
        if (dataMask[index] < 0 || 255 < dataMask[index]) {
            return false;
        }
        mask = mask.substr(pos + 1, mask.length() - pos - 1);
    }
    dataMask[3] = atoi(mask.c_str());
    if (dataMask[3] < 0 || 255 < dataMask[3]) {
        return false;
    }

    bool getOne = false;
    bool getZero = false;
    for (int index = 0; index < 4; index++) {
        for (int loop = 7; loop >= 0; loop--) {
            if (dataMask[index] & 0x1 << loop) {
                if (getZero == true) {
                    return false;
                } else {
                    getOne = true;
                }
            } else {
                getZero = true;
            }
        }
    }

    if (getOne == false || getZero == false) {
        return false;
    } else {
        return true;
    }
}

int HJ018()
{
#define A       0
#define B       1
#define C       2
#define D       3
#define E       4
#define ERROR   5
#define PRIVATE 6
#define RESULT_NUM 7
    int result[RESULT_NUM] = { 0 };
    string str;
    while (cin>>str) {
        if (str == "end") {
            break;
        }

        int pos = str.find('~');
        if (pos == string::npos) {
            continue;
        }

        string IP = str.substr(0, pos);
        string mask = str.substr(pos+1, str.length()-pos-1);

        typeIP ipType = AnalysisIP(IP);
        bool maskType = AnalysisMask(mask);

        if (ipType == IP_ERROR || maskType == false) {
            result[ERROR]++;
        } else if (ipType == IP_A) {
            result[A]++;
        } else if (ipType == IP_B) {
            result[B]++;
        } else if (ipType == IP_C) {
            result[C]++;
        } else if (ipType == IP_D) {
            result[D]++;
        } else if (ipType == IP_E) {
            result[E]++;
        } else if (ipType == IP_A_PRIVATE) {
            result[A]++;
            result[PRIVATE]++;
        } else if (ipType == IP_B_PRIVATE) {
            result[B]++;
            result[PRIVATE]++;
        } else if (ipType == IP_C_PRIVATE) {
            result[C]++;
            result[PRIVATE]++;
        }
    }

    printf("%d %d %d %d %d %d %d\n", result[A], result[B], result[C],
        result[D], result[E], result[ERROR], result[PRIVATE]);
    return 0;
}


/*
判断子网掩码是否有效:
    通过判断是否为255.255.255.255 如果是的话，错误加一，继续下次循环
    判断别的子网掩码是否正确。根据子网掩码二进制规律（开头为连续的1，然后为0），
    我们将子网掩码按位取反，然后加一，得到的新二进制位。
    然后我们通过判断二进制中1的个数来判断是否为合法的子网掩码。
    （因为合法的子网掩码，按位取反，加一后，二进制位中，只有一个1)

    int validMask(char *p)
    {
        int flag,i ;
        unsigned int b1 = 0, n[4];
        sscanf(p, "%u.%u.%u.%u", &n[3], &n[2], &n[1], &n[0]);

        if(n[0] == 255 && n[1] == 255 && n[2] == 255 && n[3] == 255 ) {
            flag = false;
            return flag;
        }

        for(i = 0; i < 4; ++i) {
            b1 += n[i] << (i * 8);
        }
        b1 = ~b1 + 1;

        if((b1 & (b1 - 1)) == 0) {
            flag = true;
        } else {
            flag = false;
        }
        return flag;
    }
*/

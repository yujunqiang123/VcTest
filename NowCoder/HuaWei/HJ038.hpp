/*
题目描述
假设一个球从任意高度自由落下，每次落地后反跳回原高度的一半; 再落下, 求它在第5次落地时，共经历多少米 ? 第5次反弹多高？

最后的误差判断是小数点6位

输入描述 :
输入起始高度，int型

输出描述 :
分别输出第5次落地时，共经过多少米第5次反弹多高

示例1
输入
1
输出
2.875
0.03125
*/

#include <iostream>

using namespace std;

int HJ038()
{
    float high = 0.0f;
    while (cin >> high) {
        float high5 = high / 32;
        float distance5 = 23 * high / 8;
        printf("%g\n%g\n", distance5, high5);
    }
    return 0;
}

/*
%f
Decimal floating point：十进制浮点数（单、双精度）。

%e
Scientific notation(mantissa / exponent)：科学记数法（尾数 / 指数）。保留小数点后六位。

% g
Use the shortest representation : %e or %f。
至多6位有效数字，去除多余的0。
当指数大于等于6或小于等于 - 5时，使用%e。
*/
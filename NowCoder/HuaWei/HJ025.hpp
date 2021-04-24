#pragma once
/*
题目描述
信息社会，有海量的数据需要分析处理，比如公安局分析身份证号码、 QQ 用户、手机号码、银行帐号等信息及活动记录。

采集输入大数据和分类规则，通过大数据分类处理程序，将大数据分类输出。

请注意本题有多组输入用例。
输入描述 :
﻿一组输入整数序列I和一组规则整数序列R，I和R序列的第一个整数为序列的个数（个数不包含第一个整数）；
整数范围为0~0xFFFFFFFF，序列个数不限

输出描述 :
﻿从R依次中取出R<i>，对I进行处理，找到满足条件的I：

I整数对应的数字需要连续包含R<i>对应的数字。比如R<i>为23，I为231，那么I包含了R<i>，条件满足 。

按R<i>从小到大的顺序 :

    (1)先输出R<i>；

    (2)再输出满足条件的I的个数；

    (3)然后输出满足条件的I在I序列中的位置索引(从0开始)；

    (4)最后再输出I。

    附加条件：

    (1)R<i>需要从小到大排序。相同的R<i>只需要输出索引小的以及满足条件的I，索引大的需要过滤掉

    (2)如果没有满足条件的I，对应的R<i>不用输出

    (3)最后需要在输出序列的第一个整数位置记录后续整数序列的个数(不包含“个数”本身)



    序列I：15, 123, 456, 786, 453, 46, 7, 5, 3, 665, 453456, 745, 456, 786, 453, 123（第一个15表明后续有15个整数）

    序列R：5, 6, 3, 6, 3, 0（第一个5表明后续有5个整数）

    输出：30, 3, 6, 0, 123, 3, 453, 7, 3, 9, 453456, 13, 453, 14, 123, 6, 7, 1, 456, 2, 786, 4, 46, 8, 665, 9, 453456, 11, 456, 12, 786

    说明：

    30----后续有30个整数

    3----从小到大排序，第一个R<i>为0，但没有满足条件的I，不输出0，而下一个R<i>是3

    6-- - 存在6个包含3的I

    0-- - 123所在的原序号为0

    123-- - 123包含3，满足条件

    示例1
    输入
    15 123 456 786 453 46 7 5 3 665 453456 745 456 786 453 123
    5 6 3 6 3 0
    输出
    30 3 6 0 123 3 453 7 3 9 453456 13 453 14 123 6 7 1 456 2 786 4 46 8 665 9 453456 11 456 12 786
*/

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
using namespace std;

struct InfoI
{
    long long index;
    long long data;
};

struct InfoDealed
{
    long long dataR;
    long long numWithR = 0;
    map<long long, long long> dataI;//<index, data>
};

int HJ025()
{
    long long temp = 0;
    long long numI = 0;
    while (cin >> numI) {
        //输入序列
        multimap<long long, long long> dataI; //<data, index>
        for (long long index = 0; index < numI; index++) {
            cin >> temp;
            dataI.insert(pair<long long, long long>(temp, index));
        }

        //输入规则
        long long numR = 0;
        cin >> numR;
        set<long long> dataR;
        for (long long index = 0; index < numR; index++) {
            cin >> temp;
            dataR.insert(temp);
        }
        
        //匹配规则
        long long sumNum = 0;
        vector<InfoDealed> matchResult;
        for (auto iterR = dataR.begin(); iterR != dataR.end(); iterR++) {
            string strR = to_string(*iterR);
            InfoDealed tempInfoDealed;
            for (auto iterI = dataI.rbegin(); iterI != dataI.rend(); iterI++) {
                bool match = false;
                if (iterI->first > *iterR) {
                    //在规则字串内查找信息串
                    string strI = to_string(iterI->first);
                    int pos = strI.find(strR);
                    match = pos == std::string::npos ? false : true;
                } else if (iterI->first == *iterR) {
                    //比当前规则相对的数肯定满足规则
                    match = true;
                } else {
                    //比当前规则小的数肯定不满足规则
                    break;
                }

                if (match == true) {
                    //匹配上，记录信息
                    tempInfoDealed.dataR = *iterR;
                    tempInfoDealed.numWithR ++;
                    tempInfoDealed.dataI[iterI->second] = iterI->first;
                }
            }

            if (tempInfoDealed.dataI.size() > 0) {
                sumNum += 2 * tempInfoDealed.numWithR + 2;
                matchResult.push_back(tempInfoDealed);
            }
        }

        //输出结果
        cout << sumNum;
        for (auto iterResult = matchResult.begin(); iterResult != matchResult.end(); iterResult++) {
            cout << ' ' << (*iterResult).dataR << ' ' << (*iterResult).numWithR;
            for (auto iterMap = (*iterResult).dataI.begin(); iterMap != (*iterResult).dataI.end(); iterMap++) {
                cout << ' ' << (*iterMap).first << ' ' << (*iterMap).second;
            }
        }
        cout << endl;
    }
    return 0;
}

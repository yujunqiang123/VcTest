#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

//测试 unordered_map 输入输出顺序
int UnorderedMap_InOutOrder()
{
    unordered_map<string, int> unorderedMap;
    unorderedMap.insert(pair<string, int>("JSAGKLXB", 17));
    unorderedMap.insert(pair<string, int>("KARXHSRFA", 16));
    unorderedMap.insert(pair<string, int>("B", 14));
    unorderedMap.insert(pair<string, int>("D", 15));

    for (auto iter = unorderedMap.begin(); iter != unorderedMap.end(); iter++) {
        cout << iter->first << " : " << iter->second << endl;
    }

    return 0;

    /*
    [output]:
    JSAGKLXB : 17
    B : 14
    KARXHSRFA : 16
    D : 15

    unorderedMap 输出顺序与输入顺序无关。
    unorderedMap 内部采用 哈希表存储数据, 采用 begin() 到 end() 的方式输出，实际上是按哈希值的顺序输出。
    */
}


int MapTest()
{
    UnorderedMap_InOutOrder();
    return 0;
}
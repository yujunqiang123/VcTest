#pragma once
/*
题目描述
题目描述
若两个正整数的和为素数，则这两个正整数称之为“素数伴侣”，如2和5、6和13，它们能应用于通信加密。
现在密码学会请你设计一个程序，从已有的N（N为偶数）个正整数中挑选出若干对组成“素数伴侣”，挑选方案多种多样，
例如有4个正整数：2，5，6，13，如果将5和6分为一组中只能得到一组“素数伴侣”，而将2和5、6和13编组将得到两组“素数伴侣”，
能组成“素数伴侣”最多的方案称为“最佳方案”，当然密码学会希望你寻找出“最佳方案”。

输入:
有一个正偶数N（N≤100），表示待挑选的自然数的个数。后面给出具体的数字，范围为[2,30000]。

输出:
输出一个整数K，表示你求得的“最佳方案”组成“素数伴侣”的对数。


输入描述:
输入说明
1 输入一个正偶数n
2 输入n个整数
注意：数据可能有多组

输出描述:
求得的“最佳方案”组成“素数伴侣”的对数。

示例1
输入
4
2 5 6 13
2
3 6
输出
2
0
*/
#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

bool isPrime(const int &num)
{
    if (num <= 3) {
        return true;
    }

    for (int index = num / 2; index >= 2; index--) {
        if (num % index == 0) {
            return false;
        }
    }

    return true;
}

int oddSize = 0;
int evenSize = 0;
int* partnerMap = nullptr;
map<int, int> evenMatcher;//偶数的匹配对象
bool match(int oddIndex, set<int> &visited)
{
    for (int evenIndex = 0; evenIndex < evenSize; evenIndex++) {
        if (partnerMap[oddIndex*evenSize + evenIndex] == 1 &&
            visited.find(evenIndex) == visited.end()) {
            visited.insert(evenIndex);

            auto iter = evenMatcher.find(evenIndex);
            if (iter == evenMatcher.end() || match(iter->second, visited)) {
                evenMatcher[evenIndex] = oddIndex;
                return true;
            }
        }
    }
    return false;
}

//二分图最大匹配问题
int HJ028()
{
    int num = 0;
    while (cin>>num) {
        evenMatcher.clear();
        vector<int> dataOdd;//奇数
        vector<int> dataEven;//偶数

        int temp = 0;
        for (int index = 0; index < num; index++) {
            cin >> temp;
            if (temp % 2) {
                dataOdd.push_back(temp);
            } else {
                dataEven.push_back(temp);
            }
        }

        oddSize = dataOdd.size();
        evenSize = dataEven.size();
        partnerMap = new int[oddSize * evenSize]();//两个数的和是否是素数 0:不是 1:是
        for (int oddIndex = 0; oddIndex < oddSize; oddIndex++) {
            for (int evenIndex = 0; evenIndex < evenSize; evenIndex++) {
                if (isPrime(dataOdd[oddIndex] + dataEven[evenIndex]) == true) {
                    partnerMap[oddIndex*evenSize + evenIndex] = 1;
                }
            }
        }

        //匈牙利法找最大匹配
        int count = 0;
        for (int oddIndex = 0; oddIndex < oddSize; oddIndex++) {
            set<int> visited;
            if (match(oddIndex, visited)) {
                count++;
            }
        }
        cout << count << endl;

        if (partnerMap != nullptr) {
            delete[] partnerMap;
            partnerMap = nullptr;
        }
    }
    return 0;
}

/*
#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

int p[100];
bool visited[100];
int map[100][100];
int n1=0;
int n2=0;
int prime (int x) {
    int flag=1;
    for (int i=2; i <= sqrt(x); i++) {
        if (x%i ==0){
            flag=0;
            break;
        }
    }
    return flag;
}
int match (int i){
    for (int j = 0; j < n2; j++){
        if ( map[i][j] && visited[j]==0 ){
            visited[j]=1;
            if ( p[j]==-1 || match(p[j])) {
                p[j]=i;
                return 1;
            }
        }
    }
    return 0;
}
int main(){
    int n;
    while(cin>>n){
        vector<int> odd;
        vector<int> even;
        n1=0;
        n2=0;
        for (int i=0;i<n;i++){
            int x;
            cin>>x;
            if (x%2){
                odd.push_back(x);
                n1++;
            }
            else {
                even.push_back(x);
                n2++;
            }
        }
        for (int i=0; i<n1;i++){
            for (int j=0; j<n2; j++){
                map[i][j]=prime(odd[i]+even[j]);
            }
        }
        int cnt=0;
        for (int j=0;j<100;j++){
            p[j]=-1;
        }
        for (int i=0; i<n1; i++){
            for (int j=0;j<100;j++){
                visited[j]=0;
            }
            if ( match(i) ){
                cnt++;
            }
        }
        cout<<cnt<<endl;
    }
}
*/
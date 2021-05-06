#pragma once
//测试 new 会不会初始化内存
#include <iostream>

using namespace std;

int NewInitTest()
{
    int* test = new int;
    cout << "new int:" << *test << endl;    //-842150451
    if (test != nullptr) {
        delete test;
        test = nullptr;
    }

    int* arrayTest = new int[5];
    cout << "new int[5]:";
    for (int index = 0; index < 5; index++) {
        cout << arrayTest[index] << ' ';//-842150451
    }
    cout << endl;
    if (arrayTest != nullptr) {
        delete arrayTest;
        arrayTest = nullptr;
    }

    int* test2 = new int();
    cout << "new int():" << *test2 << endl;    //0
    if (test2 != nullptr) {
        delete test2;
        test2 = nullptr;
    }

    int* arrayTest2 = new int[5]();
    cout << "new int[5]:";
    for (int index = 0; index < 5; index++) {
        cout << arrayTest2[index] << ' ';//0
    }
    cout << endl;
    if (arrayTest2 != nullptr) {
        delete arrayTest2;
        arrayTest2 = nullptr;
    }
    return 0;

    /*
    [output]:
    new int:-842150451
    new int[5] : -842150451 - 842150451 - 842150451 - 842150451 - 842150451
    new int() : 0
    new int[5] : 0 0 0 0 0
    
    不带 () 的 new 会没有初始化，带 () 的 new 会初始化为 0
    */
}


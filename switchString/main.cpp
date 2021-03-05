/*================================================================
*   Copyright (C) 2021 Sangfor Ltd. All rights reserved.
*   
*   文件名称：main.cpp
*   创 建 者：LuZhenrong
*   创建日期：2021年02月20日
*   描    述：
*
================================================================*/


#include <iostream>
#include <string>
#include "switch_string.h"

using namespace std;

int main(int argc, char** argv)
{
    string str;
    cin >> str;

    switch(hash_(str.c_str())){
        case "first"_hash:
            cout << "first" << endl;
            break;
        case "second"_hash:
            cout << "second" << endl;
            break;
        case "third"_hash:
            cout << "third" << endl;
            break;
        default:
            cout << "default" << endl;
            break;
    }

    return 0;
}

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
#include "string_to_enum.h"

using namespace std;

int main(int argc, char** argv)
{
    string str = "UTC";
    while(1){
    cout << "str: ";
    cin >> str;

    Zone fooEnum = convert_string_to_enum<Zone>(str);

    switch(fooEnum)
    {
        case e_utc:
            cout << "UTC" << endl;
            break;
        case e_gmt:
            cout << "GMT" << endl;
            break;
        case e_cst:
            cout << "CST" << endl;
            break;
        case e_pst:
            cout << "PST" << endl;
            break;
        case e_amt:
            cout << "AMT" << endl;
            break;
        default:
            cout << "Error" << endl;
            break;
    }
    }

    return 0;
}

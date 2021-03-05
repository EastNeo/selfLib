/*================================================================
*   Copyright (C) 2021 Sangfor Ltd. All rights reserved.
*   
*   文件名称：string_to_enum.h
*   创 建 者：Bai Xiaodong
*   创建日期：2021年02月20日
*   描    述：
*
================================================================*/


#pragma once

#include <iostream>

using namespace std;


struct ZoneEnumName
{
    static const string List[];
};

enum Zone
{
    e_utc,
    e_gmt,
    e_cst,
    e_pst,
    e_amt
};

const string ZoneEnumName::List[] =
{
    "UTC",
    "GMT",
    "CST",
    "PST",
    "AMT"
};

template <class T>
T convert_string_to_enum(string str)
{
    T fooEnum = static_cast<T>(-1);
    int count = sizeof(ZoneEnumName::List) / sizeof(ZoneEnumName::List[0]);

    for(int i = 0; i < count; ++i)
    {
        const string _str = ZoneEnumName::List[i];
        if(str == _str)
        {
            fooEnum = static_cast<T>(i);
            break;
        }
    }

    return fooEnum;
}

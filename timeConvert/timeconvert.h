/*================================================================
*   Copyright (C) 2021 Sangfor Ltd. All rights reserved.
*   
*   文件名称：timeconvert.h
*   创 建 者：Bai Xiaodong
*   创建日期：2021年02月10日
*   描    述：
*
================================================================*/
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "timeconvert.h"
using namespace std;

class TimeConvert{
    public:
        bool getTime();
        int get_time_zone_diff(string zone);
        time_t ConvertDateTimeToEpochTime();
    private:
        string tm_str;
        struct tm tm_t;
        time_t _tm_t;
};

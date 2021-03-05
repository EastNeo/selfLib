/*================================================================
*   Copyright (C) 2021 Sangfor Ltd. All rights reserved.
*   
*   文件名称：timeconvert.cpp
*   创 建 者：Bai Xiaodong
*   创建日期：2021年02月10日
*   描    述：
*
================================================================*/

#include <cctype>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include "timeconvert.h"

using namespace std;

#define ONEHOUR 1*60*60

typedef uint64_t hash_t;

constexpr hash_t prime = 0x100000001B3ull;
constexpr hash_t basis = 0xCBF29CE484222325ull;


hash_t hash_(char const* str)
{
	hash_t ret{basis};

	while(*str){
		ret ^= *str;
		ret *= prime;
		str++;
	}

	return ret;
}

constexpr hash_t hash_compile_time(char const* str, hash_t last_value = basis)
{
	return *str ? hash_compile_time(str+1, (*str ^ last_value) * prime) : last_value;
}

constexpr unsigned long long operator "" _hash(char const* p, size_t)
{
	return hash_compile_time(p);
}

bool TimeConvert::getTime()
{
    string cmd = "uname -v";
    string cmd_rst;
    char cmd_buf[512] = {0};

    FILE *fp = popen(cmd.c_str(), "r");
    if(NULL == fp){
        cerr << "Popen " << cmd << " Failed" << endl;
        return false;
    }

    fread(cmd_buf, sizeof(char), sizeof(cmd_buf), fp);
    cmd_rst = cmd_buf;
    pclose(fp);
    tm_str = cmd_rst.substr(cmd_rst.length()-29, cmd_rst.length());
    return true;
}

int TimeConvert::get_time_zone_diff(string zone)
{
    int timezone = 0;
    if(zone.empty()){
        cout << "No time zone!" << endl;
        return timezone;
    }
    
    transform(zone.begin(), zone.end(), zone.begin(), ::toupper);
    switch(hash_(zone.c_str())){
        case "UTC"_hash:
        case "GMT"_hash:
            timezone = 8 * ONEHOUR;
            break;
        case "PST"_hash:
            timezone = 16 * ONEHOUR;
            break;
        case "CST"_hash:
            timezone = 0;
            break;
        case "AMT"_hash:
            timezone = 12 * ONEHOUR;
           break;
        default:
            cout << "unrecognizable zone!!!" << endl;
    }
    return timezone;
}


time_t TimeConvert::ConvertDateTimeToEpochTime()
{
    bool is_succ = getTime();
    if(is_succ == false){
        cout << "get time error" << endl;
        return -1;
    }
    char* tm_cha = (char*)tm_str.data();
    time_t _tm_t;
    //cout << "tm_cha: " << tm_cha;
    int year, day, hour, minute, second;
    char week[4], month[4], zone[6];
    sscanf(tm_cha, "%s %s %d %d:%d:%d %s %d", week, month, &day, &hour, &minute, &second, zone, &year);
    //cout << "baixd: " << week << " "<< month <<  " "<< day << " "<< hour << " "<< minute<< " " << second << " " << zone << " " << year << endl;
    tm_t.tm_year = year - 1900;
    tm_t.tm_isdst = -1;

    if(0 == strcmp(month, "Jan")){
        tm_t.tm_mon = 0;
    }else if(0 == strcmp(month, "Feb")){
        tm_t.tm_mon = 1;
    }else if(0 == strcmp(month, "Mar")){
        tm_t.tm_mon = 2;
    }else if(0 == strcmp(month, "Apr")){
        tm_t.tm_mon = 3;
    }else if(0 == strcmp(month, "May")){
        tm_t.tm_mon = 4;
    }else if(0 == strcmp(month, "Jun")){
        tm_t.tm_mon = 5;
    }else if(0 == strcmp(month, "Jul")){
        tm_t.tm_mon = 6;
    }else if(0 == strcmp(month, "Aug")){
        tm_t.tm_mon = 7;
    }else if(0 == strcmp(month, "Sep")){
        tm_t.tm_mon = 8;
    }else if(0 == strcmp(month, "Oct")){
        tm_t.tm_mon = 9;
    }else if(0 == strcmp(month, "Nov")){
        tm_t.tm_mon = 10;
    }else if(0 == strcmp(month, "Dec")){
        tm_t.tm_mon = 11;
    }else{
        cerr << "Month is Error!" << endl;
    }

    if(day >= 0 && day <= 31){ 
        if(tm_t.tm_mon == 1 && day == 29 ){
            if(((year%100 !=0) && year%4==0) || (year%400 == 0)){
                tm_t.tm_mday = day;
            }
        }else if(tm_t.tm_mon == 1 && day <= 28){
            tm_t.tm_mday = day;
        }else if((tm_t.tm_mon == 3 || tm_t.tm_mon == 5 || tm_t.tm_mon == 8 || tm_t.tm_mon == 10) && (day < 31)){
            tm_t.tm_mday = day;
        }else{
            tm_t.tm_mday = day;
        }
    }else{
        cerr << "Day error" << endl;
        return -1;
    }

    if(hour >=0 && hour < 24){
        tm_t.tm_hour = hour;
    }else{
        cerr << "Hour error" << endl;
        return -1;
    }

    if(minute >= 0 && minute < 60){
        tm_t.tm_min = minute;
    }else{
        cerr << "Minute error" << endl;
        return -1;
    }

    if(second >= 0 && second < 60){
        tm_t.tm_sec = second;
    }else{
        cerr << "Second error" << endl;
        return -1;
    }


    //cout << tm_t.tm_year << "-" << tm_t.tm_mon << "-" << tm_t.tm_mday << " " << tm_t.tm_hour << ":" << tm_t.tm_min << ":" << tm_t.tm_sec << endl;;
    _tm_t = mktime(&tm_t);

    //string zone_str = zone;
    string zone_str = "AMT";
    int zone_diff = get_time_zone_diff(zone_str);
    _tm_t += zone_diff;
    //cout << "_tm_t: " << _tm_t << endl;
    return _tm_t*1000;
}

















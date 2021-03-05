/*================================================================
*   Copyright (C) 2021 Sangfor Ltd. All rights reserved.
*   
*   文件名称：switch_string.h
*   创 建 者：LuZhenrong
*   创建日期：2021年02月20日
*   描    述：
*
================================================================*/


#pragma once

#include <cstdint>

typedef std::uint64_t hash_t;

constexpr hash_t prime = 0x100000001B3ull;
//constexpr hash_t basis = 0xCBF29CE484222325ull;
constexpr hash_t basis = 0xCBF29CE484222456ull;

/*
 * 计算字符串的hash值，将字符串转换为1个整数
 */
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

/*
 * 利用c++自定义文字常量的语法，自定义一个constexpr函数，switch的case标签处
 * 调用这个constexpr函数
 */
constexpr hash_t hash_compile_time(char const* str, hash_t last_value=basis)
{
    return *str ? (hash_compile_time(str+1, (*str ^ last_value) * prime)) : last_value;
}

/*
 * 利用自定义文字常量，重载一个operator
 */
constexpr unsigned long long operator "" _hash(char const* p, std::size_t)
{
    return hash_compile_time(p);
}


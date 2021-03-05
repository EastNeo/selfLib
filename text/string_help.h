#pragma once

#include <vector>
#include <string>
#include <map>
#include <limits>
#include "optional.h"

namespace msl
{
/// \brief String helper functions.
class StringHelp {
public:
    /**
    * @brief: split the string by delimiterit
    * @params: src-the source string which to be split; delimiter-the delimiterit string
    * @return: the string split by delimiter map(key:before dlimit; value:after delimiter)
    */
    static std::map<std::string, std::string>
    StringSplit(const std::string &src, const std::string &delimiter);

    static std::vector<std::string> split_text(
        const std::string &text,
        const std::string &split_string,
        bool skip_empty = true);

    /// \brief Trim
    ///
    /// \param text = String Ref
    /// \param suffix = bool, include suffix
    ///
    /// \return file_name
    static std::string get_file_name(const std::string &text, bool suffix = true);

    /// \brief Replace all substrings in the text
    ///
    /// \param text = String Ref
    /// \param sub = Substring
    /// \param after = Replaced substring
    ///
    /// \return Replaced string
    static std::string replace_string(const std::string &text, const std::string &sub, const std::string &after);

    /// \brief Trim
    ///
    /// \param text = String Ref
    ///
    /// \return Temp String
    static std::string trim(const std::string &text);

    /// \brief Removes trailing zeros from floating point numbers
    ///
    /// If the input string is "42.21000", then this function returns "42.21".
    /// If the string is "42.00000", then it returns "42".
    static std::string remove_trailing_zeros(std::string text);

    /// \brief Compare
    ///
    /// \param a = String Ref8
    /// \param b = String Ref8
    /// \param case_insensitive = bool
    ///
    /// \return int
    static int compare(const std::string &a, const std::string &b, bool case_insensitive = false);

    /// \brief string to upper
    ///
    /// \param s = String Ref
    ///
    /// \return Temp String
    static std::string string_to_upper(const std::string &s);

    /// \brief string to lower
    ///
    /// \param s = String Ref
    ///
    /// \return Temp String
    static std::string string_to_lower(const std::string &s);

    /// \brief string to float
    ///
    /// \param value = String Ref
    ///
    /// \return float
    template <class T, class = typename std::enable_if<std::is_floating_point<T>::value, T>::type>
    static std::optional<T> string_to(const std::string &value)
    {
        if (value.empty()) {
            return std::nullopt;
        }
        try {
            using limits = std::numeric_limits<T>;

            auto max = (limits::max)();
            auto min = (limits::min)();
            auto l = string_to_ld(value);
            if (!l || *l > max || *l < min) {
                return std::nullopt;
            }
            return l;
        } catch (...) {
            return std::nullopt;
        }

    }

    /// \brief string to double
    ///
    /// \param value = String Ref
    ///
    /// \return double
    static std::optional<long double> string_to_ld(const std::string &value);
    /// \brief string to int
    ///
    /// \param value = String Ref
    /// \param base = value
    ///
    /// \return int
    template <class T, class = typename std::enable_if<std::is_integral<T>::value, T>::type>
    static std::optional<T> string_to(const std::string &value, int base = 10)
    {
        if (value.empty()) {
            return std::nullopt;
        }
        try {
            using limits = std::numeric_limits<T>;

            auto max = (limits::max)();
            auto min = (limits::min)();
            if (min == 0) {
                auto l = string_to_ull(value, base);
                if (!l || *l > max || *l < min) {
                    return std::nullopt;
                }
                return l;
            }
            auto l = string_to_ll(value, base);
            if (!l || *l > max || *l < min) {
                return std::nullopt;
            }
            return l;
        } catch (...) {
            return std::nullopt;
        }
    }

    /// \brief string to long long
    ///
    /// \param value = String Ref
    /// \param base = value
    ///
    /// \return long long
    static std::optional<long long> string_to_ll(const std::string &value, int base = 10);

    /// \brief string to unsigned long long
    ///
    /// \param value = String Ref
    /// \param base = value
    ///
    /// \return unsigned long long
    static std::optional<unsigned long long> string_to_ull(const std::string &value, int base = 10);

    /// \brief string to bool
    ///
    /// \param value = String Ref
    ///
    /// \return bool
    static std::optional<bool> string_to_bool(const std::string &value);

    /// \brief Get a substring of length n from the left
    ///
    /// \param s = String Ref
    /// \param n
    /// \return
    static std::string left(const std::string &s, size_t n);

    /// \brief Get a substring of length n from the right
    ///
    /// \param s = String Ref
    /// \param n
    /// \return
    static std::string right(const std::string &s, size_t n);

    /// \brief start with
    ///
    /// \param a
    /// \param b
    /// \return
    static bool start_with(const std::string &a, const std::string &b);

    static bool end_with(const std::string &a, const std::string &b);
};
}

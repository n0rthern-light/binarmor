#pragma once

#include "shared/RuntimeException.hpp"
#include "shared/self_obfuscation/strenc.hpp"
#include "shared/value/Unsigned.hpp"
#include <format>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace program::shared::string
{
    class StringFunctions
    {
    public:
        static std::string trim(const std::string& string)
        {
            size_t first = string.find_first_not_of(" \t\n\r");
            if (first == std::string::npos) {
                return "";
            }
            size_t last = string.find_last_not_of(" \t\n\r");
            return string.substr(first, last - first + 1);
        }

        static std::vector<std::string> splitByCharacter(const std::string& string, const char delimiter)
        {
            std::istringstream stream(string);
            std::vector<std::string> result;
            std::string word;

            while (std::getline(stream, word, delimiter)) {
                word = trim(word);
                if (!word.empty()) {
                    result.push_back(word);
                }
            }

            return result;
        }

        static bool isHexValue(const std::string& str)
        {
            if (str.size() > 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
                for (size_t i = 2; i < str.size(); ++i) {
                    if (!std::isxdigit(str[i])) {
                        return false;
                    }
                }
                return true;
            }
            return false;
        }

        static bool isDecValue(const std::string& str)
        {
            if (str.empty()) return false;

            size_t start = 0;
            if (str[0] == '-') {
                if (str.size() == 1) {
                    return false; 
                }
                start = 1;
            }

            for (size_t i = start; i < str.size(); ++i) {
                if (!std::isdigit(str[i])) {
                    return false;
                }
            }

            return true;
        }

        static bool isWrappedBy(const std::string& string, const std::string& frontWrap, const std::string& backWrap)
        {
            if (string.size() < frontWrap.size() + backWrap.size()) {
                return false;
            }

            bool startsWithFrontWrap = string.compare(0, frontWrap.size(), frontWrap) == 0;

            bool endsWithBackWrap = string.compare(string.size() - backWrap.size(), backWrap.size(), backWrap) == 0;

            return startsWithFrontWrap && endsWithBackWrap;
        }

        static bool endsWith(const std::string& str, const std::string& end)
        {
            if (end.size() > str.size()) {
                return false;
            }
            
            return str.compare(str.size() - end.size(), end.size(), end) == 0;
        }

        static std::string trimFromEnd(const std::string& str, unsigned int charCount)
        {
            if (str.length() < charCount) {
                throw std::out_of_range(strenc("Trimmed string is shorted than trimmed characters"));
            }

            return str.substr(0, str.length() - charCount);
        }

        static std::string replaceAll(const std::string& str, const std::string& search, const std::string& to) {
            std::string result = str;
            size_t pos = 0;

            while ((pos = result.find(search, pos)) != std::string::npos) {
                result.replace(pos, search.length(), to);
                pos += to.length(); // Move past the last replacement
            }

            return result;
        }

        static value::CUnsigned convertToUnsigned(const std::string& str)
        {
            if (isHexValue(str)) {
                std::string hexStr = str;
                if (hexStr.size() > 2 && (hexStr[0] == '0' && (hexStr[1] == 'x' || hexStr[1] == 'X'))) {
                    hexStr = hexStr.substr(2);
                }

                unsigned int value;
                std::stringstream ss;
                ss << std::hex << hexStr;
                ss >> value;

                if (ss.fail()) {
                    throw RuntimeException(std::format(strenc("{} is not a valid hex value!"), str));
                }
                return value::CUnsigned { value };
            } else if (isDecValue(str)) {
                unsigned int value;
                try {
                    value = std::stoul(str);
                } catch (const std::invalid_argument& e) {
                    throw RuntimeException(std::format(strenc("{} is not a valid decimal value!"), str));
                } catch (const std::out_of_range& e) {
                    throw RuntimeException(std::format(strenc("{} is out of range for unsigned int!"), str));
                }
                return value::CUnsigned { value };
            } else {
                throw RuntimeException(std::format(strenc("{} is neither a decimal nor a hexadecimal value!"), str));
            }
        }

        static types::byte_vec convertToBytes(const std::string& str, bool terminatingZeroByte = true)
        {
            types::byte_vec bytes(str.begin(), str.end());

            if (terminatingZeroByte == true) {
                bytes.push_back(0);
            }

            return bytes;
        }
    };
}

// Name: Alejandro Silva Juarez
// Seneca Student ID: 142655224
// Seneca email: asilva-juarez@myseneca.ca
// Date of completion: 03/07/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Utilities.h"
#include <string>
#include <iostream>
namespace seneca
{
    char Utilities::m_delimiter = 'x';
    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    }

    void Utilities::trim(std::string &str)
    {
        // delete left trim
        while (str[0] == ' ')
            str.erase(0, 1);
        // delete right trim
        while (str.back() == ' ')
            str.pop_back();
    }

    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter()
    {
        return m_delimiter;
    }

    std::string Utilities::extractToken(const std::string &str, size_t &next_pos, bool &more)
    {
        if (m_delimiter == str[next_pos])
        {
            more = false;
            throw "Error";
        }

        auto pos = str.find(m_delimiter, next_pos);
        std::string token;

        if (pos != std::string::npos)
        {
            token = str.substr(next_pos, pos - next_pos);
            trim(token);
            next_pos = pos + 1;
            more = true;
        }
        else
        {
            token = str.substr(next_pos, str.size() - next_pos);
            trim(token);
            more = false;
        }

        if (m_widthField < token.size())
            setFieldWidth(token.size());
        return token;
    }

}
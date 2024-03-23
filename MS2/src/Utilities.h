// Name: Alejandro Silva Juarez
// Seneca Student ID: 142655224
// Seneca email: asilva-juarez@myseneca.ca
// Date of completion: 03/07/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H
#include <string>
namespace seneca
{
    class Utilities
    {
        size_t m_widthField = 1;
        static char m_delimiter;

    public:
        Utilities() { m_widthField = 1; };
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        std::string extractToken(const std::string &str, size_t &next_pos, bool &more);
        void trim(std::string &str);

        static void setDelimiter(char newDelimiter);
        static char getDelimiter();
    };

    extern Utilities ut;
}
#endif // !SENECA_UTILITIES_H
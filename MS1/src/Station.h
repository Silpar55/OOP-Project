#ifndef SENECA_STATION_H
#define SENECA_STATION_H
#include <string>
#include <iostream>
namespace seneca
{

    class Station
    {
        int m_id;
        std::string m_name;
        std::string m_desc;
        size_t m_serialNumber;
        size_t m_stock;
        static size_t m_widthField;
        static size_t m_idGenerator;

    public:
        Station(const std::string &str);
        const std::string &getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream &os, bool full) const;
    };
}
#endif // !SENECA_STATION_H
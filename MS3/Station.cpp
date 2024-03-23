// Name: Alejandro Silva Juarez
// Seneca Student ID: 142655224
// Seneca email: asilva-juarez@myseneca.ca
// Date of completion: 03/07/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Station.h"
#include "Utilities.h"
#include <string>
#include <iomanip>
namespace seneca
{
    size_t Station::m_widthField = 0;
    size_t Station::m_idGenerator = 0;
    Utilities ut;

    Station::Station(const std::string &str)
    {
        size_t pos = 0;
        bool more = true;
        m_idGenerator++;
        m_id = m_idGenerator;
        m_name = ut.extractToken(str, pos, more);
        m_serialNumber = std::stoul(ut.extractToken(str, pos, more));
        m_stock = std::stoul(ut.extractToken(str, pos, more));
        // get the current width
        m_widthField = ut.getFieldWidth();

        // because description does not require format we need to extract it separately
        // instead the width might have the width of the description because is larger than the names
        m_desc = str.substr(pos, str.size() - pos);
        ut.trim(m_desc);
    }
    const std::string &Station::getItemName() const
    {
        return m_name;
    }

    size_t Station::getNextSerialNumber()
    {
        return m_serialNumber++;
    }
    size_t Station::getQuantity() const
    {
        return m_stock;
    }
    void Station::updateQuantity()
    {
        if (m_stock > 0)
            m_stock--;
    }
    void Station::display(std::ostream &os, bool full) const
    {
        if (!full)
        {
            os << std::setw(3) << std::setfill('0') << std::right << m_id << " | ";
            os << std::setw(m_widthField) << std::setfill(' ') << std::left << m_name << " | ";
            os << std::setw(6) << std::setfill('0') << std::right << m_serialNumber << " | ";
        }
        else
        {
            os << std::setw(3) << std::setfill('0') << std::right << m_id << " | ";
            os << std::setw(m_widthField) << std::setfill(' ') << std::left << m_name << " | ";
            os << std::setw(6) << std::setfill('0') << std::right << m_serialNumber << " | ";
            os << std::setw(4) << std::setfill(' ') << std::right << m_stock << " | ";
            os << std::left << m_desc;
        }

        os << std::endl;
    }
}
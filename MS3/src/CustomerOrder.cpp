// Name: Alejandro Silva Juarez
// Seneca Student ID: 142655224
// Seneca email: asilva-juarez@myseneca.ca
// Date of completion: 03/29/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <utility>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"
namespace seneca
{
    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder(const std::string &str)
    {
        size_t pos = 0;
        bool more = true;
        m_name = ut.extractToken(str, pos, more);
        // std::cout << m_name << "\n\n";
        m_product = ut.extractToken(str, pos, more);
        // std::cout << m_product << "\n\n";
        size_t posItem = pos;
        while (more)
        {
            ut.extractToken(str, posItem, more);
            m_cntItem++;
            // std::cout << m_cntItem << "\n\n";
        }
        more = true;
        m_lstItem = new Item *[m_cntItem];
        for (size_t i = 0; i < m_cntItem; i++)
        {
            m_lstItem[i] = new Item(ut.extractToken(str, pos, more));
            //  std::cout << m_lstItem[i]->m_itemName << "\n\n";
        }

        if (m_widthField < ut.getFieldWidth())
            m_widthField = ut.getFieldWidth();
        //  std::cout << m_widthField << "\n\n";
    }

    CustomerOrder::CustomerOrder(CustomerOrder &&other) noexcept
    {
        m_name = other.m_name;
        m_product = other.m_product;
        m_cntItem = other.m_cntItem;
        m_lstItem = other.m_lstItem;
        other.m_lstItem = nullptr;
    }
    CustomerOrder &CustomerOrder::operator=(CustomerOrder &&other) noexcept
    {
        if (this != &other)
        {
            // delete the resources of the current instance
            if (m_lstItem)
            {
                for (size_t i = 0; i < m_cntItem; i++)
                    delete m_lstItem[i];

                delete[] m_lstItem;
            }
            m_name = other.m_name;
            m_product = other.m_product;
            m_cntItem = other.m_cntItem;
            m_lstItem = other.m_lstItem;
            other.m_lstItem = nullptr;
        }

        return *this;
    }
    CustomerOrder::~CustomerOrder()
    {
        // delete the resources of the current instance
        if (m_lstItem)
        {
            for (size_t i = 0; i < m_cntItem; i++)
                delete m_lstItem[i];

            delete[] m_lstItem;
        }
    }
    bool CustomerOrder::isOrderFilled() const
    {
        size_t filledItem = 0;
        for (size_t i = 0; i < m_cntItem; i++)
            if (m_lstItem[i]->m_isFilled)
                filledItem++;

        return filledItem == m_cntItem;
    }
    bool CustomerOrder::isItemFilled(const std::string &itemName) const
    {
        bool isFilled = true;
        // iterate until we see an item that match with the name given and still all the items are filled
        for (size_t i = 0; i < m_cntItem && isFilled; i++)
            if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled)
                isFilled = false;

        return isFilled;
    }
    void CustomerOrder::fillItem(Station &station, std::ostream &os)
    {
        bool filledOne = false;

        for (size_t i = 0; i < m_cntItem; i++)
        {
            if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled && !filledOne)
            {
                if (station.getQuantity() > 0)
                {
                    station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    filledOne = true;
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
                else
                {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
            }
        }
    }
    void CustomerOrder::display(std::ostream &os) const
    {
        os << m_name << " - " << m_product << std::endl;
        for (size_t i = 0; i < m_cntItem; i++)
        {
            os << "[" << std::setw(6) << std::right << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
            os << std::setw(m_widthField) << std::left << std::setfill(' ') << m_lstItem[i]->m_itemName << " - ";
            if (m_lstItem[i]->m_isFilled)
                os << "FILLED";
            else
                os << "TO BE FILLED";
            os << std::endl;
        }
    }
}
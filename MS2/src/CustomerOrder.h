// Name: Alejandro Silva Juarez
// Seneca Student ID: 142655224
// Seneca email: asilva-juarez@myseneca.ca
// Date of completion: 03/23/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H
#include <string>
#include <iostream>
#include "Station.h"
namespace seneca
{
    class CustomerOrder
    {
        struct Item
        {
            std::string m_itemName;
            size_t m_serialNumber{0};
            bool m_isFilled{false};
            Item(const std::string &src) : m_itemName(src){};
        };

        std::string m_name{};
        std::string m_product{};
        size_t m_cntItem{};
        Item **m_lstItem{};
        static size_t m_widthField;

    public:
        CustomerOrder() = default;
        CustomerOrder(const std::string &str);
        CustomerOrder(const CustomerOrder &) { throw std::string("Cannot make copies."); };
        CustomerOrder &operator=(const CustomerOrder &) = delete;
        CustomerOrder(CustomerOrder &&other) noexcept;
        CustomerOrder &operator=(CustomerOrder &&other) noexcept;
        ~CustomerOrder();

        bool isOrderFilled() const;
        bool isItemFilled(const std::string &itemName) const;
        void fillItem(Station &station, std::ostream &os);
        void display(std::ostream &os) const;
    };
};
#endif // !SENECA_CUSTOMERORDER_H
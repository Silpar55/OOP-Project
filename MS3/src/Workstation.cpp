// Name: Alejandro Silva Juarez
// Seneca Student ID: 142655224
// Seneca email: asilva-juarez@myseneca.ca
// Date of completion: 03/29/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <utility>
#include "Workstation.h"
namespace seneca
{

    std::deque<CustomerOrder> g_pending;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;

    void Workstation::fill(std::ostream &os)
    {
        if (!m_orders.empty())
        {
            m_orders.front().fillItem(*this, os);
        }
    }
    bool Workstation::attemptToMoveOrder()
    {
        bool moved = false;
        if (!m_orders.empty())
        {
            if (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0)
            {
                // it will be moved it in any case
                moved = true;
                if (m_pNextStation)
                {
                    m_pNextStation->m_orders.push_back(std::move(m_orders.front()));
                    m_orders.pop_front();
                }
                else
                {
                    if (m_orders.front().isOrderFilled())
                    {
                        g_completed.push_back(std::move(m_orders.front()));
                        m_orders.pop_front();
                    }
                    else
                    {
                        g_incomplete.push_back(std::move(m_orders.front()));
                        m_orders.pop_front();
                    }
                }
            }
        }

        return moved;
    }

    Workstation &Workstation::operator+=(CustomerOrder &&newOrder)
    {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }

    void Workstation::setNextStation(Workstation *station)
    {
        m_pNextStation = station;
    }

    Workstation *Workstation::getNextStation() const
    {
        return m_pNextStation;
    }

    void Workstation::display(std::ostream &os) const
    {
        if (m_pNextStation)
            os << getItemName() << " --> " << m_pNextStation->getItemName() << std::endl;
        else
            os << getItemName() << " --> End of Line" << std::endl;
    }
}
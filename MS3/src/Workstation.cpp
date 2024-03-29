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
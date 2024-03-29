// Name: Alejandro Silva Juarez
// Seneca Student ID: 142655224
// Seneca email: asilva-juarez@myseneca.ca
// Date of completion: 03/29/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H
#include <deque>
#include <iostream>
#include "CustomerOrder.h"
#include "Station.h"

namespace seneca
{
    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station
    {
        std::deque<CustomerOrder> m_orders;
        Workstation *m_pNextStation{};

    public:
        Workstation(const std::string &str) : Station(str){};
        Workstation &operator+=(CustomerOrder &&newOrder);
        void fill(std::ostream &os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation *station);
        Workstation *getNextStation() const;
        void display(std::ostream &os) const;
    };
}
#endif // !SENECA_WORKSTATION_H
// Name: Alejandro Silva Juarez
// Seneca Student ID: 142655224
// Seneca email: asilva-juarez@myseneca.ca
// Date of completion: 03/29/2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H
#include "Workstation.h"
namespace seneca
{
    class LineManager
    {
        std::vector<Workstation *> m_activeLine;
        size_t m_cntCustomerOrder;
        Workstation *m_firstStation = nullptr;

    public:
        LineManager(const std::string &file, const std::vector<Workstation *> &stations);
        void reorderStations();
        bool run(std::ostream &os);
        void display(std::ostream &os) const;
    };
}
#endif // !SENECA_LINEMANAGER_H
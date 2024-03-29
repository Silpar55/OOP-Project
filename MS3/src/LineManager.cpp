#include <fstream>
#include <algorithm>
#include <vector>
#include "LineManager.h"
#include "Utilities.h"
namespace seneca
{
    LineManager::LineManager(const std::string &file, const std::vector<Workstation *> &stations)
    {
        std::ifstream fileStation(file);
        if (fileStation)
        {
            try
            {
                ut.setDelimiter('|');
                std::string line;
                while (!fileStation.eof())
                {
                    std::getline(fileStation, line);
                    size_t pos = 0;
                    bool more = true;

                    // find workStation by name
                    auto findWorkstation = [&stations](const std::string &name)
                    {
                        return std::find_if(stations.begin(), stations.end(), [&name](const Workstation *workstation)
                                            { return workstation->getItemName() == name; });
                    };

                    std::string wt = ut.extractToken(line, pos, more);
                    std::string nextWt = ut.extractToken(line, pos, more);
                    m_activeLine.push_back(*findWorkstation(wt));

                    // attempt to get the next work station
                    if (nextWt != wt)
                        m_activeLine.back()->setNextStation(*findWorkstation(nextWt));

                    // get the total of orders that are pending
                    m_cntCustomerOrder = g_pending.size();
                }

                // get the first station
                std::for_each(m_activeLine.begin(), m_activeLine.end(), [this](Workstation *wt)
                              {
                    // if any of the work station does not has a next work station the current station, it means it is the first station
                    if(wt->getNextStation())
                    {
                        // find in the loop if one of the wt has the address of the current workstation
                        // if nobody calls this work station, means this is the first one
                        if (std::none_of(m_activeLine.begin(), m_activeLine.end(), [&wt](Workstation *nextWt)
                                         { return nextWt->getNextStation() == wt; }))
                                         m_firstStation = wt;
                    } });
            }
            catch (const std::string &err)
            {
                throw err;
            }
        }
    }

    void LineManager::reorderStations()
    {
        // get the currentStation
        Workstation *currentStation = m_firstStation;
        std::vector<Workstation *> reorder;
        reorder.push_back(currentStation);
        std::for_each(m_activeLine.begin() + 1, m_activeLine.end(), [&reorder, &currentStation](Workstation *)
                      {
                          currentStation = currentStation->getNextStation();
                          reorder.push_back(currentStation); });

        m_activeLine = reorder;
    }
    bool LineManager::run(std::ostream &os)
    {
        static size_t itNum = 0;
        ++itNum;

        os << "Line Manager Iteration: " << itNum << std::endl;

        if (!g_pending.empty())
        {
            (*m_firstStation) += std::move(g_pending.front());
            g_pending.pop_front();
        }

        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation *station)
                      { station->fill(os); });
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation *station)
                      { station->attemptToMoveOrder(); });

        return m_cntCustomerOrder == (g_completed.size() + g_incomplete.size());
    }
    void LineManager::display(std::ostream &os) const
    {
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](const Workstation *workstation)
                      { workstation->display(os); });
    }
}

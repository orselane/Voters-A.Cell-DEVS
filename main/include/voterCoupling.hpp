#include <cadmium/celldevs/asymm/coupled.hpp>
#include "voterState.hpp"
#include "voterCell.hpp"

class VoterCoupled : public AsymmCellDEVSCoupled<voterState, double>
{
public:
    VoterCoupled(const string &id, const string &configFilePath) : AsymmCellDEVSCoupled<voterState, double>(id, configFilePath) {}

    void addCell(const string &cellId,
                 const shared_ptr<AsymmCellConfig<voterState, double>> &conf) const override
    {
        string cellModel = conf->cellModel;
        if (cellModel == "voterState")
        {
            addComponent(voter(cellId, conf));
        }
        else
        {
            throw bad_typeid();
        }
    }
}
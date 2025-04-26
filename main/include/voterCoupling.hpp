#ifndef VOTER_COUPLING_HPP_
#define VOTER_COUPLING_HPP_

#include <cadmium/modeling/celldevs/asymm/coupled.hpp>
#include "voterState.hpp"
#include "voterCell.hpp"
#include "graphWeights.hpp"

class VoterCoupled : public AsymmCellDEVSCoupled<voterState, Weights>
{
public:
    VoterCoupled(const string &id, const string &configFilePath) : AsymmCellDEVSCoupled<voterState, double>(id, configFilePath) {}

    void addCell(const string &cellId,
                 const shared_ptr<AsymmCellConfig<voterState, Weights>> &conf) const override
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

#endif
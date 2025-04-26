#ifndef VOTER_CELL_HPP
#define VOTER_CELL_HPP
// Would be cool to get these from JASON
#define STRONG_WEIGHT 3
#define WEAK_WEIGHT 1
#define rand_between(x,y) x+ rand() % (y-x)

#ifndef noise
#define noise static_cast<float> (rand()) / static_cast <float> (RAND_MAX)
#endif

#include <cmath>
#include <ctime>
#include <nlohmann/json.hpp>
#include <cadmium/modeling/celldevs/asymm/cell.hpp>
#include <cadmium/modeling/celldevs/asymm/config.hpp>
#include "voterState.hpp"

using namespace cadmium::celldevs;

enum Preference {
    BLUE, // 0 (Max <1)
	RED // 1 (Max <2)
};

Preference truncToPref(float fPref){
	return static_cast<Preference>((int) fPref);
}


// Voter cell.
class voter : public AsymmCell<voterState, double> {
	public:
	voter(const std::vector<int>& id, 
			const std::shared_ptr<const AsymmCellConfig<voterState, double>>& config
		  ): AsymmCell<voterState, double>(id, config) { }

	// Tau function
	[[nodiscard]] voterState localComputation(voterState state, const std::unordered_map<std::vector<int>, NeighborData<voterState, double>>& neighborhood, const PortSet& x) const override {
		// Create "bag" for weighted odds
		multiset<Preferences> ms = {};
		
		// Add IC, if applicable - PortSet
		// TODO: Weak
		// TODO: Strong

		// Add neighbor preferences
		for (const auto& [neighborId, neighborData] : neighborhood) {
			double neighborPreference = neighborData.state->preference;
			
			for(int i=0; i < STRONG_WEIGHT; i++){
				ms.insert(truncToPref(neighborPreference));
			}
		}

		// Add self preference
		for(int i=0; i < STRONG_WEIGHT; i++){
			ms.insert(truncToPref(state.preference));
		}
		
		// Change, if needed
		static_assert(!ms.empty());
		if(stateChangePossible(ms)){
			// Set state preference to random element from ms
			Preference random_val = *(std::next(std::begin(ms), rand_between(0, ms.size())));
			state.preference = ((float) random_val) + noise;
		}

		return state;
	}


	bool stateChangePossible(multiset<Preference> ms){
		// Needs to be at least one of each to make a change possible
		return (ms.count(RED) > 0 && ms.count(BLUE) > 0);
	}

	// ta/D: constant delay of 1
	[[nodiscard]] double outputDelay(const voterState& state) const override {
		return 1.;
	}
};

#endif // End header

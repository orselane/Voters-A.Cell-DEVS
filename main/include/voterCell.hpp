#ifndef VOTER_CELL_HPP
#define VOTER_CELL_HPP
#define rand_between(x,y) x+ rand() % (y-x)

#ifndef noise
#define noise static_cast<float> (rand()) / static_cast <float> (RAND_MAX)
#endif

#include <cmath>
#include <set>
#include <ctime>
#include <nlohmann/json.hpp>
#include <cadmium/modeling/celldevs/asymm/cell.hpp>
#include <cadmium/modeling/celldevs/asymm/config.hpp>
#include "voterState.hpp"
#include "graphWeights.hpp"

using namespace cadmium::celldevs;


bool stateChangePossible(const std::multiset<Preference> ms){
	// Needs to be at least one of each to make a change possible
	return (ms.count(RED) > 0 && ms.count(BLUE) > 0);
}



// Voter cell.
class voterCell : public AsymmCell<voterState, int> {
	public:
		voterCell(const std::string id, const std::shared_ptr<const AsymmCellConfig<voterState, int>>& config): 
			AsymmCell<voterState, int>(id, config) { }

		// Tau function
		[[nodiscard]] voterState localComputation(voterState state, const std::unordered_map<std::string, NeighborData<voterState, int>>& neighborhood) const override {
			// Create "bag" for weighted odds
			std::multiset<Preference> ms = {};
			
			// Add neighbor preferences
			for (const auto& [neighborId, neighborData] : neighborhood) {
				double neighborPreference = neighborData.state->preference;
				int weight = neighborData.vicinity;
				
				for(int i=0; i < weight; i++){
					ms.insert(truncToPref(neighborPreference));
				}
			}

			// Change, if needed
			if(stateChangePossible(ms)){
				// Set state preference to random element from ms
				Preference random_val = *(std::next(std::begin(ms), rand_between(0, ms.size())));
				state.preference = ((float) random_val) + noise;
			}

			return state;
		}

		// ta/D: constant delay of 1
		[[nodiscard]] double outputDelay(const voterState& state) const override {
			return 1.;
		}
};

#endif // End header

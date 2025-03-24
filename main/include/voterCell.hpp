#ifndef VOTER_CELL_HPP
#define VOTER_CELL_HPP
// Would be cool to get these from JASON
#define PROBABILITY 50
#define NUM_NEIGHBORS 4

#include <cmath>
#include <nlohmann/json.hpp>
#include <cadmium/modeling/celldevs/grid/cell.hpp>
#include <cadmium/modeling/celldevs/grid/config.hpp>
#include "voterState.hpp"

using namespace cadmium::celldevs;

// Voter cell.
class voter : public GridCell<voterState, double> {
	private: int neighborCaps[NUM_NEIGHBORS];
	
	public:
	voter(const std::vector<int>& id, 
			const std::shared_ptr<const GridCellConfig<voterState, double>>& config
		  ): GridCell<voterState, double>(id, config) { 
	   for(int i = 0; i < NUM_NEIGHBORS; i++){
	      neighborCaps[i] = PROBABILITY + i * (PROBABILITY/NUM_NEIGHBORS); 
	   }
	}

	// Tau function
	[[nodiscard]] voterState localComputation(voterState state,
		const std::unordered_map<std::vector<int>, NeighborData<voterState, double>>& neighborhood) const override {
		
		// TODO: Pretty sure almost all the logic can be replaced by a single T/F check because the map is unordered. Should be able to get a random cell. Not familiar enough with C++ yet though.
		int randomNum = rand() % 101;
		
		// Determine neighbor bias based on range buckets
		int neighborBias = 0;
		for(int i = 0; i < NUM_NEIGHBORS; i++){
		   if(randomNum > neighborCaps[i])
		      break;
		   neighborBias++;
		}
		
		// Get biased neighbor's state. (will default to nothing if randomNum < probability)
		int neighborCount = 0;
		for (const auto& [neighborId, neighborData]: neighborhood) {
			if(neighborCount == neighborBias) {
				state.preference = neighborData.state->preference;
			}
			neighborCount++;
		}

		return state;
	}

	// ta/D: constant delay of 1
	[[nodiscard]] double outputDelay(const voterState& state) const override {
		return 1.;
	}
};

#endif // End header

#ifndef VOTER_CELL_HPP
#define VOTER_CELL_HPP
// Would be cool to get these from JASON
#define PROBABILITY 20
#define NUM_NEIGHBORS 4
#define rand_between(x,y) x+ rand() % (y-x)

#ifndef noise
#define noise static_cast<float> (rand()) / static_cast <float> (RAND_MAX)
#endif

#include <cmath>
#include <ctime>
#include <nlohmann/json.hpp>
#include <cadmium/modeling/celldevs/grid/cell.hpp>
#include <cadmium/modeling/celldevs/grid/config.hpp>
#include "voterState.hpp"

using namespace cadmium::celldevs;

// Voter cell.
class voter : public GridCell<voterState, double> {
	public:
	voter(const std::vector<int>& id, 
			const std::shared_ptr<const GridCellConfig<voterState, double>>& config
		  ): GridCell<voterState, double>(id, config) { }

	// Tau function
	[[nodiscard]] voterState localComputation(voterState state,
		const std::unordered_map<std::vector<int>, NeighborData<voterState, double>>& neighborhood) const override {
		
		// If the change probability is not met, stay within current preferance range.
		int randomNum = rand() % 101;
		if (randomNum < PROBABILITY){
		   state.preference = trunc(state.preference) + noise;
		   return state;
		}
		
		// Get random neighbor, take their preference
		auto random_neighbor = std::next(std::begin(neighborhood), rand_between(0, neighborhood.size()));
		state.preference = trunc(random_neighbor->second.state->preference) + noise;

		return state;
	}

	// ta/D: constant delay of 1
	[[nodiscard]] double outputDelay(const voterState& state) const override {
		return 1.;
	}
};

#endif // End header

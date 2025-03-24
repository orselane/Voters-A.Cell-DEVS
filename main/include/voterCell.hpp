#ifndef VOTER_CELL_HPP
#define VOTER_CELL_HPP
// Would be cool to get these from JASON
#define PROBABILITY 20
#define NUM_NEIGHBORS 4
#define rand_between(x, y) x + rand() % (y-x)

#include <cmath>
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
		
		// If the change probability is not met, do nothing
		int randomNum = rand() % 101;
		if (randomNum < PROBABILITY)
		   return state;
		
		// Get random neighbor, take their preference
		auto random_neighbor = std::next(std::begin(neighborhood), rand_between(0, neighborhood.size()));
		state.preference = random_neighbor->second.state->preference;

		return state;
	}

	// ta/D: constant delay of 1
	[[nodiscard]] double outputDelay(const voterState& state) const override {
		return 1.;
	}
};

#endif // End header

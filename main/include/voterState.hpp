#ifndef VOTER_STATE_HPP_
#define VOTER_STATE_HPP_

#ifndef noise
#define noise static_cast<float> (rand()) / static_cast <float> (RAND_MAX)
#endif

#include <iostream>
#include <nlohmann/json.hpp>
#include "voterPreference.hpp"

// Voter cell state.
struct voterState {
	// 0-1 = Blue, 1-2 = Red. (incl. min, exlcu. max)
	float preference;

	// Default constructor function.
	voterState() : preference(0) {}
};

// It prints the preference of the cell in an output stream.
std::ostream& operator<<(std::ostream& os, const voterState& x) {
	os << "<" << x.preference << ">";
	return os;
}

// The simulator must be able to compare the equality of two state objects
bool operator!=(const voterState& x, const voterState& y) {
	// Inequalities prevent quiescence!!
	return x.preference != y.preference;
} 

// It parses a JSON file and generates the corresponding voterState object.
// TODO: Double check the json parameter is correct later
void from_json(const nlohmann::json& j, voterState& s) {
	j.at("preference").get_to(s.preference);
	s.preference += noise;
}

#endif // End header def

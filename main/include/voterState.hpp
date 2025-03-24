#ifndef VOTER_STATE_HPP_
#define VOTER_STATE_HPP_

#include <iostream>
#include <nlohmann/json.hpp>

// Voter cell state.
struct voterState {
	// 0 = Neutral, 1 = Blue, 2 = Red.
	int preference;

	// Default constructor function.
	voterState() : preference(0) {}
};

// It prints the preference of the cell in an output stream.
std::ostream& operator<<(std::ostream& os, const conwayState& x) {
	os << "<" << (x.preference) << ">";
	return os;
}

// The simulator must be able to compare the equality of two state objects
bool operator!=(const voterState& x, const voterState& y) {
	return x.preference != y.preference;
}

// It parses a JSON file and generates the corresponding voterState object.
// TODO: Double check the json parameter is correct later
void from_json(const nlohmann::json& j, voterState& s) {
	j.at("preference").get_to(s.preference);
}

#endif // End header def

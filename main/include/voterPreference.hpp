#ifndef _VOTER_PREF_HPP
#define _VOTER_PREF_HPP

#include<iostream>

enum Preference {
    BLUE, // 0 (Max <1)
	RED // 1 (Max <2)
};

Preference truncToPref(float fPref){
	return static_cast<Preference>((int) fPref);
}


inline std::ostream& operator<<(std::ostream& out, const Preference& command) {
    switch (command) {
        case Preference::BLUE: out << "BLUE"; break;
        case Preference::RED: out << "RED"; break;
        default: out << "UNKNOWN"; break;
    }
    return out;
}

#endif
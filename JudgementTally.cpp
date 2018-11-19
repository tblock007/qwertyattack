#include "JudgementTally.h"


// ********************************************************************************
/// <summary>
/// Constructs a new instance of a JudgementTally, with all counts initialized to zero
/// </summary>
/// <changed>tblock,11/19/2018</changed>
// ********************************************************************************
JudgementTally::JudgementTally() : _greats(0), _goods(0), _misses(0) {
}



// ********************************************************************************
/// <summary>
/// Returns the tallies that have been counted thus far
/// </summary>
/// <returns>The number of GREATs, the number of GOODs, the number of MISSes</returns>
/// <changed>tblock,11/19/2018</changed>
// ********************************************************************************
std::tuple<sf::Int32, sf::Int32, sf::Int32> JudgementTally::getTallies() const {
	return { _greats, _goods, _misses };
}



// ********************************************************************************
/// <summary>
/// Increments the appropriate tally given an input judgement
/// </summary>
/// <param name="judgement">The received judgement whose count is to be incremented</param>
/// <changed>tblock,11/19/2018</changed>
// ********************************************************************************
void JudgementTally::incrementTally(Judgement judgement) {
	if (judgement == Judgement::GREAT) {
		_greats++;
	}
	else if (judgement == Judgement::GOOD) {
		_goods++;
	}
	else if (judgement == Judgement::MISS) {
		_misses++;
	}
}
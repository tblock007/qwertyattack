#pragma once
#include <SFML/System.hpp>
#include "common.h"

// --------------------------------------------------------------------------------
/// <summary>
/// Represents counts for all judgements received in a SongRun
/// </summary>
// --------------------------------------------------------------------------------
class JudgementTally {
public:
	JudgementTally();
	std::tuple<sf::Int32, sf::Int32, sf::Int32> getTallies() const;
	void incrementTally(Judgement judgement);
private:
	sf::Int32 _greats;
	sf::Int32 _goods;
	sf::Int32 _misses;
};
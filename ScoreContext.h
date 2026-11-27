#pragma once

#include "Card.h"
#include "Hand.h"
#include <vector>

struct ScoreContext {
    std::vector<Card> playedCards;
    std::vector<Card> heldCards;
    HandRank handRank;

    int chips;
    int mult;

    ScoreContext()
        : handRank(HandRank::HighCard), chips(0), mult(0) {}

    ScoreContext(int c, int m, HandRank hr,
                 const std::vector<Card>& played,
                 const std::vector<Card>& held)
        : playedCards(played), heldCards(held), handRank(hr), chips(c), mult(m) {}

    int getFinalScore() const {
        return chips * mult;
    }
};

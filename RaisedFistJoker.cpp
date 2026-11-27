#include "RaisedFistJoker.h"

#include <string>

static int getLowestHeldRank(const ScoreContext& context, Card* lowestCardOut = nullptr) {
    if (context.heldCards.empty()) return 0;
    int minRank = 999;
    Card lowest = context.heldCards[0];
    for (const Card& c : context.heldCards) {
        int r = static_cast<int>(c.rank);
        if (r < minRank) {
            minRank = r;
            lowest = c;
        }
    }
    if (lowestCardOut) *lowestCardOut = lowest;
    return minRank;
}

std::string RaisedFistJoker::getName() const {
    return "Raised Fist";
}

std::string RaisedFistJoker::getDescription(const ScoreContext& context) const {
    if (context.heldCards.empty()) {
        return "Adds double the rank of lowest ranked card held in hand to Mult (No cards held)";
    }
    Card lowest;
    int rank = getLowestHeldRank(context, &lowest);
    return "Adds double rank of lowest held (" + cardName(lowest) + ", rank " +
           std::to_string(rank) + ") -> +" + std::to_string(rank * 2) + " Mult";
}

void RaisedFistJoker::onScoreCalculated(ScoreContext& context) {
    int rank = getLowestHeldRank(context);
    if (rank > 0) {
        context.mult += (rank * 2);
    }
}

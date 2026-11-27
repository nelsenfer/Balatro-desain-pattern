#include "MadJoker.h"

static bool containsTwoPair(const ScoreContext& context) {
    return context.handRank == HandRank::TwoPair ||
           context.handRank == HandRank::FullHouse ||
           context.handRank == HandRank::FlushHouse;
}

std::string MadJoker::getName() const {
    return "Mad Joker";
}

std::string MadJoker::getDescription(const ScoreContext& context) const {
    if (containsTwoPair(context)) {
        return "+10 Mult (Played hand contains Two Pair)";
    }
    return "+10 Mult if played hand contains a Two Pair (Condition not met)";
}

void MadJoker::onScoreCalculated(ScoreContext& context) {
    if (containsTwoPair(context)) {
        context.mult += 10;
    }
}

#include "PairJoker.h"

static bool containsPair(const ScoreContext& context) {
    return context.handRank == HandRank::Pair ||
           context.handRank == HandRank::TwoPair ||
           context.handRank == HandRank::ThreeOfAKind ||
           context.handRank == HandRank::FullHouse ||
           context.handRank == HandRank::FourOfAKind ||
           context.handRank == HandRank::FiveOfAKind ||
           context.handRank == HandRank::FlushHouse ||
           context.handRank == HandRank::FlushFive;
}

std::string PairJoker::getName() const {
    return "Pair Joker";
}

std::string PairJoker::getDescription(const ScoreContext& context) const {
    if (containsPair(context)) {
        return "+4 Mult (Played hand contains a Pair)";
    }
    return "+4 Mult if played hand contains a Pair (No pair)";
}

void PairJoker::onScoreCalculated(ScoreContext& context) {
    if (containsPair(context)) {
        context.mult += 4;
    }
}

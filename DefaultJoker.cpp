#include "DefaultJoker.h"

std::string DefaultJoker::getName() const {
    return "Joker";
}

std::string DefaultJoker::getDescription(const ScoreContext&) const {
    return "+4 Mult";
}

void DefaultJoker::onScoreCalculated(ScoreContext& context) {
    context.mult += 4;
}

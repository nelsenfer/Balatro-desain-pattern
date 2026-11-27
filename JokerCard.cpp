#include "JokerCard.h"

JokerCard::JokerCard() : triggered(false), bonusMult(1) {}

JokerCard::JokerCard(int bonus) : triggered(false), bonusMult(bonus) {}

std::string JokerCard::getName() const {
    return "Legacy JokerCard";
}

std::string JokerCard::getDescription(const ScoreContext&) const {
    return "+" + std::to_string(bonusMult) + " Mult";
}

void JokerCard::onScoreCalculated(ScoreContext& context) {
    context.mult += bonusMult;
}

void JokerCard::onHandPlayed(const ScoringRule::ScoreResult&) {
    triggered = true;
}

ScoringRule::ScoreResult JokerCard::modifyScore(ScoringRule::ScoreResult score) {
    if (!triggered) return score;

    score.mult += bonusMult;
    score.total = score.chips * score.mult;
    triggered = false;
    return score;
}

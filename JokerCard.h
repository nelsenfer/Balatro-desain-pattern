#pragma once

#include "GameRules.h"
#include "Joker.h"

class JokerCard : public Joker {
private:
    bool triggered;
    int bonusMult;

public:
    JokerCard();
    explicit JokerCard(int bonus);

    std::string getName() const override;
    std::string getDescription(const ScoreContext& context) const override;
    void onScoreCalculated(ScoreContext& context) override;

    // Backward-compatibility methods
    void onHandPlayed(const ScoringRule::ScoreResult& score);
    ScoringRule::ScoreResult modifyScore(ScoringRule::ScoreResult score);
};

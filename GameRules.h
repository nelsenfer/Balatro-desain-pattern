#pragma once

#include "Hand.h"

class ScoringRule {
public:
    struct ScoreResult {
        int chips;
        int mult;
        int total;
    };

    ScoreResult scoreHand(const EvaluationResult& evaluation);
};

class RewardRule {
public:
    int earnMoney(bool win, int score);
};

class BlindRule {
public:
    int getTarget(int round) const;
    bool checkBlind(int score, int target) const;
};

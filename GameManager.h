#pragma once

#include "GameRules.h"
#include "HandGenerator.h"
#include "HandSelector.h"
#include "JokerManager.h"
#include <memory>

class GameManager {
private:
    HandGenerator handGenerator;
    HandSelector selector;
    ScoringRule scoringRule;
    JokerManager jokerManager;
    RewardRule rewardRule;
    BlindRule blindRule;
    PokerHandChecker* rootChecker;
    int money;

public:
    explicit GameManager(PokerHandChecker* checker);
    void addJoker(std::unique_ptr<Joker> joker);
    void setupDefaultJokers();
    void runSession();
};

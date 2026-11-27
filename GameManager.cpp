#include "GameManager.h"
#include "DefaultJoker.h"
#include "MadJoker.h"
#include "MisprintJoker.h"
#include "RaisedFistJoker.h"

#include <iostream>

GameManager::GameManager(PokerHandChecker* checker)
    : rootChecker(checker), money(0) {
    setupDefaultJokers();
}

void GameManager::addJoker(std::unique_ptr<Joker> joker) {
    jokerManager.addJoker(std::move(joker));
}

void GameManager::setupDefaultJokers() {
    jokerManager.clear();
    // 4 Jokers sesuai referensi tugas:
    // 1. Joker: +4 Mult
    // 2. Mad Joker: +10 Mult if played hand contains Two Pair
    // 3. Misprint: +0-23 Mult (random)
    // 4. Raised Fist: Double rank of lowest held card to Mult
    jokerManager.addJoker(std::unique_ptr<Joker>(new DefaultJoker()));
    jokerManager.addJoker(std::unique_ptr<Joker>(new MadJoker()));
    jokerManager.addJoker(std::unique_ptr<Joker>(new MisprintJoker()));
    jokerManager.addJoker(std::unique_ptr<Joker>(new RaisedFistJoker()));
}

void GameManager::runSession() {
    std::cout << "=== RUN START ===\n";
    std::cout << "Active Jokers: " << jokerManager.size() << "\n";

    for (int round = 1; round <= 5; ++round) {
        std::cout << "\nRound " << round << "\n";

        Hand currentHand = handGenerator.generateHand();
        std::cout << "[CARDS] Available cards:\n";
        for (const Card& card : currentHand.availableCards)
            std::cout << "  - " << cardName(card) << "\n";

        EvaluationResult selected =
            selector.playHand(currentHand, *rootChecker);
        currentHand.playedCards = selected.playedCards;

        std::cout << "[CARDS] Played cards:\n";
        for (const Card& card : currentHand.playedCards)
            std::cout << "  - " << cardName(card) << "\n";

        std::vector<Card> heldCards = currentHand.getHeldCards();
        std::cout << "[CARDS] Held cards in hand:\n";
        for (const Card& card : heldCards)
            std::cout << "  - " << cardName(card) << "\n";

        EvaluationResult evaluation = rootChecker->check(currentHand);
        std::cout << "[HAND] Combination: "
                  << handRankName(evaluation.rank) << "\n";

        ScoringRule::ScoreResult baseScore =
            scoringRule.scoreHand(evaluation);
        std::cout << "[BASE SCORE] Chips: " << baseScore.chips
                  << " | Mult: " << baseScore.mult
                  << " | Base Total: " << baseScore.total << "\n";

        ScoreContext context(
            baseScore.chips,
            baseScore.mult,
            evaluation.rank,
            currentHand.playedCards,
            heldCards
        );

        jokerManager.notifyScoreCalculatedWithLog(context);

        ScoringRule::ScoreResult score;
        score.chips = context.chips;
        score.mult = context.mult;
        score.total = context.getFinalScore();

        int blindTarget = blindRule.getTarget(round);
        bool isWin = blindRule.checkBlind(score.total, blindTarget);
        int reward = rewardRule.earnMoney(isWin, score.total);
        money += reward;

        std::cout << "[SCORE] Chips: " << score.chips
                  << " | Mult: " << score.mult
                  << " | Total: " << score.total << "/" << blindTarget
                  << " | Lolos Blind? " << (isWin ? "Ya" : "Tidak")
                  << "\n";
        std::cout << "[REWARD] Gain: " << reward
                  << " | Money: " << money << "\n";

        if (!isWin) {
            std::cout
                << "\n>> GAME OVER! Anda gagal melewati target Blind.\n";
            break;
        }
    }

    std::cout << "\n=== RUN END ===\n";
    std::cout << "Final money: " << money << "\n";
}

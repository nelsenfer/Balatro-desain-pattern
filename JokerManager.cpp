#include "JokerManager.h"

#include <iostream>

void JokerManager::addJoker(std::unique_ptr<Joker> joker) {
    jokers.push_back(std::move(joker));
}

void JokerManager::notifyScoreCalculated(ScoreContext& context) const {
    for (const auto& joker : jokers) {
        joker->onScoreCalculated(context);
    }
}

void JokerManager::notifyScoreCalculatedWithLog(ScoreContext& context) const {
    if (jokers.empty()) return;

    std::cout << "\n=== Joker Effects ===\n";
    for (const auto& joker : jokers) {
        std::cout << "[JOKER] " << joker->getName() << "\n";
        std::cout << "  Effect: " << joker->getDescription(context) << "\n";

        int prevChips = context.chips;
        int prevMult = context.mult;

        joker->onScoreCalculated(context);

        std::cout << "  Score: (" << prevChips << " -> " << context.chips << " Chips) x ("
                  << prevMult << " -> " << context.mult << " Mult)\n";
    }

    std::cout << "=== Final Joker Score: " << context.chips << " x " << context.mult
              << " = " << context.getFinalScore() << " ===\n\n";
}

int JokerManager::size() const {
    return static_cast<int>(jokers.size());
}

void JokerManager::clear() {
    jokers.clear();
}

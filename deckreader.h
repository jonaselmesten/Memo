//Jonas Elmesten
//joel1803@student.miun.se
//Projket - DT047G

#ifndef DECKREADER_H
#define DECKREADER_H

#include "smartvector.h"
#include "cardpart.h"
#include"card.h"
#include <filesystem>

namespace fs = std::filesystem;

/**
 * @brief The DeckReader class
 * Class that handles reading I/O for already saved decks.
 */
class DeckReader {

public:
    DeckReader();

    SmartVector<Card>* readDeck(const fs::path path);

private:

    bool isNumber(const std::string& string);

    CardPart* loadCardPart(std::string className, std::string cardPart);
};

#endif // DECKREADER_H

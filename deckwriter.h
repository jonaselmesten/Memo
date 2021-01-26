//Jonas Elmesten
//joel1803@student.miun.se
//Projket - DT047G

#ifndef DECKWRITER_H
#define DECKWRITER_H

#include <string>
#include <filesystem>
#include <iostream>
#include <typeinfo>
#include "card.h"
#include "smartvector.h"

namespace fs = std::filesystem;

/**
 * @brief The DeckWriter class
 * Class that handles all writing I/O-operations when decks are saved to file.
 */
class DeckWriter {

public:
    DeckWriter(std::string writePath);

    void writeDeckToFile(SmartVector<Card> &deck);

    void handleImagePart(CardPart &part, std::string folderPath);

private:
    std::string writePath;

};

#endif // DECKWRITER_H

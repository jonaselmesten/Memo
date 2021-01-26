//Jonas Elmesten
//joel1803@student.miun.se
//Projket - DT047G

#include "deckreader.h"
#include <fstream>
#include "textpart.h"
#include "imagepart.h"
#include <QString>
#include <iostream>
#include "deckformatexception.h"
#include "linkpart.h"
#include <sstream>

DeckReader::DeckReader() {}

/**
 * @brief DeckReader::readDeck
 * @param path Path to the deck directory on the PC.
 * @return A vector with all the cards added from the directory.
 * Will throw DeckFormatException if errors are found in the deck format when reading the text file.
 */
SmartVector<Card>* DeckReader::readDeck(const fs::path path) {

    SmartVector<Card>* deck = nullptr;

    //Get path of deck.
    std::string deckName = path.filename().string();
    std::string deckPath = path.string() + "\\" + deckName + ".txt";

    std::ifstream deckFile(deckPath, std::ios::binary);

    if(deckFile.is_open()) {

        deck = new SmartVector<Card>(deckName);
        std::stringstream buffer;
        buffer << deckFile.rdbuf();
        deckFile.close();

        std::string modifier;
        std::string nextDate;
        std::string classQ;
        std::string classA;
        std::string dataQ;
        std::string dataA;

        //Read file in this format:
        /* Modifier(int)
         * Date
         * Question class
         * Answer class
         * Data
         * Data
         */
        while(std::getline(buffer, modifier)) {

            std::getline(buffer, nextDate);
            std::getline(buffer, classQ);
            std::getline(buffer, classA);
            std::getline(buffer, dataQ);
            std::getline(buffer, dataA);

            if(!isNumber(nextDate.substr(0,3)))
                throw new DeckFormatException();

            QDateTime date = QDateTime::fromString(QString::fromStdString(nextDate), "yyyy-MM-dd");

            CardPart *question = loadCardPart(classQ, dataQ);
            CardPart *answer = loadCardPart(classA, dataA);

            deck->addObject(std::make_shared<Card>(question, answer, std::stoi(modifier), date));


        }

        std::cout << "Card read:" << deck->size() << std::endl;

    }else {
        deckFile.close();
        delete deck;
        throw std::exception("File error");
    }

    return deck;
}


/**
 * @brief DeckReader::isNumber
 * @param string String to be examined.
 * @return True if numbers are found in this string.
 */
bool DeckReader::isNumber(const std::string& string) {

    return !string.empty() && std::find_if(string.begin(), string.end(),
            [](unsigned char c) { return !std::isdigit(c); }) == string.end();
}


/**
 * @brief DeckReader::loadCardPart
 * @param className Name of the class to be created.
 * @param cardPart Data that will be added to the card part-object.
 * @return A cardPart object.
 *
 * Creates different cardPart-objects depeding on the className.
 * Will throw exception if no compatible class could be created from className.
 */
CardPart* DeckReader::loadCardPart(std::string className, std::string cardPart) {

    CardPart* part = nullptr;

    if(className == "TextPart")
        part = new TextPart(QString(cardPart.c_str()));

    if(className == "ImagePart")
        part =  new ImagePart(cardPart);

    if(className == "LinkPart")
        part =  new LinkPart(QString(cardPart.c_str()));

    if(part == nullptr)
        throw std::exception("No class");
    else
        return part;
}








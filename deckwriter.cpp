//Jonas Elmesten
//joel1803@student.miun.se
//Projket - DT047G

#include "deckwriter.h"
#include <fstream>
#include "imagepart.h"
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;


DeckWriter::DeckWriter(std::string writePath)
    : writePath(writePath) {}

/**
 * @brief DeckWriter::writeDeckToFile
 * @param deck Deck to save to PC.
 * Will create a directory and a text file to hold all the data.
 * ImageParts' images will be copied and saved in the directory.
 * Throws exception if it fails to open and write to the file.
 */
void DeckWriter::writeDeckToFile(SmartVector<Card> &deck) {

    std::string folderPath = writePath + "\\" + deck.getName();

    //Create separate folder for deck.
    if(!fs::exists(folderPath))
        fs::create_directory(folderPath);

    //Create text file to store data.
    std::ofstream file(folderPath + "\\" + deck.getName() + ".txt", std::ios::binary);

    if(file.is_open()) {

        //Save each card.
        for (auto it = deck.begin() ; it != deck.end(); it++) {

            std::stringstream stream;

            Card *card = it->get();
            CardPart *question = card->getQuestion();
            CardPart *answer = card->getAnswer();

            handleImagePart(*question, folderPath);
            handleImagePart(*answer, folderPath);

            std::string questionClass = typeid(*question).name();
            std::string answerClass = typeid(*answer).name();

            //Create save format for card.
            stream << card->getDateModifier();
            stream << "\n";
            stream << card->getNextDate().toString("yyyy-MM-dd").toStdString() + "\n";
            stream << questionClass.substr(6) + "\n";
            stream << answerClass.substr(6) + "\n";
            stream << card->getQuestion()->toSaveable() + "\n";
            stream << card->getAnswer()->toSaveable() + "\n";

            //Store in file.
            file << stream.str();
        }

    }else {
        file.close();
        throw std::exception("Could not open data text file.");
    }

    file.close();
}

/**
 * @brief DeckWriter::handleImagePart
 * @param part CardPart to be checked.
 * @param folderPath Path of this decks' folder.
 * Will copy and save ImageParts' images in the folder that was created for this deck.
 * Nothing will happen if the CardPart is not and ImagePart.
 */
void DeckWriter::handleImagePart(CardPart &part, std::string folderPath) {

    //Handle ImageParts
    if(typeid(part).name() == typeid(ImagePart).name()) {

        ImagePart *image = dynamic_cast<ImagePart*>(&part);
        std::string image_path = folderPath + "\\" + fs::path(image->toSaveable()).filename().string();

        //Move the image to its folder if not already there.
        if(!fs::exists(image_path)) {
            fs::copy_file(image->toSaveable(), image_path);
            image->changeImagePath(image_path);
        }
    }

}

//Jonas Elmesten
//joel1803@student.miun.se
//Projket - DT047G

#ifndef CARD_H
#define CARD_H

#include <QDateTime>
#include <string>
#include "cardpart.h"

enum Level {VERY_HARD, HARD, MEDIUM, EASY, VERY_EASY};

/**
 * @brief The Card class
 * Card as in "flash card".
 * Cards will always consist of a question and an answer.
 * The card will also have a difficulty level that can be adjusted
 * by the user when studying it.
 * It will be adjusted by 5 levels: very hard, hard, medium, easy and very easy.
 * Depending on the level the date of the card will change.
 *
 * The date decides when the card can be studied next time.
 * If you press very easy many times it will be seen less often and
 * the date will be pushed further into the future.
 */
class Card {

public:

    Card(CardPart *question, CardPart *answer, int nextDateModifier, QDateTime nextDate);

    Card(const Card &rhs); //Copy

    Card(Card &&rhs); //Move const

    Card& operator =(const Card &rhs); //Copy assign

    Card& operator =(Card &&rhs); //Move assign

    std::string updateNextReview(Level difficultyLevel);

    void adjustDifficulty();

    CardPart* getQuestion();

    CardPart* getAnswer();

    int getDateModifier();

    QDateTime& getNextDate();

    ~Card ();

private:

    void swap(Card &lhs, Card &rhs);

    int nextDateModifier;
    QDateTime nextDate;

    CardPart *question;
    CardPart *answer;

};

#endif // CARD_H

#ifndef CARD_H
#define CARD_H

#include <QDateTime>
#include <string>
#include "cardpart.h"

//Gör denna abstrakt också (OM TID FINNS)
class Card
{
    int next_date_modifier;
    QDateTime next_date;

    CardPart *question;
    CardPart *answer;

public:

    Card(CardPart *question, CardPart *answer);

    Card(CardPart *question, CardPart *answer, int next_date_modifier, QDateTime next_date);

    std::string to_saveable_string();

    std::string update_next_review(int difficultyLevel);

    void adjustDifficulty();

    CardPart& getQuestion();

    CardPart& getAnswer();

};

#endif // CARD_H

#include "card.h"

Card::Card(CardPart* question, CardPart* answer)
    : next_date_modifier{0}
    , next_date(QDateTime::currentDateTime())
    , question(question)
    , answer(answer) {}

Card::Card(CardPart *question, CardPart *answer, int next_date_modifier, QDateTime next_date)
    : next_date_modifier{next_date_modifier}
    , next_date(next_date)
    , question(question)
    , answer(answer) {}

std::string Card::to_saveable_string() {
    return question->to_saveable() + answer->to_saveable();
}

std::string Card::update_next_review(int difficultyLevel) {

    switch (difficultyLevel) {
    case 1:
        next_date_modifier += 3;
        next_date = next_date.addDays(next_date_modifier);
        break;
    case 2:
        next_date_modifier += 1;
        next_date = next_date.addDays(next_date_modifier);
        break;
    case 3:
        next_date = next_date.addDays(next_date_modifier);
        break;
    case 4:
        next_date_modifier -= 3;

        // Continue to show cards on the next day until next_date_modifier is positive again.
        if(next_date_modifier < 0)
            next_date = next_date.addDays(1);
        else
            next_date = next_date.addDays(next_date_modifier);
        break;
    case 5:
        next_date_modifier -= 6;

        // Continue to show cards on the next day until next_date_modifier is positive again.
        if(next_date_modifier < 0)
            next_date = next_date.addDays(1);
        else
            next_date = next_date.addDays(next_date_modifier);
        break;
    }

    return next_date.toString("yyyy-MM-dd").toStdString();
}


CardPart& Card::getQuestion() {
    return *question;
}

CardPart& Card::getAnswer() {
    return *answer;
}


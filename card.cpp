//Jonas Elmesten
//joel1803@student.miun.se
//Projket - DT047G

#include "card.h"
#include <typeinfo>
#include <algorithm>


Card::Card(CardPart *question, CardPart *answer, int nextDateModifier = 0, QDateTime nextDate = QDateTime::currentDateTime())
    : nextDateModifier{nextDateModifier}
    , nextDate(nextDate)
    , question(question)
    , answer(answer) {}

//Copy
Card::Card(const Card &rhs)
    : Card(rhs.question, rhs.answer, rhs.nextDateModifier, rhs.nextDate){}

//Move const
Card::Card(Card &&rhs)
    : Card(rhs.question, rhs.answer, rhs.nextDateModifier, rhs.nextDate) {
    swap(*this, rhs);
}

//Copy assign
Card& Card::operator =(const Card &rhs) {

    Card temp(rhs.question, rhs.answer, rhs.nextDateModifier, rhs.nextDate);
    swap(*this, temp);

    return *this;
}

//Move assign
Card& Card::operator =(Card &&rhs) {

    swap(*this, rhs);

    return *this;
}

Card::~Card () {
    delete question;
    delete answer;
}

void Card::swap(Card &lhs, Card &rhs) {

    using std::swap;

    swap(lhs.answer, rhs.answer);
    swap(rhs.answer, rhs.question);
}

/**
 * @brief Card::updateNextReview
 * Adjust the next-date-modifier and the next study date for this card.
 * @param difficultyLevel The difficulty level to use when adjusting date modifier and next date.
 * @return Next study date int yyyy-mm-dd
 */
std::string Card::updateNextReview(Level difficultyLevel) {

    switch (difficultyLevel) {
    case VERY_EASY:
        nextDateModifier += 3;
        break;
    case EASY:
        nextDateModifier += 1;
        break;
    case MEDIUM:
        break;
    case HARD:
        nextDateModifier -= 3;
        break;
    case VERY_HARD:
        nextDateModifier -= 6;
        break;
    }

    nextDate = nextDate.addDays(nextDateModifier <= 0 ? 1 : nextDateModifier);

    return nextDate.toString("yyyy-MM-dd").toStdString();
}

CardPart* Card::getQuestion() {
    return question;
}

CardPart* Card::getAnswer() {
    return answer;
}

int Card::getDateModifier() {
    return nextDateModifier;
}

QDateTime& Card::getNextDate() {
    return nextDate;
}

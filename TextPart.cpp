//Jonas Elmesten
//joel1803@student.miun.se
//Projket - DT047G


#include "textpart.h"
#include <QLabel>
#include <iostream>

TextPart::TextPart(QString text)
    : CardPart(new QVBoxLayout)
{
    this->text = text;
    QLabel *label = new QLabel(text);

    label->setWordWrap(true);
    label->setAlignment(Qt::AlignHCenter);
    this->layout->addWidget(label);
}

//Copy
TextPart::TextPart(const TextPart &rhs)
    : TextPart(rhs.text) {}

//Move const
TextPart::TextPart(TextPart &&rhs)
    : TextPart(rhs.text) {
    swap(*this, rhs);
}

//Copy assign
TextPart& TextPart::operator =(const TextPart &rhs) {
    TextPart temp(rhs);
    swap(*this, temp);

    return *this;
}

//Move assign
TextPart& TextPart::operator =(TextPart &&rhs) {
    swap(*this, rhs);

    return *this;
}

void TextPart::swap(TextPart &lhs, TextPart &rhs) {

    using std::swap;

    swap(lhs.text, rhs.text);
    swap(lhs.layout, rhs.layout);
}

QVBoxLayout* TextPart::toGui() {
    return layout;
}

std::string TextPart::toSaveable() {
    return text.toStdString();
}

TextPart::~TextPart() {
    delete layout;
}


#include "textpart.h"
#include <QLabel>
#include <iostream>

TextPart::TextPart(QString text)
    : CardPart(new QVBoxLayout)
{
    this->text = text;
    QLabel *label = new QLabel(text);

    label->setWordWrap(true);
    this->layout->addWidget(label);
}

QVBoxLayout* TextPart::to_gui() {
    return layout;
}

std::string TextPart::to_saveable() {
    return text.toStdString();
}


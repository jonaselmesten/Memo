//Jonas Elmesten
//joel1803@student.miun.se
//Projket - DT047G

#include "imagepart.h"
#include <QLabel>
#include <QString>

ImagePart::ImagePart(std::string imagePath)
    : CardPart(new QVBoxLayout)
{
    QLabel* imageLabel = new QLabel();
    QPixmap pixmap = QPixmap(QString::fromStdString(imagePath));

    imageLabel->setPixmap(pixmap);

    layout->addWidget(imageLabel);

    this->imagePath = imagePath;
}

//Copy
ImagePart::ImagePart(const ImagePart &rhs)
    : ImagePart(rhs.imagePath) {}

//Move const
ImagePart::ImagePart(ImagePart &&rhs)
    : ImagePart(rhs.imagePath) {
    swap(*this, rhs);
}

//Copy assign
ImagePart& ImagePart::operator =(const ImagePart &rhs) {
    ImagePart temp(rhs);
    swap(*this, temp);

    return *this;
}

//Move assign
ImagePart& ImagePart::operator =(ImagePart &&rhs) {
    swap(*this, rhs);

    return *this;
}

void ImagePart::swap(ImagePart &lhs, ImagePart &rhs) {

    using std::swap;

    swap(lhs.imagePath, rhs.imagePath);
    swap(lhs.layout, rhs.layout);
}

QVBoxLayout* ImagePart::toGui() {
    return layout;
}

std::string ImagePart::toSaveable() {
    return imagePath;
}

/**
 * @brief ImagePart::changeImagePath
 * @param image_path New path to the image.
 */
void ImagePart::changeImagePath(std::string image_path) {

    //If fail - set to old path.
    std::string old_path = this->imagePath;

    this->imagePath = image_path;
}

ImagePart::~ImagePart() {
    delete layout;
}




#include "cardwidget.h"


CardWidget::CardWidget(const QString& imagePath, QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(180, 70);

    QLabel* imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);

    QPixmap pixmap(imagePath);
    imageLabel->setPixmap(pixmap.scaled(180, 200, Qt::KeepAspectRatio));

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(imageLabel);
}

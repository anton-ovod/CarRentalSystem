#include "custommessagebox.h"

CustomMessageBox::CustomMessageBox(const QString& labelText, QWidget* parent)
    : QDialog(parent)
{

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(10);

    QLabel* label = new QLabel(labelText, this);
    label->setAlignment(Qt::AlignCenter);
    QFont font("Arial", 12);
    label->setFont(font);
    layout->addWidget(label);

    QPushButton* okButton = new QPushButton("OK", this);
    okButton->setProperty("class", "okButton");
    layout->addWidget(okButton, 0, Qt::AlignCenter);

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);

    setStyleSheet(
        "QDialog {"
        "   background-color: #F0F0F0;"
        "   border-radius: 15px;"
        "}"
        "QLabel {"
        "   color: #333333;"
        "}"
        "QPushButton {"
        "   background-color: rgb(98, 142, 151) ;"
        "   color: #FFFFFF;"
        "   border-radius: 10px;"
        "   min-width: 50px;"
        "   padding: 5px"
        "}"
        "QPushButton:hover {"
        "    background-color: rgba(84, 112, 130, 222);"
        "}"
        "QPushButton:pressed {"
        "   background-color: rgb(98, 142, 151) ;"
        "}"
        );
    adjustSize();
}



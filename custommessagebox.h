#ifndef CUSTOMMESSAGEBOX_H
#define CUSTOMMESSAGEBOX_H

#include <QtWidgets>

class CustomMessageBox : public QDialog
{
    Q_OBJECT
public:
    CustomMessageBox(const QString& labelText, QWidget* parent = nullptr);
};

#endif

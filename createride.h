#ifndef CREATERIDE_H
#define CREATERIDE_H

#include <QDialog>
#include <QString>
#include <QPainter>
#include <QSqlQuery>

#include "databasehandler.h"
#include "custommessagebox.h"

namespace Ui {
class CreateRide;
}

class CreateRide : public QDialog
{
    Q_OBJECT

public:
    explicit CreateRide(QWidget *parent = nullptr);
    ~CreateRide();

    void paintEvent(QPaintEvent *);
    void ClearInput();
    bool CheckSeats();
    bool CheckPrice();
    bool CheckEngine();
    QString CurrentUserName;

private slots:
    void on_submitBtn_clicked();
    void GetData();

private:
    Ui::CreateRide *ui;

    QSqlQuery query;

    QString CarName;
    QString CarModel;
    QString CarSeats;
    QString CarEngine;
    QString CarColor;
    QString CarPrice;

    QSqlDatabase &database = DatabaseHandler::getInstance().getDatabase();
};

#endif // CREATERIDE_H

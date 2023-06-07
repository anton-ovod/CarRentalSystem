#ifndef RESERVECAR_H
#define RESERVECAR_H

#include <QDialog>
#include <QStringList>
#include <QPainter>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QSqlDatabase>
#include <QDateTime>
#include <random>

#include "databasehandler.h"
#include "ClickableLabel.h"
#include "custommessagebox.h"

namespace Ui {
class ReserveCar;
}

class ReserveCar : public QDialog
{
    Q_OBJECT

public:
    explicit ReserveCar(QWidget *parent = nullptr);
    ~ReserveCar();
    void SetCarData();
    void paintEvent(QPaintEvent *);
    QString GenerateOrderNumber();
    QString CurrentUserName;
    QStringList CarData;

private slots:
    void UpdateDataBase();

signals:
    void ReservedComplete();

private:
    Ui::ReserveCar *ui;
    QSqlQuery query;
    QString queryStr;
    QSqlDatabase& database = DatabaseHandler::getInstance().getDatabase();
};

#endif // RESERVECAR_H

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
#include <QtGlobal>

#include "databasehandler.h"
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
    QString CurrentUserName;
    QStringList CarData;

private:
    Ui::ReserveCar *ui;

    QSqlDatabase& database = DatabaseHandler::getInstance().getDatabase();
};

#endif // RESERVECAR_H

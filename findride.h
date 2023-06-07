#ifndef FINDRIDE_H
#define FINDRIDE_H

#include <QWidget>
#include <QPainter>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QDebug>
#include <QAbstractItemModel>
#include <QString>

#include "databasehandler.h"
#include "custommessagebox.h"
#include "reservecar.h"

namespace Ui {
class FindRide;
}

class FindRide : public QWidget
{
    Q_OBJECT

public:
    explicit FindRide(QWidget *parent = nullptr);
    ~FindRide();

    void paintEvent(QPaintEvent *);
    void appendData();
    void RefreshData();
    int getCurrentData();
    QString CurrentUserName;

signals:
    void backToMainWindowPage();

private slots:
    void on_backBtn_clicked();

    void on_reserveBtn_clicked();

    void search();

private:
    Ui::FindRide *ui;
    QStringList CarData;
    QSqlTableModel *tableModel;
    ReserveCar *ReservePage;
    QSqlDatabase& database = DatabaseHandler::getInstance().getDatabase();
};

#endif // FINDRIDE_H

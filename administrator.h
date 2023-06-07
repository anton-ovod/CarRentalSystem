#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QtSql>
#include <QSqlTableModel>
#include <QPainter>
#include <QDebug>

#include "databasehandler.h"
#include "custommessagebox.h"


namespace Ui {
class Administrator;
}

class Administrator : public QWidget
{
    Q_OBJECT

public:
    explicit Administrator(QWidget *parent = nullptr);
    ~Administrator();

    void appendData();
    void paintEvent(QPaintEvent *);

private slots:
    void search();
    void on_BackBtn_clicked();

signals:
    void backToLogin();

private:
    Ui::Administrator *ui;
    QSqlTableModel* tableModel;
    QSqlDatabase& database = DatabaseHandler::getInstance().getDatabase();

};

#endif // ADMINISTRATOR_H

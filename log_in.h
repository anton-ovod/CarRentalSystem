#ifndef LOG_IN_H
#define LOG_IN_H

#include <QWidget>
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QTimer>
#include <QPainter>

#include "databasehandler.h"
#include "sign_in.h"
#include "administrator.h"
#include "mainwindow.h"


namespace Ui {
class Log_in;
}

class Log_in : public QWidget
{
    Q_OBJECT

public:
    explicit Log_in(QWidget *parent = nullptr);
    ~Log_in();

    void paintEvent(QPaintEvent *) override;
    void cleanLineEdit();
    void handleLabelClicked();

    Sign_In *sign_in;
    Administrator *admin;
    MainWindow *main;

protected:
    //void mousePressEvent(QMouseEvent* event) override;

private slots:
    void on_LogBtn_clicked();

private:
    Ui::Log_in *ui;
    QSqlDatabase& database = DatabaseHandler::getInstance().getDatabase();
};

#endif // LOG_IN_H

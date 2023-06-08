#ifndef SIGN_IN_H
#define SIGN_IN_H


#include <QMessageBox>
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QPainter>
#include <QRegularExpression>
#include <QPixmap>

#include "databasehandler.h"
#include "custommessagebox.h"


namespace Ui {
class Sign_In;
}

class Sign_In : public QWidget
{
    Q_OBJECT

public:
    explicit Sign_In(QWidget *parent = 0);
    ~Sign_In();

    void paintEvent(QPaintEvent *);
    void cleanLineEdit();
    void insertData();
    bool CheckPassword();
    bool CheckEmail();
    bool CheckPhoneNumber();

signals:
    void backLogIn();

private slots:
    void on_signBtn_clicked();
    void getInput();



private:
    Ui::Sign_In *ui;
    QSqlDatabase& database = DatabaseHandler::getInstance().getDatabase();

    QString signName;
    QString signPassword;
    QString signEmail;
    QString signPhone;

};

#endif // SIGN_IN_H

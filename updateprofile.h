#ifndef UPDATEPROFILE_H
#define UPDATEPROFILE_H

#include <QDialog>
#include <QPainter>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QRegularExpression>

#include "databasehandler.h"
#include "custommessagebox.h"

namespace Ui {
class UpdateProfile;
}

class UpdateProfile : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateProfile(QWidget *parent = nullptr);
    ~UpdateProfile();

    void paintEvent(QPaintEvent *);
    QString CurrentUserName;
    void InitData();
    bool CheckUserName();
    bool CheckPassword();
    bool CheckEmail();
    bool CheckPhoneNumber();

private slots:
    void on_updateBtn_clicked();
    void on_cancelBtn_clicked();

signals:
    void ChangedData();

private:

    Ui::UpdateProfile *ui;
    QSqlQuery query;
    QString queryStr;
    QString UserName;
    QString PhoneNumber;
    QString Email;
    QString Password;
    int CurrentUserID;
    QSqlDatabase& database = DatabaseHandler::getInstance().getDatabase();

};

#endif // UPDATEPROFILE_H

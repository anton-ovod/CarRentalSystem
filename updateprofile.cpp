#include "updateprofile.h"
#include "ui_updateprofile.h"

UpdateProfile::UpdateProfile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateProfile)
{
    ui->setupUi(this);
    this->setFixedSize(400, 450);
    this->setWindowTitle("Update Profile");
}

void UpdateProfile::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/images/images/rose2.png");
    painter.drawPixmap(0,0,pix);
}


void UpdateProfile::InitData()
{
    if(!database.open())
    {
        CustomMessageBox messageBox("Something went wrong!");
        int result = messageBox.exec();
        if (result == QMessageBox::Ok) {
            messageBox.close();
        }
    }
    else
    {
        //getting user name from database
        queryStr = QString("SELECT UserName FROM USERS WHERE UserName = '"+CurrentUserName+"'");

        if(!query.exec(queryStr))
        {
            CustomMessageBox messageBox("Something went wrong!");
            int result = messageBox.exec();
            if (result == QMessageBox::Ok) {
                messageBox.close();
            }
        }
        else
        {
            if(query.next()){
                QString UserName = query.value(0).toString();
                ui->showUserName->setText(UserName);
            }
            else
            {
                CustomMessageBox messageBox("Something went wrong!");
                int result = messageBox.exec();
                if (result == QMessageBox::Ok) {
                    messageBox.close();
                }
            }
        }

        //getting user email from database
        queryStr = QString("SELECT Email FROM USERS WHERE UserName = '"+CurrentUserName+"'");

        if(!query.exec(queryStr))
        {
            CustomMessageBox messageBox("Something went wrong!");
            int result = messageBox.exec();
            if (result == QMessageBox::Ok) {
                messageBox.close();
            }
        }
        else
        {
            if(query.next())
            {
                QString UserEmail = query.value(0).toString();
                ui->showEmail->setText(UserEmail);
            }
        }

        //geting user phone number from database

        queryStr = QString("SELECT PhoneNumber FROM USERS WHERE UserName = '"+CurrentUserName+"'");

        if(!query.exec(queryStr))
        {
            CustomMessageBox messageBox("Something went wrong!");
            int result = messageBox.exec();
            if (result == QMessageBox::Ok) {
                messageBox.close();
            }
        }
        else
        {
            if(query.next())
            {
                QString UserPhoneNumber = query.value(0).toString();
                ui->showPhoneNumber->setText(UserPhoneNumber);
            }
        }

        queryStr = QString("SELECT Password FROM USERS WHERE UserName = '"+CurrentUserName+"'");

        if(!query.exec(queryStr))
        {
            CustomMessageBox messageBox("Something went wrong!");
            int result = messageBox.exec();
            if (result == QMessageBox::Ok) {
                messageBox.close();
            }
        }
        else
        {
            if(query.next())
            {
                QString UserPassword = query.value(0).toString();
                ui->showPassword->setText(UserPassword);
            }
        }

        database.close();
    }
}


void UpdateProfile::on_cancelBtn_clicked()
{
    emit this->ChangedData();
    this->hide();
}

void UpdateProfile::on_updateBtn_clicked()
{
    QString newName = ui->showUserName->text();
    QString newEmail = ui->showEmail->text();
    QString newPhoneNumber = ui->showPhoneNumber->text();
    QString newPassword = ui->showPassword->text();

    if(!database.open())
    {
        CustomMessageBox messageBox("Something went wrong!");
        int result = messageBox.exec();
        if (result == QMessageBox::Ok) {
            messageBox.close();
        }
    }
    else
    {
        // getting the id of CurrentUser
        queryStr = "SELECT id FROM USERS WHERE UserName = '"+CurrentUserName+"'";

        if(!query.exec(queryStr))
        {
            CustomMessageBox messageBox("Something went wrong!");
            int result = messageBox.exec();
            if (result == QMessageBox::Ok) {
                messageBox.close();
            }
        }
        else
        {
            int CurrentUserID;
            if(query.next())
            {
                CurrentUserID = query.value(0).toInt();
            }
        }

        queryStr = "UPDATE USERS SET UserName = '"+newName+"', Password = '"+newPassword+"', PhoneNumber = '"+newPhoneNumber+"', Email = '"+newEmail+"'";

        if(!query.exec(queryStr))
        {
            CustomMessageBox messageBox("Something went wrong!");
            int result = messageBox.exec();
            if (result == QMessageBox::Ok) {
                messageBox.close();
            }
        }
        else
        {
            CustomMessageBox messageBox("Your profile has been succesfully updated!");
            int result = messageBox.exec();
            if (result == QMessageBox::Ok) {
                messageBox.close();
            }
            CurrentUserName = newName;
        }
        database.close();
    }


}

UpdateProfile::~UpdateProfile()
{
    delete ui;
}

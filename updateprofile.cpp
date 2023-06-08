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

bool UpdateProfile::CheckUserName()
{
    QString NewUserName = ui->showUserName->text().trimmed();
    if(!database.open())
    {
        CustomMessageBox messageBox("Something went wrong!");
        int result = messageBox.exec();
        if (result == QMessageBox::Ok) {
            messageBox.close();
        }
        return 0;
    }
    else
    {
    query.prepare("SELECT UserName FROM USERS WHERE UserName = '"+NewUserName+"'");
    if(query.exec() && query.next())
    {
        return 0;
    }
    return 1;
    }
}

bool UpdateProfile::CheckEmail()
{
    QString NewUserEmail = ui->showEmail->text().trimmed();
    QRegularExpression emailRegex("^\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}\\b$");
    bool isEmailValid = emailRegex.match(NewUserEmail).hasMatch();
    if(!isEmailValid)
    {
        return 0;
    }
    return 1;
}

bool UpdateProfile::CheckPassword()
{
    QString NewPassword = ui->showPassword->text().trimmed();
    bool hasMinLength = NewPassword.length() >= 8;
    bool hasUppercase = NewPassword.contains(QRegularExpression("[A-Z]"));
    bool hasNumber = NewPassword.contains(QRegularExpression("\\d"));
    bool hasSpecialSymbol = NewPassword.contains(QRegularExpression("[^a-zA-Z0-9]"));

    if(!hasNumber || !hasSpecialSymbol || !hasMinLength || !hasMinLength)
    {
        return 0;
    }
    return 1;
}

bool UpdateProfile::CheckPhoneNumber()
{
    QString NewPhoneNumber = ui->showPhoneNumber->text().trimmed();
    QRegularExpression regex("^\\+?[1-9]\\d{1,14}$");
    bool match = regex.match(NewPhoneNumber).hasMatch();
    if(!match)
    {
        return 0;
    }
    return 1;
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
    QString newName = ui->showUserName->text().trimmed();
    QString newEmail = ui->showEmail->text().trimmed();
    QString newPhoneNumber = ui->showPhoneNumber->text().trimmed();
    QString newPassword = ui->showPassword->text().trimmed();
    if(!CheckEmail())
    {
        CustomMessageBox messageBox("New Email is not valid!");
        int result = messageBox.exec();
        if (result == QMessageBox::Ok) {
            messageBox.close();
        }
    }
    else if(!CheckPassword())
    {
        CustomMessageBox messageBox("New password is to weak!");
        int result = messageBox.exec();
        if (result == QMessageBox::Ok) {
            messageBox.close();
        }
    }
    else if(!CheckPhoneNumber())
    {
        CustomMessageBox messageBox("New phone number is not valid!");
        int result = messageBox.exec();
        if (result == QMessageBox::Ok) {
            messageBox.close();
        }
    }
    else if(ui->showUserName->text().trimmed() != CurrentUserName && !CheckUserName())
    {
        CustomMessageBox messageBox("This user name already exists!");
        int result = messageBox.exec();
        if (result == QMessageBox::Ok) {
            messageBox.close();
        }
    }
    else if(!database.open())
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
            if(query.next())
            {
                CurrentUserID = query.value(0).toInt();
            }
        }
        query.prepare("UPDATE USERS SET UserName = '"+newName+"', Password = '"+newPassword+"', PhoneNumber = '"+newPhoneNumber+"', Email = '"+newEmail+"' WHERE Id = :ID");
        query.bindValue(":ID", CurrentUserID);
        if(!query.exec())
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

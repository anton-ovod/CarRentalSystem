#include "sign_in.h"
#include "ui_sign_in.h"


Sign_In::Sign_In(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sign_In)
{
    ui->setupUi(this);
    this->setFixedSize(1100, 700);
    this->setWindowTitle("Sign up");

    connect(ui->backLog, &ClickableLabel::clicked, [=](){
        cleanLineEdit();
        emit this->backLogIn();
    });
}


void Sign_In::insertData()
{
    QSqlQuery sql;
    sql.prepare("INSERT INTO USERS (UserName, Password, Email, PhoneNumber) "
                "VALUES (:UserName, :Password, :Email, :PhoneNumber)");
    sql.bindValue(":UserName", signName);
    sql.bindValue(":Password", signPassword);
    sql.bindValue(":Email", signEmail);
    sql.bindValue(":PhoneNumber", signPhone);

    if(sql.exec())
    {
        CustomMessageBox messageBox("User has been succesfully added");
        int result = messageBox.exec();
        if (result == QMessageBox::Ok) {
            messageBox.close();
        }
    }
    else
    {
        CustomMessageBox messageBox("Something went wrong");
        int result = messageBox.exec();
        if (result == QMessageBox::Ok) {
            messageBox.close();
        }
    }

}
void Sign_In::getInput()
{
    signName = ui->fullNameTxt->text();
    signPassword = ui->passwordTxt->text();
    signEmail = ui->emailTxt->text();
    signPhone = ui->phoneTxt->text();
}

void Sign_In::cleanLineEdit()
{
    ui->fullNameTxt->clear();
    ui->passwordTxt->clear();
    ui->emailTxt->clear();
    ui->phoneTxt->clear();
}

void Sign_In::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/images/images/CoverMain.png");
    painter.drawPixmap(0,0,pix);
}

Sign_In::~Sign_In()
{
    delete ui;
}



void Sign_In::on_signBtn_clicked()
{
    getInput();
    if(signName.isEmpty() || signPassword.isEmpty() ||
        signEmail.isEmpty() || signPhone.isEmpty())
    {
        CustomMessageBox messageBox("You need to enter all the information beforehead");
        int result = messageBox.exec();
        if (result == QMessageBox::Ok) {
            messageBox.close();
        }
    }
    else
    {
        if(!database.open())
        {
            CustomMessageBox messageBox("Check your database connection");
            int result = messageBox.exec();
            if (result == QMessageBox::Ok) {
                messageBox.close();
            }
            return;
        }
        QSqlQuery sql;
        QString checkExist = "SELECT * from USERS where UserName = '"+signName+"' ";
        if(sql.exec(checkExist))
        {
            if(sql.next() == true)
            {
                CustomMessageBox messageBox("This user name already exists");
                int result = messageBox.exec();
                if (result == QMessageBox::Ok) {
                    messageBox.close();
                }
            }
            else
            {
                insertData();
                cleanLineEdit();
            }
        }
    }
    database.close();
}



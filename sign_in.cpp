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

    connect(ui->PasswordTxt, &QLineEdit::textChanged, this, &Sign_In::CheckPassword);
    connect(ui->EmailTxt, &QLineEdit::textChanged, this, &Sign_In::CheckEmail);
    connect(ui->PhoneTxt, &QLineEdit::textChanged, this, &Sign_In::CheckPhoneNumber);
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
    signName = ui->NameTxt->text().trimmed();
    signPassword = ui->PasswordTxt->text().trimmed();
    signEmail = ui->EmailTxt->text().trimmed();
    signPhone = ui->PhoneTxt->text().trimmed();
}

void Sign_In::cleanLineEdit()
{
    ui->NameTxt->clear();
    ui->PasswordTxt->clear();
    ui->EmailTxt->clear();
    ui->PhoneTxt->clear();
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

bool Sign_In::CheckEmail()
{
    QString Email = ui->EmailTxt->text().trimmed();
    QRegularExpression emailRegex("^\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}\\b$");
    bool isEmailValid = emailRegex.match(Email).hasMatch();
    if(!isEmailValid)
    {
        ui->EmailTxt->setStyleSheet("color: rgb(192, 192, 192);");
        return 0;
    }
    ui->EmailTxt->setStyleSheet("color: white;");
    return 1;


}
bool Sign_In::CheckPhoneNumber()
{
    QString PhoneNumber = ui->PhoneTxt->text().trimmed();
    QRegularExpression regex("^\\+?[1-9]\\d{1,14}$");
    bool match = regex.match(PhoneNumber).hasMatch();
    if(!match)
    {
        ui->PhoneTxt->setStyleSheet("color: rgb(192, 192, 192);");
        return 0;
    }
        ui->PhoneTxt->setStyleSheet("color: white;");
        return 1;
}

bool Sign_In::CheckPassword()
{
    QString password = ui->PasswordTxt->text().trimmed();
    bool hasMinLength = password.length() >= 8;
    bool hasUppercase = password.contains(QRegularExpression("[A-Z]"));
    bool hasNumber = password.contains(QRegularExpression("\\d"));
    bool hasSpecialSymbol = password.contains(QRegularExpression("[^a-zA-Z0-9]"));

    ui->LengthCheck->setPixmap(hasMinLength ? QPixmap(":/images/images/tick.png") : QPixmap(":/images/images/cross.png"));
    ui->UpperCaseCheck->setPixmap(hasUppercase ? QPixmap(":/images/images/tick.png") : QPixmap(":/images/images/cross.png"));
    ui->NumberCheck->setPixmap(hasNumber ? QPixmap(":/images/images/tick.png") : QPixmap(":/images/images/cross.png"));
    ui->SpecSymbCheck->setPixmap(hasSpecialSymbol ? QPixmap(":/images/images/tick.png") : QPixmap(":/images/images/cross.png"));
    if(!hasNumber || !hasSpecialSymbol || !hasMinLength || !hasMinLength)
    {
        ui->PasswordTxt->setStyleSheet("color: rgb(192, 192, 192);");
        return 0;
    }
    ui->PasswordTxt->setStyleSheet("color: white;");
        return 1;
}

void Sign_In::on_signBtn_clicked()
{
    getInput();
    bool hasMinLength = signPassword.length() >= 8;
    bool hasUppercase = signPassword.contains(QRegularExpression("[A-Z]"));
    bool hasNumber = signPassword.contains(QRegularExpression("\\d"));
    bool hasSpecialSymbol = signPassword.contains(QRegularExpression("[^a-zA-Z0-9]"));



    if(signName.isEmpty() || signPassword.isEmpty() ||
        signEmail.isEmpty() || signPhone.isEmpty())
    {
        CustomMessageBox messageBox("You need to enter all the information beforehead");
        int result = messageBox.exec();
        if (result == QMessageBox::Ok) {
            messageBox.close();
        }
    }
    else if(!CheckEmail())
    {
        CustomMessageBox messageBox("Your email is not valid!");
        int result = messageBox.exec();
        if (result == QMessageBox::Ok) {
            messageBox.close();
        }
    }
    else if(!CheckPassword())
    {
        CustomMessageBox messageBox("Your password is too weak!");
        int result = messageBox.exec();
        if (result == QMessageBox::Ok) {
            messageBox.close();
        }
    }
    else if(!CheckPhoneNumber())
    {
        CustomMessageBox messageBox("Your phone number is not valid!");
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



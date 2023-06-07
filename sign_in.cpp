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

void Sign_In::CheckPassword()
{
    QString password = ui->PasswordTxt->text();
    bool hasMinLength = password.length() >= 8;
    bool hasUppercase = password.contains(QRegularExpression("[A-Z]"));
    bool hasNumber = password.contains(QRegularExpression("\\d"));
    bool hasSpecialSymbol = password.contains(QRegularExpression("[^a-zA-Z0-9]"));

    ui->LengthCheck->setPixmap(hasMinLength ? QPixmap(":/images/images/tick.png") : QPixmap(":/images/images/cross.png"));
    ui->UpperCaseCheck->setPixmap(hasUppercase ? QPixmap(":/images/images/tick.png") : QPixmap(":/images/images/cross.png"));
    ui->NumberCheck->setPixmap(hasNumber ? QPixmap(":/images/images/tick.png") : QPixmap(":/images/images/cross.png"));
    ui->SpecSymbCheck->setPixmap(hasSpecialSymbol ? QPixmap(":/images/images/tick.png") : QPixmap(":/images/images/cross.png"));
}

void Sign_In::on_signBtn_clicked()
{
    getInput();
    bool hasMinLength = signPassword.length() >= 8;
    bool hasUppercase = signPassword.contains(QRegularExpression("[A-Z]"));
    bool hasNumber = signPassword.contains(QRegularExpression("\\d"));
    bool hasSpecialSymbol = signPassword.contains(QRegularExpression("[^a-zA-Z0-9]"));

    QRegularExpression emailRegex("^\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}\\b$");
    bool isEmailValid = emailRegex.match(signEmail).hasMatch();

    if(signName.isEmpty() || signPassword.isEmpty() ||
        signEmail.isEmpty() || signPhone.isEmpty())
    {
        CustomMessageBox messageBox("You need to enter all the information beforehead");
        int result = messageBox.exec();
        if (result == QMessageBox::Ok) {
            messageBox.close();
        }
    }
    else if(!hasMinLength || !hasUppercase || !hasNumber || !hasSpecialSymbol)
    {
        CustomMessageBox messageBox("Your password is too weak");
        int result = messageBox.exec();
        if (result == QMessageBox::Ok) {
            messageBox.close();
        }
    }
    else if(!isEmailValid)
    {
        CustomMessageBox messageBox("Your email address is not correct");
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



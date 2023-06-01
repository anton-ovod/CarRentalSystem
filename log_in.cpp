#include "log_in.h"
#include "ui_log_in.h"
#include "ClickableLabel.h"


Log_in::Log_in(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Log_in)
{
    ui->setupUi(this);
    this->setFixedSize(1100, 700);
    this->setWindowTitle("Log in");
    ui->userNameTxt->setFocus();
    ui->logInSuccessful->setVisible(false);
    DatabaseHandler::getInstance().initializeDatabase();

    sign_in = new Sign_In;
    admin = new Administrator;
    main = new MainWindow;

    connect(ui->SignInBtn, &ClickableLabel::clicked, [=](){

        sign_in->show();
        this->close();
    });
    connect(sign_in, &Sign_In::backLogIn, [=](){
        cleanLineEdit();
        this->show();
        sign_in->close();

    });
    connect(admin, &Administrator::backToLogin, [=]() {
        this->show();
        admin->close();
    });

    connect(main, &MainWindow::backToLogIn, [=](){
        QTimer::singleShot(500, this, [=](){
                main->close();
                this->show();
        });
    });


}
void Log_in::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/images/images/CoverMain.png");
    painter.drawPixmap(0,0,pix);
}


void Log_in::cleanLineEdit()
{
    ui->userNameTxt->clear();
    ui->passwordTxt->clear();

}



void Log_in::HandleLogInInput()
{
    if(ui->userNameTxt->text().isEmpty() || ui->passwordTxt->text().isEmpty())
    {
        CustomMessageBox messageBox("Check your name and password!");
        int result = messageBox.exec();
        if (result == QMessageBox::Ok) {
            messageBox.close();
        }
    }
    else
    {
        UserName = ui->userNameTxt->text();
        Password = ui->passwordTxt->text();
        QSqlQuery query;
        query.prepare("SELECT * FROM USERS WHERE UserName = :username AND Password = :password");
        query.bindValue(":username", UserName);
        query.bindValue(":password", Password);

        if(!query.exec())
        {
            CustomMessageBox messageBox("Something went wrong!");
            int result = messageBox.exec();
            if (result == QMessageBox::Ok) {
                messageBox.close();
            }
            qDebug() << "Error executing the query:" << query.lastError().text();
        }

        if(query.next())
        {

            if(UserName == "Admin" && Password == "admin")
            {
                adminShow();
            }
            else
            {
                database.close();
                mainWindowShow();
            }
        }
        else
        {
            CustomMessageBox messageBox("You are not signed up!");
            int result = messageBox.exec();
            if (result == QMessageBox::Ok) {
                messageBox.close();
            }
            qDebug() << "You are not signed up";
        }
    }


}

void Log_in::adminShow()
{
    QTimer::singleShot(500, this, [=](){
        ui->logInSuccessful->setVisible(true);
        QTimer::singleShot(1000, this, [=](){
            this->close();
            admin->show();
            admin->appendData();
            ui->logInSuccessful->setVisible(false);
            cleanLineEdit();
        });
    });
}

void Log_in::mainWindowShow()
{
    QTimer::singleShot(500, this, [=](){
        ui->logInSuccessful->setVisible(true);
    });
    QTimer::singleShot(1500, this, [=](){
        main->CurrentUserName = UserName;
        this->close();
        main->show();
        main->init();
        ui->logInSuccessful->setVisible(false);
        cleanLineEdit();
    });
}

Log_in::~Log_in()
{
    delete ui;
}

void Log_in::on_LogBtn_clicked()
{
    if(!database.open())
    {
        CustomMessageBox messageBox("Error with database connection!");
        int result = messageBox.exec();
        if (result == QMessageBox::Ok) {
            messageBox.close();
        }
    }
    else
    {
        HandleLogInInput();
    }


}


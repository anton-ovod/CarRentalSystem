#include "log_in.h"
#include "ui_log_in.h"
#include "ClickableLable.h"

Log_in::Log_in(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Log_in)
{
    ui->setupUi(this);
    this->setFixedSize(1100, 700);
    this->setWindowTitle("Log in");
    ui->userNameTxt->setFocus();  //set the cursor on user name area
    ui->logInSuccessful->setVisible(false);

    connect(ui->SignInBtn, &ClickableLable::clicked,this, &Log_in::handleLabelClicked);
    // operator new pages of sign in, main screen and adminstrator
    //admin = new Administrator;

    /*connect( &ClickableLabel::clicked, [=](){
        // When the user click sign up button
        // The sign up page shows
        // Log in page hide
        signIn->show();
        this->close();
    });

    connect(signIn, &Sign_in::backLogin, [=](){
        cleanLineEdit();
        signIn->hide();
        this->show();
    });

    connect(mainPage, &MainWindow::backToLogin, [=](){
        QTimer::singleShot(500, this, [=](){
            mainPage->hide();
            this->show();
        });
    });

    connect(admin, &Administrator::backToLogIn, [=](){
        admin->hide();
        this->show();
    });*/
}
void Log_in::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/images/images/CoverMain.png");
    painter.drawPixmap(0,0,pix);

}

void Log_in::handleLabelClicked()
{
    ui->title->setText("Working");
}

/*void Log_in::on_LogBtn_clicked()
{
    connectDatabase();

    //get username and password from user input areas


    if(db.open()) {
        matchDatabase();
    }else {
        QMessageBox::information(this, "database", "connection failed");
    }

    // if database close in there, then the data cannot match
}
*/

/*
void Log_in::connectDatabase()
{
    if(QSqlDatabase::contains("qt_sql_default_connection")) {

        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else {
        db = QSqlDatabase::addDatabase("QSQLITE");
    }

    db.setHostName("localhost");
    db.setUserName("Root");
    db.setPassword("");
    db.setDatabaseName("/Users/a233/Desktop/Car pool/dataBase/usersData.db");
}
*/
/*
void Log_in::matchDatabase()
{
    QString userName = ui->userNameBtn->text();
    QString password = ui->passwordBtn->text();
    //    qDebug <<userName + password;  //get data succeed
    qDebug()<<"connection succeed";
    QSqlQuery query(QSqlDatabase::database("QSQLITE"));
    query.prepare(QString("Select * from users Where userName = :userName "
                          "And password = :password"));
    // retrived data from database
    query.bindValue(":userName", userName);
    query.bindValue(":password", password);

    if(!query.exec()) {
        QMessageBox::information(this, "failed", "faile to execute");
    }else {
        if(query.next()) {
            //next is to determine whether the matching result is in the database
            //matching from 0
            QString userNameFromDB = query.value(0).toString();
            QString passwordFromDB = query.value(1).toString();

            if(userNameFromDB == "Ellie" && passwordFromDB == "1137") {
                qDebug() <<"Admin login"<<endl;   //testing Admin
                adminShow();
            }
            else if(userNameFromDB == userName && passwordFromDB == password)
            {
                mainScreenShow();
            }
        }
        else
        {
            QMessageBox::information(this, "failed", "Log in failed, Please check your username or "
                                                     "password");
        }
    }
}

void Log_in::adminShow()
{
    QTimer::singleShot(500, this, [=](){
        ui->logInSuccessful->setVisible(true);
        QTimer::singleShot(1000, this, [=](){
            admin->show();
            this->hide();
            ui->logInSuccessful->setVisible(false);
        });
    });
}

void Log_in::mainScreenShow()
{
    QString userName = ui->userNameBtn->text();
    //Pause 0.5 second when login successed for better user experience
    QTimer::singleShot(500, this, [=](){
        ui->logInSuccessful->setVisible(true);
    });
    QTimer::singleShot(1500, this, [=](){
        // username of main page is inherited to here
        mainPage->usersNames = userName;
        this->hide();
        mainPage->show();
        //declear in mainPage, implement in here.
        //Otherwise the obtained data will be covered
        mainPage->init();
        ui->logInSuccessful->setVisible(false);
        cleanLineEdit();
    });

}
*/
void Log_in::cleanLineEdit()
{
    ui->userNameTxt->clear();
    ui->passwordTxt->clear();

}


Log_in::~Log_in()
{
    delete ui;
}

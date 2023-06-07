#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1100, 700);
    this->setWindowTitle("Main Page");
    updatePage = new UpdateProfile;
    ui->Main->setCurrentIndex(1);
    findRide = new FindRide;
    createRide = new CreateRide;

    connect(ui->tripsBtn, &QPushButton::clicked, [=](){
        myTrips();
        ui->Main->setCurrentIndex(0);
    });

    connect(ui->backAccountBtn, &QPushButton::clicked, [=](){
        ui->Main->setCurrentIndex(1);
    });

    connect(ui->BackBtn, &ClickableLabel::clicked, [=]()
            {
        emit this->backToLogIn();
    });

    connect(updatePage, &UpdateProfile::ChangedData, [=](){
        CurrentUserName = updatePage->CurrentUserName;
        init();
    });

    connect(ui->findRideBtn, &QPushButton::clicked, [=](){
                findRide->CurrentUserName = CurrentUserName;
                findRide->appendData();
                findRide->show();
                this->hide();
            });

    connect(findRide, &FindRide::backToMainWindowPage, [=](){
        this->show();
        findRide->hide();

    });

    connect(ui->createRideBtn, &QPushButton::clicked, [=](){
        createRide->CurrentUserName = CurrentUserName;
        createRide->show();
    });
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/images/images/rose2.png");
    painter.drawPixmap(0, 0, pix);
}

void MainWindow::init()
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
                ui->ShowPhoneNumber->setText(UserPhoneNumber);
            }
        }

        database.close();
    }

}

void MainWindow::myTrips()
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
        queryStr = QString("SELECT OrderNumber FROM USERS WHERE UserName = '"+CurrentUserName+"'");

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
                QString UserOrderNumber = query.value(0).toString();
                ui->showOrderNumber->setText(UserOrderNumber);
            }
        }
        database.close();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_editBtn_clicked()
{
    updatePage->CurrentUserName = CurrentUserName;
    updatePage->show();
    updatePage->InitData();
}


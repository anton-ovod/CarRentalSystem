#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1100, 700);
    this->setWindowTitle("Main Page");

    ui->Main->setCurrentIndex(1);
    connect(ui->backAccountBtn, &QPushButton::clicked, [=](){
        ui->Main->setCurrentIndex(1);
    });

    connect(ui->BackBtn, &ClickableLabel::clicked, [=]()
            {
        emit this->backToLogIn();
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
        QString NamequeryStr = QString("SELECT UserName FROM USERS WHERE UserName = '%1'").arg(CurrentUserName);
        QSqlQuery query;
        if(!query.exec(NamequeryStr))
        {
            CustomMessageBox messageBox("Something went wrong1!");
            int result = messageBox.exec();
            if (result == QMessageBox::Ok) {
                messageBox.close();
            }
        }
        else
        {
            //QString UserName = query.value(0).toString();
            ui->showUserName->setText("UserName");
        }


        database.close();
    }

}

void MainWindow::myTrips()
{

}
MainWindow::~MainWindow()
{
    delete ui;
}


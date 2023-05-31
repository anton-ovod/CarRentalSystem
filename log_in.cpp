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
        this->hide();
    });

    connect(sign_in, &Sign_In::backLogIn, [=](){
        cleanLineEdit();
        this->show();
        sign_in->hide();

    });
    connect(admin, &Administrator::backToLogin, [=]() {
        this->show();
        admin->hide();
    });


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


void Log_in::cleanLineEdit()
{
    ui->userNameTxt->clear();
    ui->passwordTxt->clear();

}


Log_in::~Log_in()
{
    delete ui;
}

void Log_in::on_LogBtn_clicked()
{
   admin->show();
}


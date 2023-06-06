#include "reservecar.h"
#include "ui_reservecar.h"

ReserveCar::ReserveCar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReserveCar)
{
    ui->setupUi(this);
    this->setFixedSize(500, 500);
    this->setWindowTitle("Reserve Cars");
}

ReserveCar::~ReserveCar()
{
    delete ui;
}


void ReserveCar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/images/images/Mystic.png");
    painter.drawPixmap(0, 0, pix);
}

void ReserveCar::SetCarData()
{
    ui->Name->setText(CarData.at(1));
    ui->Model->setText(CarData.at(2));
    ui->Seats->setText(CarData.at(3));
    ui->Engine->setText(CarData.at(4));
    ui->Color->setText(CarData.at(5));
    ui->Price->setText(CarData.at(7));
    ui->Owner->setText(CarData.at(6));
}

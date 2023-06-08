#include "reservecar.h"
#include "ui_reservecar.h"

ReserveCar::ReserveCar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReserveCar)
{
    ui->setupUi(this);
    this->setFixedSize(500, 500);
    this->setWindowTitle("Reserve Cars");

    connect(ui->confirmBtn, &ClickableLabel::clicked, this, [=](){
        UpdateDataBase();
    });
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
    ui->Engine->setText(CarData.at(5));
    ui->Color->setText(CarData.at(4));
    ui->Price->setText(CarData.at(7));
    ui->Owner->setText(CarData.at(6));
}
void ReserveCar::UpdateDataBase()
{
    QString CurrentOrderNumber = GenerateOrderNumber();
    qDebug() << CurrentOrderNumber;
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
        queryStr = "UPDATE CARS SET CarHolder = '"+CurrentUserName+"' WHERE id = '"+CarData.at(0)+"'";
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
            queryStr = "UPDATE USERS SET OrderNumber = '"+CurrentOrderNumber+"' WHERE UserName = '"+CurrentUserName+"'";
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
                CustomMessageBox messageBox("Thank you!\n Your order number is: " + CurrentOrderNumber);
                int result = messageBox.exec();
                if (result == QMessageBox::Ok) {
                    messageBox.close();
                }
            }
        }
        database.close();
        emit this->ReservedComplete();
        this->hide();
    }
}

QString ReserveCar::GenerateOrderNumber()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    const QString characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::uniform_int_distribution<> dis(0, characters.size() - 1);

    QString orderNumber;
    for (int i = 0; i < 6; ++i)
    {
        int randomIndex = dis(gen);
        QChar randomChar = characters.at(randomIndex);
        orderNumber.append(randomChar);
    }

    return orderNumber;
}

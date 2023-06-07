#include "createride.h"
#include "ui_createride.h"

CreateRide::CreateRide(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateRide)
{
    ui->setupUi(this);
    this->setWindowTitle("Create new Ride");
    this->setFixedSize(620, 620);
}

CreateRide::~CreateRide()
{
    delete ui;
}

void CreateRide::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/images/images/rose2.png");
    painter.drawPixmap(0,0,pix);
}

void CreateRide::on_submitBtn_clicked()
{
    if(ui->carModel->text().isEmpty() || ui->carCapacity->text().isEmpty() ||
        ui->carColor->text().isEmpty() || ui->carEngine->text().isEmpty() ||
        ui->carName->text().isEmpty() || ui->carPrice->text().isEmpty())
    {
        CustomMessageBox messageBox("Fill all the fields!");
        int result = messageBox.exec();
        if (result == QMessageBox::Ok) {
            messageBox.close();
        }
    }
    else
    {
        GetData();

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
            query.prepare("INSERT INTO CARS(CarName, CarModel, CarCapacity, EngineCapacity, CarColour, CarOwner, CarPrice)"
                          " VALUES (:carName, :carModel, :carCapacity, :engineCapacity, :carColour, :carOwner, :carPrice)");

            query.bindValue(":carName", CarName);
            query.bindValue(":carModel", CarModel);
            query.bindValue(":carCapacity", CarSeats);
            query.bindValue(":engineCapacity", CarEngine);
            query.bindValue(":carColour", CarColor);
            query.bindValue(":carOwner", CurrentUserName);
            query.bindValue(":carPrice", CarPrice);
            if(!query.exec())
            {
                CustomMessageBox messageBox("Something went wrong!");
                int result = messageBox.exec();
                if (result == QMessageBox::Ok) {
                    messageBox.close();
                }
            }
            else
            {
                CustomMessageBox messageBox("Car succesfully added!");
                int result = messageBox.exec();
                if (result == QMessageBox::Ok) {
                    messageBox.close();
                }
                database.close();
                this->hide();
                ClearInput();
            }
        }
    }
}

void CreateRide::GetData()
{
    CarName = ui->carName->text().trimmed();
    CarModel = ui->carModel->text().trimmed();
    CarSeats = ui->carCapacity->text().trimmed();
    CarEngine = ui->carEngine->text().trimmed();
    CarColor = ui->carColor->text().trimmed();
    CarPrice = ui->carPrice->text().trimmed() + "/day";
}

void CreateRide::ClearInput()
{
    ui->carCapacity->clear();
    ui->carColor->clear();
    ui->carEngine->clear();
    ui->carModel->clear();
    ui->carName->clear();
    ui->carPrice->clear();
}

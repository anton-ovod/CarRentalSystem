#include "createride.h"
#include "ui_createride.h"

CreateRide::CreateRide(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateRide)
{
    ui->setupUi(this);
    this->setWindowTitle("Create new Ride");
    this->setFixedSize(620, 620);

    connect(ui->carCapacity, &QLineEdit::textChanged, this, &CreateRide::CheckSeats);
    connect(ui->carEngine, &QLineEdit::textChanged, this, &CreateRide::CheckEngine);
    connect(ui->carPrice, &QLineEdit::textChanged, this, &CreateRide::CheckPrice);
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
        ui->carCapacity->text().isEmpty() || ui->carEngine->text().isEmpty() ||
        ui->carName->text().isEmpty() || ui->carPrice->text().isEmpty())
    {
        CustomMessageBox messageBox("Fill all the fields!");
        int result = messageBox.exec();
        if (result == QMessageBox::Ok) {
            messageBox.close();
        }
    }
    else if(!CheckEngine())
    {
        CustomMessageBox messageBox("Engine capacity is not valid!");
        int result = messageBox.exec();
        if (result == QMessageBox::Ok) {
            messageBox.close();
        }
    }
    else if(!CheckPrice())
    {
        CustomMessageBox messageBox("Price is not valid!");
        int result = messageBox.exec();
        if (result == QMessageBox::Ok) {
            messageBox.close();
        }
    }
    else if(!CheckSeats())
    {
        CustomMessageBox messageBox("Number of seats is not valid!");
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
            query.prepare("INSERT INTO CARS(CarName, CarModel, CarCapacity, EngineCapacity, CarColor, CarOwner, CarPrice)"
                          " VALUES (:carName, :carModel, :carCapacity, :engineCapacity, :carColour, :carOwner, :carPrice)");

            query.bindValue(":carName", CarName);
            query.bindValue(":carModel", CarModel);
            query.bindValue(":carCapacity", CarSeats);
            query.bindValue(":engineCapacity", CarEngine);
            query.bindValue(":carColor", CarColor);
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

bool CreateRide::CheckEngine()
{
    double Engine = ui->carEngine->text().trimmed().toDouble();
    if(Engine <= 0)
    {
        ui->carEngine->setStyleSheet("color: rgb(235, 0, 0);");
        return 0;
    }
    ui->carEngine->setStyleSheet("color: rgb(92, 89, 106);");
    return 1;
}

bool CreateRide::CheckPrice()
{
    double Price = ui->carPrice->text().trimmed().toDouble();
    if(Price <= 0)
    {
        ui->carPrice->setStyleSheet("color: rgb(235, 0, 0);");
        return 0;
    }
    ui->carPrice->setStyleSheet("color: rgb(92, 89, 106);");
    return 1;
}

bool CreateRide::CheckSeats()
{
    int Seats = ui->carCapacity->text().trimmed().toInt();
    if(Seats <= 1)
    {
        ui->carCapacity->setStyleSheet("color: rgb(235, 0, 0);");
        return 0;
    }
    ui->carCapacity->setStyleSheet("color: rgb(92, 89, 106);");
    return 1;
}

void CreateRide::GetData()
{
    CarName = ui->carName->text().trimmed();
    CarModel = ui->carModel->text().trimmed();
    CarSeats = ui->carCapacity->text().trimmed();
    CarEngine = ui->carEngine->text().trimmed() + "L";
    CarColor = ui->carColor->text().trimmed();
    CarPrice = "$"+ui->carPrice->text().trimmed() + "/day";
}

void CreateRide::ClearInput()
{
    ui->carCapacity->clear();
    ui->carCapacity->clear();
    ui->carEngine->clear();
    ui->carModel->clear();
    ui->carName->clear();
    ui->carPrice->clear();
}

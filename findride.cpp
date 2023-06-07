#include "findride.h"
#include "ui_findride.h"

FindRide::FindRide(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindRide)
{
    ui->setupUi(this);
    this->setFixedSize(800, 600);
    this->setWindowTitle("Find Ride");
    ReservePage = new ReserveCar;
    connect(ui->searchArea, SIGNAL(textChanged(QString)), this, SLOT(search()));

    connect(ReservePage, &ReserveCar::ReservedComplete, this, &FindRide::RefreshData);

}

FindRide::~FindRide()
{
    delete ui;
}

void FindRide::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/images/images/Mystic.png");
    painter.drawPixmap(0,0,pix);
}

void FindRide::appendData()
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
        tableModel = new QSqlTableModel(this);
        tableModel->setTable("CARS");
        tableModel->select();
        tableModel->setFilter("CarHolder = 'Ready for rent'");
        ui->CarsView->setModel(tableModel);
        ui->CarsView->hideColumn(0);
        ui->CarsView->hideColumn(8);
        ui->CarsView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->CarsView->verticalHeader()->setVisible(false);
        ui->CarsView->setSelectionBehavior(QAbstractItemView::SelectRows);

        ui->CarsView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        database.close();
    }
}

void FindRide::on_backBtn_clicked()
{
    emit this->backToMainWindowPage();
}

int FindRide::getCurrentData()
{
    CarData.clear();
    QModelIndex currentIndex = ui->CarsView->currentIndex();
    int row = currentIndex.row();
    QAbstractItemModel *model = ui->CarsView->model();

    if (row != -1)
    {
        CarData << model->index(row, 0).data().toString();
        CarData << model->index(row, 1).data().toString();
        CarData << model->index(row, 2).data().toString();
        CarData << model->index(row, 3).data().toString();
        CarData << model->index(row, 4).data().toString();
        CarData << model->index(row, 5).data().toString();
        CarData << model->index(row, 6).data().toString();
        CarData << model->index(row, 7).data().toString();
        return 1;
    }
    else
    {
        CustomMessageBox messageBox("Select car to reserve beforehead");
        int result = messageBox.exec();
        if (result == QMessageBox::Ok) {
            messageBox.close();
        }
        return 0;
    }
}

void FindRide::on_reserveBtn_clicked()
{
    if(getCurrentData())
    {

        ReservePage->CurrentUserName = CurrentUserName;
        ReservePage->CarData = CarData;
        ReservePage->SetCarData();
        ReservePage->show();
        qDebug() << CarData;
    }
}
void FindRide::RefreshData()
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
        tableModel->select();
        ui->CarsView->viewport()->repaint();

        database.close();
    }
}

void FindRide::search()
{
    QString search = ui->searchArea->text().trimmed();
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
    tableModel->setTable("CARS");
    QString queryStr = QString("CarName LIKE '%%1%' AND CarHolder = 'Ready for rent'").arg(search);
    tableModel->setFilter(queryStr);
    tableModel->select();
    ui->CarsView->setModel(tableModel);
    ui->CarsView->hideColumn(0);
    ui->CarsView->hideColumn(8);
    database.close();
    }

}

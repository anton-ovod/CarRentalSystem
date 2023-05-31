#include "administrator.h"
#include "ui_administrator.h"

Administrator::Administrator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Administrator)
{
    ui->setupUi(this);
    this->setFixedSize(800, 600);
    this->setWindowTitle("Administration");

    appendData();

    connect(ui->searchLine, SIGNAL(textChanged(QString)), this, SLOT(search()));

}

void Administrator::appendData()
{
    tableModel = new QSqlTableModel;
    tableModel->setTable("USERS");
    tableModel->select();
    tableModel->removeColumn(0);
    ui->usersView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->usersView->setModel(tableModel);
}

void Administrator::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/images/images/blue.png");
    painter.drawPixmap(0,0,pix);
}

void Administrator::search()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QString search, data;
    search = ui->searchLine->text();
    data = "SELECT UserName as UserName, Password as Password, Email as Email, PhoneNumber as PhoneNumber, OrderNumber as OrderNumber FROM USERS WHERE UserName LIKE '%"+search+"%'";
    model->setQuery(data);
    ui->usersView->setModel(model);
}

void Administrator::on_BackBtn_clicked()
{
    emit this->backToLogin();
}


Administrator::~Administrator()
{
    delete ui;
}

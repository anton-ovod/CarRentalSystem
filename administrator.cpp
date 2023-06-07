#include "administrator.h"
#include "ui_administrator.h"

Administrator::Administrator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Administrator)
{
    ui->setupUi(this);
    this->setFixedSize(880, 600);
    this->setWindowTitle("Administration");
    connect(ui->searchLine, SIGNAL(textChanged(QString)), this, SLOT(search()));
}

void Administrator::appendData()
{
        tableModel = new QSqlTableModel(this);
        //RoundedHeader* roundedHeader = new RoundedHeader(Qt::Horizontal, ui->usersView);

        tableModel->setTable("USERS");
        tableModel->select();
        //ui->usersView->setHorizontalHeader(roundedHeader);
        ui->usersView->setModel(tableModel);
        ui->usersView->hideColumn(0);
        ui->usersView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->usersView->verticalHeader()->setVisible(false);

        tableModel->setEditStrategy(QSqlTableModel::OnFieldChange);
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
    QString search = ui->searchLine->text().trimmed();

    tableModel->setTable("USERS");

    QString queryStr = QString("UserName LIKE '%%1%'").arg(search);
    tableModel->setFilter(queryStr);
    tableModel->select();
    ui->usersView->setModel(tableModel);
    ui->usersView->hideColumn(0);
}

void Administrator::on_BackBtn_clicked()
{
    emit this->backToLogin();
}


Administrator::~Administrator()
{
    database.close();
    delete ui;
}

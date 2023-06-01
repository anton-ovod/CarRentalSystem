#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlError>
#include <QSqlQueryModel>

#include "databasehandler.h"
#include "ClickableLabel.h"
#include "custommessagebox.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent *);
    QString CurrentUserName;
    void init();
    void myTrips();

signals:
    void backToLogIn();

private:
    Ui::MainWindow *ui;
    QSqlDatabase& database = DatabaseHandler::getInstance().getDatabase();
};
#endif // MAINWINDOW_H

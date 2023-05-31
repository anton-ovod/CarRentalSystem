#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QtSql/QSqlDatabase>
#include <QMessageBox>
#include <QtSql/QSqlTableModel>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQueryModel>

#include "databasehandler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSqlDatabase& database = DatabaseHandler::getInstance().getDatabase();
};
#endif // MAINWINDOW_H

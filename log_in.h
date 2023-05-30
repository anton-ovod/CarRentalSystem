#ifndef LOG_IN_H
#define LOG_IN_H

#include <QWidget>
#include <QString>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QTimer>
#include <QPainter>

namespace Ui {
class Log_in;
}

class Log_in : public QWidget
{
    Q_OBJECT

public:
    explicit Log_in(QWidget *parent = nullptr);
    ~Log_in();

    void paintEvent(QPaintEvent *) override;
    void cleanLineEdit();
    void handleLabelClicked();

protected:
    //void mousePressEvent(QMouseEvent* event) override;

private:
    Ui::Log_in *ui;
};

#endif // LOG_IN_H

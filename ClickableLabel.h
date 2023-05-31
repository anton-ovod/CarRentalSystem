#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QMouseEvent>

class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget *parent = nullptr);
    ~ClickableLabel();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override;
};

#endif // CLICKABLELABLE_H

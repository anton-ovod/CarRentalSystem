#ifndef CLICKABLELABLE_H
#define CLICKABLELABLE_H

#include <QLabel>
#include <QMouseEvent>

class ClickableLable : public QLabel
{
    Q_OBJECT

public:
    explicit ClickableLable(QWidget *parent = nullptr);
    ~ClickableLable();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override;
};

#endif // CLICKABLELABLE_H

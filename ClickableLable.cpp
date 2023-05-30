#include "ClickableLable.h"

ClickableLable::ClickableLable(QWidget* parent):QLabel(parent){}

ClickableLable::~ClickableLable() {}


void ClickableLable::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();
    }

    QLabel::mousePressEvent(event);
}

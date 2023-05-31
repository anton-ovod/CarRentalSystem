#include "ClickableLabel.h"

ClickableLabel::ClickableLabel(QWidget* parent):QLabel(parent){}

ClickableLabel::~ClickableLabel() {}


void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();
    }

    QLabel::mousePressEvent(event);
}

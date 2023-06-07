#ifndef CUSTOMTABLEVUIEW_H
#define CUSTOMTABLEVUIEW_H

#include <QTableView>
#include <QHeaderView>
#include <QPainter>
#include <QStyleOption>

class RoundedHeaderView : public QHeaderView
{
public:
    RoundedHeaderView(Qt::Orientation orientation, QWidget* parent = nullptr)
        : QHeaderView(orientation, parent)
    {
        setStyleSheet("QHeaderView::section { border: none; }"); // Remove default borders
    }

    QSize sizeHint() const override
    {
        QSize size = QHeaderView::sizeHint();
        size.setHeight(size.height() + 10); // Increase the height to include rounded corners
        return size;
    }

    void paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const override
    {
        QStyleOptionHeader option;
        initStyleOption(&option);
        option.rect = rect;
        option.section = logicalIndex;

        QHeaderView::paintSection(painter, rect, logicalIndex);

        painter->save();
        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->setPen(Qt::NoPen);
        painter->setBrush(option.palette.color(QPalette::Button));
        painter->drawRoundedRect(rect.adjusted(1, 1, -1, -1), 5, 5);
        painter->restore();
    }
};

class RoundedTableView : public QTableView
{
public:
    RoundedTableView(QWidget* parent = nullptr)
        : QTableView(parent)
    {
        setStyleSheet("QTableView { border: none; }"); // Remove default borders
    }

protected:
    void paintEvent(QPaintEvent* event) override
    {
        QStyleOption opt;
        opt.initFrom(this);

        QPainter painter(viewport());
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

        QTableView::paintEvent(event);
    }

    QHeaderView* createDefaultHeader() const
    {
        return new RoundedHeaderView(horizontalHeader()->orientation(), const_cast<RoundedTableView*>(this));
    }
};

#endif // CUSTOMTABLEVUIEW_H

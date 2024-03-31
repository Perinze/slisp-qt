#ifndef QGRAPHIC_ARC_ITEM_HPP
#define QGRAPHIC_ARC_ITEM_HPP

#include <QGraphicsEllipseItem>

class QGraphicsArcItem: public QGraphicsEllipseItem{

public:

  QGraphicsArcItem(qreal center_x, qreal center_y, qreal start_x, qreal start_y,
                   qreal span, QGraphicsItem *parent = nullptr);

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

  qreal radius;
};


#endif

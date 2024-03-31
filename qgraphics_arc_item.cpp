#include "qgraphics_arc_item.hpp"

#include <cmath>

#include <QDebug>
#include <QPainter>

QGraphicsArcItem::QGraphicsArcItem(qreal x, qreal y, qreal width, qreal height,
                                   qreal start, qreal span,
                                   QGraphicsItem *parent):
                  QGraphicsEllipseItem(x, y, width, height, parent),
                  start(start), span(span) {}

void QGraphicsArcItem::paint(QPainter *painter,
                             const QStyleOptionGraphicsItem *option,
                             QWidget *widget) {
  painter->drawArc(boundingRect(), start, span);
}

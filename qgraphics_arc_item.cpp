#include "qgraphics_arc_item.hpp"

#include <cmath>
#include <iostream>

#include <QDebug>
#include <QPainter>
#include <QtMath>

#define SQUARE(x) ((x) * (x))

qreal distance(qreal x1, qreal y1, qreal x2, qreal y2) {
  return qSqrt(SQUARE(x1 - x2) + SQUARE(y1 - y2));
}

QGraphicsArcItem::QGraphicsArcItem(qreal center_x, qreal center_y, qreal start_x, qreal start_y,
                                   qreal span, QGraphicsItem *parent):
                  radius(distance(center_x, center_y, start_x, start_y)),
                  QGraphicsEllipseItem(center_x - radius, center_y - radius,
                                       radius * 2, radius * 2) {
  auto dx = start_x - center_x;
  auto dy = start_y - center_y;
  auto start_angle = qAtan(dy / dx) * 180 / M_PI;
  int start_angle_16th = start_angle * 16;
  int span_angle_16th = span * 180 / M_PI * 16;
  setStartAngle(start_angle_16th);
  setSpanAngle(span_angle_16th);
  setRect(center_x - radius, center_y - radius, radius * 2, radius * 2);
}


void QGraphicsArcItem::paint(QPainter *painter,
                             const QStyleOptionGraphicsItem *option,
                             QWidget *widget) {
  painter->drawArc(boundingRect(), startAngle(), spanAngle());
}

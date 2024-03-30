#include "canvas_widget.hpp"

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLayout>

CanvasWidget::CanvasWidget(QWidget * parent): QWidget(parent){
  scene = new QGraphicsScene(this);
  QGraphicsView *view = new QGraphicsView(scene, this);
  view->setRenderHint(QPainter::Antialiasing);
  view->setMinimumSize(400, 400);
}

void CanvasWidget::addGraphic(QGraphicsItem * item){
  scene->addItem(item);
}

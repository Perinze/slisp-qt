#include "canvas_widget.hpp"

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLayout>

CanvasWidget::CanvasWidget(QWidget * parent): QWidget(parent){
  scene = new QGraphicsScene(this);
  QGraphicsView *view = new QGraphicsView(scene, this);
  view->setMinimumSize(1000, 600);
}

void CanvasWidget::addGraphic(QGraphicsItem * item){
  scene->addItem(item);
}

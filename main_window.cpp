#include "main_window.hpp"

#include <iostream>

#include <QLayout>

#include "message_widget.hpp"
#include "canvas_widget.hpp"
#include "repl_widget.hpp"
#include "interpreter_semantic_error.hpp"

MainWindow::MainWindow(QWidget * parent): MainWindow("", parent) {}

MainWindow::MainWindow(std::string filename, QWidget * parent): QWidget(parent){
  if (!filename.empty()) {
    // TODO
  }

  QVBoxLayout *layout = new QVBoxLayout(this);

  MessageWidget *messageWidget = new MessageWidget(this);
  layout->addWidget(messageWidget);

  CanvasWidget *canvasWidget = new CanvasWidget(this);
  layout->addWidget(canvasWidget);

  REPLWidget *replWidget = new REPLWidget(this);
  layout->addWidget(replWidget);

  QtInterpreter *interpreter = new QtInterpreter(this);
  connect(replWidget, &REPLWidget::lineEntered, interpreter, &QtInterpreter::parseAndEvaluate);
  connect(interpreter, &QtInterpreter::info, messageWidget, &MessageWidget::info);
  connect(interpreter, &QtInterpreter::error, messageWidget, &MessageWidget::error);
  connect(interpreter, &QtInterpreter::drawGraphic, canvasWidget, &CanvasWidget::addGraphic);
}

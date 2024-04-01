#include "main_window.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#include <QLayout>

#include "message_widget.hpp"
#include "canvas_widget.hpp"
#include "repl_widget.hpp"
#include "interpreter_semantic_error.hpp"

MainWindow::MainWindow(QWidget * parent): MainWindow("", parent) {}

MainWindow::MainWindow(std::string filename, QWidget * parent): QWidget(parent){
  QVBoxLayout *layout = new QVBoxLayout(this);

  MessageWidget *messageWidget = new MessageWidget(this);
  layout->addWidget(messageWidget);

  CanvasWidget *canvasWidget = new CanvasWidget(this);
  layout->addWidget(canvasWidget);

  REPLWidget *replWidget = new REPLWidget(this);
  layout->addWidget(replWidget);

  layout->setStretchFactor(messageWidget, 0);
  layout->setStretchFactor(canvasWidget, 1);
  layout->setStretchFactor(replWidget, 0);

  connect(replWidget, &REPLWidget::lineEntered, &interp, &QtInterpreter::parseAndEvaluate);
  connect(&interp, &QtInterpreter::info, messageWidget, &MessageWidget::info);
  connect(&interp, &QtInterpreter::error, messageWidget, &MessageWidget::error);
  connect(&interp, &QtInterpreter::drawGraphic, canvasWidget, &CanvasWidget::addGraphic);

  if (!filename.empty()) {
    std::ifstream ifs(filename);
    std::stringstream buf;
    buf << ifs.rdbuf();
    ifs.close();
    interp.parseAndEvaluate(QString::fromStdString(buf.str()));
  }
}

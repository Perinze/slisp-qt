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
}

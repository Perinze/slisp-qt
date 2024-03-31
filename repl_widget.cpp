#include "repl_widget.hpp"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QLayout>
#include <QKeyEvent>

REPLWidget::REPLWidget(QWidget * parent): QWidget(parent){
  QHBoxLayout *layout = new QHBoxLayout(this);

  QLabel *label = new QLabel("slisp>", this);
  layout->addWidget(label);

  lineEdit = new QLineEdit(this);
  connect(lineEdit, &QLineEdit::returnPressed, this, &REPLWidget::changed);
  layout->addWidget(lineEdit);
}

void REPLWidget::changed() {
  QString text = lineEdit->text();
  lineEdit->clear();
  emit lineEntered(text);
}

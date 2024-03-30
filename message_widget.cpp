#include "message_widget.hpp"

#include <QLabel>
#include <QLayout>
#include <QLineEdit>

MessageWidget::MessageWidget(QWidget *parent) : QWidget(parent) {
  QHBoxLayout *layout = new QHBoxLayout(this);

  QLabel *label = new QLabel("Message:", this);
  layout->addWidget(label);

  lineEdit = new QLineEdit(this);
  lineEdit->setReadOnly(true);
  layout->addWidget(lineEdit);
}

void MessageWidget::info(QString message) {
  lineEdit->setText(message);
  lineEdit->setStyleSheet("");
}

void MessageWidget::error(QString message) {
  lineEdit->setText(message);
  lineEdit->setStyleSheet("color: red;");
}

void MessageWidget::clear() {
  lineEdit->clear();
}

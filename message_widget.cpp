#include "message_widget.hpp"

#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QPalette>
#include <QGuiApplication>

MessageWidget::MessageWidget(QWidget *parent) : QWidget(parent) {
  QHBoxLayout *layout = new QHBoxLayout(this);

  QLabel *label = new QLabel("Message:", this);
  layout->addWidget(label);

  lineEdit = new QLineEdit(this);
  lineEdit->setReadOnly(true);
  layout->addWidget(lineEdit);
}

void MessageWidget::info(QString message) {
  lineEdit->setPalette(QGuiApplication::palette());
  lineEdit->setText(message);
  lineEdit->setStyleSheet("");
}

void MessageWidget::error(QString message) {
  static QPalette palette = lineEdit->palette();
  palette.setColor(QPalette::Highlight, QColor(Qt::red));
  lineEdit->setPalette(palette);
  lineEdit->setText("Error: " + message);
  lineEdit->selectAll();
}

void MessageWidget::clear() {
  lineEdit->clear();
}

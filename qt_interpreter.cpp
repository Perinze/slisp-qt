#include "qt_interpreter.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <fstream>

#include <QBrush>
#include <QDebug>

#include "qgraphics_arc_item.hpp"

#include "interpreter_semantic_error.hpp"

QtInterpreter::QtInterpreter(QObject * parent): QObject(parent) {}

void QtInterpreter::parseAndEvaluate(QString entry){
  static auto format = [](const Expression &exp) -> QString {
    std::stringstream ss;
    ss << exp;
    return QString::fromStdString(ss.str());
  };
  std::istringstream is(entry.toStdString());
  if (!interpreter.parse(is)) {
    emit error(QString::fromStdString("invalid syntax"));
    return;
  }
  try {
    auto exp = interpreter.eval();
    switch (exp.head.type) {
      default:
      break;
    }
    emit info(format(exp));
  } catch (const InterpreterSemanticError &e) {
    emit error(e.what());
  }
}

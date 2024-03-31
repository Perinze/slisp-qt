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
    for (const auto &item_exp : exp.tail) {
      switch (item_exp.head.type) {
        case PointType:
        {
          auto point = item_exp.head.value.point_value;
          auto point_item = new QGraphicsEllipseItem(point.x, point.y, 2, 2);
          emit drawGraphic(point_item);
        }
        break;

        case LineType:
        {
          auto line = item_exp.head.value.line_value;
          auto line_item = new QGraphicsLineItem(line.first.x, line.first.y,
                                               line.second.x, line.second.y);
          emit drawGraphic(line_item);
        }
        break;

        case ArcType:
        {
          auto arc = item_exp.head.value.arc_value;
          auto arc_item = new QGraphicsArcItem(arc.center.x, arc.center.y,
                                               arc.start.x, arc.start.y,
                                               arc.span, arc.span);
          emit drawGraphic(arc_item);
        }
        break;
      }
    }
    emit info(format(exp));
  } catch (const InterpreterSemanticError &e) {
    emit error(e.what());
  }
}

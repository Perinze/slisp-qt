#include "expression.hpp"


// system includes
#include <sstream>
#include <cmath>
#include <limits>
#include <cctype>
#include <tuple>
#include <exception>
#include <regex>

Expression::Expression(bool tf){
  head.type = BooleanType;
  head.value.bool_value = tf;
}

Expression::Expression(double num){
  head.type = NumberType;
  head.value.num_value = num;
}

Expression::Expression(const std::string & sym){
  head.type = SymbolType;
  head.value.sym_value = sym;
}

Expression::Expression(std::tuple<double,double> value){
  head.type = PointType;
  head.value.point_value = Point(value);
}

Expression::Expression(std::tuple<double,double> start,
		       std::tuple<double,double> end){
  head.type = LineType;
  head.value.line_value = Line(start, end);
}


Expression::Expression(std::tuple<double,double> center,
		       std::tuple<double,double> start,
		       double angle){
  head.type = ArcType;
  head.value.arc_value = Arc(center, start, angle);
}

bool Expression::operator==(const Expression & exp) const noexcept{
  if (head.type != exp.head.type) return false;
  switch (head.type)
  {
  case NoneType:
    break;

  case BooleanType:
    if (head.value.bool_value != exp.head.value.bool_value)
      return false;
    break;

  case NumberType:
    if (head.value.num_value != exp.head.value.num_value)
      return false;
    break;

  case SymbolType:
    if (head.value.sym_value != exp.head.value.sym_value)
      return false;
    break;

  case PointType:
    if (head.value.point_value != exp.head.value.point_value)
      return false;
    break;
  
  case LineType:
    if (head.value.line_value.first != exp.head.value.line_value.first)
      return false;
    if (head.value.line_value.second != exp.head.value.line_value.second)
      return false;
    break;

  case ArcType:
    if (head.value.arc_value.center != exp.head.value.arc_value.center)
      return false;
    if (head.value.arc_value.start != exp.head.value.arc_value.start)
      return false;
    if (head.value.arc_value.span != exp.head.value.arc_value.span)
      return false;
  
  default:
    break;
  }
  if (tail.size() != exp.tail.size()) return false;
  return false;
}

std::ostream & operator<<(std::ostream & out, const Point point) {
  out << point.x << "," << point.y;
  return out;
}

std::ostream & operator<<(std::ostream & out, const Line line) {
  out << "(" << line.first << "),(" << line.second << ")";
  return out;
}

std::ostream & operator<<(std::ostream & out, const Arc arc) {
  out << "(" << arc.center << "),(" << arc.start << ") ";
  out << arc.span;
  return out;
}

std::ostream & operator<<(std::ostream & out, const Expression & exp){
  out << "(";
  switch (exp.head.type)
  {
  case NoneType:
    out << "";
    break;
  case BooleanType:
    out << (exp.head.value.bool_value ? "True" : "False");
    break;
  case NumberType:
    out << exp.head.value.num_value;
    break;
  case SymbolType:
    out << exp.head.value.sym_value;
    break;
  case PointType:
    out << exp.head.value.point_value;
    break;
  case LineType:
    out << exp.head.value.line_value;
    break;
  case ArcType:
    out << exp.head.value.arc_value;
    break;
  default:
    break;
  }
  for (auto e : exp.tail) {
    out << e;
  }
  out << ")";
  return out;
}

bool token_to_atom(const std::string & token, Atom & atom){
  // return true if it a token is valid. otherwise, return false.
  auto is_num = [](const std::string & s) -> bool {
    char *end = 0;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && *end == '\0' && val != HUGE_VAL;
  };
  auto is_sym = [](const std::string & s) -> bool {
    std::regex sym("[^\\d\\s]\\S*");
    if (std::regex_match(s, sym)) return true;
    else return false;
  };

  if (token == "begin" || token == "define" || token == "if" || token == "draw") {
    atom.type = KeywordType;
    atom.value.sym_value = token;
  } else if (token == "(" || token == ")") {
    return false;
  } else if (token == "True") {
    atom.type = BooleanType;
    atom.value.bool_value = true;
  } else if (token == "False") {
    atom.type = BooleanType;
    atom.value.bool_value = false;
  } else if (is_num(token)) {
    try {
      atom.type = NumberType;
      atom.value.num_value = std::stod(token);
    } catch (const std::out_of_range&) {
      return false;
    }
  } else if (is_sym(token)) {
    atom.type = SymbolType;
    atom.value.sym_value = token;
  } else {
    return false;
  }
  return true;
}


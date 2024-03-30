#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

// system includes
#include <string>
#include <istream>
#include <vector>
#include <functional>


// module includes
#include "expression.hpp"
#include "environment.hpp"
#include "tokenize.hpp"

// Interpreter has
// Environment, which starts at a default
// parse method, builds an internal AST
// eval method, updates Environment, returns last result
class Interpreter{
public:
  bool parse(std::istream & expression) noexcept;
  Expression eval();
protected:
  Environment env;
  Expression ast;
  std::vector<Atom> graphics;
private:
  static Expression parse_top_down(const TokenSequenceType::iterator&, std::function<std::string&(void)>, std::function<bool()>);
  Expression eval_top_down(const Expression & exp);
};


#endif

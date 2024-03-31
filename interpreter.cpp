#include "interpreter.hpp"

// system includes
#include <stack>
#include <stdexcept>
#include <iostream>

// module includes
#include "tokenize.hpp"
#include "expression.hpp"
#include "environment.hpp"
#include "interpreter_semantic_error.hpp"

class InterpreterParseError: public std::runtime_error {
public:
  InterpreterParseError(const std::string& message): std::runtime_error(message){};
};

bool Interpreter::parse(std::istream & expression) noexcept{
  // return true if input is valid. otherwise, return false.
  TokenSequenceType tokens = tokenize(expression);

  // in case of empty program
  if (tokens.empty()) {
    return false;
  } else {
    auto it = tokens.begin();
    auto inc_it = [&]() -> bool {
      if (it == tokens.end()) {
        throw InterpreterParseError("truncated program");
        return false;
      }
      it++;
      return true;
    };
    auto read_it = [&]() -> std::string& {
      if (it == tokens.end()) {
        throw InterpreterParseError("truncated program");
      }
      return *it;
    };
    try {
      ast = parse_top_down(it, read_it, inc_it);
      if (it != tokens.end()) throw InterpreterParseError("unclosed program");
    } catch (const InterpreterParseError &e) {
      std::cout << "Parse error: " << e.what() << std::endl;
      return false;
    }
    // fit single symbol case
    EnvResult _;
    if (ast == Expression(ast.head.value.sym_value)
        && !Environment().lookup(ast.head.value.sym_value, _)) {
      std::cout << "Parse error: single non-keyword" << std::endl;
      return false;
    }
  }
  // warning: not handling invalid input
  return true;
}

Expression Interpreter::eval(){
  return eval_top_down(ast);
}

Expression Interpreter::parse_top_down(const TokenSequenceType::iterator & it,
                                        std::function<std::string&(void)> read,
                                        std::function<bool()> inc) {
  Expression exp;
  if (read() != "(") { // atom without parenthesis
    if (!token_to_atom(read(), exp.head)) throw InterpreterParseError("failed to parse token: " + read());
  } else { // (...), *it == "("
    if (!inc()) return Expression();
    if (read() == ")") { // special case: none
      //exp.head.type = NoneType;
      // this case can be treated invalid
      throw InterpreterParseError("empty application");
    } else {
      // assert first is atom due to its syntax
      if (!token_to_atom(read(), exp.head)) throw InterpreterParseError("failed to parse token: " + read());

      if (!inc()) return Expression();
      while (read() != ")") {
        exp.tail.push_back(parse_top_down(it, read, inc));
      }
    }
  }
  if (!inc()) return Expression();
  return exp;
}

Expression Interpreter::eval_top_down(Expression & exp) {
  EnvResult envres;
  if (exp.head.type == KeywordType) {
    if (exp.head.value.sym_value == "begin") {
      Expression r; // result
      for (auto a : exp.tail) {
        r = eval_top_down(a);
      }
      return r;
    } else if (exp.head.value.sym_value == "define") {
      if (exp.tail.size() != 2) throw InterpreterSemanticError("incorrect define");
      if (exp.tail[0].head.type != SymbolType) throw InterpreterSemanticError("incorrect define symbol");
      Expression ret;
      if (!env.define(exp.tail[0].head.value.sym_value, (ret = eval_top_down(exp.tail[1])))) {
        throw InterpreterSemanticError("redefining " + exp.tail[0].head.value.sym_value);
      };
      return ret;
    } else if (exp.head.value.sym_value == "if") {
      if (exp.tail.size() != 3) throw InterpreterSemanticError("incorrect if");
      auto cond = eval_top_down(exp.tail[0]);
      if (cond.head.type != BooleanType) throw InterpreterSemanticError("incorrect cond type");
      if (cond.head.value.bool_value) {
        return eval_top_down(exp.tail[1]);
      } else {
        return eval_top_down(exp.tail[2]);
      }
    } else if (exp.head.value.sym_value == "draw") {
      for (auto &item : exp.tail) {
        item = eval_top_down(item);
      }
      return exp;
    } else {
      throw InterpreterSemanticError("unexpected keyword");
    }
  } else if (exp.head.type == SymbolType) {
    if (env.lookup(exp.head.value.sym_value, envres)) {
      if (envres.type == ProcedureType) {
        // 1. eval all args, retrieve their head as atom
        std::vector<Atom> args;
        for (auto a : exp.tail) {
          args.push_back(eval_top_down(a).head);
        }
        // 2. apply
        return envres.proc(args);
      } else {
        return envres.exp;
      }
    } else { // unbound
      throw InterpreterSemanticError("unbound symbol");
    }
  }
  // otherwise value
  return exp;
}

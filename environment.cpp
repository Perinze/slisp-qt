#include "environment.hpp"

#include <cassert>
#include <cmath>

#include "interpreter_semantic_error.hpp"

EnvResult proc_not = {
  ProcedureType,
  Expression(),
  [](const std::vector<Atom>&args) -> Expression {
    if (args.size() != 1) throw InterpreterSemanticError("incorrect not");
    if (args[0].type != BooleanType) throw InterpreterSemanticError("incorrect arg type");
    return !args[0].value.bool_value;
  }
};

EnvResult proc_and = {
  ProcedureType,
  Expression(),
  [](const std::vector<Atom>&args) -> Expression {
    Boolean res = true;
    for (auto a : args) {
      if (a.type != BooleanType) throw InterpreterSemanticError("incorrect arg type");
      res &= a.value.bool_value;
    }
    return res;
  }
};

EnvResult proc_or = {
  ProcedureType,
  Expression(),
  [](const std::vector<Atom>&args) -> Expression {
    Boolean res = false;
    for (auto a : args) {
      if (a.type != BooleanType) throw InterpreterSemanticError("incorrect arg type");
      res |= a.value.bool_value;
    }
    return res;
  }
};

EnvResult proc_lt = {
  ProcedureType,
  Expression(),
  [](const std::vector<Atom>&args) -> Expression {
    if (args.size() != 2) throw InterpreterSemanticError("incorrect compare");
    if (args[0].type != NumberType) throw InterpreterSemanticError("incorrect arg type");
    if (args[1].type != NumberType) throw InterpreterSemanticError("incorrect arg type");
    return args[0].value.num_value < args[1].value.num_value;
  }
};

EnvResult proc_le = {
  ProcedureType,
  Expression(),
  [](const std::vector<Atom>&args) -> Expression {
    if (args.size() != 2) throw InterpreterSemanticError("incorrect compare");
    if (args[0].type != NumberType) throw InterpreterSemanticError("incorrect arg type");
    if (args[1].type != NumberType) throw InterpreterSemanticError("incorrect arg type");
    return args[0].value.num_value <= args[1].value.num_value;
  }
};

EnvResult proc_gt = {
  ProcedureType,
  Expression(),
  [](const std::vector<Atom>&args) -> Expression {
    if (args.size() != 2) throw InterpreterSemanticError("incorrect compare");
    if (args[0].type != NumberType) throw InterpreterSemanticError("incorrect arg type");
    if (args[1].type != NumberType) throw InterpreterSemanticError("incorrect arg type");
    return args[0].value.num_value > args[1].value.num_value;
  }
};

EnvResult proc_ge = {
  ProcedureType,
  Expression(),
  [](const std::vector<Atom>&args) -> Expression {
    if (args.size() != 2) throw InterpreterSemanticError("incorrect compare");
    if (args[0].type != NumberType) throw InterpreterSemanticError("incorrect arg type");
    if (args[1].type != NumberType) throw InterpreterSemanticError("incorrect arg type");
    return args[0].value.num_value >= args[1].value.num_value;
  }
};

EnvResult proc_eq = {
  ProcedureType,
  Expression(),
  [](const std::vector<Atom>&args) -> Expression {
    if (args.size() != 2) throw InterpreterSemanticError("incorrect compare");
    if (args[0].type != NumberType) throw InterpreterSemanticError("incorrect arg type");
    if (args[1].type != NumberType) throw InterpreterSemanticError("incorrect arg type");
    return args[0].value.num_value == args[1].value.num_value;
  }
};

EnvResult proc_add = {
  ProcedureType,
  Expression(),
  [](const std::vector<Atom>&args) -> Expression {
    Number sum = 0.;
    for (auto a : args) {
      if (a.type != NumberType) throw InterpreterSemanticError("incorrect arg type");
      sum += a.value.num_value;
    }
    return sum;
  }
};

EnvResult proc_sub = {
  ProcedureType,
  Expression(),
  [](const std::vector<Atom>&args) -> Expression {
    if (args.size() > 2) {
      throw InterpreterSemanticError("incorrect sub, too many args");
    } else if (args.size() == 2) {
      if (args[0].type != NumberType) throw InterpreterSemanticError("incorrect arg type");
      if (args[1].type != NumberType) throw InterpreterSemanticError("incorrect arg type");
      return args[0].value.num_value - args[1].value.num_value;
    } else if (args.size() == 1) {
      if (args[0].type != NumberType) throw InterpreterSemanticError("incorrect arg type");
      return -args[0].value.num_value;
    } else {
      throw InterpreterSemanticError("incorrect sub, too few args");
    }
  }
};

EnvResult proc_mul = {
  ProcedureType,
  Expression(),
  [](const std::vector<Atom>&args) -> Expression {
    Number prod = 1.;
    for (auto a : args) {
      if (a.type != NumberType) throw InterpreterSemanticError("incorrect arg type");
      prod *= a.value.num_value;
    }
    return prod;
  }
};

EnvResult proc_div = {
  ProcedureType,
  Expression(),
  [](const std::vector<Atom>&args) -> Expression {
    if (args.size() != 2) throw InterpreterSemanticError("incorrect compare");
    if (args[0].type != NumberType) throw InterpreterSemanticError("incorrect arg type");
    if (args[1].type != NumberType) throw InterpreterSemanticError("incorrect arg type");
    return args[0].value.num_value / args[1].value.num_value;
  }
};

EnvResult proc_log = {
  ProcedureType,
  Expression(),
  [](const std::vector<Atom>&args) -> Expression {
    if (args.size() != 1) throw InterpreterSemanticError("incorrect log");
    if (args[0].type != NumberType) throw InterpreterSemanticError("incorrect arg type");
    return log10(args[0].value.num_value);
  }
};

EnvResult proc_pow = {
  ProcedureType,
  Expression(),
  [](const std::vector<Atom>&args) -> Expression {
    if (args.size() != 2) throw InterpreterSemanticError("incorrect pow");
    if (args[0].type != NumberType) throw InterpreterSemanticError("incorrect arg type");
    if (args[1].type != NumberType) throw InterpreterSemanticError("incorrect arg type");
    return pow(args[0].value.num_value, args[1].value.num_value);
  }
};

EnvResult const_pi = {
  ExpressionType,
  Expression(atan2(0, -1))
};

EnvResult proc_point = {
  ProcedureType,
  Expression(),
  [](const std::vector<Atom>&args) -> Expression {
    if (args.size() != 2) throw InterpreterSemanticError("incorrect point");
    if (args[0].type != NumberType) throw InterpreterSemanticError("incorrect arg type");
    if (args[1].type != NumberType) throw InterpreterSemanticError("incorrect arg type");
    return Point(args[0].value.num_value, args[1].value.num_value);
  }
};

EnvResult proc_line = {
  ProcedureType,
  Expression(),
  [](const std::vector<Atom>&args) -> Expression {
    if (args.size() != 2) throw InterpreterSemanticError("incorrect line");
    if (args[0].type != PointType) throw InterpreterSemanticError("incorrect arg type");
    if (args[1].type != PointType) throw InterpreterSemanticError("incorrect arg type");
    return Line(args[0].value.point_value, args[1].value.point_value);
  }
};

EnvResult proc_arc = {
  ProcedureType,
  Expression(),
  [](const std::vector<Atom>&args) -> Expression {
    if (args.size() != 3) throw InterpreterSemanticError("incorrect arc");
    if (args[0].type != PointType) throw InterpreterSemanticError("incorrect arg type");
    if (args[1].type != PointType) throw InterpreterSemanticError("incorrect arg type");
    if (args[2].type != NumberType) throw InterpreterSemanticError("incorrect arg type");
    return Arc(args[0].value.point_value, args[1].value.point_value, args[2].value.num_value);
  }
};

EnvResult proc_sin = {
  ProcedureType,
  Expression(),
  [](const std::vector<Atom>&args) -> Expression {
    if (args.size() != 1) throw InterpreterSemanticError("incorrect sin");
    if (args[0].type != NumberType) throw InterpreterSemanticError("incorrect arg type");
    return sin(args[0].value.num_value);
  }
};

EnvResult proc_cos = {
  ProcedureType,
  Expression(),
  [](const std::vector<Atom>&args) -> Expression {
    if (args.size() != 1) throw InterpreterSemanticError("incorrect cos");
    if (args[0].type != NumberType) throw InterpreterSemanticError("incorrect arg type");
    return cos(args[0].value.num_value);
  }
};

EnvResult proc_arctan = {
  ProcedureType,
  Expression(),
  [](const std::vector<Atom>&args) -> Expression {
    if (args.size() != 1) throw InterpreterSemanticError("incorrect arctan");
    if (args[0].type != NumberType) throw InterpreterSemanticError("incorrect arg type");
    return atan(args[0].value.num_value);
  }
};

Environment::Environment(){
  // add default env
  envmap["not"] = proc_not;
  envmap["and"] = proc_and;
  envmap["or"] = proc_or;
  envmap["<"] = proc_lt;
  envmap["<="] = proc_le;
  envmap[">"] = proc_gt;
  envmap[">="] = proc_ge;
  envmap["="] = proc_eq;
  envmap["+"] = proc_add;
  envmap["-"] = proc_sub;
  envmap["*"] = proc_mul;
  envmap["/"] = proc_div;
  envmap["log10"] = proc_log;
  envmap["pow"] = proc_pow;
  envmap["pi"] = const_pi;
  envmap["point"] = proc_point;
  envmap["line"] = proc_line;
  envmap["arc"] = proc_arc;
  envmap["sin"] = proc_sin;
  envmap["cos"] = proc_cos;
  envmap["arctan"] = proc_arctan;
}

bool Environment::lookup(Symbol sym, EnvResult &res) {
  auto it = envmap.find(sym);
  if (it == envmap.end()) {
    return false;
  }
  res = it->second;
  return true;
}

bool Environment::define(Symbol sym, Expression exp) {
  if (envmap.find(sym) != envmap.end()) {
    return false;
  }
  envmap[sym] = {ExpressionType, exp};
  return true;
}
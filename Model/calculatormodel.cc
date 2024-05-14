#include "calculatormodel.h"

namespace s21 {
const std::unordered_map<std::string, std::string> SmartCalc::replacements_ = {
    {"cos", "c"},  {"sin", "s"},  {"tan", "t"}, {"acos", "a"}, {"asin", "i"},
    {"atan", "q"}, {"sqrt", "r"}, {"ln", "l"},  {"log", "g"},  {"mod", "%"}};

const std::unordered_map<std::string, int> SmartCalc::priority_ = {
    {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"%", 2}, {"^", 3}, {"u", 4}};

double SmartCalc::calcExpression(double x) {
  convertInfixToPostfixStr(expression_);
  return calcPostfix(x);
}

void SmartCalc::convertInfixToPostfixStr(std::string &infix) {
  checkBrackets(infix);
  std::string postfix;
  std::stack<std::string> signs;

  replaceFunctions(infix);
  bool isPrevDig = false;
  bool isPrevExp = false;
  bool prevIsOperatorOrParen = true;

  for (char c : infix) {
    if (isPrevDig && !isdigit(c) && c != '.' && c != 'E' && c != 'e') {
      postfix += kSeparator;
    }

    isdigit(c) ? isPrevDig = true : isPrevDig = false;

    std::string token(1, c);

    if (token == "-" && prevIsOperatorOrParen) {
      token = "u";
    }

    prevIsOperatorOrParen = false;

    if (isdigit(c) || c == '.' || c == 'e' || c == 'E' || c == 'x' ||
        c == 'X' || (isPrevExp && (c == '+' || c == '-'))) {
      if (c == 'e' || c == 'E')
        isPrevExp = true;
      else
        isPrevExp = false;
      postfix += c;
      continue;
    }

    auto it =
        std::find_if(replacements_.begin(), replacements_.end(),
                     [&token](const auto &map) { return token == map.second; });

    if (token == "(" || it != replacements_.end()) {
      signs.push(token);
      prevIsOperatorOrParen = true;
      continue;
    }

    auto it_operator = priority_.find(token);
    if (it_operator != priority_.end()) {
      while (!signs.empty() && priority_.find(signs.top()) != priority_.end() &&
             (priority_.at(signs.top()) > priority_.at(it_operator->first) ||
              (priority_.at(signs.top()) == priority_.at(it_operator->first) &&
               token != "^"))) {
        postfix += signs.top();
        signs.pop();
      }
      signs.push(token);
      prevIsOperatorOrParen = true;
      continue;
    }

    if (token == ")") {
      while (!signs.empty() && signs.top() != "(") {
        postfix += signs.top();
        signs.pop();
      }
      signs.pop();
      if (!signs.empty()) {
        auto it1 = std::find_if(
            replacements_.begin(), replacements_.end(),
            [&signs](const auto &map) { return signs.top() == map.second; });
        if (it1 != replacements_.end()) {
          postfix += signs.top();
          signs.pop();
        }
      }
      continue;
    }
  }

  while (!signs.empty()) {
    postfix += signs.top();
    signs.pop();
  }
  convertPostfixStrToVector(postfix);
}

void SmartCalc::convertPostfixStrToVector(const std::string &notation) {
  std::string number;
  bool isPrevExp = false;

  for (char c : notation) {
    if (isdigit(c) || c == '.' || c == 'e' || c == 'E' ||
        (isPrevExp && (c == '+' || c == '-'))) {
      if (c == 'e' || c == 'E')
        isPrevExp = true;
      else
        isPrevExp = false;

      number += c;
    } else if (c == kSeparator) {
      if (!number.empty()) {
        postfix_.push_back(number);
        number.clear();
      }
    } else {
      if (!number.empty()) {
        postfix_.push_back(number);
        number.clear();
      }
      std::string token(1, c);
      postfix_.push_back(token);
    }
  }
  if (!number.empty()) {
    postfix_.push_back(number);
  }
}

double SmartCalc::calcPostfix(const double x) {
  std::stack<double> s;
  for (const auto &token : postfix_) {
    if (token == "x") {
      s.push(x);
    } else if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
      s.push(stod(token));
    } else {
      double op2, op1;
      if (token == "+" || token == "-" || token == "*" || token == "/" ||
          token == "%" || token == "^") {
        if (s.size() < 2) {
          throw std::invalid_argument("insufficient args for function");
        }
        op2 = s.top();
        s.pop();
        op1 = s.top();
        s.pop();
      } else {
        if (s.empty()) {
          throw std::invalid_argument("insufficient args for function");
        }
        op1 = s.top();
        s.pop();
      }

      if (token == "+")
        s.push(op1 + op2);
      else if (token == "-")
        s.push(op1 - op2);
      else if (token == "*")
        s.push(op1 * op2);
      else if (token == "/")
        s.push(op1 / op2);
      else if (token == "%")
        s.push(fmod(op1, op2));
      else if (token == "^")
        s.push(pow(op1, op2));
      else if (token == replacements_.at("cos"))
        s.push(cos(op1));
      else if (token == replacements_.at("sin"))
        s.push(sin(op1));
      else if (token == replacements_.at("tan"))
        s.push(tan(op1));
      else if (token == replacements_.at("acos"))
        s.push(acos(op1));
      else if (token == replacements_.at("asin"))
        s.push(asin(op1));
      else if (token == replacements_.at("atan"))
        s.push(atan(op1));
      else if (token == replacements_.at("sqrt")) {
        if (op1 < 0) throw std::invalid_argument("arg should be >= 0");
        s.push(sqrt(op1));
      } else if (token == replacements_.at("ln")) {
        if (op1 <= 0) throw std::invalid_argument("arg should be > 0");
        s.push(log(op1));
      } else if (token == replacements_.at("log")) {
        if (op1 <= 0) throw std::invalid_argument("arg should be > 0");
        s.push(log10(op1));
      } else if (token == "u")
        s.push(-op1);
    }
  }
  return s.top();
}

void SmartCalc::replaceFunctions(std::string &str) {
  for (const auto &pair : replacements_) {
    const std::string &from = pair.first;
    const std::string &to = pair.second;
    size_t pos = str.find(from);
    while (pos != std::string::npos) {
      str.replace(pos, from.length(), to);
      pos = str.find(from, pos + to.length());
    }
  }
}

void SmartCalc::checkBrackets(const std::string &str) {
  int count = 0;
  for (char c : str) {
    if (c == '(') {
      ++count;
    } else if (c == ')') {
      --count;
    }
    if (count < 0) {
      throw std::invalid_argument("mismatched brackets");
    }
  }
  if (count != 0) {
    throw std::invalid_argument("mismatched brackets");
  }
}

}  // namespace s21

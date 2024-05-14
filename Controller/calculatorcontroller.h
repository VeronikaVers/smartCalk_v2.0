#ifndef SRC_CONTROLLER_CALCULATORCONTROLLER_H
#define SRC_CONTROLLER_CALCULATORCONTROLLER_H

#include "../Model/calculatormodel.h"

namespace s21 {
class CalculatorController {
 public:
  CalculatorController() {}
  CalculatorController(std::string expression) : calc_(std::move(expression)) {}
  double calculateExpression(double xValue = 0);

 private:
  SmartCalc calc_;
};
}  // namespace s21
#endif  // SRC_CONTROLLER_CALCULATORCONTROLLER_H

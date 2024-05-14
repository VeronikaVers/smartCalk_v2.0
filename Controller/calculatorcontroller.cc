#include "calculatorcontroller.h"

namespace s21 {
double CalculatorController::calculateExpression(const double xValue) {
  return calc_.calcExpression(xValue);
}
}  // namespace s21

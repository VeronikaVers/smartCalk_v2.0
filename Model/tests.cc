#include <gtest/gtest.h>

#include "calculatormodel.h"

TEST(CalcTest, Base) {
  s21::SmartCalc calc("0");
  EXPECT_NEAR(calc.calcExpression(0), 0, 1e-5);
}

TEST(CalcTest, Plus) {
  s21::SmartCalc calc("1 + 1");
  EXPECT_NEAR(calc.calcExpression(0), 2, 1e-5);
}

TEST(CalcTest, Minus) {
  s21::SmartCalc calc("1 - 1");
  EXPECT_NEAR(calc.calcExpression(0), 0, 1e-5);
}

TEST(CalcTest, Mult) {
  s21::SmartCalc calc("6 * 3");
  EXPECT_NEAR(calc.calcExpression(0), 18, 1e-5);
}

TEST(CalcTest, Div) {
  s21::SmartCalc calc("7 / 2");
  EXPECT_NEAR(calc.calcExpression(0), 3.5, 1e-5);
}

TEST(CalcTest, Pow) {
  s21::SmartCalc calc("3^4");
  EXPECT_NEAR(calc.calcExpression(0), 81, 1e-5);
}

TEST(CalcTest, Sqrt) {
  s21::SmartCalc calc("sqrt(9)");
  EXPECT_NEAR(calc.calcExpression(0), 3, 1e-5);
}

TEST(CalcTest, Log) {
  s21::SmartCalc calc("log(1)");
  EXPECT_NEAR(calc.calcExpression(0), 0, 1e-5);
}

TEST(SmartCalcTest, Log0) {
  s21::SmartCalc calc("log(0)");
  EXPECT_THROW(calc.calcExpression(0), std::invalid_argument);
}

TEST(CalcTest, LogM) {
  s21::SmartCalc calc("log(-1)");
  EXPECT_THROW(calc.calcExpression(0), std::invalid_argument);
}

TEST(CalcTest, Cos) {
  s21::SmartCalc calc("cos(0)");
  EXPECT_NEAR(calc.calcExpression(0), 1, 1e-5);
}

TEST(CalcTest, Sin) {
  s21::SmartCalc calc("sin(0)");
  EXPECT_NEAR(calc.calcExpression(0), 0, 1e-5);
}

TEST(CalcTest, Tan) {
  s21::SmartCalc calc("tan(0)");
  EXPECT_NEAR(calc.calcExpression(0), 0, 1e-5);
}

TEST(CalcTest, ATan) {
  s21::SmartCalc calc("atan(0)");
  EXPECT_NEAR(calc.calcExpression(0), 0, 1e-5);
}

TEST(CalcTest, Mod) {
  s21::SmartCalc calc("5mod4");
  EXPECT_NEAR(calc.calcExpression(0), 1, 1e-5);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

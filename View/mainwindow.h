#ifndef SRC_VIEW_MAINWINDOW_H
#define SRC_VIEW_MAINWINDOW_H

#include <QDoubleValidator>
#include <QIntValidator>
#include <QMainWindow>
#include <cstring>

#include "creditwindow.h"
#include "depositwindow.h"
#include "graphwindow.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  // Constructor
  MainWindow(QWidget* parent = nullptr);
  // Destructor
  ~MainWindow();

 private:
  Ui::MainWindow* ui;
  s21::CalculatorController controller;
  double in_x = 0;

 private slots:
  void push_formula();
  void on_pushButton_deposit_clicked();
  void on_pushButton_credit_clicked();
  void on_pushButton_graph_clicked();
  void on_pushButton_X_clicked();
};

#endif  // SRC_VIEW_MAINWINDOW_H

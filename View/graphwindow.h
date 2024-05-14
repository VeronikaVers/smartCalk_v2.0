#ifndef SRC_VIEW_GRAPHWINDOW_H
#define SRC_VIEW_GRAPHWINDOW_H

#include <QDialog>
#include <QVector>

#include "ui_graphwindow.h"

namespace Ui {
class GraphWindow;
}

#include "../Controller/calculatorcontroller.h"

class GraphWindow : public QDialog {
  Q_OBJECT

 public:
  GraphWindow(QWidget *parent = nullptr);
  ~GraphWindow();

 private:
  Ui::GraphWindow *ui;
  s21::CalculatorController controller;

 private slots:

  void on_build_clicked();
};
#endif  // SRC_VIEW_GRAPHWINDOW_H

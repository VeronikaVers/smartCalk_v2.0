#ifndef SRC_VIEW_CREDITWINDOW_H
#define SRC_VIEW_CREDITWINDOW_H

#include <QDialog>

#include "../Controller/creditcontroller.h"
#include "ui_creditwindow.h"

namespace Ui {
class CreditWindow;
}

class CreditWindow : public QDialog {
  Q_OBJECT

 public:
  // Constructor
  explicit CreditWindow(QWidget* parent = nullptr);
  // Destructor
  ~CreditWindow();
  // Setters
  void SetNull();
  void SetValidators();
  void SetCreditInfo();
  void SetResult();

 private:
  Ui::CreditWindow* ui;
  QString q_pay_{};
  QString q_overpay_{};
  QString q_sum_{};
  QString q_pay_clone_{};
  s21::CreditInfo info_{};
  s21::CreditResult result_{};
  s21::CreditController controller_{};

 private slots:
  int ValidateInput();
  int CheckNull(QString str);
  void AppendPoints();
  void DeleteResult();
  void on_pushButton_calculate_clicked();
};

#endif  // SRC_VIEW_CREDITWINDOW_H

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(push_formula()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(push_formula()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(push_formula()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(push_formula()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(push_formula()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(push_formula()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(push_formula()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(push_formula()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(push_formula()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(push_formula()));
  connect(ui->pushButton_tchk, SIGNAL(clicked()), this, SLOT(push_formula()));

  connect(ui->pushButton_multiply, SIGNAL(clicked()), this,
          SLOT(push_formula()));
  connect(ui->pushButton_divide, SIGNAL(clicked()), this, SLOT(push_formula()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(push_formula()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(push_formula()));

  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(push_formula()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(push_formula()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(push_formula()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(push_formula()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(push_formula()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(push_formula()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(push_formula()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(push_formula()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(push_formula()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(push_formula()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(push_formula()));

  connect(ui->pushButton_L, SIGNAL(clicked()), this, SLOT(push_formula()));
  connect(ui->pushButton_R, SIGNAL(clicked()), this, SLOT(push_formula()));

  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(push_formula()));
  connect(ui->pushButton_rez, SIGNAL(clicked()), this, SLOT(push_formula()));
  //  connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(push_formula()));

  setFixedSize(366, 427);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::push_formula() {
  QPushButton *button = (QPushButton *)sender();
  QString pressedKey = button->text();

  int Function =
      pressedKey.compare("sin") == 0 || pressedKey.compare("asin") == 0 ||
      pressedKey.compare("cos") == 0 || pressedKey.compare("acos") == 0 ||
      pressedKey.compare("tan") == 0 || pressedKey.compare("atan") == 0 ||
      pressedKey.compare("log") == 0 || pressedKey.compare("ln") == 0 ||
      pressedKey.compare("sqrt") == 0;

  if (pressedKey.compare("AC") == 0) {
    ui->rez_label->setText("");

  } else if (Function) {
    pressedKey.push_back("(");
    ui->rez_label->setText(ui->rez_label->text() + pressedKey);

  } else if (pressedKey.compare("=") == 0) {
    QString formula = ui->rez_label->text();

    if (in_x != 0) {
      std::string text = formula.toStdString();
      std::string X_str{"X"};
      std::string num_str = (ui->lineEdit_2->text()).toStdString();
      if (num_str == "") {
        num_str = "0";
      }
      size_t start{text.find(X_str)};

      while (start != std::string::npos) {
        text.replace(start, X_str.length(), num_str);
        start = text.find(X_str, start + num_str.length());
      }

      formula = QString::fromStdString(text);
    }

    if (!formula.isEmpty()) {
      std::string string = formula.toStdString();
      try {
        s21::CalculatorController controller(string);
        double result = controller.calculateExpression();
        ui->rez_label->setText(QString::number(result));
      } catch (const std::invalid_argument &e) {
        ui->rez_label->setText(QString::fromStdString(e.what()));
      }
    }

  } else {
    ui->rez_label->setText(ui->rez_label->text() + pressedKey);
  }
}

void MainWindow::on_pushButton_deposit_clicked() {
  DepositWindow deposit_window;
  deposit_window.setModal(true);
  deposit_window.exec();
}

void MainWindow::on_pushButton_credit_clicked() {
  CreditWindow credit_window;
  credit_window.setModal(true);
  credit_window.exec();
}

void MainWindow::on_pushButton_graph_clicked() {
  GraphWindow graph_window;
  graph_window.setModal(true);
  graph_window.exec();
}

void MainWindow::on_pushButton_X_clicked() {
  ui->rez_label->setText(ui->rez_label->text() + "X");
  in_x++;
}

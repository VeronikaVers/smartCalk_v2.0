#include "graphwindow.h"

GraphWindow::GraphWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::GraphWindow) {
  ui->setupUi(this);

  setFixedSize(500, 450);
}

GraphWindow::~GraphWindow() { delete ui; }

void GraphWindow::on_build_clicked() {
  ui->err->setText("");

  ui->widget->clearGraphs();
  QString function = ui->formula->text();
  if (function.count(' ') != function.length()) {
    std::string string = function.toStdString();

    QVector<double> x, y;

    double xAxisStart = ui->x1->text().toDouble();
    double xAxisEnd = ui->x2->text().toDouble();
    double yAxisStart = ui->y1->text().toDouble();
    double yAxisEnd = ui->y2->text().toDouble();
    double step = ui->step->text().toDouble();

    ui->widget->xAxis->setRange(xAxisStart, xAxisEnd);
    ui->widget->yAxis->setRange(yAxisStart, yAxisEnd);
    s21::CalculatorController controller(string);

    for (double x_graph = 0; x_graph <= xAxisEnd; x_graph += step) {
      x.push_back(x_graph);
      try {
        y.push_back(controller.calculateExpression(x_graph));
      } catch (const std::invalid_argument &e) {
        ui->err->setText(QString::fromStdString(e.what()));
      }
    }

    for (double x_graph = xAxisStart; x_graph <= 0; x_graph += step) {
      x.push_back(x_graph);
      try {
        y.push_back(controller.calculateExpression(x_graph));
      } catch (const std::invalid_argument &e) {
        ui->err->setText(QString::fromStdString(e.what()));
      }
    }

    ui->widget->addGraph();
    QPen pen(Qt::red);
    pen.setWidth(2);

    ui->widget->graph(0)->setPen(pen);
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
  }
}

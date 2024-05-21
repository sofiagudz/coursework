#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dovidka.h"
#include "BisectionMethod.h"
#include "newthonmethod.h"
#include "SecantMethod.h"
#include "graph.h"
#include "inputvalidator.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboBox->addItem("Метод бісекції");
    ui->comboBox->addItem("Метод Ньютона");
    ui->comboBox->addItem("Метод січних");

    setup_graph();

    QRegularExpressionValidator *validator_for_x = new QRegularExpressionValidator(QRegularExpression("-?\\d+(?:\\.\\d+)?"), this);
    ui->x1_input->setValidator(validator_for_x);
    ui->x2_input->setValidator(validator_for_x);
    ui->x0_input->setValidator(validator_for_x);
    QRegularExpressionValidator *validator_for_e = new QRegularExpressionValidator(QRegularExpression("^0\\.0+1$"), this);
    ui->e_input->setValidator(validator_for_e);

    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index){
        if(index == 1)
            ui->stackedWidget->setCurrentIndex(1);
        else
            ui->stackedWidget->setCurrentIndex(0);
    });
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Clean_button_clicked()
{
    if(!ui->polynomial_input->text().isEmpty()) ui->polynomial_input->clear();
    if(!ui->x1_input->text().isEmpty()) ui->x1_input->clear();
    if(!ui->x2_input->text().isEmpty()) ui->x2_input->clear();
    if(!ui->x0_input->text().isEmpty()) ui->x0_input->clear();
    if(!ui->textBrowser->toHtml().isEmpty()) ui->textBrowser->clear();
    ui->e_input->setText("0.001");
    if(isGraphDrawn){
        ui->graph->graph(0)->data()->clear();
        ui->graph->replot();
        ui->graph->update();
    }
}

void MainWindow::on_Solve_button_clicked()
{
    if(isGraphDrawn){
        ui->graph->graph(0)->data()->clear();
        ui->graph->replot();
        ui->graph->update();
    }

    if(!ui->textBrowser->toHtml().isEmpty()) ui->textBrowser->clear();

    int method_ind = ui->comboBox->currentIndex();

    Polynomial *p = nullptr;
    try{
        InputValidator inputValidator(ui->polynomial_input->text(), ui->x1_input->text(), ui->x2_input->text(), ui->x0_input->text(), ui->e_input->text(), method_ind);
        p = new Polynomial(ui->polynomial_input->text().toStdString());
        double x1 = ui->x1_input->text().toDouble();
        double x2 = ui->x2_input->text().toDouble();
        double x0 = ui->x0_input->text().toDouble();
        double e = ui->e_input->text().toDouble();
        if(method_ind == 0){
            BisectionMethod bisection(*p, x1, x2, e);
            Graph(*p, x1, x2, this->ui->graph);
            ui->textBrowser->setText(QString::fromStdString(bisection.print_iterations()));
        }
        else if(method_ind == 1){
            NewthonMethod newthon(*p, x0, e);
            Graph(*p, -1 * abs(newthon.get_result()) - 5, abs(newthon.get_result()) + 5, this->ui->graph);
            ui->textBrowser->setText(QString::fromStdString(newthon.print_iterations()));
        }
        else{
            SecantMethod secant(*p, x1, x2, e);
            Graph(*p, x1, x2, this->ui->graph);
            ui->textBrowser->setText(QString::fromStdString(secant.print_iterations()));
        }
        isGraphDrawn = true;
    }
    catch(std::invalid_argument &err){
        QMessageBox::critical(this, "Помилка", err.what());
    }
}

void MainWindow::setup_graph()
{
    ui->graph->xAxis->setRange(-10, 10);
    ui->graph->yAxis->setRange(-10, 10);
    ui->graph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->graph->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->graph->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->graph->xAxis->setTickPen(QPen(Qt::white, 1));
    ui->graph->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->graph->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->graph->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->graph->xAxis->setTickLabelColor(Qt::white);
    ui->graph->yAxis->setTickLabelColor(Qt::white);
    ui->graph->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->graph->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->graph->xAxis->grid()->setSubGridVisible(false);
    ui->graph->yAxis->grid()->setSubGridVisible(false);
    ui->graph->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->graph->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->graph->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->graph->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->graph->setBackground(QBrush(Qt::black));
    ui->graph->xAxis->grid()->setSubGridVisible(false);
    ui->graph->yAxis->grid()->setSubGridVisible(false);
}

void MainWindow::on_save_Button_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(nullptr, "Зберегти файл", QDir::homePath(), "Текстові файли (*.txt)");

    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            stream << QString::fromStdString(ui->textBrowser->toPlainText().toStdString());
            file.close();
        }
    }
}

void MainWindow::on_OpenDovidkaButton_clicked()
{
    Dovidka *dov = new Dovidka(this);
    dov->exec();

}

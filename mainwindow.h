#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegularExpressionValidator>
#include <QDoubleValidator>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Clean_button_clicked();

    void on_Solve_button_clicked();

    void on_save_Button_clicked();

    void on_OpenDovidkaButton_clicked();

private:
    bool isGraphDrawn = false;

    void setup_graph();

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H


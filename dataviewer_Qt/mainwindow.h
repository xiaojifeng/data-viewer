#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QString filename;
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_display_clicked();

    void on_parse_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

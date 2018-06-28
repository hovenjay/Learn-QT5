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
    ~MainWindow();

private slots:
    void searchAll();

    void on_submitBtn_clicked();

    void on_addBtn_clicked();

    void on_delBtn_clicked();

    void on_revertBtn_clicked();

    void on_searchBtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

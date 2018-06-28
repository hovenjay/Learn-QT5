#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("Students");                                                   // 设置查询的表格
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);                        // 手动提交（改动即提交，选择其他行时提交，手动提交）
    model->select();                                                               // 执行查询
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("学号"));                  // 第一列别名
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("姓名"));                  // 第二列别名
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("成绩"));                  // 第三列别名
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 表格自适应容器宽度
    ui->tableView->setModel(model);
}
MainWindow::~MainWindow()
{
    delete ui;
}
// 查询全部：
void MainWindow::searchAll()
{
    QSqlTableModel *model = dynamic_cast<QSqlTableModel *>(ui->tableView->model());
    model->setTable("Students");                                  // 设置查询的表格
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);       // 手动提交（改动即提交，选择其他行时提交，手动提交）
    model->select();                                              // 执行查询
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("学号")); // 第一列别名
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("姓名")); // 第二列别名
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("成绩")); // 第三列别名
}
// 选择查询：
void MainWindow::on_searchBtn_clicked()
{
    QSqlTableModel *model = dynamic_cast<QSqlTableModel *>(ui->tableView->model());
    int StuID = ui->lineEdit->text().toInt(); // 获取文本输入框字符串并强制转换为 int 类型
    if (StuID >= 101 && StuID <= 1000)
    {
        model->setFilter(QString("StuID = %1").arg(StuID)); // 设置查询的参数为 StuID
        model->select();                                    // 执行查询
    }
    else
    {
        MainWindow::searchAll(); // 查询全部
    }
}
// 提交更改：作为事务去提交
void MainWindow::on_submitBtn_clicked()
{
    QSqlTableModel *model = dynamic_cast<QSqlTableModel *>(ui->tableView->model());
    model->database().transaction(); // 开始事务操作
    if (model->submitAll())          // 提交被修改的数据到数据库中
    {
        model->database().commit(); // 数据提交成功，事务提交
    }
    else
    {
        model->database().rollback(); // 数据提交失败，事务回滚
        QMessageBox::warning(this, tr("tableModel"), tr("数据库错误: %1").arg(model->lastError().text()));
    }
    model->revertAll(); // 撤销修改
}
// 撤销更改：如果事务提交了数据库就修改不了
void MainWindow::on_revertBtn_clicked()
{
    QSqlTableModel *model = dynamic_cast<QSqlTableModel *>(ui->tableView->model());
    model->revertAll();
}
// 添加数据：
void MainWindow::on_addBtn_clicked()
{
    QSqlTableModel *model = dynamic_cast<QSqlTableModel *>(ui->tableView->model());
    QSqlRecord record = model->record();
    int number;
    for (number = 101;; number++) // 从 1 开始遍历，遇到相同的主键，自增再遍历
    {                             // 防止主键重复导致提交失败，因为提交失败 tableview 还是会更新修改后的结果
        bool bFlag = false;
        for (int index = 0; index < model->rowCount(); index++)
        {
            if (model->index(index, 0).data().toInt() == number)
            {
                bFlag = true;
                break;
            }
        }
        if (!bFlag)
        {
            break;
        }
    } // 遍历完成，没有相同的主键，将 number 作为新的一行的主键
    QString stuName = ui->lineEdit_2->text();
    int score = ui->lineEdit_3->text().toInt();
    if (stuName.isEmpty() || score < 0 || score > 100)
    {
        QMessageBox::warning(NULL, "警告", "输入不合法！请检查后重新输入。");
    }
    else
    {
        record.setValue(0, number);  // 插入记录-学号
        record.setValue(1, stuName); // 插入记录-姓名
        record.setValue(2, score);   // 插入记录-成绩
        model->insertRecord(model->rowCount(), record);
        model->submitAll(); // 插入数据后刷新 tableView
    }
}
// 删除选中：
void MainWindow::on_delBtn_clicked()
{
    QSqlTableModel *model = dynamic_cast<QSqlTableModel *>(ui->tableView->model());
    model->removeRow(ui->tableView->currentIndex().row()); // 删除当前选中
    model->submitAll();                                    // 删除数据后刷新 tableView
}

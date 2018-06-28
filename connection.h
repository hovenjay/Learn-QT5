#ifndef CONNECTION_H
#define CONNECTION_H
#include <QApplication>       // qApp 依赖
#include <QtSql/QSqlDatabase> // 数据库驱动
#include <QMessageBox>
#include <QSqlError> // 返回查询错误信息
#include <QSqlQuery> // 返回查询结果
static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(": memory: ");
    QSqlQuery query;
    if (!db.open())
    {
        QMessageBox::critical(0, qApp->tr("Cannot open database"), qApp->tr("Unable to establisha database connection."), QMessageBox::Cancel);
        return false;
    }
    else
    {
        query.exec("CREATE TABLE Students( StuID INT PRIMARY KEY NOT NULL, StuName TEXT NOT NULL, Score INT NOT NULL)");
        query.exec("INSERT INTO Students (StuID, StuName, Score) VALUES (101, '何文杰', 80)");
        query.exec("INSERT INTO Students (StuID, StuName, Score) VALUES (102, '石磊', 85)");
        query.exec("INSERT INTO Students (StuID, StuName, Score) VALUES (103, '韦竣南', 90)");
        query.exec("INSERT INTO Students (StuID, StuName, Score) VALUES (104, 'Jason', 95)");
        query.exec("INSERT INTO Students (StuID, StuName, Score) VALUES (105, 'Charles', 100)");
        return true;
    }
}
#endif // CONNECTION_H

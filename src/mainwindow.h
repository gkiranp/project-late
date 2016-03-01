#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define TEST 0

#include <QMainWindow>
#include <QList>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QTextStream>
#include <QApplication>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "ws_storage.h"
#include "dlgfilter.h"
#include "dlgfind.h"
#include "dlgformat.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
public:
    bool ApplyFilter(void);

private:
    bool Operate_ROW_Filter(QString format, WS_OperationType type);
    bool Operate_COLUMN_Filter(QString format, WS_OperationType type);
    bool Operate_TIME_Filter(QString format, WS_OperationType type);
    bool Operate_DATE_Filter(QString format, WS_OperationType type);
    bool Operate_STRING_Filter(QString format, WS_OperationType type);
    bool Operate_CUSTOM_Filter(QString format, WS_OperationType type);
    bool ApplyFilter_Delete(QString format);
    bool ApplyFilter_Highlight(QString format);

private slots:
    void on_actionFilter_triggered();
    void on_actionOpen_triggered();
    void on_actionFind_triggered();
    void on_actionExport_triggered();

    void on_actionFormat_triggered();

private:
    Ui::MainWindow *ui;

public:
    ws_storage m_StoreWS;

private:
    QList<WS_OperationStorage> m_StoreFilter;
};

#endif // MAINWINDOW_H

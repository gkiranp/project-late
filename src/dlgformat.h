#ifndef DLGFORMAT_H
#define DLGFORMAT_H

#include <QDialog>
#include <QFileDialog>
#include <QStringList>
#include <QString>
#include <QStringListModel>
#include <QFile>
#include <QTextStream>

namespace Ui {
class DlgFormat;
}

class DlgFormat : public QDialog
{
    Q_OBJECT

public:
    explicit DlgFormat(QWidget *parent = 0);
    ~DlgFormat();

signals:
    void operation_format_progress(int cur_progress);

public slots:
    void show_format_progress(int cur_progress);

private slots:
    void on_pshbtnFormat_released();
    void on_pshbtnCancel_released();
    void on_pshbtn_AddFiles_released();
    void on_pshbtnBrowseSaveFile_released();
    void on_pshbtn_ClearFiles_released();

private:
    void Format_Log_File(QString fileName, QStringList frmtStrs,
                         QString saveTo, QString preAppend, bool caseSensitive);
    void Enable_UI_Components(bool en);

private:
    Ui::DlgFormat *ui;
    QStringListModel *m_FileListModel;
    QStringList      m_FileListEntries;
};

#endif // DLGFORMAT_H

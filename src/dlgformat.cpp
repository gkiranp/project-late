#include "dlgformat.h"
#include "ui_dlgformat.h"

DlgFormat::DlgFormat(QWidget *parent) : QDialog(parent), ui(new Ui::DlgFormat)
{
    ui->setupUi(this);
    m_FileListModel = new QStringListModel();
    ui->lstFileNames->setModel(m_FileListModel);
    m_FileListEntries.empty();
    connect(this, SIGNAL(operation_format_progress(int)), this, SLOT(show_format_progress(int)));
}

DlgFormat::~DlgFormat()
{
    delete ui;
}

void DlgFormat::show_format_progress(int cur_progress)
{
    ui->prgStatus->setMinimum(0);
    ui->prgStatus->setMaximum(100);
    ui->prgStatus->setValue(cur_progress);
    ui->prgStatus->setTextVisible(true);
    ui->prgStatus->show();
}

void DlgFormat::Format_Log_File(QString fileName, QStringList frmtStrs,
                                QString saveTo, QString preAppend, bool caseSensitive)
{
    if((!fileName.isEmpty()) && (!frmtStrs.empty()) && (!saveTo.isEmpty())) {
        /* prepare file to read from */
        QFile fileRead(fileName);
        if(!fileRead.open(QFile::ReadOnly | QFile::Text)) {
            //qDebug() << "Cant read ...";
            return;
        }
        QTextStream rd_stream(&fileRead);

        /* create file paths with file name to store logs */
        QStringList pathWriteTo;
        int tmp_index = 0;
        QString curLine = "";
        for(tmp_index = 0 ; tmp_index < frmtStrs.count() ; tmp_index++) {
            curLine = saveTo + "/" + frmtStrs.at(tmp_index) + "_" + preAppend + ".log";
            pathWriteTo.append(curLine);
        }

        /* prepare to write into */
        QFile fileWrite[pathWriteTo.count()];
        for(tmp_index = 0 ; tmp_index < pathWriteTo.count() ; tmp_index++) {
            fileWrite[tmp_index].setFileName(pathWriteTo.at(tmp_index));
            if(!fileWrite[tmp_index].open(QFile::WriteOnly | QFile::Text)) {
                //qDebug() << "Cant write ..." << tmp_index;
                return;
            }
        }

        /* look into format and write into file */
        QTextStream wr_stream;
        QString what2look = "";
        bool match_flag = false;
        do
        {
            curLine = rd_stream.readLine();
            for (tmp_index = 0 ; tmp_index < frmtStrs.count() ; tmp_index++) {
                what2look = frmtStrs.at(tmp_index);
                match_flag = false;
                if(caseSensitive) {
                    if(curLine.contains(what2look, Qt::CaseSensitive)) {
                        match_flag = true;
                    }
                } else {
                    if(curLine.contains(what2look, Qt::CaseInsensitive)) {
                        match_flag = true;
                    }
                }
                if(match_flag) {
                    wr_stream.setDevice(&fileWrite[tmp_index]);
                    curLine = curLine + "\n"; //add a new line
                    wr_stream << curLine;
                    wr_stream.flush();
                }
            }

        } while (!curLine.isNull());

        /* close all files safely */
        fileRead.close();
        for(tmp_index = 0 ; tmp_index < pathWriteTo.count() ; tmp_index++) {
            fileWrite[tmp_index].close();
        }
    }
}

void DlgFormat::Enable_UI_Components(bool en)
{
    ui->lstFileNames->setEnabled(en);
    ui->editFormatString->setEnabled(en);
    ui->editSaveFileTo->setEnabled(en);
    ui->pshbtnBrowseSaveFile->setEnabled(en);
    ui->pshbtnFormat->setEnabled(en);
    ui->pshbtnCancel->setEnabled(en);
    ui->pshbtn_AddFiles->setEnabled(en);
    ui->pshbtn_ClearFiles->setEnabled(en);
}

void DlgFormat::on_pshbtnFormat_released()
{
    //this->accept();
    QStringList formatStr = ui->editFormatString->text().split(',');
    QString FilePath = ui->editSaveFileTo->text();
    bool caseSensitivity = false;
    if(ui->chkbxCaseSensitivity->checkState() == Qt::Checked) {
        caseSensitivity = true;
    }
    if((!m_FileListEntries.empty()) &&
            (!formatStr.empty()) &&
            (!FilePath.isEmpty()))
    {
        /* disable components first */
        this->Enable_UI_Components(false);
        /* we shall prepare to display progress */
        int curProgress = 0;
        QString prefixStr = ui->editPrefixFileWith->text();
        for(int index = 0 ; index < m_FileListEntries.count() ; index++) {
            this->Format_Log_File(m_FileListEntries.at(index), formatStr,FilePath,prefixStr,caseSensitivity);
            curProgress += (100/m_FileListEntries.count());
            emit this->operation_format_progress(curProgress);
        }
        /* emit 100% work done */
        emit this->operation_format_progress(100);
        /* enable back all components */
        this->Enable_UI_Components(true);
    }
}

void DlgFormat::on_pshbtnCancel_released()
{
    this->reject();
}

void DlgFormat::on_pshbtn_AddFiles_released()
{
    QStringList CurFileList;
    CurFileList = QFileDialog::getOpenFileNames(this, tr("Select Files To Add"), tr("/home/"), tr("Log Files (*.*)"));
    if(!CurFileList.empty()) {
        m_FileListEntries.append(CurFileList);
        m_FileListModel->setStringList(m_FileListEntries);
    }
}

void DlgFormat::on_pshbtn_ClearFiles_released()
{
    m_FileListEntries.clear();
    m_FileListModel->setStringList(m_FileListEntries);
}


void DlgFormat::on_pshbtnBrowseSaveFile_released()
{
    QString dirPath = "";
    dirPath = QFileDialog::getExistingDirectory(this, tr("Chose A Directory"),
                                                "/home", QFileDialog::ShowDirsOnly |
                                                QFileDialog::DontResolveSymlinks);
    if(!dirPath.isEmpty()) {
        ui->editSaveFileTo->setText(dirPath);
    }
}


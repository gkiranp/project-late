#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
#if TEST
    WS_OperationStorage one;
    one.m_OpType = e_Op_DELETE;
    one.m_OpSub = e_sub_ROW;
    one.m_OpFormat = "1";
    m_StoreFilter.append(one);
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::ApplyFilter_Delete(QString format)
{
    bool ret = false;
    if(!format.isEmpty()) {
        QTextCursor newCursor(ui->rtxtLogBrowser->document());
        while(! newCursor.isNull() && !newCursor.atEnd()) {
            newCursor = ui->rtxtLogBrowser->document()->find(format, newCursor);
            if(!newCursor.isNull()) {
                newCursor.removeSelectedText();
                ret = true; //true if atleast one operation performed
            }
        }
    }
    return ret;
}

bool MainWindow::ApplyFilter_Highlight(QString format)
{
    bool ret = false;
    if(!format.isEmpty()) {
        QTextCursor newCursor(ui->rtxtLogBrowser->document());
        while(! newCursor.isNull() && !newCursor.atEnd()) {
            newCursor = ui->rtxtLogBrowser->document()->find(format, newCursor);
            if(!newCursor.isNull()) {
                newCursor.movePosition(QTextCursor::WordRight, QTextCursor::KeepAnchor);
                QTextCharFormat plainFormat = newCursor.charFormat();
                plainFormat.setForeground(QColor("#990011"));
                plainFormat.setBackground(QColor("#FFFF55"));
                newCursor.mergeCharFormat(plainFormat);
                ret = true; //true if atleast one operation performed
            }
        }
    }
    return ret;
}

bool MainWindow::ApplyFilter(void)
{
    bool sts = false;
    if(!m_StoreFilter.isEmpty()) {
        WS_OperationStorage fltr;
        qDebug() << "Applying filters...";
        for(int i = 0 ; i < m_StoreFilter.size(); i++) {
            fltr = m_StoreFilter.at(i);
            switch(fltr.m_OpSub) {
            case e_sub_ROW:
                qDebug() <<"Applying ROW filter";
                this->Operate_ROW_Filter(fltr.m_OpFormat, fltr.m_OpType);
                break;
            case e_sub_COLUMN:
                qDebug() <<"Applying COLUMN filter";
                this->Operate_COLUMN_Filter(fltr.m_OpFormat, fltr.m_OpType);
                break;
            case e_sub_DATE:
                qDebug() <<"Applying DATE filter";
                this->Operate_DATE_Filter(fltr.m_OpFormat, fltr.m_OpType);
                break;
            case e_sub_TIME:
                qDebug() <<"Applying TIME filter";
                this->Operate_TIME_Filter(fltr.m_OpFormat, fltr.m_OpType);
                break;
            case e_sub_STRING:
                qDebug() <<"Applying STRING filter";
                this->Operate_STRING_Filter(fltr.m_OpFormat, fltr.m_OpType);
                break;
            case e_sub_CUSTOM:
                qDebug() <<"Applying CUSTOM filter";
                this->Operate_CUSTOM_Filter(fltr.m_OpFormat, fltr.m_OpType);
                break;
            default:
                qDebug() <<"Unknown filter";
                break;
            }
        }
    }
    return sts;
}

bool MainWindow::Operate_ROW_Filter(QString format, WS_OperationType type)
{
    if(!format.isEmpty() && (format.toInt() >= 0)) {
        bool HighlightFlag = false;
        QStringList RowList;
        RowList = QString(ui->rtxtLogBrowser->toPlainText()).split('\n');
        int RNum = format.toInt();
        switch(type) {
        case e_Op_DELETE:
            RowList.removeAt(RNum-1); //because this start from zero
            break;
        case e_Op_HIGHLIGHT:
            HighlightFlag = true;
            break;
        }
        int i = 0;
        ui->rtxtLogBrowser->clear();
        QString str = "";
        while(i != RowList.length()) {
            str = RowList.at(i);
            ui->rtxtLogBrowser->append(str);
            i++;
        }
        if(HighlightFlag) {
            this->ApplyFilter_Highlight(RowList.at(RNum-1));
        }
    }
}

bool MainWindow::Operate_COLUMN_Filter(QString format, WS_OperationType type)
{
    if(!format.isEmpty()) {
        QStringList RowList;
        RowList = QString(ui->rtxtLogBrowser->toPlainText()).split('\n');
        ui->rtxtLogBrowser->clear();
        int i = 0;
        QString str = "";
        while(i != RowList.length()) {
            str = RowList.at(i);
            switch(type) {
            case e_Op_DELETE:
                str = str.replace(str.split(" ").first(), "");
                ui->rtxtLogBrowser->append(str);
                break;
            case e_Op_HIGHLIGHT:
                ui->rtxtLogBrowser->append(str);
                this->ApplyFilter_Highlight(str);
                break;
            }
            i++;
        }
    }
}

bool MainWindow::Operate_TIME_Filter(QString format, WS_OperationType type)
{
    if(!format.isEmpty()) {
        QRegularExpression re(format);
        QRegularExpressionMatch match = re.match(ui->rtxtLogBrowser->toPlainText());
        if(match.hasMatch()) {
            switch (type) {
            case e_Op_DELETE:
                this->ApplyFilter_Delete(match.captured(0));
                break;
            case e_Op_HIGHLIGHT:
                this->ApplyFilter_Highlight(match.captured(0));
                break;
            default:
                break;
            }
        }
    }
}

bool MainWindow::Operate_DATE_Filter(QString format, WS_OperationType type)
{
    if(!format.isEmpty()) {
        QRegularExpression re(format);
        QRegularExpressionMatch match = re.match(ui->rtxtLogBrowser->toPlainText());
        if(match.hasMatch()) {
            switch (type) {
            case e_Op_DELETE:
                this->ApplyFilter_Delete(match.captured(0));
                break;
            case e_Op_HIGHLIGHT:
                this->ApplyFilter_Highlight(match.captured(0));
                break;
            default:
                break;
            }
        }
    }
}

bool MainWindow::Operate_STRING_Filter(QString format, WS_OperationType type)
{
    if(!format.isEmpty()) {
        QRegularExpression re(format, QRegularExpression::MultilineOption);
        QRegularExpressionMatch match = re.match(ui->rtxtLogBrowser->toPlainText());
        if(match.hasMatch()) {
            switch (type) {
            case e_Op_DELETE:
                this->ApplyFilter_Delete(match.captured(0));
                break;
            case e_Op_HIGHLIGHT:
                this->ApplyFilter_Highlight(match.captured(0));
                break;
            default:
                break;
            }
        }
    }
}

bool MainWindow::Operate_CUSTOM_Filter(QString format, WS_OperationType type)
{
    if(!format.isEmpty()) {
        QRegularExpression re(format, QRegularExpression::MultilineOption);
        QRegularExpressionMatch match = re.match(ui->rtxtLogBrowser->toPlainText());
        if(match.hasMatch()) {
            switch (type) {
            case e_Op_DELETE:
                this->ApplyFilter_Delete(match.captured(0));
                break;
            case e_Op_HIGHLIGHT:
                this->ApplyFilter_Highlight(match.captured(0));
                break;
            default:
                break;
            }
        }
    }
}

void MainWindow::on_actionFilter_triggered()
{
    DlgFilter *dlgFilter = NULL;
    dlgFilter = new DlgFilter(this);
    if(dlgFilter) {
        if(dlgFilter->init_FilterWS(&m_StoreWS, &m_StoreFilter)) {
            dlgFilter->setModal(true);
            dlgFilter->exec();
            if(dlgFilter->Accepted) {
                qDebug() << "Accepted dialog...";
                //clear early entry
                m_StoreFilter.empty();
                //store filters
                if(!dlgFilter->exit_FilterWS(&m_StoreFilter)) {
                    QMessageBox msg;
                    msg.setText("Error encountered while exiting filter window !!");
                    msg.setStandardButtons(QMessageBox::Ok);
                    msg.exec();
                }
                //apply filter
                this->ApplyFilter();
            }
        }
        qDebug() << "Deleted dialog...";
        delete dlgFilter;
        dlgFilter = NULL;
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = "";
    filename = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/", tr("Log Files (*.*)"));
    if(!filename.isEmpty()) {
        QFile myfile(filename);
        if(!myfile.open(QFile::ReadOnly | QFile::Text)) {
            qDebug() << "Cannot read file....";
            return;
        }
        QTextStream stream(&myfile);
        QApplication::setOverrideCursor(Qt::WaitCursor);
        ui->rtxtLogBrowser->setText(stream.readAll());
        QApplication::restoreOverrideCursor();
    }
}

void MainWindow::on_actionFind_triggered()
{
    DlgFind *FindMe = NULL;
    FindMe = new DlgFind(this);
    if(FindMe) {
        FindMe->setModal(true);
        FindMe->show();
    }
}

void MainWindow::on_actionExport_triggered()
{
    QString FileName = QFileDialog::getSaveFileName(this, "tr(Save As HTML)", "/home/", tr("HTML File (*.html)"));
    if(!FileName.isEmpty()) {
        QFile file1(FileName);
        if(!file1.open(QFile::WriteOnly | QFile::Text)) {
            qDebug() << "Cant write ...";
            return;
        }
        QTextStream writer(&file1);
        writer << ui->rtxtLogBrowser->toHtml();
        writer.flush();
        file1.close();
    }
}

void MainWindow::on_actionFormat_triggered()
{
    DlgFormat *dlgFrmt = NULL;
    dlgFrmt = new DlgFormat(this);
    if(dlgFrmt) {
        dlgFrmt->setModal(true);
        dlgFrmt->show();
    }
}

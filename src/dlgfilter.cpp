#include "dlgfilter.h"
#include "ui_dlgfilter.h"

DlgFilter::DlgFilter(QWidget *parent) : QDialog(parent),ui(new Ui::DlgFilter)
{
    ui->setupUi(this);
    ui->cmbbx_OpType->addItem("Select Type");
    ui->cmbbx_OpSubj->addItem("Select Type");
    m_FilterStorage.clear();
    m_StringListModel = new QStringListModel();
    m_FilterStringList.empty();
    ui->lstview_Filters->setModel(m_StringListModel);
    m_WS = NULL;
}

DlgFilter::~DlgFilter()
{
    delete ui;
}

void DlgFilter::AddToFilterFormat(WS_OperationStorage store, bool addToView, bool addToRecord)
{
    if(m_WS) {
        QString str1 = "";
        QString str2 = "";
        QString str3 = "";
        QString formatStr = "";
        str1 = m_WS->GetStr_OperationType(store.m_OpType);
        str2 = m_WS->GetStr_OperationSubject(store.m_OpSub);
        str3 = store.m_OpFormat;
        formatStr = str1 + "," + str2 + "," + str3;
        qDebug() << "Adding to filter format : " << formatStr << ", previous num = " << m_FilterStringList.count();
        m_FilterStringList.push_back(formatStr);
        if(addToView) {
            m_StringListModel->setStringList(m_FilterStringList);
        }
        if(addToRecord) {
            m_FilterStorage.append(store);
        }
    }
}

void DlgFilter::RemoveFilterFormat(int index, bool removeFromView, bool removeFromRecord)
{
    if(m_WS) {
        m_FilterStringList.removeAt(index);
        if(removeFromView) {
            m_StringListModel->setStringList(m_FilterStringList);
        }
        if(removeFromRecord) {
            m_FilterStorage.removeAt(index);
        }
    }
}

bool DlgFilter::init_FilterWS(ws_storage *ws_val, QList<WS_OperationStorage> *fltr)
{
    bool ret = false;

    if(ws_val) {
        if(ws_val->m_InitStatus) {
            qDebug() << "InitStatus - success";
            StringOperationType type;
            StringOperationSubject sub;
            for (int i = 0 ; i < WS_OP_TYPE_COUNT ; i++) {
                type = ws_val->m_StrOpType_Ref.at(i);
                ui->cmbbx_OpType->addItem(type.m_String);
            }
            for (int i = 0 ; i < WS_OP_SUBJ_COUNT ; i++) {
                sub = ws_val->m_StrOpSub_Ref.at(i);
                ui->cmbbx_OpSubj->addItem(sub.m_String);
            }
            qDebug() << "Items added to combo box";
            ui->cmbbx_OpType->setCurrentIndex(0);
            ui->cmbbx_OpSubj->setCurrentIndex(0);
            m_WS = ws_val;
            ret = true;
        }
        if((fltr) && (fltr->count() > 0)) {
            WS_OperationStorage store;
            qDebug() << "Clearing existing " << m_FilterStorage.count() <<"; Storing early filters...";
            m_FilterStorage.empty();
            for(int i = 0 ; i < fltr->count() ; i++) {
                store = fltr->at(i);
                this->AddToFilterFormat(store, true, true);
            }
        }
    }

    return ret;
}

bool DlgFilter::exit_FilterWS(QList<WS_OperationStorage> *fltr)
{
    bool ret = false;

    if(fltr){
        WS_OperationStorage store;
        fltr->clear();
        qDebug() << "On Exit -- Filter total count = " << m_FilterStorage.count();
        for(int i = 0 ; i < m_FilterStorage.count() ; i++) {
            store = m_FilterStorage.at(i);
            fltr->append(store);
        }
        ret = true;
    }

    return ret;
}

void DlgFilter::on_pshbtn_Apply_released()
{
    this->accept();
}

void DlgFilter::on_pshbtn_Cancel_released()
{
    this->reject();
}

void DlgFilter::on_cmbbx_OpSubj_currentIndexChanged(int index)
{
    if((index > 0) && (m_WS))
    {
        StringOperationSubject sub = m_WS->m_StrOpSub_Ref.at((index-1));
        ui->lbl_OpFormatStr->setText(sub.m_Format);
        ui->txt_OpFormat->setText(sub.m_Value);
    }
}

void DlgFilter::on_pshbtn_Add_released()
{
    if(m_WS) {
        WS_OperationStorage store;
        int CurIndex = -1;
        CurIndex = ui->cmbbx_OpType->currentIndex();
        store.m_OpType = m_WS->m_StrOpType_Ref.at(CurIndex-1).m_Type;
        CurIndex = ui->cmbbx_OpSubj->currentIndex();
        store.m_OpSub  = m_WS->m_StrOpSub_Ref.at(CurIndex-1).m_SubType;
        store.m_OpFormat = ui->txt_OpFormat->text();
        this->AddToFilterFormat(store, true, true);
    }
}

void DlgFilter::on_pshbtn_Remove_released()
{
    if(m_WS) {
        int CurIndex = -1;
        CurIndex = ui->lstview_Filters->currentIndex().row();
        this->RemoveFilterFormat(CurIndex, true, true);
    }
}

void DlgFilter::on_pshbtn_Save_released()
{
    if(m_WS) {
        QString filename = "";
        filename = QFileDialog::getSaveFileName(this, tr("Save Filter As"), "/home", tr("CSV File (*.csv)"));
        if(!filename.isEmpty()) {
            QFile file1(filename);
            if(!file1.open(QFile::WriteOnly | QFile::Text)) {
                qDebug() << "Cant write ...";
                return;
            }
            QTextStream writer(&file1);
            QString str1 = "";
            QString str2 = "";
            QString str3 = "";
            QString formatStr = "";
            for(int i = 0 ; i < m_FilterStorage.count() ; i++) {
                str1 = m_WS->GetStr_OperationType(m_FilterStorage.at(i).m_OpType);
                str2 = m_WS->GetStr_OperationSubject(m_FilterStorage.at(i).m_OpSub);
                str3 = m_FilterStorage.at(i).m_OpFormat;
                formatStr = str1 + "," + str2 + "," + str3 + "\n";
                writer << formatStr;
                writer.flush();
            }
            file1.close();
        }
    }
}

WS_OperationStorage DlgFilter::GetFillOperationFormat(QString unFormatted)
{
    WS_OperationStorage store;
    if(m_WS)
    {
        if(!unFormatted.isEmpty()) {
            QStringList tmpList;
            tmpList = unFormatted.split(',');
            if(tmpList.count() == 3) {
                store.m_OpType = m_WS->GetOpType_ByString(tmpList.at(0));
                store.m_OpSub  = m_WS->GetOpSub_ByString(tmpList.at(1));
                store.m_OpFormat = tmpList.at(2);
            }
        }
    }
    return store;
}

void DlgFilter::on_pshbtn_Load_released()
{
    if(m_WS) {
        QString filename = "";
        filename = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/", tr("Log Files (*.*)"));
        if(!filename.isEmpty()) {
            QFile myfile(filename);
            if(!myfile.open(QFile::ReadOnly | QFile::Text)) {
                qDebug() << "Cannot read file....";
                return;
            }
            QTextStream stream(&myfile);
            QStringList RowList;
            WS_OperationStorage store;
            QString filterFrmt = "";
            RowList = stream.readAll().split('\n');
            for(int i = 0 ; i < RowList.count() ; i++) {
                filterFrmt = RowList.at(i);
                if(!filterFrmt.isEmpty()) {
                    store = this->GetFillOperationFormat(filterFrmt);
                    this->AddToFilterFormat(store, true, true);
                }
            }
            myfile.close();
        }
    }
}

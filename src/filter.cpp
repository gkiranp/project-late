#include "filter.h"
#include "ui_filter.h"

filter::filter(QWidget *parent) : QDialog(parent), ui(new Ui::filter)
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

filter::~filter()
{
    delete ui;
}

void filter::AddToFilterFormat(WS_OperationStorage store, bool addToView, bool addToRecord)
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
        //m_FilterStringList.append(formatStr);
        m_FilterStringList.push_back(formatStr);
        if(addToView) {
            m_StringListModel->setStringList(m_FilterStringList);
        }
        if(addToRecord) {
            m_FilterStorage.append(store);
        }
    }
}

void filter::RemoveFilterFormat(int index, bool removeFromView, bool removeFromRecord)
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

bool filter::init_FilterWS(ws_storage *ws_val, QList<WS_OperationStorage> *fltr)
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

bool filter::exit_FilterWS(QList<WS_OperationStorage> *fltr)
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

void filter::on_pshbtn_Apply_released()
{
    this->accept();
}

void filter::on_pshbtn_Cancel_released()
{
    this->reject();
}

void filter::on_cmbbx_OpSubj_currentIndexChanged(int index)
{
    if((index > 0) && (m_WS))
    {
        StringOperationSubject sub = m_WS->m_StrOpSub_Ref.at((index-1));
        ui->lbl_OpFormatStr->setText(sub.m_Format);
        ui->txt_OpFormat->setText(sub.m_Value);
    }
}

void filter::on_pshbtn_Add_released()
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

void filter::on_pshbtn_Remove_released()
{
    if(m_WS) {
        int CurIndex = -1;
        CurIndex = ui->lstview_Filters->currentIndex().row();
        this->RemoveFilterFormat(CurIndex, true, true);
    }
}

void filter::on_pshbtn_Save_released()
{
    if(m_WS) {

    }
}

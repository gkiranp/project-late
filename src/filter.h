#ifndef FILTER_H
#define FILTER_H

#include <QDialog>
#include <QStringList>
#include <QStringListModel>
#include <QDebug>
#include "ws_storage.h"

namespace Ui {
class filter;
}

class filter : public QDialog
{
    Q_OBJECT
    
public:
    explicit filter(QWidget *parent = 0);
    ~filter();
    bool init_FilterWS(ws_storage *ws_val, QList<WS_OperationStorage> *fltr);
    bool exit_FilterWS(QList<WS_OperationStorage> *fltr);
    
public:
    void AddToFilterFormat(WS_OperationStorage store, bool addToView, bool addToRecord);
    void RemoveFilterFormat(int index, bool removeFromView, bool removeFromRecord);

private slots:
    void on_pshbtn_Apply_released();
    void on_pshbtn_Cancel_released();
    void on_cmbbx_OpSubj_currentIndexChanged(int index);
    void on_pshbtn_Add_released();
    void on_pshbtn_Remove_released();
    void on_pshbtn_Save_released();

private:
    Ui::filter *ui;

public:
    ws_storage *m_WS;

private:
    QList<WS_OperationStorage>  m_FilterStorage;
    QStringListModel            *m_StringListModel;
    QStringList                 m_FilterStringList;
};

#endif // FILTER_H

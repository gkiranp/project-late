#include "dlgfind.h"
#include "ui_dlgfind.h"

DlgFind::DlgFind(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgFind)
{
    ui->setupUi(this);
}

DlgFind::~DlgFind()
{
    delete ui;
}

void DlgFind::on_pshbtnFindIt_released()
{
    this->accept();
}

void DlgFind::on_pshbtnCancel_released()
{
    this->reject();
}

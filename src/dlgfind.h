#ifndef DLGFIND_H
#define DLGFIND_H

#include <QDialog>

namespace Ui {
class DlgFind;
}

class DlgFind : public QDialog
{
    Q_OBJECT

public:
    explicit DlgFind(QWidget *parent = 0);
    ~DlgFind();

private slots:
    void on_pshbtnFindIt_released();

    void on_pshbtnCancel_released();

private:
    Ui::DlgFind *ui;
};

#endif // DLGFIND_H

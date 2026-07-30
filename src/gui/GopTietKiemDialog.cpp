#include "GopTietKiemDialog.h"
#include "ui_GopTietKiemDialog.h"

GopTietKiemDialog::GopTietKiemDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GopTietKiemDialog)
{
    ui->setupUi(this);
}

GopTietKiemDialog::~GopTietKiemDialog()
{
    delete ui;
}

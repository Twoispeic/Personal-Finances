#include "themchitieudialog.h"
#include "ui_themchitieudialog.h"

ThemChiTieuDialog::ThemChiTieuDialog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::themchitieudialog)
{
    ui->setupUi(this);
}

ThemChiTieuDialog::~ThemChiTieuDialog()
{
    delete ui;
}
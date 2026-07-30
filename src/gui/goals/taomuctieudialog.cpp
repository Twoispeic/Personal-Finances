#include "taomuctieudialog.h"
#include "ui_taomuctieudialog.h"

taomuctieudialog::taomuctieudialog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::taomuctieudialog)
{
    ui->setupUi(this);
}

taomuctieudialog::~taomuctieudialog()
{
    delete ui;
}

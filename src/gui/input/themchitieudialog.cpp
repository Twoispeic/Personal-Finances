#include "themchitieudialog.h"
#include "ui_themchitieudialog.h"

themchitieudialog::themchitieudialog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::themchitieudialog)
{
    ui->setupUi(this);
}

themchitieudialog::~themchitieudialog()
{
    delete ui;
}

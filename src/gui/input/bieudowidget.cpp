#include "bieudowidget.h"
#include "ui_bieudowidget.h"

bieudowidget::bieudowidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::bieudowidget)
{
    ui->setupUi(this);
}

bieudowidget::~bieudowidget()
{
    delete ui;
}
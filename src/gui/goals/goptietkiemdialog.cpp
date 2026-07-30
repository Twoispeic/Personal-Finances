#include "goptietkiemdialog.h"
#include "ui_goptietkiemdialog.h"

goptietkiemdialog::goptietkiemdialog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::goptietkiemdialog)
{
    ui->setupUi(this);
}

goptietkiemdialog::~goptietkiemdialog()
{
    delete ui;
}

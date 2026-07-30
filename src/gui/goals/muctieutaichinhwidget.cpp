#include "muctieutaichinhwidget.h"
#include "ui_muctieutaichinhwidget.h"

muctieutaichinhwidget::muctieutaichinhwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::muctieutaichinhwidget)
{
    ui->setupUi(this);
}

muctieutaichinhwidget::~muctieutaichinhwidget()
{
    delete ui;
}

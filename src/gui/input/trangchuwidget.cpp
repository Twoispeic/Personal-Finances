#include "trangchuwidget.h"
#include "ui_trangchuwidget.h"

trangchuwidget::trangchuwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::trangchuwidget)
{
    ui->setupUi(this);
}

trangchuwidget::~trangchuwidget()
{
    delete ui;
}

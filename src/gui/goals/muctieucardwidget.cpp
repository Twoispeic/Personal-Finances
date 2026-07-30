#include "muctieucardwidget.h"
#include "ui_muctieucardwidget.h"

muctieucardwidget::muctieucardwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::muctieucardwidget)
{
    ui->setupUi(this);
}

muctieucardwidget::~muctieucardwidget()
{
    delete ui;
}

#include "quanlychitieuwidget.h"
#include "ui_quanlychitieuwidget.h"

quanlychitieuwidget::quanlychitieuwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::quanlychitieuwidget)
{
    ui->setupUi(this);
}

quanlychitieuwidget::~quanlychitieuwidget()
{
    delete ui;
}

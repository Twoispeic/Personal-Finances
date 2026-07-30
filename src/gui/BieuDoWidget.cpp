#include "BieuDoWidget.h"
#include "ui_BieuDoWidget.h"

BieuDoWidget::BieuDoWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BieuDoWidget)
{
    ui->setupUi(this);
}

BieuDoWidget::~BieuDoWidget()
{
    delete ui;
}

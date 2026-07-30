#include "MucTieuWidget.h"
#include "ui_MucTieuWidget.h"

MucTieuWidget::MucTieuWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MucTieuWidget)
{
    ui->setupUi(this);
}

MucTieuWidget::~MucTieuWidget()
{
    delete ui;
}

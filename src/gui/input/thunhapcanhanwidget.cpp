#include "thunhapcanhanwidget.h"
#include "ui_thunhapcanhanwidget.h"

thunhapcanhanwidget::thunhapcanhanwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::thunhapcanhanwidget)
{
    ui->setupUi(this);
}

thunhapcanhanwidget::~thunhapcanhanwidget()
{
    delete ui;
}

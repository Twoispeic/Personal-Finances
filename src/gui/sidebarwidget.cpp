#include "sidebarwidget.h"
#include "ui_sidebarwidget.h"

sidebarwidget::sidebarwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::sidebarwidget)
{
    ui->setupUi(this);
}

sidebarwidget::~sidebarwidget()
{
    delete ui;
}

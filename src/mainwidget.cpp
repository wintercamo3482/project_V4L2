// src/mainwidget.cpp
#include "mainwidget.h"
#include "ui_mainwidget.h"

Form::Form(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

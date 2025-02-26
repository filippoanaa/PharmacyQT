#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PharmacyQT.h"

class PharmacyQT : public QMainWindow
{
    Q_OBJECT

public:
    PharmacyQT(QWidget *parent = nullptr);
    ~PharmacyQT();

private:
    Ui::PharmacyQTClass ui;
};

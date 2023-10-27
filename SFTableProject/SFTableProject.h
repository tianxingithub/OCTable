#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SFTableProject.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SFTableProjectClass; };
QT_END_NAMESPACE

class SFTableProject : public QMainWindow
{
    Q_OBJECT

public:
    SFTableProject(QWidget *parent = nullptr);
    ~SFTableProject();
    void test();

private:
    Ui::SFTableProjectClass *ui;
};

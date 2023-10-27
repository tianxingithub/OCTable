#include "SFTableProject.h"
#include "OCTable.h"

SFTableProject::SFTableProject(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SFTableProjectClass())
{
    ui->setupUi(this);

}

SFTableProject::~SFTableProject()
{
    delete ui;
}

void SFTableProject::test()
{
	
}

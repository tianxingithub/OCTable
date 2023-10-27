#include "SFTableProject.h"
#include <QtWidgets/QApplication>
#include "OCTable.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SFTableProject w;

	OCTable* oc = new OCTable;

	w.setCentralWidget(oc);

	QStringList header;
	header << "A" << "B" << "C" << "D";
	oc->setHeader(header);

	QVector<QStringList> datas;
	QStringList d1; d1 << "a1" << "b1" << "c1" << "d1";
	QStringList d2; d2 << "a11" << "b12" << "c12" << "d12";
	QStringList d3; d3 << "a23" << "b23" << "c23" << "d23";
	datas << d1 << d2 << d3;
	QVector<int>v1; v1 << 0 << 2;
	QVector<int>v2; v2 << 1;
	oc->insertDatas(datas, v1);
	oc->insertDatas(datas);
	oc->insertDatas(datas, v2);

    w.show();
    return a.exec();
}

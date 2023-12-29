#include "SFTableProject.h"
#include <QtWidgets/QApplication>
#include "OCTable.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SFTableProject w;

	SF::OCTable* oc = new SF::OCTable;

	w.setCentralWidget(oc);

	QStringList header;
	header << "A" << "B" << "C" << "D";
	oc->setHeader(header);

	QVector<QStringList> data;
	QStringList d1; d1 << "a1" << "b1" << "c1" << "d1";
	QStringList d2; d2 << "a11" << "b12" << "c12" << "d12";
	QStringList d3; d3 << "a23" << "b23" << "c23" << "d23";
	data << d1 << d2 << d3;
	QVector<int>v1; v1 << 0 << 2;
	QVector<int>v2; v2 << 1;
	oc->insertData(data, v1);
	oc->insertData(data);
	oc->insertData(data, v2);

// 	QVector<int> vv1; vv1 << 1 << 2 << 3;
// 	QVector<int> vv2; vv2 = vv1; vv2 << 11 << 22 << 33;
// 	qDebug() << vv1;
// 	qDebug() << vv2;


    w.show();
    return a.exec();
}

#include "SFTableProject.h"
#include <QtWidgets/QApplication>
#include "OCTable.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//     SFTableProject w;

	SF::OCTable* table = new SF::OCTable;

// 	w.setCentralWidget(table);

	QStringList header;
	header << "A" << "B" << "C" << "D";
	table->setHeader(header);

	QVector<QStringList> data;
	QStringList d1; d1 << "a1" << "b1" << "c1" << "d1";
	QStringList d2; d2 << "a11" << "b12" << "c12" << "d12";
	QStringList d3; d3 << "a23" << "b23" << "c23" << "d23";
	data << d1 << d2 << d3;
	QVector<int>highlight1; highlight1 << 0 << 2;
	QVector<int>highlight2; highlight2 << 1;
	table->insertData(data, highlight1);

	d1 = QStringList(); d1 << "aa1" << "bb1" << "cc1" << "dd1";
	d2 = QStringList(); d2 << "aa11" << "bb12" << "cc12" << "dd12";
	d3 = QStringList(); d3 << "aa23" << "bb23" << "cc23" << "dd23";
	data = QVector<QStringList>();
	data << d1 << d2 << d3;
	table->insertData(data);

	data = QVector<QStringList>();
	QStringList d; d << "A" << "B" << "C" << "D";
	data << d;
	table->insertData(data);


	d1 = QStringList(); d1 << "aaa1" << "bbb1" << "ccc1" << "ddd1";
	d2 = QStringList(); d2 << "aaa11" << "bbb12" << "ccc12" << "ddd12";
	d3 = QStringList(); d3 << "aaa23" << "bbb23" << "ccc23" << "ddd23";
	data = QVector<QStringList>();
	data << d1 << d2 << d3;
	table->insertData(data, highlight2);


	table->setFixedSize(700, 400);
//     w.show();
	table->show();
    return a.exec();
}

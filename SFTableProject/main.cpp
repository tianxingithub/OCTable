#include "SFTableProject.h"
#include <QtWidgets/QApplication>
#include "OCTable.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SFTableProject w;

	SF::OCTable* table = new SF::OCTable;

	w.setCentralWidget(table);

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
	table->insertData(data);
	table->insertData(data, highlight2);


    w.show();
    return a.exec();
}

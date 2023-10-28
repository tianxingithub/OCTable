# OCTable
继承QTableWidget，可将有父子关系的数据显示成类似QTreeWdiget的效果

## 如何使用
OCTable* oc = new OCTable;

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

#include <QTableWidget>
#include <QDebug>
#include "OCTable.h"

OCTable::OCTable()
{
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	QString style = "QHeaderView::section { background-color: #f0f2f5}";

}

OCTable::~OCTable()
{

}

void OCTable::tableMsgSlot()
{
	int cur_row = this->currentRow();
	QPushButton* btn = qobject_cast<QPushButton*>(sender());
	auto btnText = btn->text();
	QString strNumber;
	for (QChar c : btnText)
	{
		if (c.isDigit())
		{
			strNumber.append(c);
		}
	}
	int index = strNumber.toInt() - 1;

	QVector<QStringList> datas = m_TableDatas[index];
	STATE state = m_DataStates[index];
	QVector<int> colorIndex = m_TableDatasColorIndex[index];

	switch (state)
	{
	case OPEN:
	{
		QString pic = QString("%1/images/table-close.png").arg(QApplication::applicationDirPath());
		btn->setIcon(QIcon(pic));
		m_DataStates[index] = CLOSE;
		removeDatas(datas);
		break;

	}
	case CLOSE:
	{
		QString pic = QString("%1/images/table-open.png").arg(QApplication::applicationDirPath());
		btn->setIcon(QIcon(pic));
		m_DataStates[index] = OPEN;
		btnAddDatas(datas, colorIndex, cur_row);
		break;
	}
	case ONLY:
		break;
	default:
		break;
	}
}


void OCTable::addHead(const int queryCount, QStringList data, QVector<int>colorIndex, bool only)
{
	QPushButton* btn = new QPushButton(this);
	connect(btn, &QPushButton::clicked, this, &OCTable::tableMsgSlot);
	auto r_n = this->rowCount();
	this->setRowCount(r_n + 1);

	this->setCellWidget(r_n, 0, btn);
	btn->setText(QString::number(queryCount));
	btn->setStyleSheet("background-color:transparent;");
	QString pic = QString("%1/images/table-open.png").arg(QApplication::applicationDirPath());
	if (only)
	{
		pic= QString("%1/images/table-only.png").arg(QApplication::applicationDirPath());
		m_DataStates << ONLY;
	}
	else
	{
		m_DataStates << OPEN;
	}
	btn->setIcon(QIcon(pic));

	for (int i = 0; i < data.size() && i < this->colorCount(); i++)
	{
		QTableWidgetItem* item = new QTableWidgetItem(data[i]);
		if (colorIndex.contains(i))
		{
			item->setBackground(QColor(230, 240, 250));
		}
		this->setItem(r_n, i + 1, item);
	}
}

void OCTable::autoAddDatas(QVector<QStringList> datas, QVector<int> colorIndx)
{
	auto tdatas = datas.mid(1, datas.size() - 1);
	for (auto data : tdatas)
	{
		auto r_n = this->rowCount();
		this->setRowCount(r_n + 1);

		for (int i = 0; i < data.size() && i < this->colorCount(); i++)
		{
			QTableWidgetItem* item = new QTableWidgetItem(data[i]);
			if (colorIndx.contains(i))
			{
				item->setBackground(QColor(230, 240, 250));
			}
			this->setItem(r_n, i + 1, item);
		}
	}
}

void OCTable::btnAddDatas(QVector<QStringList> datas, QVector<int> colorIndx, int insertRow)
{
	auto tdatas = datas.mid(1, datas.size() - 1);
	auto r_n = insertRow;

	for (auto data : tdatas)
	{
		r_n++;
		this->insertRow(r_n);

		for (int i = 0; i < data.size() && i < this->colorCount(); i++)
		{
			QTableWidgetItem* item = new QTableWidgetItem(data[i]);
			if (colorIndx.contains(i))
			{
				item->setBackground(QColor(230, 240, 250));
			}
			this->setItem(r_n, i + 1, item);
		}
		
	}
}

void OCTable::insertDatas(QVector<QStringList>datas, QVector<int>colorIndex)
{
	auto size = datas.size();
	int a = this->colorCount();
	if (size == 0) return;
	m_TableDatas << datas;
	m_TableDatasColorIndex << colorIndex;
	dataIndex++;

	auto headData = datas[0];
	bool only = (size == 1 ? true : false);
	addHead(dataIndex, headData, colorIndex, only);

	autoAddDatas(datas, colorIndex);
}


void OCTable::removeDatas(QVector<QStringList>datas)
{
	auto size = datas.size();
	if (size == 0 || size == 1) return;
	int cur_row = this->currentRow()+1;
	for (int i = 1; i < size; i++)
	{
		this->removeRow(cur_row);
	}

}

void OCTable::setHeader(QStringList header)
{
	this->setColumnCount(header.size()+1);
	QStringList tt;
	tt << u8"ÐòºÅ" << header;
	this->setHorizontalHeaderLabels(tt);
	this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


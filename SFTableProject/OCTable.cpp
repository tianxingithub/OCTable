#include <QTableWidget>
#include <QDebug>
#include "OCTable.h"

SF::OCTable::OCTable()
{
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	QString style = "QHeaderView::section { background-color: #f0f2f5}";

}

SF::OCTable::~OCTable()
{

}

void SF::OCTable::tableMsgSlot()
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
		hideData(datas);
		break;

	}
	case CLOSE:
	{
		QString pic = QString("%1/images/table-open.png").arg(QApplication::applicationDirPath());
		btn->setIcon(QIcon(pic));
		m_DataStates[index] = OPEN;
		showData(datas, colorIndex, cur_row);
		break;
	}
	case ONLY:
		break;
	default:
		break;
	}
}


void SF::OCTable::addHead(const int queryCount, QStringList head, QVector<int>colorIndex, bool only)
{
	QPushButton* btn = new QPushButton(this);
	connect(btn, &QPushButton::clicked, this, &SF::OCTable::tableMsgSlot);
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

	for (int i = 0; i < head.size() && i < this->colorCount(); i++)
	{
		QTableWidgetItem* item = new QTableWidgetItem(head[i]);
		if (colorIndex.contains(i))
		{
			item->setBackground(QColor(230, 240, 250));
		}
		this->setItem(r_n, i + 1, item);
	}
}

void SF::OCTable::fillData(QVector<QStringList> data, QVector<int> colorIndx)
{
	auto noHeadData = data.mid(1, data.size() - 1);
	for (QStringList data : noHeadData)
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

void SF::OCTable::showData(QVector<QStringList> data, QVector<int> colorIndx, int insertRow)
{
	auto tdatas = data.mid(1, data.size() - 1);
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

void SF::OCTable::insertData(QVector<QStringList>data, QVector<int>colorIndex)
{
	auto size = data.size();
	int a = this->colorCount();
	if (size == 0) return;
	m_TableDatas << data;
	m_TableDatasColorIndex << colorIndex;
	m_dataIndex++;

	QStringList head = data[0];
	bool only = (size == 1 ? true : false);

	addHead(m_dataIndex, head, colorIndex, only);

	fillData(data, colorIndex);
}


void SF::OCTable::hideData(QVector<QStringList>data)
{
	auto size = data.size();
	if (size == 0 || size == 1) return;
	int cur_row = this->currentRow()+1;
	for (int i = 1; i < size; i++)
	{
		this->removeRow(cur_row);
	}

}

void SF::OCTable::setHeader(QStringList header)
{
	m_header = header;
	this->setColumnCount(header.size()+1);
	QStringList head;
	head << u8"ÐòºÅ" << header;
	this->setHorizontalHeaderLabels(head);
	this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


#include <QDebug>
#include <QContextMenuEvent>
#include <QDateTime>
#include <QSettings>

#include "OCTable.h"

SF::OCTable::OCTable()
{
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setMouseTracking(true);
	// �����Զ��������Ĳ˵�
	this->setContextMenuPolicy(Qt::CustomContextMenu);

	m_menu = new QMenu();
	QString configpath = "./setting/defaultSaveDir.ini";
	m_settings = new QSettings(configpath, QSettings::IniFormat);

	QString style = "QHeaderView::section { background-color: #f0f2f5}";
	connect(this, &QTableWidget::itemClicked, this, &OCTable::itemEnteredSlot);

	QAction* table_clear = m_menu->addAction(u8"������");
	QAction* table_delete = m_menu->addAction(u8"���ɾ��");
	QAction* table_save = m_menu->addAction(u8"�������");
	QAction* table_open = m_menu->addAction(u8"ѡ�񱣴�Ŀ¼");

	connect(this, &QTableWidget::customContextMenuRequested, this, &OCTable::customContextMenuSlot);
	connect(this, &QTableWidget::itemClicked, this, &OCTable::rightClickSlot);

	connect(table_clear, &QAction::triggered, this, &OCTable::tableClearSlot);
	connect(table_delete, &QAction::triggered, this, &OCTable::tableDeleteSlot);
	connect(table_save, &QAction::triggered, this, &OCTable::tableSaveSlot);
	connect(table_open, &QAction::triggered, this, &OCTable::tableOpenSlot);


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


void SF::OCTable::itemEnteredSlot(QTableWidgetItem* item)
{
	if (item) {
		// ��ʾ��ʾ��Ϣ
		int item_row = item->row();
		int item_col = item->column();
		QString info = QString(u8"�У�%1\n�У�%2").arg(item_row).arg(item_col);
		QToolTip::showText(QCursor::pos(), info);
	}
}

void SF::OCTable::customContextMenuSlot()
{
	m_menu->exec(QCursor::pos());
}

void SF::OCTable::rightClickSlot(QTableWidgetItem* item)
{
	QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(QApplication::instance()->property("lastMouseEvent").value<QEvent*>());

	

}

void SF::OCTable::tableClearSlot()
{
	int rows = this->rowCount();
	for (int i = 0; i < rows; i++)
	{
		this->removeRow(0);
	}
	m_dataIndex = 0;
}

void SF::OCTable::tableDeleteSlot()
{
	auto item = this->selectedItems();
	for (int i = item.size()-1; i >=0 ; i--)
	{
		int row = item[i]->row();
		auto first = this->cellWidget(row, 0);		
		QPushButton* btn = qobject_cast<QPushButton*>(first);

		// ����ǲ�ѯ���ݵ�����
		if (btn)
		{
			auto index = btn->text().toInt();
			auto curQuery = m_TableDatas[index - 1];
			auto state = m_DataStates[index - 1];
			// ��ѯ�����Ƕ�����ʾ
			if (state == OPEN)
			{
				for (int i = 0; i < curQuery.size(); i++)
				{
					this->removeRow(row);
				}
// 				m_TableDatas.removeAt(index - 1);
				m_isExsit[index - 1] = false;
				m_TableDatas[index - 1] = QVector<QStringList>();
			}
			else
			{
				this->removeRow(row);
				m_TableDatas[index - 1] = QVector<QStringList>();
				m_isExsit[index - 1] = false;
			}
		}
		// ɾ���в�������
		else
		{
			// �ҵ�������
			int btnRow = -1;
			int btnText = -1;
			for (btnRow = row; btnRow >= 0; btnRow--)
			{
				auto first = this->cellWidget(btnRow, 0);
				QPushButton* btn = qobject_cast<QPushButton*>(first);
				if (btn)
				{
					btnText = btn->text().toInt();
					break;
				}
			}
			if (btnRow == -1 || btnText == -1)
			{
				return;
			}

			// �õ���ǰ���������е�λ��
			int dataIndex = row - btnRow;
			m_TableDatas[btnText - 1].removeAt(dataIndex);
			this->removeRow(row);

			// ������ɾ��ֻʣ��ѡ��
			if (m_TableDatas[btnText - 1].size() == 1)
			{
				this->removeRow(row - 1);
				m_TableDatas[btnText - 1] = QVector<QStringList>();
			}

		}
		
	}

}

void SF::OCTable::tableSaveSlot()
{
	if (this->rowCount() == 0)
	{
		QMessageBox::information(nullptr, u8"��ʾ", u8"δ��ȡ�����ݣ������ԣ�");
	}
	// ��ȡ��ǰ���ں�ʱ��
	QDateTime currentDateTime = QDateTime::currentDateTime();
	// ��ʽ�����ں�ʱ��Ϊ "yyyyMMdd_hhmmss" ����ʽ
	QString formattedDateTime = currentDateTime.toString("yyyyMMdd_hhmmss");

	QString defaultDir = QCoreApplication::applicationDirPath();
	auto sdir = m_settings->value("saveTableDir").toString();
	if (sdir == "")
	{
		defaultDir += u8"/CSV";
	}
	else
	{
		defaultDir = sdir;
	}

	QString filePath = defaultDir + u8"/������" + formattedDateTime + ".csv";

// 	QString filePath = "./csv/output.csv";
	QFile file(filePath);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) 
	{
		QTextStream stream(&file);
		// д�������
		for (int col = 0; col < this->columnCount(); ++col) 
		{
			stream << this->horizontalHeaderItem(col)->text();

			// ��ÿһ�е�ĩβ��Ӷ��ţ��������һ�У�
			if (col < this->columnCount() - 1) 
			{
				stream << ",";
			}
		}
		// ����
		stream << "\n";
		// ����ÿһ�к���
		for (int row = 0; row < this->rowCount(); ++row) 
		{
			for (int col = 0; col < this->columnCount(); ++col)
			{
				if (col == 0)
				{
					auto first = this->cellWidget(row, 0);
					QPushButton* btn = qobject_cast<QPushButton*>(first);
					if (btn)
					{
						QString data = btn->text();
						stream << data << ",";
					}
					else
					{
						stream << "" << ",";
					}
				}
				else
				{
					// ��ȡ��Ԫ������
					QTableWidgetItem* item = this->item(row, col);
					if (item) 
					{
						QString data = item->text();

						// ������д���ļ���ʹ�ö��ŷָ���CSV��ʽ��
						stream << data;

						// ��ÿһ�е�ĩβ��Ӷ��ţ��������һ�У�
						if (col < this->columnCount() - 1) {
							stream << ",";
						}
					}
				}
			}
			// ����
			stream << "\n";
		}

		file.close();
	}

	QString info = u8"�����ѱ�����" + filePath;
	QMessageBox::information(nullptr, u8"�ɹ�", info);
}

void SF::OCTable::tableOpenSlot()
{
	// �����ļ���ѡ��Ի���
	QString pathDir = QFileDialog::getExistingDirectory(nullptr, u8"ѡ��Ĭ�ϱ����ļ���", QDir::homePath());

	if (pathDir == NULL)
	{
		return;
	}
	m_settings->setValue("saveTableDir", pathDir);
	m_settings->sync();
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
	m_TableDatas.append(data);
	m_isExsit.append(true);
	m_TableDatasColorIndex.append(colorIndex);
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
	head << u8"���" << header;
	this->setHorizontalHeaderLabels(head);
	this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


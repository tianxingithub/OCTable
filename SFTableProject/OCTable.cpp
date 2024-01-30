#include <QDebug>
#include <QContextMenuEvent>
#include <QDateTime>
#include <QSettings>

#include "OCTable.h"

SF::OCTable::OCTable()
{
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setMouseTracking(true);
	// 启用自定义上下文菜单
	this->setContextMenuPolicy(Qt::CustomContextMenu);

	m_menu = new QMenu();
	QString configpath = "./setting/defaultSaveDir.ini";
	m_settings = new QSettings(configpath, QSettings::IniFormat);

	QString style = "QHeaderView::section { background-color: #f0f2f5}";
	connect(this, &QTableWidget::itemClicked, this, &OCTable::itemEnteredSlot);

	QAction* table_clear = m_menu->addAction(u8"结果清空");
	QAction* table_delete = m_menu->addAction(u8"结果删除");
	QAction* table_save = m_menu->addAction(u8"结果保存");
	QAction* table_open = m_menu->addAction(u8"选择保存目录");

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
		// 显示提示信息
		int item_row = item->row();
		int item_col = item->column();
		QString info = QString(u8"行：%1\n列：%2").arg(item_row).arg(item_col);
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

		// 如果是查询数据的首行
		if (btn)
		{
			auto index = btn->text().toInt();
			auto curQuery = m_TableDatas[index - 1];
			auto state = m_DataStates[index - 1];
			// 查询数据是多列显示
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
		// 删除行不是首行
		else
		{
			// 找到其首行
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

			// 得到当前行在数据中的位置
			int dataIndex = row - btnRow;
			m_TableDatas[btnText - 1].removeAt(dataIndex);
			this->removeRow(row);

			// 若数据删除只剩多选行
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
		QMessageBox::information(nullptr, u8"提示", u8"未获取到数据，请重试！");
	}
	// 获取当前日期和时间
	QDateTime currentDateTime = QDateTime::currentDateTime();
	// 格式化日期和时间为 "yyyyMMdd_hhmmss" 的形式
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

	QString filePath = defaultDir + u8"/表格测试" + formattedDateTime + ".csv";

// 	QString filePath = "./csv/output.csv";
	QFile file(filePath);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) 
	{
		QTextStream stream(&file);
		// 写入标题行
		for (int col = 0; col < this->columnCount(); ++col) 
		{
			stream << this->horizontalHeaderItem(col)->text();

			// 在每一列的末尾添加逗号（除了最后一列）
			if (col < this->columnCount() - 1) 
			{
				stream << ",";
			}
		}
		// 换行
		stream << "\n";
		// 遍历每一行和列
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
					// 获取单元格数据
					QTableWidgetItem* item = this->item(row, col);
					if (item) 
					{
						QString data = item->text();

						// 将数据写入文件，使用逗号分隔（CSV格式）
						stream << data;

						// 在每一列的末尾添加逗号（除了最后一列）
						if (col < this->columnCount() - 1) {
							stream << ",";
						}
					}
				}
			}
			// 换行
			stream << "\n";
		}

		file.close();
	}

	QString info = u8"数据已保存至" + filePath;
	QMessageBox::information(nullptr, u8"成功", info);
}

void SF::OCTable::tableOpenSlot()
{
	// 弹出文件夹选择对话框
	QString pathDir = QFileDialog::getExistingDirectory(nullptr, u8"选择默认保存文件夹", QDir::homePath());

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
	head << u8"序号" << header;
	this->setHorizontalHeaderLabels(head);
	this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


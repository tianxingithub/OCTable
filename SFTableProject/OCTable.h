#pragma once
#include <QtWidgets>

//! OCTable：OpenCloseTable
namespace SF {
	class OCTable : public QTableWidget
	{
	public:
		OCTable();
		~OCTable();
		enum STATE
		{
			OPEN = 1,
			CLOSE = 0,
			ONLY = 2
		};

	private:
		//! 查询结果索引
		int m_dataIndex{ 0 };

		//! 查询结果状态：展开、收缩、仅一个结果
		QVector<STATE> m_DataStates;

		//! 保存所有的查询结果
		QVector<QVector<QStringList>> m_TableDatas;

		//! 每次查询结果的高亮行
		QVector<QVector<int>> m_TableDatasColorIndex;

		//! 数据标题
		QStringList m_header;

	private:
		void tableMsgSlot();

	private:
		void addHead(const int queryCount, QStringList head, QVector<int>colorIndex, bool only);

		// 添加标题外的数据
		void fillData(QVector<QStringList> data, QVector<int> colorIndx);

		void showData(QVector<QStringList> data, QVector<int> colorIndx, int insertRow);

		void hideData(QVector<QStringList>data);


		//! 已开放的接口名称不要改动。
		//! 若要改动，保留当前接口名称，新增改动后的接口。
	public:

		//************************************
		// Method:    setHeader
		// FullName:  OCTable::setHeader
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: QStringList header
		//************************************
		void setHeader(QStringList header);


		//************************************
		// Method:    insertData
		// FullName:  OCTable::insertData
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: QVector<QStringList>data。插入的数据
		// Parameter: QVector<int>colorIndex。需要高亮显示的列索引，从0开始索引
		//************************************
		void insertData(QVector<QStringList>data, QVector<int>colorIndex = QVector<int>());


		// delCountIndex 删除Table第几次查询结果
		// void delData(int delCountIndex);
		//! 1. 得到删除查询结果的行号
		//! 2. 判断查询结果是展开还是收缩。展开先收缩起来，收缩则直接删除当前行。
		//! 3. 从m_TableDatas删除索引的查询结果。删除元素之前，确保索引值有效，避免越界访问 QVector::remove(removeIndex);
	};

}
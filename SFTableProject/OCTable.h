#pragma once
#include <QtWidgets>

class OCTable : public QTableWidget
{
public:
	OCTable ();
	~OCTable();
	enum STATE
	{
		OPEN = 1,
		CLOSE = 0,
		ONLY = 2
	};

private:
	int dataIndex{ 0 };
	QVector<STATE> m_DataStates;
	QVector<QVector<QStringList>> m_TableDatas;
	QVector<QVector<int>> m_TableDatasColorIndex;

private:
	void tableMsgSlot();

private:
	//************************************
	// Method:    addHead
	// FullName:  OCTable::addHead
	// Access:    private 
	// Returns:   void
	// Qualifier: 添加父节点
	// Parameter: const int queryCount
	// Parameter: QStringList data
	// Parameter: QVector<int>colorIndex
	// Parameter: bool only
	//************************************
	void addHead(const int queryCount, QStringList data, QVector<int>colorIndex, bool only);

	//************************************
	// Method:    autoAddDatas
	// FullName:  OCTable::autoAddDatas
	// Access:    private 
	// Returns:   void
	// Qualifier: 响应insertDatas
	// Parameter: QVector<QStringList> datas
	// Parameter: QVector<int> colorIndx
	//************************************
	void autoAddDatas(QVector<QStringList> datas, QVector<int> colorIndx);

	//************************************
	// Method:    btnAddDatas
	// FullName:  OCTable::btnAddDatas
	// Access:    private 
	// Returns:   void
	// Qualifier: 子节点的隐藏、显示响应
	// Parameter: QVector<QStringList> datas
	// Parameter: QVector<int> colorIndx
	// Parameter: int insertRow
	//************************************
	void btnAddDatas(QVector<QStringList> datas, QVector<int> colorIndx, int insertRow);

	//************************************
	// Method:    removeDatas
	// FullName:  OCTable::removeDatas
	// Access:    public 
	// Returns:   void
	// Qualifier: 隐藏子节点
	// Parameter: QVector<QStringList>datas
	//************************************
	void removeDatas(QVector<QStringList>datas);


public:

	//************************************
	// Method:    insertDatas
	// FullName:  OCTable::insertDatas
	// Access:    public 
	// Returns:   void
	// Qualifier: 往table里面写入数据，datas[0]为父节点，其余为子节点
	// Parameter: QVector<QStringList>datas
	// Parameter: QVector<int>colorIndex。高亮显示的列，索引从0开始
	//************************************
	void insertDatas(QVector<QStringList>datas, QVector<int>colorIndex = QVector<int>());


	//************************************
	// Method:    setHeader
	// FullName:  OCTable::setHeader
	// Access:    public 
	// Returns:   void
	// Qualifier: 设置table的标题
	// Parameter: QStringList header
	//************************************
	void setHeader(QStringList header);
};


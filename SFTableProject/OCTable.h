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
	// Qualifier: ��Ӹ��ڵ�
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
	// Qualifier: ��ӦinsertDatas
	// Parameter: QVector<QStringList> datas
	// Parameter: QVector<int> colorIndx
	//************************************
	void autoAddDatas(QVector<QStringList> datas, QVector<int> colorIndx);

	//************************************
	// Method:    btnAddDatas
	// FullName:  OCTable::btnAddDatas
	// Access:    private 
	// Returns:   void
	// Qualifier: �ӽڵ�����ء���ʾ��Ӧ
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
	// Qualifier: �����ӽڵ�
	// Parameter: QVector<QStringList>datas
	//************************************
	void removeDatas(QVector<QStringList>datas);


public:

	//************************************
	// Method:    insertDatas
	// FullName:  OCTable::insertDatas
	// Access:    public 
	// Returns:   void
	// Qualifier: ��table����д�����ݣ�datas[0]Ϊ���ڵ㣬����Ϊ�ӽڵ�
	// Parameter: QVector<QStringList>datas
	// Parameter: QVector<int>colorIndex��������ʾ���У�������0��ʼ
	//************************************
	void insertDatas(QVector<QStringList>datas, QVector<int>colorIndex = QVector<int>());


	//************************************
	// Method:    setHeader
	// FullName:  OCTable::setHeader
	// Access:    public 
	// Returns:   void
	// Qualifier: ����table�ı���
	// Parameter: QStringList header
	//************************************
	void setHeader(QStringList header);
};


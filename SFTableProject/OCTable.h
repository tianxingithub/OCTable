#pragma once
#include <QtWidgets>
#include <QMenu>

class QSettings;
//! OCTable��OpenCloseTable
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
		//! ��ѯ�������
		int m_dataIndex{ 0 };

		//! ��ѯ���״̬��չ������������һ�����
		QVector<STATE> m_DataStates;

		//! ��ѯ�����״̬���Ƿ�ɾ��
		QVector<bool> m_isExsit;

		//! �������еĲ�ѯ���
		QVector<QVector<QStringList>> m_TableDatas;

		//! ÿ�β�ѯ����ĸ�����
		QVector<QVector<int>> m_TableDatasColorIndex;

		//! ���ݱ���
		QStringList m_header;

		//! �Ҽ��˵�
		QMenu* m_menu;

		//! Ĭ�ϱ����ļ���
		QSettings* m_settings;

	private:
		void tableMsgSlot();

		// �������itemʱ��ʾ��Ϣ
		void itemEnteredSlot(QTableWidgetItem *item);

		// �Ҽ���Ӧ
		void customContextMenuSlot();
		void rightClickSlot(QTableWidgetItem* item);

		void tableClearSlot();
		void tableDeleteSlot();
		void tableSaveSlot();
		void tableOpenSlot();
	private:
		void addHead(const int queryCount, QStringList head, QVector<int>colorIndex, bool only);

		// ��ӱ����������
		void fillData(QVector<QStringList> data, QVector<int> colorIndx);

		void showData(QVector<QStringList> data, QVector<int> colorIndx, int insertRow);

		void hideData(QVector<QStringList>data);


		//! �ѿ��ŵĽӿ����Ʋ�Ҫ�Ķ���
		//! ��Ҫ�Ķ���������ǰ�ӿ����ƣ������Ķ���Ľӿڡ�
		//! �����ֱ�Ӻ�������
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
		// Parameter: QVector<QStringList>data�����������
		// Parameter: QVector<int>colorIndex����Ҫ������ʾ������������0��ʼ����
		//************************************
		void insertData(QVector<QStringList>data, QVector<int>colorIndex = QVector<int>());


		// delCountIndex ɾ��Table�ڼ��β�ѯ���
		// void delData(int delCountIndex);
		//! 1. �õ�ɾ����ѯ������к�
		//! 2. �жϲ�ѯ�����չ������������չ��������������������ֱ��ɾ����ǰ�С�
		//! 3. ��m_TableDatasɾ�������Ĳ�ѯ�����ɾ��Ԫ��֮ǰ��ȷ������ֵ��Ч������Խ����� QVector::remove(removeIndex);
	};

}
#pragma once
#include <QAxObject>
class CWordOperation
{
private:
	CWordOperation();
public:
	static CWordOperation* m_singletion;
	static CWordOperation* GetInstance();
	~CWordOperation();
	//////////////////////////////////////////////////////////////////////////
	//����word ����
	QAxObject	*m_pWord;      //ָ������WordӦ�ó���  
	QAxObject	*m_pWorkDocuments;  //ָ���ĵ���,Word�кܶ��ĵ�  
	QAxObject	*m_pWorkDocument;   //ָ��m_sFile��Ӧ���ĵ�������Ҫ�������ĵ�
	bool		m_bIsOpen;
public:
	bool Open(QString const&  sFile, bool bVisible=false);

	//���� ���ر�
	void save(QString const&  sSavePath="");

	//д�ĵ� 
	//ͨ��word ��ǩ Ѱ�Ҳ�д������
	bool writeText(QString sLabel, QString sText);
};


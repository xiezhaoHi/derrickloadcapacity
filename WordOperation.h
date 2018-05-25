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
	//导出word 报表
	QAxObject	*m_pWord;      //指向整个Word应用程序  
	QAxObject	*m_pWorkDocuments;  //指向文档集,Word有很多文档  
	QAxObject	*m_pWorkDocument;   //指向m_sFile对应的文档，就是要操作的文档
	bool		m_bIsOpen;
public:
	bool Open(QString const&  sFile, bool bVisible=false);

	//保存 并关闭
	void save(QString const&  sSavePath="");

	//写文档 
	//通过word 标签 寻找并写入数据
	bool writeText(QString sLabel, QString sText);
};


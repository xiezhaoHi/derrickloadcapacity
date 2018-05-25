#include "WordOperation.h"
#include <mutex>
#include <string>
#include <windows.h>  
std::mutex gmutex;//声明互斥锁m
CWordOperation* CWordOperation::m_singletion = nullptr;
CWordOperation* CWordOperation::GetInstance()
{
	if (m_singletion == nullptr)
	{
		gmutex.lock();
		if (m_singletion == nullptr)
		{
			m_singletion = new CWordOperation();
		}
		gmutex.unlock();
		
	}
	return m_singletion;
}
CWordOperation::CWordOperation()
{
	HRESULT r = OleInitialize(0);
	if (r != S_OK && r != S_FALSE)
	{
		//qWarning("Qt:初始化Ole失败（error %x）", (unsigned int)r);
	}
	m_pWord=nullptr;      //
	m_pWorkDocuments = nullptr;
	m_pWorkDocument = nullptr;
}


CWordOperation::~CWordOperation()
{
	OleUninitialize();
}

bool CWordOperation::Open(QString const& sFile, bool bVisible)
{
	//新建一个word应用程序  
	m_pWord = new QAxObject();
	bool bFlag = m_pWord->setControl("word.Application");
	if (!bFlag)
	{
		return false;
	}
	m_pWord->setProperty("Visible", bVisible);
	//获取所有的工作文档  
	QAxObject *document = m_pWord->querySubObject("Documents");
	if (!document)
	{
		return false;
	}
	//以文件template.dot为模版新建一个文档  
	document->dynamicCall("Add(QString)", sFile);
	//获取当前激活的文档  
	m_pWorkDocument = m_pWord->querySubObject("ActiveDocument");
	if (m_pWorkDocument)
		m_bIsOpen = true;
	else
		m_bIsOpen = false;

	return m_bIsOpen;
}

void CWordOperation::save(QString const&  sSavePath)
{
	if (m_bIsOpen && m_pWorkDocument)
	{
		//绝对路径非空
		if (sSavePath.isEmpty()) {
			m_pWorkDocument->dynamicCall("Save()");
		}
		else {
			m_pWorkDocument->dynamicCall("SaveAs(QString)", sSavePath);
		}
		if (m_pWord) {
			m_pWord->setProperty("DisplayAlerts", true);
		}
		if (m_pWorkDocument) {
			m_pWorkDocument->dynamicCall("Close(bool)", true);
		}
		if (m_pWord) {
			m_pWord->dynamicCall("Quit()");
		}

		if (m_pWorkDocument)
		{
			delete m_pWorkDocument;
		}

		if (m_pWorkDocuments)
		{
			delete m_pWorkDocuments;
		}
		if (m_pWord)
		{
			delete m_pWord;
		}
		m_pWorkDocument = NULL;
		m_pWorkDocuments = NULL;
		m_pWord = NULL;

		m_bIsOpen = false;
		
	}
	
}

bool CWordOperation::writeText(QString sLabel, QString sText)
{
	if (!m_pWorkDocument) {
		return false;
	}
	//获取文档中名字为sLabel的标签  
	QAxObject *pBookmark = m_pWorkDocument->querySubObject("Bookmarks(QString)", sLabel);
	if (pBookmark)
	{
		pBookmark->dynamicCall("Select(void)");
		pBookmark->querySubObject("Range")->setProperty("Text", sText);
		delete pBookmark;
	}
	return true;
}
#include "WordOperation.h"
#include <mutex>
#include <string>
#include <windows.h>  
std::mutex gmutex;//����������m
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
		//qWarning("Qt:��ʼ��Oleʧ�ܣ�error %x��", (unsigned int)r);
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
	//�½�һ��wordӦ�ó���  
	m_pWord = new QAxObject();
	bool bFlag = m_pWord->setControl("word.Application");
	if (!bFlag)
	{
		return false;
	}
	m_pWord->setProperty("Visible", bVisible);
	//��ȡ���еĹ����ĵ�  
	QAxObject *document = m_pWord->querySubObject("Documents");
	if (!document)
	{
		return false;
	}
	//���ļ�template.dotΪģ���½�һ���ĵ�  
	document->dynamicCall("Add(QString)", sFile);
	//��ȡ��ǰ������ĵ�  
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
		//����·���ǿ�
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
	//��ȡ�ĵ�������ΪsLabel�ı�ǩ  
	QAxObject *pBookmark = m_pWorkDocument->querySubObject("Bookmarks(QString)", sLabel);
	if (pBookmark)
	{
		pBookmark->dynamicCall("Select(void)");
		pBookmark->querySubObject("Range")->setProperty("Text", sText);
		delete pBookmark;
	}
	return true;
}
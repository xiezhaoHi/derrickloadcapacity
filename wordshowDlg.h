#pragma once

#include <QWidget>
#include "ui_wordmode.h"
typedef struct  gWordJssjLabelsNamesData
{
	QString  m_strScsj1; //"ʵ������1",
	QString  m_strScsj2; //"ʵ������2",
}gWordJssjLabelsNamesData;
class wordshowDlg : public QDialog
{
	Q_OBJECT

public:
	wordshowDlg(QDialog *parent = Q_NULLPTR);
	~wordshowDlg();

public slots:
	void on_click_pushButton_up();
	void on_click_pushButton_next();
	void on_click_pushButton_print();
	void showEvent(QShowEvent *);
	void resizeEvent(QResizeEvent *);
	bool eventFilter(QObject *, QEvent *);
	//////////////////////////////////////////////////////////////////////////
	//����
public:

	//��ʼ�� �������õ�ֵ
	void InitgWordJssjLabelsNamesData(gWordJssjLabelsNamesData const&);
	//���������ݵ�word��
	void WriteDataToWord();

	//��ʼ��word ��ǩ ��
	void InitWordLabel();
	//��ʼ����һ��ǩ
	void InitgWordLabelsNamesOne();
	//��ʼ�����ǩ
	void InitgWordLabelsNamesTwo();

	//��ʼ����һ��ǩ
	void InitgWordConfigNamesOne();
	//��ʼ�����ǩ
	void InitgWordConfigNamesTwo();



	//�������ļ���ȡֵ ����ʼ���ؼ�
	void InitConfigCtrl();
	//�ӿؼ���ȡֵ �����������ļ�
	void SaveConfig();
	//////////////////////////////////////////////////////////////////////////
	//����
public:
	gWordJssjLabelsNamesData	m_strJssjData;//��������
	QString m_strConfigPath; //�����ļ�·��
	QString m_strWordPath;   //wordģ��·��
	//������ word ��ǩ��
	QMap<QLineEdit*, QString>	m_mapWordLabel;
	//�����ļ��е�key ���ڵĿؼ�����
	QMap<QString, QLineEdit*>    m_mapConfigLabel;


	QMap<QComboBox*, QString>	m_mapWordCombox;
	//�����ļ��е�key ���ڵĿؼ�����
	QMap<QString, QComboBox*>	m_mapConfigCombox;

	//��ѡ���������
	QMap<QRadioButton*, QString>  m_mapWordRadio;
	QMap<QString, QRadioButton*>  m_mapConfigRadio;
private:
	Ui::wordPrint ui;
};

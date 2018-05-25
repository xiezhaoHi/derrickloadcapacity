#pragma once

#include <QWidget>
#include "ui_wordmode.h"
typedef struct  gWordJssjLabelsNamesData
{
	QString  m_strScsj1; //"实测数据1",
	QString  m_strScsj2; //"实测数据2",
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
	//方法
public:

	//初始化 计算所得的值
	void InitgWordJssjLabelsNamesData(gWordJssjLabelsNamesData const&);
	//填充计算数据到word上
	void WriteDataToWord();

	//初始化word 标签 绑定
	void InitWordLabel();
	//初始化单一标签
	void InitgWordLabelsNamesOne();
	//初始化多标签
	void InitgWordLabelsNamesTwo();

	//初始化单一标签
	void InitgWordConfigNamesOne();
	//初始化多标签
	void InitgWordConfigNamesTwo();



	//从配置文件读取值 并初始化控件
	void InitConfigCtrl();
	//从控件获取值 并更改配置文件
	void SaveConfig();
	//////////////////////////////////////////////////////////////////////////
	//变量
public:
	gWordJssjLabelsNamesData	m_strJssjData;//计算数据
	QString m_strConfigPath; //配置文件路径
	QString m_strWordPath;   //word模板路径
	//变量绑定 word 标签绑定
	QMap<QLineEdit*, QString>	m_mapWordLabel;
	//配置文件中的key 对于的控件变量
	QMap<QString, QLineEdit*>    m_mapConfigLabel;


	QMap<QComboBox*, QString>	m_mapWordCombox;
	//配置文件中的key 对于的控件变量
	QMap<QString, QComboBox*>	m_mapConfigCombox;

	//单选框相关配置
	QMap<QRadioButton*, QString>  m_mapWordRadio;
	QMap<QString, QRadioButton*>  m_mapConfigRadio;
private:
	Ui::wordPrint ui;
};

#include "wordshowDlg.h"
#include <QMenuBar>
#include <QAction>
#include "gEnum.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QString>
#include <QSettings>
#include "WordOperation.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollBar>
// #if _MSC_VER >= 1600
// #pragma execution_character_set("utf-8") 
// #endif
wordshowDlg::~wordshowDlg()
{
}

wordshowDlg::wordshowDlg(QDialog *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	//从配置文件初始化控件值
	m_strConfigPath = qApp->applicationDirPath()+QString("\\config\\configData.ini");
	m_strWordPath = qApp->applicationDirPath() + QStringLiteral("\\wordTemplate\\导出模板.doc");
	//初始化控件绑定
	InitWordLabel();

	//设为首页
	ui.centerPage->setCurrentIndex(0);

	//绑定 按钮 事件
	//上下翻页
	connect(ui.pushButton_up, &QPushButton::clicked, this, &wordshowDlg::on_click_pushButton_up);
	connect(ui.pushButton_next, &QPushButton::clicked, this, &wordshowDlg::on_click_pushButton_next);
	//生成报表
	connect(ui.pushButton_print, &QPushButton::clicked, this, &wordshowDlg::on_click_pushButton_print);
	
	ui.gWordLabelsNamesTwo_fzhlzc_3->installEventFilter(this);
	
	//初始化配置项
	InitConfigCtrl();
}

//从配置文件读取值 并初始化控件
void wordshowDlg::InitConfigCtrl()
{
	
	QSettings setting(m_strConfigPath, QSettings::IniFormat);//读配置文件
	//libel 标签
	setting.beginGroup("gWordLabelsNamesOne");
	QLineEdit* editTemp = nullptr;
	QMap<QString, QLineEdit*>::const_iterator iterLabel;
	for (iterLabel = m_mapConfigLabel.constBegin();
		iterLabel != m_mapConfigLabel.constEnd(); ++iterLabel) {
		editTemp = iterLabel.value();
		if (editTemp == nullptr)
		{
			continue;
		}
		editTemp->setText(setting.value(iterLabel.key(), "").toString());
	}
	setting.endGroup();
	//combox标签
	int comboxIndex = 0;
	int radioIndex = 0; //0不勾选 1勾选
	QComboBox* comboxTemp = nullptr;
	setting.beginGroup("gWordLabelsNamesTwo");
	QMap<QString, QComboBox*>::const_iterator iterCombox;
	for (iterCombox = m_mapConfigCombox.constBegin();
		iterCombox != m_mapConfigCombox.constEnd(); ++iterCombox) {
		comboxTemp = iterCombox.value();
		comboxIndex = setting.value(iterCombox.key(), 0).toInt();
		if (comboxTemp == nullptr)
		{
			continue;
		}
		for (int index = combox_one ; index < combox_max; ++index)
		{
			comboxTemp->addItem(gcomboxIndexs[index]);
		}
		
		comboxTemp->setCurrentIndex(comboxIndex>combox_max?0: comboxIndex);
	}

	QMap<QString, QRadioButton*>::const_iterator iterRadio;
	for (iterRadio = m_mapConfigRadio.constBegin();
		iterRadio != m_mapConfigRadio.constEnd(); ++iterRadio)
	{
		radioIndex = setting.value(iterRadio.key(), 0).toInt();
		iterRadio.value()->setChecked(radioIndex);
	}
	

	setting.endGroup();
}
//从控件获取值 并更改配置文件
void wordshowDlg::SaveConfig()
{
	QSettings setting(m_strConfigPath, QSettings::IniFormat);//读配置文件
															 //libel 标签
	setting.beginGroup("gWordLabelsNamesOne");
	QLineEdit* editTemp = nullptr;
	QMap<QString, QLineEdit*>::const_iterator iterLabel;
	for (iterLabel = m_mapConfigLabel.constBegin();
		iterLabel != m_mapConfigLabel.constEnd(); ++iterLabel) {
		editTemp = iterLabel.value();
		if (editTemp == nullptr)
		{
			continue;
		}
		setting.setValue(iterLabel.key(), editTemp->text());
	}

	//setting.setValue("test", QStringLiteral("编码"));

	setting.endGroup();
	//combox标签
	int comboxIndex = 0, radioIndex=0;
	QComboBox* comboxTemp = nullptr;
	setting.beginGroup("gWordLabelsNamesTwo");
	QMap<QString, QComboBox*>::const_iterator iterCombox;
	for (iterCombox = m_mapConfigCombox.constBegin();
		iterCombox != m_mapConfigCombox.constEnd(); ++iterCombox) {
		comboxTemp = iterCombox.value();
		
		if (comboxTemp == nullptr)
		{
			continue;
		}
		comboxIndex = comboxTemp->currentIndex();
		
		setting.setValue(iterCombox.key(),QString::number(comboxIndex > 0 ? comboxIndex : 0));
	}
	QMap<QString, QRadioButton*>::const_iterator iterRadio;
	for (iterRadio = m_mapConfigRadio.constBegin();
		iterRadio != m_mapConfigRadio.constEnd(); ++iterRadio)
	{
		setting.setValue(iterRadio.key(), QString::number(iterRadio.value()->isChecked()?1:0));
	}
	setting.endGroup();
}

//完成打印 并保存现有的数据设置
void wordshowDlg::on_click_pushButton_print()
{
	CWordOperation::GetInstance()->Open(m_strWordPath);
	//单标签
	QMap<QLineEdit*, QString>::const_iterator iterLabel;
	for (iterLabel = m_mapWordLabel.constBegin();
		iterLabel != m_mapWordLabel.constEnd(); ++iterLabel) {
		CWordOperation::GetInstance()->writeText(iterLabel.value(),iterLabel.key()->text());
	}
	//"测点布置1"
	CWordOperation::GetInstance()->writeText(QString::fromLocal8Bit(gWordJssjLabelsNames[gWordJssjLabelsNames_cdbz1]), ui.gWordLabelsNamesTwo_cpfx_1->text());
	//"测点布置2"
	CWordOperation::GetInstance()->writeText(QString::fromLocal8Bit(gWordJssjLabelsNames[gWordJssjLabelsNames_cdbz2]), ui.gWordLabelsNamesTwo_cpfx_10->text());

	//报告编号2: 
	CWordOperation::GetInstance()->writeText(QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_bgbh2]), ui.gWordLabelsNamesOne_bgbh->text());
	//页脚
	CWordOperation::GetInstance()->writeText(QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_ym]), ui.gWordLabelsNamesOne_bgbh->text());

	//多标签
	QMap<QComboBox*, QString>::const_iterator iterCombox;
	for (iterCombox = m_mapWordCombox.constBegin();
		iterCombox != m_mapWordCombox.constEnd(); ++iterCombox) {
		QString temp = iterCombox.key()->currentText();
		CWordOperation::GetInstance()->writeText(iterCombox.value(), temp);
	}
	QMap<QRadioButton*, QString>::const_iterator iterRadio;
	for (iterRadio = m_mapWordRadio.constBegin();
		iterRadio != m_mapWordRadio.constEnd(); ++iterRadio) {
		CWordOperation::GetInstance()->writeText(iterRadio.value(), iterRadio.key()->isChecked()? gcomboxIndexs[combox_two]:"");
	}

	//计算数据填充
	WriteDataToWord();


	QString file_name = QFileDialog::getSaveFileName(NULL, QStringLiteral("导出报表"), ".", "*.doc");
	if (!file_name.isEmpty()) //选择导出
	{
		CWordOperation::GetInstance()->save(file_name);
	}

	//打印完成 保存 更新
	SaveConfig();
	QMessageBox box;
	box.setText(QStringLiteral("生成报表操作完成!"));
	box.setWindowTitle(QStringLiteral("提示"));
	box.exec();
}
bool wordshowDlg::eventFilter(QObject * target, QEvent * event)
{
	QRect ret;
	if (target == ui.gWordLabelsNamesTwo_fzhlzc_3)
	{
		ret = ui.gWordLabelsNamesTwo_fzhlzc_3->geometry();
		
	}
	return QDialog::eventFilter(target, event);
}
void wordshowDlg::showEvent(QShowEvent *)
{
	//QRect ret = ui.gWordLabelsNamesTwo_fzhlzc_3->geometry();
}
void wordshowDlg::resizeEvent(QResizeEvent *)
{
	//QRect ret = ui.gWordLabelsNamesTwo_fzhlzc_3->geometry();
}

//向上
void wordshowDlg::on_click_pushButton_next()
{
	int curIndex = ui.centerPage->currentIndex() + 1;
	if (curIndex != ui.centerPage->count())
	{
		ui.centerPage->setCurrentIndex(curIndex);
	}
	else
		ui.centerPage->setCurrentIndex(0);
	ui.scrollArea->verticalScrollBar()->setSliderPosition(0);
}

//向下
void wordshowDlg::on_click_pushButton_up()
{
	int curIndex = ui.centerPage->currentIndex()-1;
	if (curIndex != -1)
	{
		ui.centerPage->setCurrentIndex(curIndex);
	}
	else
		ui.centerPage->setCurrentIndex(ui.centerPage->count()-1);
	ui.scrollArea->verticalScrollBar()->setSliderPosition(0);
}



//初始化 计算所得的值
void wordshowDlg::InitgWordJssjLabelsNamesData(gWordJssjLabelsNamesData const& data)
{
	m_strJssjData = data;
}

//填充计算数据到word上
void wordshowDlg::WriteDataToWord() 
{
	//标签-实测数据1
	CWordOperation::GetInstance()->writeText(gWordJssjLabelsNames[gWordJssjLabelsNames_scsj1], m_strJssjData.m_strScsj1);
	//标签-实测数据2
	CWordOperation::GetInstance()->writeText(gWordJssjLabelsNames[gWordJssjLabelsNames_scsj2], m_strJssjData.m_strScsj2);
}

//初始化word 标签 绑定
void wordshowDlg::InitWordLabel()
{
	//单标签和多标签 说明:多标签-同类的标题内容下 有多个相似的combox控件

	//单标签
	InitgWordLabelsNamesOne();
	
	//多标签
	InitgWordLabelsNamesTwo();

	//绑定配置文件中key 与变量 -单标签情况
	InitgWordConfigNamesOne();

	//绑定配置文件中key 与变量 -多标签情况
	InitgWordConfigNamesTwo();
}				

//初始化单一标签
void wordshowDlg::InitgWordLabelsNamesOne()
{
	m_mapWordLabel[ui.gWordLabelsNamesOne_bgbh] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_bgbh]);
	m_mapWordLabel[ui.gWordLabelsNamesOne_wtf] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_wtf]);
	m_mapWordLabel[ui.gWordLabelsNamesOne_ypmc] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_ypmc]);
	m_mapWordLabel[ui.gWordLabelsNamesOne_ggxh] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_ggxh]);
	m_mapWordLabel[ui.gWordLabelsNamesOne_cplb] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_cplb]);
	//m_mapWordLabel[ui.gWordLabelsNamesOne_bgbh2] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_bgbh2]);
	m_mapWordLabel[ui.gWordLabelsNamesOne_ypmc2] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_ypmc2]);
	m_mapWordLabel[ui.gWordLabelsNamesOne_ggxh2] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_ggxh2]);
	m_mapWordLabel[ui.gWordLabelsNamesOne_wtfdz] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_wtfdz]);
	m_mapWordLabel[ui.gWordLabelsNamesOne_sb] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_sb]);
	m_mapWordLabel[ui.gWordLabelsNamesOne_xsdw] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_xsdw]);
	m_mapWordLabel[ui.gWordLabelsNamesOne_scrq] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_scrq]);
	m_mapWordLabel[ui.gWordLabelsNamesOne_sydw] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_sydw]);
	m_mapWordLabel[ui.gWordLabelsNamesOne_ccbh] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_ccbh]);
	m_mapWordLabel[ui.gWordLabelsNamesOne_sydd] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_sydd]);
	m_mapWordLabel[ui.gWordLabelsNamesOne_ypsl] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_ypsl]);
	m_mapWordLabel[ui.gWordLabelsNamesOne_ypztms] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_ypztms]);
	m_mapWordLabel[ui.gWordLabelsNamesOne_ypbsfs] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_ypbsfs]);
	m_mapWordLabel[ui.gWordLabelsNamesOne_hjtj] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_hjtj]);
	m_mapWordLabel[ui.gWordLabelsNamesOne_ypbh] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_ypbh]);
	m_mapWordLabel[ui.gWordLabelsNamesOne_dyrq] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_dyrq]);
	m_mapWordLabel[ui.gWordLabelsNamesOne_wtflxr] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_wtflxr]);
	m_mapWordLabel[ui.gWordLabelsNamesOne_cprq] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_cprq]);
	m_mapWordLabel[ui.gWordLabelsNamesOne_cpdd] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_cpdd]);
	m_mapWordLabel[ui.gWordLabelsNamesOne_cpsb] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_cpsb]);
	m_mapWordLabel[ui.gWordLabelsNamesOne_hls] = QString::fromLocal8Bit(gWordLabelsNamesOne[gWordLabelsNamesOne_hls]);

	//测评分析
	m_mapWordLabel[ui.gWordLabelsNamesTwo_cpfx_1] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_cpfx]) + QString("1");
	m_mapWordLabel[ui.gWordLabelsNamesTwo_cpfx_2] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_cpfx]) + QString("2");
	m_mapWordLabel[ui.gWordLabelsNamesTwo_cpfx_3] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_cpfx]) + QString("3");
	m_mapWordLabel[ui.gWordLabelsNamesTwo_cpfx_4] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_cpfx]) + QString("4");
	m_mapWordLabel[ui.gWordLabelsNamesTwo_cpfx_5] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_cpfx]) + QString("5");
	m_mapWordLabel[ui.gWordLabelsNamesTwo_cpfx_6] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_cpfx]) + QString("6");
	m_mapWordLabel[ui.gWordLabelsNamesTwo_cpfx_7] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_cpfx]) + QString("7");
	m_mapWordLabel[ui.gWordLabelsNamesTwo_cpfx_8] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_cpfx]) + QString("8");
	m_mapWordLabel[ui.gWordLabelsNamesTwo_cpfx_9] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_cpfx]) + QString("9");
	m_mapWordLabel[ui.gWordLabelsNamesTwo_cpfx_10] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_cpfx]) + QString("10");
	m_mapWordLabel[ui.gWordLabelsNamesTwo_cpfx_11] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_cpfx]) + QString("11");
	m_mapWordLabel[ui.gWordLabelsNamesTwo_cpfx_12] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_cpfx]) + QString("12");
	m_mapWordLabel[ui.gWordLabelsNamesTwo_cpfx_13] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_cpfx]) + QString("13");
	m_mapWordLabel[ui.gWordLabelsNamesTwo_cpfx_14] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_cpfx]) + QString("14");
	m_mapWordLabel[ui.gWordLabelsNamesTwo_cpfx_15] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_cpfx]) + QString("15");
	m_mapWordLabel[ui.gWordLabelsNamesTwo_cpfx_16] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_cpfx]) + QString("16");
	m_mapWordLabel[ui.gWordLabelsNamesTwo_cpfx_17] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_cpfx]) + QString("17");
	m_mapWordLabel[ui.gWordLabelsNamesTwo_cpfx_18] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_cpfx]) + QString("18");
}
//初始化多标签
void wordshowDlg::InitgWordLabelsNamesTwo()
{
	//天车总成
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_1] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("1");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_2] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("2");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_3] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("3");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_4] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("4");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_5] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("5");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_6] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("6");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_7] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("7");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_8] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("8");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_9] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("9");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_10] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("10");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_11] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("11");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_12] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("12");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_13] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("13");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_14] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("14");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_15] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("15");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_16] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("16");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_17] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("17");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_18] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("18");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_19] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("19");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_20] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("20");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_21] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("21");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_22] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("22");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_23] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("23");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_24] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("24");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_25] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("25");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_26] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("26");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_27] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("27");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_28] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("28");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_29] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("29");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tczc_30] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tczc]) + QString("30");

	//"辅助滑轮总成"
	m_mapWordCombox[ui.gWordLabelsNamesTwo_fzhlzc_1] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_fzhlzc]) + QString("1");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_fzhlzc_2] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_fzhlzc]) + QString("2");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_fzhlzc_3] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_fzhlzc]) + QString("3");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_fzhlzc_4] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_fzhlzc]) + QString("4");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_fzhlzc_5] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_fzhlzc]) + QString("5");

	//"天车梁",
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tcl_1] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tcl]) + QString("1");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tcl_2] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tcl]) + QString("2");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tcl_3] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tcl]) + QString("3");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tcl_4] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tcl]) + QString("4");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tcl_5] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tcl]) + QString("5");

	//"井架大腿",
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_1] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("1");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_2] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("2");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_3] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("3");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_4] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("4");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_5] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("5");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_6] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("6");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_7] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("7");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_8] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("8");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_9] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("9");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_10] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("10");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_11] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("11");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_12] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("12");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_13] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("13");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_14] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("14");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_15] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("15");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_16] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("16");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_17] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("17");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_18] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("18");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_19] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("19");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_20] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("20");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_21] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("21");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_22] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("22");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_23] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("23");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_24] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("24");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_25] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("25");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_26] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("26");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_27] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("27");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_28] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("28");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_29] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("29");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_30] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("30");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_31] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("31");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_32] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("32");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_33] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("33");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_34] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("34");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_35] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("35");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_36] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("36");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jjdt_37] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jjdt]) + QString("37");

	//"横拉筋和斜拉筋",
	m_mapWordCombox[ui.gWordLabelsNamesTwo_hljhxlj_1] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_hljhxlj]) + QString("1");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_hljhxlj_2] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_hljhxlj]) + QString("2");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_hljhxlj_3] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_hljhxlj]) + QString("3");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_hljhxlj_4] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_hljhxlj]) + QString("4");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_hljhxlj_5] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_hljhxlj]) + QString("5");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_hljhxlj_6] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_hljhxlj]) + QString("6");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_hljhxlj_7] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_hljhxlj]) + QString("7");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_hljhxlj_8] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_hljhxlj]) + QString("8");

	//"二层台",
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ect_1] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ect]) + QString("1");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ect_2] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ect]) + QString("2");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ect_3] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ect]) + QString("3");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ect_4] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ect]) + QString("4");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ect_5] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ect]) + QString("5");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ect_6] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ect]) + QString("6");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ect_7] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ect]) + QString("7");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ect_8] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ect]) + QString("8");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ect_9] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ect]) + QString("9");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ect_10] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ect]) + QString("10");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ect_11] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ect]) + QString("11");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ect_12] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ect]) + QString("12");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ect_13] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ect]) + QString("13");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ect_14] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ect]) + QString("14");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ect_15] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ect]) + QString("15");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ect_16] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ect]) + QString("16");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ect_17] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ect]) + QString("17");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ect_18] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ect]) + QString("18");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ect_19] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ect]) + QString("19");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ect_20] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ect]) + QString("20");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ect_21] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ect]) + QString("21");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ect_22] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ect]) + QString("22");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ect_23] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ect]) + QString("23");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ect_24] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ect]) + QString("24");

	//"梯子",
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tz_1] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tz]) + QString("1");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tz_2] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tz]) + QString("2");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tz_3] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tz]) + QString("3");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tz_4] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tz]) + QString("4");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tz_5] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tz]) + QString("5");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tz_6] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tz]) + QString("6");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_tz_7] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_tz]) + QString("7");

	//"起升装置和伸缩装置",
	m_mapWordCombox[ui.gWordLabelsNamesTwo_qszzhsszz_1] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_qszzhsszz]) + QString("1");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_qszzhsszz_2] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_qszzhsszz]) + QString("2");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_qszzhsszz_3] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_qszzhsszz]) + QString("3");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_qszzhsszz_4] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_qszzhsszz]) + QString("4");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_qszzhsszz_5] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_qszzhsszz]) + QString("5");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_qszzhsszz_6] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_qszzhsszz]) + QString("6");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_qszzhsszz_7] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_qszzhsszz]) + QString("7");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_qszzhsszz_8] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_qszzhsszz]) + QString("8");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_qszzhsszz_9] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_qszzhsszz]) + QString("9");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_qszzhsszz_10] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_qszzhsszz]) + QString("10");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_qszzhsszz_11] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_qszzhsszz]) + QString("11");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_qszzhsszz_12] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_qszzhsszz]) + QString("12");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_qszzhsszz_13] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_qszzhsszz]) + QString("13");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_qszzhsszz_14] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_qszzhsszz]) + QString("14");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_qszzhsszz_15] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_qszzhsszz]) + QString("15");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_qszzhsszz_16] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_qszzhsszz]) + QString("16");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_qszzhsszz_17] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_qszzhsszz]) + QString("17");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_qszzhsszz_18] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_qszzhsszz]) + QString("18");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_qszzhsszz_19] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_qszzhsszz]) + QString("19");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_qszzhsszz_20] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_qszzhsszz]) + QString("20");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_qszzhsszz_21] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_qszzhsszz]) + QString("21");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_qszzhsszz_22] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_qszzhsszz]) + QString("22");


	//"锁紧装置伸缩式轻便井架",
	m_mapWordCombox[ui.gWordLabelsNamesTwo_sjzzsssqbjj_1] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_sjzzsssqbjj]) + QString("1");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_sjzzsssqbjj_2] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_sjzzsssqbjj]) + QString("2");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_sjzzsssqbjj_3] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_sjzzsssqbjj]) + QString("3");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_sjzzsssqbjj_4] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_sjzzsssqbjj]) + QString("4");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_sjzzsssqbjj_5] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_sjzzsssqbjj]) + QString("5");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_sjzzsssqbjj_6] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_sjzzsssqbjj]) + QString("6");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_sjzzsssqbjj_7] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_sjzzsssqbjj]) + QString("7");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_sjzzsssqbjj_8] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_sjzzsssqbjj]) + QString("8");

	//"绷绳系统",
	m_mapWordCombox[ui.gWordLabelsNamesTwo_bsxt_1] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_bsxt]) + QString("1");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_bsxt_2] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_bsxt]) + QString("2");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_bsxt_3] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_bsxt]) + QString("4");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_bsxt_4] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_bsxt]) + QString("5");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_bsxt_5] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_bsxt]) + QString("6");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_bsxt_6] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_bsxt]) + QString("7");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_bsxt_7] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_bsxt]) + QString("8");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_bsxt_8] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_bsxt]) + QString("9");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_bsxt_9] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_bsxt]) + QString("10");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_bsxt_10] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_bsxt]) + QString("11");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_bsxt_11] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_bsxt]) + QString("12");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_bsxt_12] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_bsxt]) + QString("13");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_bsxt_13] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_bsxt]) + QString("14");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_bsxt_14] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_bsxt]) + QString("15");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_bsxt_15] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_bsxt]) + QString("16");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_bsxt_16] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_bsxt]) + QString("17");
	

	//"栓装结构件",
	m_mapWordCombox[ui.gWordLabelsNamesTwo_szjgj_1] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_szjgj]) + QString("1");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_szjgj_2] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_szjgj]) + QString("2");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_szjgj_3] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_szjgj]) + QString("3");

	//死绳国定器及支座",
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ssgdqjzz_1] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ssgdqjzz]) + QString("1");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ssgdqjzz_2] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ssgdqjzz]) + QString("2");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ssgdqjzz_3] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ssgdqjzz]) + QString("3");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ssgdqjzz_4] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ssgdqjzz]) + QString("4");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ssgdqjzz_5] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ssgdqjzz]) + QString("5");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ssgdqjzz_6] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ssgdqjzz]) + QString("6");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ssgdqjzz_7] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ssgdqjzz]) + QString("7");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_ssgdqjzz_8] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_ssgdqjzz]) + QString("8");

	//底座",
	m_mapWordCombox[ui.gWordLabelsNamesTwo_dz_1] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_dz]) + QString("1");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_dz_2] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_dz]) + QString("2");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_dz_3] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_dz]) + QString("3");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_dz_4] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_dz]) + QString("4");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_dz_5] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_dz]) + QString("5");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_dz_6] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_dz]) + QString("6");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_dz_7] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_dz]) + QString("7");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_dz_8] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_dz]) + QString("8");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_dz_9] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_dz]) + QString("9");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_dz_10] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_dz]) + QString("10");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_dz_11] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_dz]) + QString("11");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_dz_12] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_dz]) + QString("12");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_dz_13] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_dz]) + QString("13");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_dz_14] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_dz]) + QString("14");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_dz_15] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_dz]) + QString("15");
	m_mapWordCombox[ui.gWordLabelsNamesTwo_dz_16] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_dz]) + QString("16");

	//检验情况摘要
	m_mapWordCombox[ui.gWordLabelsNamesTwo_jyqkzy_4] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jyqkzy]) + QString("8");

	//radio button 控件
	m_mapWordRadio[ui.gWordLabelsNamesTwo_jyqkzy_1_1] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jyqkzy]) + QString("1");
	m_mapWordRadio[ui.gWordLabelsNamesTwo_jyqkzy_1_2] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jyqkzy]) + QString("2");
	m_mapWordRadio[ui.gWordLabelsNamesTwo_jyqkzy_2_1] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jyqkzy]) + QString("3");
	m_mapWordRadio[ui.gWordLabelsNamesTwo_jyqkzy_2_2] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jyqkzy]) + QString("4");
	m_mapWordRadio[ui.gWordLabelsNamesTwo_jyqkzy_2_3] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jyqkzy]) + QString("5");
	m_mapWordRadio[ui.gWordLabelsNamesTwo_jyqkzy_3_1] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jyqkzy]) + QString("6");
	m_mapWordRadio[ui.gWordLabelsNamesTwo_jyqkzy_3_2] = QString::fromLocal8Bit(gWordLabelsNamesTwo[gWordLabelsNamesTwo_jyqkzy]) + QString("7");

}

//初始化单一标签   配置map
void wordshowDlg::InitgWordConfigNamesOne()
{
	m_mapConfigLabel["gWordLabelsNamesOne_bgbh"] = ui.gWordLabelsNamesOne_bgbh;
	m_mapConfigLabel["gWordLabelsNamesOne_wtf"] = ui.gWordLabelsNamesOne_wtf;
	m_mapConfigLabel["gWordLabelsNamesOne_ypmc"] = ui.gWordLabelsNamesOne_ypmc;
	m_mapConfigLabel["gWordLabelsNamesOne_ggxh"] = ui.gWordLabelsNamesOne_ggxh;
	m_mapConfigLabel["gWordLabelsNamesOne_cplb"] = ui.gWordLabelsNamesOne_cplb;
	m_mapConfigLabel["gWordLabelsNamesOne_ypmc2"] = ui.gWordLabelsNamesOne_ypmc2;
	m_mapConfigLabel["gWordLabelsNamesOne_ggxh2"] = ui.gWordLabelsNamesOne_ggxh2;
	m_mapConfigLabel["gWordLabelsNamesOne_wtfdz"] = ui.gWordLabelsNamesOne_wtfdz;
	m_mapConfigLabel["gWordLabelsNamesOne_sb"] = ui.gWordLabelsNamesOne_sb;
	m_mapConfigLabel["gWordLabelsNamesOne_xsdw"] = ui.gWordLabelsNamesOne_xsdw;
	m_mapConfigLabel["gWordLabelsNamesOne_scrq"] = ui.gWordLabelsNamesOne_scrq;
	m_mapConfigLabel["gWordLabelsNamesOne_sydw"] = ui.gWordLabelsNamesOne_sydw;
	m_mapConfigLabel["gWordLabelsNamesOne_ccbh"] = ui.gWordLabelsNamesOne_ccbh;
	m_mapConfigLabel["gWordLabelsNamesOne_sydd"] = ui.gWordLabelsNamesOne_sydd;
	m_mapConfigLabel["gWordLabelsNamesOne_ypsl"] = ui.gWordLabelsNamesOne_ypsl;
	m_mapConfigLabel["gWordLabelsNamesOne_ypztms"] = ui.gWordLabelsNamesOne_ypztms;
	m_mapConfigLabel["gWordLabelsNamesOne_ypbsfs"] = ui.gWordLabelsNamesOne_ypbsfs;
	m_mapConfigLabel["gWordLabelsNamesOne_hjtj"] = ui.gWordLabelsNamesOne_hjtj;
	m_mapConfigLabel["gWordLabelsNamesOne_ypbh"] = ui.gWordLabelsNamesOne_ypbh;
	m_mapConfigLabel["gWordLabelsNamesOne_dyrq"] = ui.gWordLabelsNamesOne_dyrq;
	m_mapConfigLabel["gWordLabelsNamesOne_wtflxr"] = ui.gWordLabelsNamesOne_wtflxr;
	m_mapConfigLabel["gWordLabelsNamesOne_cprq"] = ui.gWordLabelsNamesOne_cprq;
	m_mapConfigLabel["gWordLabelsNamesOne_cpdd"] = ui.gWordLabelsNamesOne_cpdd;
	m_mapConfigLabel["gWordLabelsNamesOne_cpsb"] = ui.gWordLabelsNamesOne_cpsb;
	m_mapConfigLabel["gWordLabelsNamesOne_hls"] = ui.gWordLabelsNamesOne_hls;
	//测评分析                                    
	m_mapConfigLabel["gWordLabelsNamesTwo_cpfx_1"] = ui.gWordLabelsNamesTwo_cpfx_1;
	m_mapConfigLabel["gWordLabelsNamesTwo_cpfx_2"] = ui.gWordLabelsNamesTwo_cpfx_2;
	m_mapConfigLabel["gWordLabelsNamesTwo_cpfx_3"] = ui.gWordLabelsNamesTwo_cpfx_3;
	m_mapConfigLabel["gWordLabelsNamesTwo_cpfx_4"] = ui.gWordLabelsNamesTwo_cpfx_4;
	m_mapConfigLabel["gWordLabelsNamesTwo_cpfx_5"] = ui.gWordLabelsNamesTwo_cpfx_5;
	m_mapConfigLabel["gWordLabelsNamesTwo_cpfx_6"] = ui.gWordLabelsNamesTwo_cpfx_6;
	m_mapConfigLabel["gWordLabelsNamesTwo_cpfx_7"] = ui.gWordLabelsNamesTwo_cpfx_7;
	m_mapConfigLabel["gWordLabelsNamesTwo_cpfx_8"] = ui.gWordLabelsNamesTwo_cpfx_8;
	m_mapConfigLabel["gWordLabelsNamesTwo_cpfx_9"] = ui.gWordLabelsNamesTwo_cpfx_9;
	m_mapConfigLabel["gWordLabelsNamesTwo_cpfx_10"] = ui.gWordLabelsNamesTwo_cpfx_10;
	m_mapConfigLabel["gWordLabelsNamesTwo_cpfx_11"] = ui.gWordLabelsNamesTwo_cpfx_11;
	m_mapConfigLabel["gWordLabelsNamesTwo_cpfx_12"] = ui.gWordLabelsNamesTwo_cpfx_12;
	m_mapConfigLabel["gWordLabelsNamesTwo_cpfx_13"] = ui.gWordLabelsNamesTwo_cpfx_13;
	m_mapConfigLabel["gWordLabelsNamesTwo_cpfx_14"] = ui.gWordLabelsNamesTwo_cpfx_14;
	m_mapConfigLabel["gWordLabelsNamesTwo_cpfx_15"] = ui.gWordLabelsNamesTwo_cpfx_15;
	m_mapConfigLabel["gWordLabelsNamesTwo_cpfx_16"] = ui.gWordLabelsNamesTwo_cpfx_16;
	m_mapConfigLabel["gWordLabelsNamesTwo_cpfx_17"] = ui.gWordLabelsNamesTwo_cpfx_17;
	m_mapConfigLabel["gWordLabelsNamesTwo_cpfx_18"] = ui.gWordLabelsNamesTwo_cpfx_18;

}
//初始化多标签  配置map
void wordshowDlg::InitgWordConfigNamesTwo()
{
	//天车总成
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_1"] = ui.gWordLabelsNamesTwo_tczc_1;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_2"] = ui.gWordLabelsNamesTwo_tczc_2;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_3"] = ui.gWordLabelsNamesTwo_tczc_3;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_4"] = ui.gWordLabelsNamesTwo_tczc_4;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_5"] = ui.gWordLabelsNamesTwo_tczc_5;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_6"] = ui.gWordLabelsNamesTwo_tczc_6;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_7"] = ui.gWordLabelsNamesTwo_tczc_7;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_8"] = ui.gWordLabelsNamesTwo_tczc_8;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_9"] = ui.gWordLabelsNamesTwo_tczc_9;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_10"] = ui.gWordLabelsNamesTwo_tczc_10;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_11"] = ui.gWordLabelsNamesTwo_tczc_11;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_12"] = ui.gWordLabelsNamesTwo_tczc_12;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_13"] = ui.gWordLabelsNamesTwo_tczc_13;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_14"] = ui.gWordLabelsNamesTwo_tczc_14;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_15"] = ui.gWordLabelsNamesTwo_tczc_15;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_16"] = ui.gWordLabelsNamesTwo_tczc_16;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_17"] = ui.gWordLabelsNamesTwo_tczc_17;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_18"] = ui.gWordLabelsNamesTwo_tczc_18;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_19"] = ui.gWordLabelsNamesTwo_tczc_19;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_20"] = ui.gWordLabelsNamesTwo_tczc_20;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_21"] = ui.gWordLabelsNamesTwo_tczc_21;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_22"] = ui.gWordLabelsNamesTwo_tczc_22;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_23"] = ui.gWordLabelsNamesTwo_tczc_23;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_24"] = ui.gWordLabelsNamesTwo_tczc_24;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_25"] = ui.gWordLabelsNamesTwo_tczc_25;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_26"] = ui.gWordLabelsNamesTwo_tczc_26;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_27"] = ui.gWordLabelsNamesTwo_tczc_27;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_28"] = ui.gWordLabelsNamesTwo_tczc_28;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_29"] = ui.gWordLabelsNamesTwo_tczc_29;
	m_mapConfigCombox["gWordLabelsNamesTwo_tczc_30"] = ui.gWordLabelsNamesTwo_tczc_30;



	//"辅助滑轮总成"                                     
	m_mapConfigCombox["gWordLabelsNamesTwo_fzhlzc_1"] = ui.gWordLabelsNamesTwo_fzhlzc_1;
	m_mapConfigCombox["gWordLabelsNamesTwo_fzhlzc_2"] = ui.gWordLabelsNamesTwo_fzhlzc_2;
	m_mapConfigCombox["gWordLabelsNamesTwo_fzhlzc_3"] = ui.gWordLabelsNamesTwo_fzhlzc_3;
	m_mapConfigCombox["gWordLabelsNamesTwo_fzhlzc_4"] = ui.gWordLabelsNamesTwo_fzhlzc_4;
	m_mapConfigCombox["gWordLabelsNamesTwo_fzhlzc_5"] = ui.gWordLabelsNamesTwo_fzhlzc_5;

	//"天车梁",                                                                              
	m_mapConfigCombox["gWordLabelsNamesTwo_tcl_1"] = ui.gWordLabelsNamesTwo_tcl_1;
	m_mapConfigCombox["gWordLabelsNamesTwo_tcl_2"] = ui.gWordLabelsNamesTwo_tcl_2;
	m_mapConfigCombox["gWordLabelsNamesTwo_tcl_3"] = ui.gWordLabelsNamesTwo_tcl_3;
	m_mapConfigCombox["gWordLabelsNamesTwo_tcl_4"] = ui.gWordLabelsNamesTwo_tcl_4;
	m_mapConfigCombox["gWordLabelsNamesTwo_tcl_5"] = ui.gWordLabelsNamesTwo_tcl_5;

	//"井架大腿",                                                                     
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_1"] = ui.gWordLabelsNamesTwo_jjdt_1;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_2"] = ui.gWordLabelsNamesTwo_jjdt_2;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_3"] = ui.gWordLabelsNamesTwo_jjdt_3;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_4"] = ui.gWordLabelsNamesTwo_jjdt_4;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_5"] = ui.gWordLabelsNamesTwo_jjdt_5;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_6"] = ui.gWordLabelsNamesTwo_jjdt_6;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_7"] = ui.gWordLabelsNamesTwo_jjdt_7;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_8"] = ui.gWordLabelsNamesTwo_jjdt_8;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_9"] = ui.gWordLabelsNamesTwo_jjdt_9;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_10"] = ui.gWordLabelsNamesTwo_jjdt_10;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_11"] = ui.gWordLabelsNamesTwo_jjdt_11;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_12"] = ui.gWordLabelsNamesTwo_jjdt_12;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_13"] = ui.gWordLabelsNamesTwo_jjdt_13;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_14"] = ui.gWordLabelsNamesTwo_jjdt_14;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_15"] = ui.gWordLabelsNamesTwo_jjdt_15;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_16"] = ui.gWordLabelsNamesTwo_jjdt_16;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_17"] = ui.gWordLabelsNamesTwo_jjdt_17;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_18"] = ui.gWordLabelsNamesTwo_jjdt_18;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_19"] = ui.gWordLabelsNamesTwo_jjdt_19;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_20"] = ui.gWordLabelsNamesTwo_jjdt_20;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_21"] = ui.gWordLabelsNamesTwo_jjdt_21;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_22"] = ui.gWordLabelsNamesTwo_jjdt_22;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_23"] = ui.gWordLabelsNamesTwo_jjdt_23;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_24"] = ui.gWordLabelsNamesTwo_jjdt_24;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_25"] = ui.gWordLabelsNamesTwo_jjdt_25;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_26"] = ui.gWordLabelsNamesTwo_jjdt_26;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_27"] = ui.gWordLabelsNamesTwo_jjdt_27;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_28"] = ui.gWordLabelsNamesTwo_jjdt_28;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_29"] = ui.gWordLabelsNamesTwo_jjdt_29;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_30"] = ui.gWordLabelsNamesTwo_jjdt_30;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_31"] = ui.gWordLabelsNamesTwo_jjdt_31;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_32"] = ui.gWordLabelsNamesTwo_jjdt_32;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_33"] = ui.gWordLabelsNamesTwo_jjdt_33;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_34"] = ui.gWordLabelsNamesTwo_jjdt_34;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_35"] = ui.gWordLabelsNamesTwo_jjdt_35;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_36"] = ui.gWordLabelsNamesTwo_jjdt_36;
	m_mapConfigCombox["gWordLabelsNamesTwo_jjdt_37"] = ui.gWordLabelsNamesTwo_jjdt_37;

	//"横拉筋和斜拉筋                                                                       
	m_mapConfigCombox["gWordLabelsNamesTwo_hljhxlj_1"] = ui.gWordLabelsNamesTwo_hljhxlj_1;
	m_mapConfigCombox["gWordLabelsNamesTwo_hljhxlj_2"] = ui.gWordLabelsNamesTwo_hljhxlj_2;
	m_mapConfigCombox["gWordLabelsNamesTwo_hljhxlj_3"] = ui.gWordLabelsNamesTwo_hljhxlj_3;
	m_mapConfigCombox["gWordLabelsNamesTwo_hljhxlj_4"] = ui.gWordLabelsNamesTwo_hljhxlj_4;
	m_mapConfigCombox["gWordLabelsNamesTwo_hljhxlj_5"] = ui.gWordLabelsNamesTwo_hljhxlj_5;
	m_mapConfigCombox["gWordLabelsNamesTwo_hljhxlj_6"] = ui.gWordLabelsNamesTwo_hljhxlj_6;
	m_mapConfigCombox["gWordLabelsNamesTwo_hljhxlj_7"] = ui.gWordLabelsNamesTwo_hljhxlj_7;
	m_mapConfigCombox["gWordLabelsNamesTwo_hljhxlj_8"] = ui.gWordLabelsNamesTwo_hljhxlj_8;

	//"二层台",                                                                        
	m_mapConfigCombox["gWordLabelsNamesTwo_ect_1"] = ui.gWordLabelsNamesTwo_ect_1;
	m_mapConfigCombox["gWordLabelsNamesTwo_ect_2"] = ui.gWordLabelsNamesTwo_ect_2;
	m_mapConfigCombox["gWordLabelsNamesTwo_ect_3"] = ui.gWordLabelsNamesTwo_ect_3;
	m_mapConfigCombox["gWordLabelsNamesTwo_ect_4"] = ui.gWordLabelsNamesTwo_ect_4;
	m_mapConfigCombox["gWordLabelsNamesTwo_ect_5"] = ui.gWordLabelsNamesTwo_ect_5;
	m_mapConfigCombox["gWordLabelsNamesTwo_ect_6"] = ui.gWordLabelsNamesTwo_ect_6;
	m_mapConfigCombox["gWordLabelsNamesTwo_ect_7"] = ui.gWordLabelsNamesTwo_ect_7;
	m_mapConfigCombox["gWordLabelsNamesTwo_ect_8"] = ui.gWordLabelsNamesTwo_ect_8;
	m_mapConfigCombox["gWordLabelsNamesTwo_ect_9"] = ui.gWordLabelsNamesTwo_ect_9;
	m_mapConfigCombox["gWordLabelsNamesTwo_ect_10"] = ui.gWordLabelsNamesTwo_ect_10;
	m_mapConfigCombox["gWordLabelsNamesTwo_ect_11"] = ui.gWordLabelsNamesTwo_ect_11;
	m_mapConfigCombox["gWordLabelsNamesTwo_ect_12"] = ui.gWordLabelsNamesTwo_ect_12;
	m_mapConfigCombox["gWordLabelsNamesTwo_ect_13"] = ui.gWordLabelsNamesTwo_ect_13;
	m_mapConfigCombox["gWordLabelsNamesTwo_ect_14"] = ui.gWordLabelsNamesTwo_ect_14;
	m_mapConfigCombox["gWordLabelsNamesTwo_ect_15"] = ui.gWordLabelsNamesTwo_ect_15;
	m_mapConfigCombox["gWordLabelsNamesTwo_ect_16"] = ui.gWordLabelsNamesTwo_ect_16;
	m_mapConfigCombox["gWordLabelsNamesTwo_ect_17"] = ui.gWordLabelsNamesTwo_ect_17;
	m_mapConfigCombox["gWordLabelsNamesTwo_ect_18"] = ui.gWordLabelsNamesTwo_ect_18;
	m_mapConfigCombox["gWordLabelsNamesTwo_ect_19"] = ui.gWordLabelsNamesTwo_ect_19;
	m_mapConfigCombox["gWordLabelsNamesTwo_ect_20"] = ui.gWordLabelsNamesTwo_ect_20;
	m_mapConfigCombox["gWordLabelsNamesTwo_ect_21"] = ui.gWordLabelsNamesTwo_ect_21;
	m_mapConfigCombox["gWordLabelsNamesTwo_ect_22"] = ui.gWordLabelsNamesTwo_ect_22;
	m_mapConfigCombox["gWordLabelsNamesTwo_ect_23"] = ui.gWordLabelsNamesTwo_ect_23;
	m_mapConfigCombox["gWordLabelsNamesTwo_ect_24"] = ui.gWordLabelsNamesTwo_ect_24;

	//"梯子",                                                                                
	m_mapConfigCombox["gWordLabelsNamesTwo_tz_1"] = ui.gWordLabelsNamesTwo_tz_1;
	m_mapConfigCombox["gWordLabelsNamesTwo_tz_2"] = ui.gWordLabelsNamesTwo_tz_2;
	m_mapConfigCombox["gWordLabelsNamesTwo_tz_3"] = ui.gWordLabelsNamesTwo_tz_3;
	m_mapConfigCombox["gWordLabelsNamesTwo_tz_4"] = ui.gWordLabelsNamesTwo_tz_4;
	m_mapConfigCombox["gWordLabelsNamesTwo_tz_5"] = ui.gWordLabelsNamesTwo_tz_5;
	m_mapConfigCombox["gWordLabelsNamesTwo_tz_6"] = ui.gWordLabelsNamesTwo_tz_6;
	m_mapConfigCombox["gWordLabelsNamesTwo_tz_7"] = ui.gWordLabelsNamesTwo_tz_7;

	//"起升装置和伸缩                                                                         
	m_mapConfigCombox["gWordLabelsNamesTwo_qszzhsszz_1"] = ui.gWordLabelsNamesTwo_qszzhsszz_1;
	m_mapConfigCombox["gWordLabelsNamesTwo_qszzhsszz_2"] = ui.gWordLabelsNamesTwo_qszzhsszz_2;
	m_mapConfigCombox["gWordLabelsNamesTwo_qszzhsszz_3"] = ui.gWordLabelsNamesTwo_qszzhsszz_3;
	m_mapConfigCombox["gWordLabelsNamesTwo_qszzhsszz_4"] = ui.gWordLabelsNamesTwo_qszzhsszz_4;
	m_mapConfigCombox["gWordLabelsNamesTwo_qszzhsszz_5"] = ui.gWordLabelsNamesTwo_qszzhsszz_5;
	m_mapConfigCombox["gWordLabelsNamesTwo_qszzhsszz_6"] = ui.gWordLabelsNamesTwo_qszzhsszz_6;
	m_mapConfigCombox["gWordLabelsNamesTwo_qszzhsszz_7"] = ui.gWordLabelsNamesTwo_qszzhsszz_7;
	m_mapConfigCombox["gWordLabelsNamesTwo_qszzhsszz_8"] = ui.gWordLabelsNamesTwo_qszzhsszz_8;
	m_mapConfigCombox["gWordLabelsNamesTwo_qszzhsszz_9"] = ui.gWordLabelsNamesTwo_qszzhsszz_9;
	m_mapConfigCombox["gWordLabelsNamesTwo_qszzhsszz_10"] = ui.gWordLabelsNamesTwo_qszzhsszz_10;
	m_mapConfigCombox["gWordLabelsNamesTwo_qszzhsszz_11"] = ui.gWordLabelsNamesTwo_qszzhsszz_11;
	m_mapConfigCombox["gWordLabelsNamesTwo_qszzhsszz_12"] = ui.gWordLabelsNamesTwo_qszzhsszz_12;
	m_mapConfigCombox["gWordLabelsNamesTwo_qszzhsszz_13"] = ui.gWordLabelsNamesTwo_qszzhsszz_13;
	m_mapConfigCombox["gWordLabelsNamesTwo_qszzhsszz_14"] = ui.gWordLabelsNamesTwo_qszzhsszz_14;
	m_mapConfigCombox["gWordLabelsNamesTwo_qszzhsszz_15"] = ui.gWordLabelsNamesTwo_qszzhsszz_15;
	m_mapConfigCombox["gWordLabelsNamesTwo_qszzhsszz_16"] = ui.gWordLabelsNamesTwo_qszzhsszz_16;
	m_mapConfigCombox["gWordLabelsNamesTwo_qszzhsszz_17"] = ui.gWordLabelsNamesTwo_qszzhsszz_17;
	m_mapConfigCombox["gWordLabelsNamesTwo_qszzhsszz_18"] = ui.gWordLabelsNamesTwo_qszzhsszz_18;
	m_mapConfigCombox["gWordLabelsNamesTwo_qszzhsszz_19"] = ui.gWordLabelsNamesTwo_qszzhsszz_19;
	m_mapConfigCombox["gWordLabelsNamesTwo_qszzhsszz_20"] = ui.gWordLabelsNamesTwo_qszzhsszz_20;
	m_mapConfigCombox["gWordLabelsNamesTwo_qszzhsszz_21"] = ui.gWordLabelsNamesTwo_qszzhsszz_21;
	m_mapConfigCombox["gWordLabelsNamesTwo_qszzhsszz_22"] = ui.gWordLabelsNamesTwo_qszzhsszz_22;


	//"锁紧装置伸缩式                                                                        
	m_mapConfigCombox["gWordLabelsNamesTwo_sjzzsssqbjj_1"] = ui.gWordLabelsNamesTwo_sjzzsssqbjj_1;
	m_mapConfigCombox["gWordLabelsNamesTwo_sjzzsssqbjj_2"] = ui.gWordLabelsNamesTwo_sjzzsssqbjj_2;
	m_mapConfigCombox["gWordLabelsNamesTwo_sjzzsssqbjj_3"] = ui.gWordLabelsNamesTwo_sjzzsssqbjj_3;
	m_mapConfigCombox["gWordLabelsNamesTwo_sjzzsssqbjj_4"] = ui.gWordLabelsNamesTwo_sjzzsssqbjj_4;
	m_mapConfigCombox["gWordLabelsNamesTwo_sjzzsssqbjj_5"] = ui.gWordLabelsNamesTwo_sjzzsssqbjj_5;
	m_mapConfigCombox["gWordLabelsNamesTwo_sjzzsssqbjj_6"] = ui.gWordLabelsNamesTwo_sjzzsssqbjj_6;
	m_mapConfigCombox["gWordLabelsNamesTwo_sjzzsssqbjj_7"] = ui.gWordLabelsNamesTwo_sjzzsssqbjj_7;
	m_mapConfigCombox["gWordLabelsNamesTwo_sjzzsssqbjj_8"] = ui.gWordLabelsNamesTwo_sjzzsssqbjj_8;

	//"绷绳系统",                                                                             
	m_mapConfigCombox["gWordLabelsNamesTwo_bsxt_1"] = ui.gWordLabelsNamesTwo_bsxt_1;
	m_mapConfigCombox["gWordLabelsNamesTwo_bsxt_2"] = ui.gWordLabelsNamesTwo_bsxt_2;
	m_mapConfigCombox["gWordLabelsNamesTwo_bsxt_3"] = ui.gWordLabelsNamesTwo_bsxt_3;
	m_mapConfigCombox["gWordLabelsNamesTwo_bsxt_4"] = ui.gWordLabelsNamesTwo_bsxt_4;
	m_mapConfigCombox["gWordLabelsNamesTwo_bsxt_5"] = ui.gWordLabelsNamesTwo_bsxt_5;
	m_mapConfigCombox["gWordLabelsNamesTwo_bsxt_6"] = ui.gWordLabelsNamesTwo_bsxt_6;
	m_mapConfigCombox["gWordLabelsNamesTwo_bsxt_7"] = ui.gWordLabelsNamesTwo_bsxt_7;
	m_mapConfigCombox["gWordLabelsNamesTwo_bsxt_8"] = ui.gWordLabelsNamesTwo_bsxt_8;
	m_mapConfigCombox["gWordLabelsNamesTwo_bsxt_9"] = ui.gWordLabelsNamesTwo_bsxt_9;
	m_mapConfigCombox["gWordLabelsNamesTwo_bsxt_10"] = ui.gWordLabelsNamesTwo_bsxt_10;
	m_mapConfigCombox["gWordLabelsNamesTwo_bsxt_11"] = ui.gWordLabelsNamesTwo_bsxt_11;
	m_mapConfigCombox["gWordLabelsNamesTwo_bsxt_12"] = ui.gWordLabelsNamesTwo_bsxt_12;
	m_mapConfigCombox["gWordLabelsNamesTwo_bsxt_13"] = ui.gWordLabelsNamesTwo_bsxt_13;
	m_mapConfigCombox["gWordLabelsNamesTwo_bsxt_14"] = ui.gWordLabelsNamesTwo_bsxt_14;
	m_mapConfigCombox["gWordLabelsNamesTwo_bsxt_15"] = ui.gWordLabelsNamesTwo_bsxt_15;
	m_mapConfigCombox["gWordLabelsNamesTwo_bsxt_16"] = ui.gWordLabelsNamesTwo_bsxt_16;

	//"栓装结构件",                                                                          
	m_mapConfigCombox["gWordLabelsNamesTwo_szjgj_1"] = ui.gWordLabelsNamesTwo_szjgj_1;
	m_mapConfigCombox["gWordLabelsNamesTwo_szjgj_2"] = ui.gWordLabelsNamesTwo_szjgj_2;
	m_mapConfigCombox["gWordLabelsNamesTwo_szjgj_3"] = ui.gWordLabelsNamesTwo_szjgj_3;

	//死绳国定器及支座                                                                       
	m_mapConfigCombox["gWordLabelsNamesTwo_ssgdqjzz_1"] = ui.gWordLabelsNamesTwo_ssgdqjzz_1;
	m_mapConfigCombox["gWordLabelsNamesTwo_ssgdqjzz_2"] = ui.gWordLabelsNamesTwo_ssgdqjzz_2;
	m_mapConfigCombox["gWordLabelsNamesTwo_ssgdqjzz_3"] = ui.gWordLabelsNamesTwo_ssgdqjzz_3;
	m_mapConfigCombox["gWordLabelsNamesTwo_ssgdqjzz_4"] = ui.gWordLabelsNamesTwo_ssgdqjzz_4;
	m_mapConfigCombox["gWordLabelsNamesTwo_ssgdqjzz_5"] = ui.gWordLabelsNamesTwo_ssgdqjzz_5;
	m_mapConfigCombox["gWordLabelsNamesTwo_ssgdqjzz_6"] = ui.gWordLabelsNamesTwo_ssgdqjzz_6;
	m_mapConfigCombox["gWordLabelsNamesTwo_ssgdqjzz_7"] = ui.gWordLabelsNamesTwo_ssgdqjzz_7;
	m_mapConfigCombox["gWordLabelsNamesTwo_ssgdqjzz_8"] = ui.gWordLabelsNamesTwo_ssgdqjzz_8;

	//底座",                                                                                 
	m_mapConfigCombox["gWordLabelsNamesTwo_dz_1"] = ui.gWordLabelsNamesTwo_dz_1;
	m_mapConfigCombox["gWordLabelsNamesTwo_dz_2"] = ui.gWordLabelsNamesTwo_dz_2;
	m_mapConfigCombox["gWordLabelsNamesTwo_dz_3"] = ui.gWordLabelsNamesTwo_dz_3;
	m_mapConfigCombox["gWordLabelsNamesTwo_dz_4"] = ui.gWordLabelsNamesTwo_dz_4;
	m_mapConfigCombox["gWordLabelsNamesTwo_dz_5"] = ui.gWordLabelsNamesTwo_dz_5;
	m_mapConfigCombox["gWordLabelsNamesTwo_dz_6"] = ui.gWordLabelsNamesTwo_dz_6;
	m_mapConfigCombox["gWordLabelsNamesTwo_dz_7"] = ui.gWordLabelsNamesTwo_dz_7;
	m_mapConfigCombox["gWordLabelsNamesTwo_dz_8"] = ui.gWordLabelsNamesTwo_dz_8;
	m_mapConfigCombox["gWordLabelsNamesTwo_dz_9"] = ui.gWordLabelsNamesTwo_dz_9;
	m_mapConfigCombox["gWordLabelsNamesTwo_dz_10"] = ui.gWordLabelsNamesTwo_dz_10;
	m_mapConfigCombox["gWordLabelsNamesTwo_dz_11"] = ui.gWordLabelsNamesTwo_dz_11;
	m_mapConfigCombox["gWordLabelsNamesTwo_dz_12"] = ui.gWordLabelsNamesTwo_dz_12;
	m_mapConfigCombox["gWordLabelsNamesTwo_dz_13"] = ui.gWordLabelsNamesTwo_dz_13;
	m_mapConfigCombox["gWordLabelsNamesTwo_dz_14"] = ui.gWordLabelsNamesTwo_dz_14;
	m_mapConfigCombox["gWordLabelsNamesTwo_dz_15"] = ui.gWordLabelsNamesTwo_dz_15;
	m_mapConfigCombox["gWordLabelsNamesTwo_dz_16"] = ui.gWordLabelsNamesTwo_dz_16;
	
	//检验情况摘要                                                                            
	m_mapConfigCombox["gWordLabelsNamesTwo_jyqkzy_4"] = ui.gWordLabelsNamesTwo_jyqkzy_4;

	m_mapConfigRadio["gWordLabelsNamesTwo_jyqkzy_1_1"] = ui.gWordLabelsNamesTwo_jyqkzy_1_1;
	m_mapConfigRadio["gWordLabelsNamesTwo_jyqkzy_1_2"] = ui.gWordLabelsNamesTwo_jyqkzy_1_2;
	m_mapConfigRadio["gWordLabelsNamesTwo_jyqkzy_2_1"] = ui.gWordLabelsNamesTwo_jyqkzy_2_1;
	m_mapConfigRadio["gWordLabelsNamesTwo_jyqkzy_2_2"] = ui.gWordLabelsNamesTwo_jyqkzy_2_2;
	m_mapConfigRadio["gWordLabelsNamesTwo_jyqkzy_2_3"] = ui.gWordLabelsNamesTwo_jyqkzy_2_3;
	m_mapConfigRadio["gWordLabelsNamesTwo_jyqkzy_3_1"] = ui.gWordLabelsNamesTwo_jyqkzy_3_1;
	m_mapConfigRadio["gWordLabelsNamesTwo_jyqkzy_3_2"] = ui.gWordLabelsNamesTwo_jyqkzy_3_2;
}
#include "sderrickloadcapacitymainwin.h"
#include "ui_sderrickloadcapacitymainwin.h"
#include "sdatabasemanager.h"
#include "salgo.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <cmath>
#include "WordOperation.h"
#include <QString>
#include <QFileDialog>
#include "wordshowDlg.h"


SDerrickLoadCapacityMainWin::SDerrickLoadCapacityMainWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SDerrickLoadCapacityMainWin)
{
    ui->setupUi(this);
    ui->tableWidgetLoadVal->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetMaxLoadCapacity->verticalHeader()->hide();
    ui->tableWidgetMaxLoadCapacity->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ui->tableWidgetMaxLoadCapacity->horizontalHeader()->setStretchLastSection(true);
//    ui->tableWidgetMaxLoadCapacity->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
//    ui->tableWidgetMaxLoadCapacity->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);

    ui->tableWidgetLoadVal->verticalHeader()->hide();
    ui->tableWidgetMaxLoadCapacity->setColumnWidth(1,130);

    ui->tableWidgetMaxLoadStress->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetMaxLoadStress->verticalHeader()->hide();
    ui->tableWidgetMaxLoadStress->horizontalHeader()->setStretchLastSection(true);

	//连接槽函数
	//报表打印
	connect(ui->pushButton_printOut, &QPushButton::clicked, this, &SDerrickLoadCapacityMainWin::on_click_export_word_trigger);



    m_pSinTestDataA=NULL;//外推拟合数据
    m_pSinDataWeightA=NULL;//测量点值
    m_pWeightOutputVal=NULL;
    m_nChannelNum=0;
    m_nMeasurePointNum=0;
    m_fMaxLoadCapacity=0;//线性外推载荷(设计最大钩载)
    m_frx=0;//计算出的回转半径rx
    m_fry=0;//计算出的回转半径ry
    m_fr=0;//计算出的回转半径r(取rx,ry中小的)
    m_fE=0;
    m_fFy=0;
	
}

SDerrickLoadCapacityMainWin::~SDerrickLoadCapacityMainWin()
{
    delete ui;
}
void SDerrickLoadCapacityMainWin::on_actionExit_triggered()
{
    close();
}


void SDerrickLoadCapacityMainWin::on_actionOpenOriFile_triggered()
{
    QString strAccessFile = QFileDialog::getOpenFileName(this, QStringLiteral("打开文件"),
                                                         QString(),
                                                         QStringLiteral("数据文件 (*.mdb)"));
    if(strAccessFile.isEmpty())
    {
        return;
    }
    bool bRet= SDataBaseManager::getDataBaseManagerInstance()->createAndOpenDatabase(strAccessFile);
    if(!bRet)
    {
        return ;
    }

    QVector< float >   vecMeasurePointLoad;
    int nChannelNum=0;
    int  nMeasurePointNum=0;

    SDataBaseManager::getDataBaseManagerInstance()->selectMeasurePoint(vecMeasurePointLoad,nChannelNum, nMeasurePointNum);

    m_nChannelNum=nChannelNum;
    m_nMeasurePointNum=nMeasurePointNum;
    ui->wChannelStartEdit->setText(QString::number(1));
    ui->wChannelEndEdit->setText(QString::number(nChannelNum));
    ui->wLoadCapacityIndexStartEdit->setText((QString::number(1)));
    ui->wLoadCapacityIndexEndEdit->setText((QString::number(nMeasurePointNum)));
    ui->tableWidgetLoadVal->setRowCount(0);
    ui->tableWidgetMaxLoadCapacity->setRowCount(0);
    ui->tableWidgetMaxLoadStress->setRowCount(0);
    ui->wCcEdit->clear();
    ui->wldividerEdit->clear();
    ui->wFaEdit->clear();
    ui->wFbEdit->clear();
    ui->wFexEdit->clear();
    ui->wFeyEdit->clear();

    ui->tableWidgetLoadVal->setRowCount(nMeasurePointNum);
    for(int i=0;i<nMeasurePointNum;i++)
    {
        QTableWidgetItem *pRowIndex=new QTableWidgetItem(QString::number(i+1));
        ui->tableWidgetLoadVal->setItem(i,0,pRowIndex);
        pRowIndex->setFlags(pRowIndex->flags() & (~Qt::ItemIsEditable));
        ui->tableWidgetLoadVal->setItem(i,1,new QTableWidgetItem(QString::number(vecMeasurePointLoad.at(i))));
    }
    if(m_pSinTestDataA !=NULL)
    {
        free3d(m_pSinTestDataA,m_nMeasurePointNum,3);
    }
    m_pSinTestDataA = alloc3d(m_nMeasurePointNum,3,nChannelNum);

    if(m_pSinDataWeightA !=NULL)
    {
        delete []m_pSinDataWeightA;
        m_pSinDataWeightA=NULL;
    }
    m_pSinDataWeightA=new float[m_nMeasurePointNum];
    memcpy(m_pSinDataWeightA,vecMeasurePointLoad.data(),m_nMeasurePointNum*sizeof(float));

    QVector< float >   vecStressMeasurePoint;

    QVector< float >   vecZeroDegress ;
    QVector< float >   vecThetaVal;

    SDataBaseManager::getDataBaseManagerInstance()->selectMeasureValue(vecStressMeasurePoint,vecZeroDegress, vecThetaVal);
    for(int nMeasureIndex=0;nMeasureIndex<m_nMeasurePointNum;nMeasureIndex++)
    {
        for(int nChannelIndex=0;nChannelIndex<m_nChannelNum;nChannelIndex++)
        {
            m_pSinTestDataA[nMeasureIndex][0][nChannelIndex]=vecStressMeasurePoint.takeFirst();
            m_pSinTestDataA[nMeasureIndex][1][nChannelIndex]=vecZeroDegress.takeFirst();
            m_pSinTestDataA[nMeasureIndex][2][nChannelIndex]=vecThetaVal.takeFirst();
        }

    }


}

//三维数组内存分配
float *** SDerrickLoadCapacityMainWin::alloc3d( int l, int m, int n )
{
    int i,j;
    float ***temp = NULL;

    temp = new float **[l];
    if (temp == NULL) {
        return (NULL);
    }

    for (i = 0; i < l; i++) {
        temp[i] = new float *[m];
        for (j = 0; j < m; j++) {
            temp[i][j] = new float[n];
        }
    }

    return temp;

}
//三维数组内存释放
void SDerrickLoadCapacityMainWin::free3d( float * * * temp, int l, int m )
{
    int i, j;

    if (temp==NULL)
        return;

    for (i = 0; i < l; i++) {
        if (temp[i] == NULL)
            continue;
        for (j = 0; j < m; j++) {
            if (temp[i][j] != NULL) {
                delete []temp[i][j];
                temp[i][j] = NULL;
            }
        }
        delete []temp[i];
        temp[i] = NULL;
    }

    delete []temp;
    temp = NULL;

}
//二维数组内存分配
float ** SDerrickLoadCapacityMainWin::alloc2d( int m, int n )
{

    int i;
    float **temp;

    temp =  new float *[m];
    if (temp == NULL) {
        return (NULL);
    }

    for (i = 0; i < m; i++) {
        temp[i] = new float[n];
    }

    return temp;

}
//二维数组内存释放
void SDerrickLoadCapacityMainWin::free2d( float * * temp, int m )
{
    int i;

    if (temp==NULL)
        return;

    for (i = 0; i < m; i++)
        if (temp[i]!=NULL) {
            delete []temp[i];
            temp[i] = NULL;
        }
    if (temp!=NULL) {
        delete []temp;
        temp = NULL;
    }

}
//计算按钮对应的槽函数
void SDerrickLoadCapacityMainWin::on_wComputeButton_clicked()
{
    bool bRet=false;
    QString strOriAccessFileName =SDataBaseManager::getDataBaseManagerInstance()->getOriFileName();
    if(strOriAccessFileName.isEmpty())
    {
       warningTips(QStringLiteral("请选择原始数据"));
        return;
    }

    bRet=getLinearExtrapolationGUIParm();
    if(!bRet)
        return ;
    bRet=getLoadCapacityGUIParm();
    if(!bRet)
        return ;

    //线性外推拟合计算
    if(m_pWeightOutputVal !=NULL)
    {
        delete []m_pWeightOutputVal;
        m_pWeightOutputVal=NULL;
    }
    //weight数据,最大钩载时的应力
    m_pWeightOutputVal =new float[m_nChannelNum];
    memset(m_pWeightOutputVal,0,sizeof(float)*m_nChannelNum);

    SAlgo objAlgo;
    objAlgo.fitting(m_pSinTestDataA,m_pSinDataWeightA,m_nMeasurePointNum,3,m_nChannelNum,m_fMaxLoadCapacity,m_pWeightOutputVal);
    //qDebug()<<QStringLiteral("测点号")<<QStringLiteral("最大钩载时的应力");
    for(int i=0;i<m_nChannelNum;i++)
    {
        //qDebug()<<i+1<<"   "<<m_pWeightOutputVal[i];
        ui->tableWidgetMaxLoadStress->insertRow(i);
        ui->tableWidgetMaxLoadStress->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));

        QString strMaxLoadStress=QString("%1").arg(m_pWeightOutputVal[i],0,'f',3);
        ui->tableWidgetMaxLoadStress->setItem(i,1,new QTableWidgetItem(strMaxLoadStress));
    }

    //计算中间参数
    //计算Cc
    float fCc=objAlgo.computeCc(m_fE,m_fFy);
    float flDivider=m_flx/m_fr;
    float fFa=objAlgo.computeFaVal(1.0f,m_flx,m_fr,fCc,m_fFy,m_fE);
    float fFb=m_fFy*0.66f;
    float fFex=objAlgo.computeFe(m_fE,1.0f,m_flx,m_frx);
    float fFey=objAlgo.computeFe(m_fE,1.0f,m_fly,m_fry);
    //
    //qDebug()<<" ";
    //qDebug()<<"Cc "<<fCc;
    //qDebug()<<"Fa "<<fFa;
   // qDebug()<<"Fb "<<fFb;
   // qDebug()<<"Fex "<<fFex;
    //qDebug()<<"Fey "<<fFey;
    //中间参数Cc
    QString strMidParam=QString("%1").arg(fCc,0,'f',3);
    ui->wCcEdit->setText(strMidParam);
    //中间参数l/r
    strMidParam=QString("%1").arg(flDivider,0,'f',3);
    ui->wldividerEdit->setText(strMidParam);
    //中间参数Fa
    strMidParam=QString("%1").arg(fFa,0,'f',3);
    ui->wFaEdit->setText(strMidParam);
    //中间参数Fb
    strMidParam=QString("%1").arg(fFb,0,'f',3);
    ui->wFbEdit->setText(strMidParam);
    //中间参数Fex
    strMidParam=QString("%1").arg(fFex,0,'f',3);
    ui->wFexEdit->setText(strMidParam);
    //中间参数Fey
    strMidParam=QString("%1").arg(fFey,0,'f',3);
    ui->wFeyEdit->setText(strMidParam);


    ui->tableWidgetMaxLoadCapacity->setRowCount(0);
    for(int nChannelIndex=0;nChannelIndex<m_nChannelNum;nChannelIndex+=4)
    {
        //计算fa,fbx,fby
        float fa=objAlgo.computefa(m_pWeightOutputVal[nChannelIndex],m_pWeightOutputVal[nChannelIndex+1],
                m_pWeightOutputVal[nChannelIndex+2],m_pWeightOutputVal[nChannelIndex+3] ,m_fDerrickWeight);
        float fbx=objAlgo.computefbx(m_pWeightOutputVal[nChannelIndex],m_pWeightOutputVal[nChannelIndex+1],
                m_pWeightOutputVal[nChannelIndex+2],m_pWeightOutputVal[nChannelIndex+3]);
        float fby=objAlgo.computefby(m_pWeightOutputVal[nChannelIndex],m_pWeightOutputVal[nChannelIndex+1],
                m_pWeightOutputVal[nChannelIndex+2],m_pWeightOutputVal[nChannelIndex+3]);

        //qDebug()<<QStringLiteral("分组编号:")<<nChannelIndex/4+1<<" fa: "<<fa<<" fbx: "<<fbx<<" fby: "<<fby;


        int nCurRow=nChannelIndex/4;
        ui->tableWidgetMaxLoadCapacity->insertRow(nCurRow);
        //第一列
        ui->tableWidgetMaxLoadCapacity->setItem(nCurRow,0,new QTableWidgetItem(QString::number(nCurRow+1)));
        //第二列 强度校核
        float fStrengthCheck1=objAlgo.strengthcheckFormula1(fa,fFa,0.85f,fbx,fFex,fFb,fby,fFey);
        QString strStrengthCheck1=QString("%1").arg(fStrengthCheck1,0,'g',3);
        float fStrengthCheck2=objAlgo.strengthcheckFormula2(fa,m_fFy,fbx,fFb,fby);
        QString strStrengthCheck2=QString("%1").arg(fStrengthCheck2,0,'g',3);
        ui->tableWidgetMaxLoadCapacity->setItem(nCurRow,1,new QTableWidgetItem(strStrengthCheck1+"   "+strStrengthCheck2));

        //第三列 最大承载
        float fMaxLoad=1.0f/fStrengthCheck1*m_fMaxLoadCapacity;
        QString strMaxLoad=QString("%1").arg(fMaxLoad,0,'f',3);
        ui->tableWidgetMaxLoadCapacity->setItem(nCurRow,2,new QTableWidgetItem(strMaxLoad));


    }

}
//获取界面线性外推参数
bool SDerrickLoadCapacityMainWin::getLinearExtrapolationGUIParm()//线性外推参数
{
    QString strMaxLoad =ui->wMaxLoadCapacityEdit->text();
    if(strMaxLoad.trimmed().isEmpty())
    {
        warningTips(QStringLiteral("请输入线性外推载荷"));
        return false;
    }
    bool bConvert=false;
    m_fMaxLoadCapacity = strMaxLoad.toFloat(&bConvert);
    if(!bConvert)
    {
        warningTips(QStringLiteral("线性外推载荷值无效，请重新输入"));
        return false;
    }

    for(int i=0;i<ui->tableWidgetLoadVal->rowCount();i++)
    {
        QTableWidgetItem *pItem =ui->tableWidgetLoadVal->item(i,1);
        m_pSinDataWeightA[i]= pItem->text().toFloat();

        //qDebug()<<"m_pSinDataWeightA[i]"<<m_pSinDataWeightA[i];
    }



    return true;
}
//获取界面承载能力参数
bool SDerrickLoadCapacityMainWin::getLoadCapacityGUIParm()
{
    QString strlx=ui->wlxEdit->text();//无支撑长度lx
    if(strlx.trimmed().isEmpty())
    {
        this->warningTips(QStringLiteral("请输入无支撑长度lx"));
        return false;
    }
    QString strly=ui->wlyEdit->text();//无支撑长度ly
    if(strly.trimmed().isEmpty())
    {
        this->warningTips(QStringLiteral("请输入无支撑长度ly"));
        return false;
    }
    QString strb=ui->wWingbEdit->text();//翼板长b
    if(strb.trimmed().isEmpty())
    {
        this->warningTips(QStringLiteral("请输入翼板长b"));
        return false;
    }
    QString stra=ui->wBodyaEdit->text();//腹板长a
    if(stra.trimmed().isEmpty())
    {
        this->warningTips(QStringLiteral("请输入腹板长a"));
        return false;
    }
    QString strt1=ui->wWingt1Edit->text();//翼板厚度t1
    if(strt1.trimmed().isEmpty())
    {
        this->warningTips(QStringLiteral("请输入翼板厚度t1"));
        return false;
    }
    QString strt2= ui->wBodyt2Edit->text();//腹板厚度t2
    if(strt2.trimmed().isEmpty())
    {
        this->warningTips(QStringLiteral("请输入腹板厚度t2"));
        return false;
    }
    bool bConvert=false;
    float lx=strlx.toFloat(&bConvert);
    if(!bConvert)
    {
        warningTips(QStringLiteral("无支撑长度lx值无效，请重新输入"));
        return false;
    }
    float ly=strly.toFloat(&bConvert);
    if(!bConvert)
    {
        warningTips(QStringLiteral("无支撑长度ly值无效，请重新输入"));
        return false;
    }

    m_flx=lx;//无支撑长度lx
    m_fly=ly;//无支撑长度ly

    float b=strb.toFloat(&bConvert);
    if(!bConvert)
    {
        warningTips(QStringLiteral("翼板长b值无效，请重新输入"));
        return false;
    }
    float a=stra.toFloat(&bConvert);
    if(!bConvert)
    {
        warningTips(QStringLiteral("腹板长a值无效，请重新输入"));
        return false;
    }
    float t1=strt1.toFloat(&bConvert);
    if(!bConvert)
    {
        warningTips(QStringLiteral("翼板厚度t1值无效，请重新输入"));
        return false;
    }
    float t2=strt2.toFloat(&bConvert);
    if(!bConvert)
    {
        warningTips(QStringLiteral("腹板厚度t2值无效，请重新输入"));
        return false;
    }
    //计算rx,ry
    float rx=0.0f;
    float ry=0.0f;
    SAlgo objAlgo;
    objAlgo.computerxry(b,a,t1,t2,rx,ry);
    m_frx=rx;
    m_fry=ry;
    m_fr=qMin(rx,ry);
    //qDebug()<<QStringLiteral("回转半径")<<"rx:"<< m_frx<< "ry:"<<m_fry<<"r:"<<m_fr;
    QString strMidParm= QString("%1").arg(m_frx,0,'f',3);
    ui->wrxEdit->setText(strMidParm);
    strMidParm= QString("%1").arg(m_fry,0,'f',3);
    ui->wryEdit->setText(strMidParm);
    strMidParm= QString("%1").arg(m_fr,0,'f',3);
    ui->wrEdit->setText(strMidParm);

    QString strE=ui->wEedit->text();//弹性模量
    if(strE.trimmed().isEmpty())
    {
        this->warningTips(QStringLiteral("请输入弹性模量E"));
        return false;
    }
    QString strFy=ui->wFyEdit->text();//屈服极限
    if(strFy.trimmed().isEmpty())
    {
        warningTips(QStringLiteral("请输入屈服极限Fy"));
        return false;
    }
    m_fE=strE.toFloat(&bConvert);
    if(!bConvert)
    {
        warningTips(QStringLiteral("弹性模量E值无效，请重新输入"));
        return false;
    }
    m_fFy=strFy.toFloat(&bConvert);
    if(!bConvert)
    {
        warningTips(QStringLiteral("屈服极限Fy值无效，请重新输入"));
        return false;
    }
    QString strDerrickWeight= ui->wDerrickWeightEdit->text();
    if(strDerrickWeight.trimmed().isEmpty())
    {
        warningTips(QStringLiteral("请输入井架自重"));
        return false;
    }
    m_fDerrickWeight=strDerrickWeight.toFloat(&bConvert);
    if(!bConvert)
    {
        warningTips(QStringLiteral("井架自重值无效，请重新输入"));
        return false;
    }


    return true;
}
void SDerrickLoadCapacityMainWin::warningTips(QString strWarningInfo)
{
    QMessageBox box(QMessageBox::Warning,QStringLiteral("提示"),strWarningInfo);
    box.setStandardButtons(QMessageBox::Ok);
    box.setButtonText(QMessageBox::Ok,QStringLiteral("确定"));
    box.exec();
}

//生成报表
void SDerrickLoadCapacityMainWin::on_click_export_word_trigger()
{

	gWordJssjLabelsNamesData jssjData;
	//填充数据
	float weightMax = 0; //最大钩载荷值
	int  weightMaxIndex = 0;//最大钩载荷值 索引值
	QString strScsj1; 
	for (int index =0; index < m_nMeasurePointNum && m_pSinDataWeightA != nullptr;++index)
	{

		if (m_pSinDataWeightA[index] > weightMax)
		{
			weightMax = m_pSinDataWeightA[index];
			weightMaxIndex = index;
		}
		strScsj1 += QString::number(m_pSinDataWeightA[index]);
		
	}

	jssjData.m_strScsj1 = strScsj1;
	jssjData.m_strScsj2 = QString::number(weightMax);
	




	wordshowDlg dlg;
	dlg.InitgWordJssjLabelsNamesData(jssjData);
	dlg.exec();
}
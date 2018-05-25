#include "sdatabasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>
SDataBaseManager *SDataBaseManager::g_pDBManager = NULL;
SDataBaseManager::SDataBaseManager()
{

}

SDataBaseManager *SDataBaseManager::getDataBaseManagerInstance()
{
    if (NULL == g_pDBManager)
    {

        g_pDBManager = new  SDataBaseManager;

    }

    return g_pDBManager;
}


bool SDataBaseManager::createAndOpenDatabase(QString strAccessFile)
{


    //        if(m_objWellDB.isValid() &&m_objWellDB.isOpen())
    //            return true;
    QSqlDatabase   objWellDB;
    if(QSqlDatabase::contains(strAccessFile))
    {
        objWellDB = QSqlDatabase::database(strAccessFile);
    }
    else
    {
        objWellDB = QSqlDatabase::addDatabase("QODBC",strAccessFile);

        QString strDBName = QString("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ=%1").arg(strAccessFile);
        objWellDB.setDatabaseName(strDBName);
    }


    if (!objWellDB.open())
    {
        qWarning(objWellDB.lastError().text().toLatin1().data());
        return false;
    }
    m_strAccessFileName=strAccessFile;

    return true;
}

QSqlDatabase SDataBaseManager::getWellDataBase()
{
    QSqlDatabase objWellDB = QSqlDatabase::database(m_strAccessFileName);

    return objWellDB;

}
bool SDataBaseManager::isValid()
{
    QSqlDatabase objWellDB = getWellDataBase();
    if(m_strAccessFileName.isEmpty() || !objWellDB.isValid() || !objWellDB.isOpen())
    {
        return false;
    }
    return true;
}

//从S4测量值表中查找所有数据
//vecMeasurePointLoad测量点载荷，对应S4表中P1列数据
//nMeasurePointNum:测量点个数

bool SDataBaseManager::selectMeasurePoint( QVector< float > & vecMeasurePointLoad,int &nChannelNum ,int &nMeasurePointNum)

{

    if(!isValid())
    {
        return false;
    }

    vecMeasurePointLoad.clear();

    int nTemp=0;
    QString strSQL = QStringLiteral("select * from S4测量值  ");
    QSqlQuery query(getWellDataBase());
    bool retBool = query.exec(strSQL);
    if (retBool == false)
    {
        qWarning(query.lastError().text().toLatin1().data());
        return false;
    }
    QSqlRecord rec = query.record();
    int nMeasurePointLoadIndex=rec.indexOf("P1");//P1列对应测量点载荷列索引
    QVector<int> vecChannelIndex;//通道数据所处的列索引
    int nAccessColumnNum=rec.count();////S4测量值表总列数列数

    for(  nTemp =0;nTemp<nAccessColumnNum;nTemp++)
    {
        if(rec.fieldName(nTemp).startsWith("S"))
        {
            vecChannelIndex.append(nTemp);

        }
    }
    nChannelNum=0;//通道数，即表中S1、S2...列数
    nChannelNum= vecChannelIndex.count();
    if(0 == nChannelNum   )
        return false;
   // QVector< float > *pVecEveryChannelVal= new QVector< float >[nChannelNum];


    int nAccessRowNum=0;//access行数
    float fValue=0.0f;
    while (query.next())
    {
        nAccessRowNum++;
        //P1列对应测量点载荷
        fValue=query.value(nMeasurePointLoadIndex).toFloat();
        vecMeasurePointLoad.append(fValue);
    }
    nMeasurePointNum=nAccessRowNum;

    return true;
}

//从测量数据表中查找应力测点，0度，theta1的值
bool SDataBaseManager::selectMeasureValue( QVector< float > & vecStressMeasurePoint,QVector< float > & vecZeroDegress ,QVector< float > & vecThetaVal)
{
    QString strSQL = QStringLiteral("select * from 测量数据表  ");
    QSqlQuery query(getWellDataBase());
    bool retBool = query.exec(strSQL);
    if (retBool == false)
    {
        qWarning(query.lastError().text().toLatin1().data());
        return false;
    }
    vecStressMeasurePoint.clear();
    vecZeroDegress.clear();
    vecThetaVal.clear();
    while (query.next())
        {
            vecStressMeasurePoint.append(query.value(2).toFloat());
            vecZeroDegress.append(query.value(3).toFloat());
            vecThetaVal.append(query.value(6).toFloat());
        }

    return true;
}

QString SDataBaseManager::getOriFileName()
{
    return m_strAccessFileName;
}

#ifndef SDATABASEMANAGER_H
#define SDATABASEMANAGER_H
#include <QSqlDatabase>
#include <QVector>
class SDataBaseManager
{
public:

    static SDataBaseManager *getDataBaseManagerInstance();
    bool   createAndOpenDatabase(QString strAccessFile);
    bool   selectMeasurePoint(QVector< float > & vecMeasurePointLoad,int &nChannelNum ,int &nMeasurePointNum);
   bool isValid();
   QString getOriFileName();

   bool   selectMeasureValue( QVector< float > & vecStressMeasurePoint,
                              QVector< float > & vecZeroDegress ,QVector< float > & vecThetaVal);


 private:
     SDataBaseManager();
    static SDataBaseManager *g_pDBManager;
    QString m_strAccessFileName;
     QSqlDatabase   getWellDataBase();
};

#endif // SDATABASEMANAGER_H

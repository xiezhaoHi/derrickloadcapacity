#ifndef SDERRICKLOADCAPACITYMAINWIN_H
#define SDERRICKLOADCAPACITYMAINWIN_H

#include <QMainWindow>

namespace Ui {
class SDerrickLoadCapacityMainWin;
}

class SDerrickLoadCapacityMainWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit SDerrickLoadCapacityMainWin(QWidget *parent = 0);
    ~SDerrickLoadCapacityMainWin();
public slots:
	void on_click_export_word_trigger();

    void on_actionOpenOriFile_triggered();
    void on_actionExit_triggered();
    void on_wComputeButton_clicked();
    bool getLinearExtrapolationGUIParm();//线性外推参数
    bool getLoadCapacityGUIParm();//承载能力参数

      float *** alloc3d( int l, int m, int n );
        void free3d( float * * * temp, int l, int m );
        float ** alloc2d( int m, int n );
        void free2d( float * * temp, int m );
protected:
        void  warningTips(QString strWarningInfo);
 private:
    Ui::SDerrickLoadCapacityMainWin *ui;


     float *** m_pSinTestDataA;//外推拟合数据
     float * m_pSinDataWeightA;//测量点值
     float *m_pWeightOutputVal;//weight文件中数据

     int m_nChannelNum;
     int m_nMeasurePointNum;
     float m_fMaxLoadCapacity;//线性外推载荷(设计最大钩载)

     float m_flx;//无支撑长度lx
     float m_fly;//无支撑长度ly
     float m_frx;//计算出的回转半径rx
     float m_fry;//计算出的回转半径ry
      float m_fr;//计算出的回转半径r(取rx,ry中小的)

      float m_fE;//弹性模量
      float m_fFy;//屈服极限
      float m_fDerrickWeight;//井架自重


};

#endif // SDERRICKLOADCAPACITYMAINWIN_H

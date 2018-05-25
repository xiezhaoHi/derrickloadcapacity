#ifndef SALGO_H
#define SALGO_H


class SAlgo
{
public:
    SAlgo();
    //计算中间参数Fa
    float computeFaVal(float k,float l,float r, float Cc,float Fy,float E);
    //计算中间参数Fe
    float computeFe(float E,float k,float l,float r);
    //计算中间参数Cc
    float computeCc(float E,float Fy);
    //pSinDataWeight 长度为nMeasurePointNum
    //pOutputData为输出数据，即weight文件数据,长度为nChannelNum
    //float fSinWeight:外推载荷
    //最小二乘法线性拟合
    void fitting(float ***pSinTestData,float *pSinDataWeight,
                 int nMeasurePointNum,int nMidDemMun,int nChannelNum,float fSinWeight,float *pOutputData);
    //计算回转半径rx,ry
    //b:翼板长b,腹板长a,翼板厚度t1;腹板厚度t2
    bool computerxry(float b,float a,float t1,float t2,float &rx,float &ry);


    //应力分解
    //计算fa
    float computefa(float fDelta1,float fDelta2,float fDelta3,float fDelta4,float fDerrickWeight);
    //计算fbx
    float computefbx(float fDelta1,float fDelta2,float fDelta3,float fDelta4);
    //计算fby
    float computefby(float fDelta1,float fDelta2,float fDelta3,float fDelta4);

    //强度校核公式1
    float strengthcheckFormula1(float fa,float Fa,float C,float fbx, float Fex,float Fb,
                                float fby,float Fey);
    //强度校核公式2
    float strengthcheckFormula2(float fa,float Fy,float fbx,float Fb,float fby);

};

#endif // SALGO_H

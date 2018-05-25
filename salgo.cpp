#include "salgo.h"
#include <math.h>
#ifndef M_PI
#define M_PI  3.14
#endif
SAlgo::SAlgo()
{

}
//计算中间参数Fa
float SAlgo::computeFaVal(float k,float l,float r, float Cc,float Fy,float E)
{
    float Fa=0.0f;
    if(k*l/r<Cc)
    {
        float ii=(1-(k*l/r)*(k*l/r)/(2*Cc*Cc))*Fy;
        float jj= 5/3.0f+3*(k*l/r)/(8*Cc)-(k*l/r)*(k*l/r)*(k*l/r)/(8*Cc*Cc*Cc);
        Fa=ii/jj;

    }
    else
    {
        float ii=12.0f*M_PI*M_PI*E;
        float jj=23.0f*(k*l/r)*(k*l/r);
        Fa=ii/jj;
    }
    return Fa;
}
//计算中间参数Fe
float SAlgo::computeFe(float E,float k,float l,float r)
{
    return 12*M_PI*M_PI*E/(23.0f*(k*l/r)*(k*l)/r);
}
//计算中间参数Cc
float SAlgo::computeCc(float E,float Fy)
{
    return sqrt((2*M_PI*M_PI*E)/Fy);
}


//pSinDataWeight 长度为nMeasurePointNum
//pOutputData为输出数据，即weight文件数据,长度为nChannelNum
//float fSinWeight:外推载荷
//最小二乘法线性拟合
void SAlgo::fitting(float ***pSinTestData,float *pSinDataWeight,
                    int nMeasurePointNum,int nMidDemMun,int nChannelNum,float fSinWeight,float *pOutputData)
{
    for(int i=0;i<nChannelNum;i++)
    {
        float xx=0.0f;
        float yy=0;
        float pp1=0;
        float XG21=0;
        float XG22=0;
        float Px=0;
        float Py=0;
        for(int j=0;j<nMeasurePointNum;j++)
        {
            yy+=pSinTestData[j][2][i];
            xx+=pSinDataWeight[j];
        }
        xx=xx/nMeasurePointNum;
        yy=yy/nMeasurePointNum;
        float XG1=0;
        for(int j=0;j<nMeasurePointNum;j++)
        {
            XG1=XG1+(pSinTestData[j][2][i] - yy) * (pSinDataWeight[j] -xx);
            XG21=XG21+(pSinDataWeight[j] -xx)*(pSinDataWeight[j] -xx);
            pp1=pp1+pSinDataWeight[j]*pSinTestData[j][2][i];
            Px=Px+pSinDataWeight[j]*pSinDataWeight[j];
            Py=Py+pSinTestData[j][2][i]*pSinTestData[j][2][i];
            XG22=XG22+(pSinTestData[j][2][i] - yy)*(pSinTestData[j][2][i] - yy);
        }
        //float XG2=sqrt(XG21*XG22);
        float PP2=abs((int)(Px-nChannelNum*xx*xx))*(Py-nChannelNum*yy*yy);
        //float p11=(pp1-nChannelNum*xx*yy)/sqrt(PP2);
        float A1=(pp1 -nChannelNum*xx*yy )/(Px - nChannelNum*xx*xx);
        // float B1=yy-A1*xx;
        float Ai=XG1/XG21;
        float Bi=yy-Ai*xx;
        float fWeight=Bi+Ai*fSinWeight;
        pOutputData[i]=fWeight;

    }

}

//计算回转半径rx,ry
//b:翼板长b,腹板长a,翼板厚度t1;腹板厚度t2
bool SAlgo::computerxry(float b,float a,float t1,float t2,float &rx,float &ry)
{
    float Ix1=2.0f/3*(a/2.0f-t1)*t2*t2*t2/8.0f;
    float Ix2=2.0f/3*t1*b*b*b/8.0f;
    float Iy1=t2/3.0f*(a/2.0f-t1)*(a/2.0f-t1)*(a/2.0f-t1);
    float Iy2=b/3.0f*(a*a*a/8.0f-(a/2.0f-t1)*(a/2.0f-t1)*(a/2.0f-t1));
    float Ix=2.0f*(Ix1+Ix2);
    float Iy=2.0f*(Iy1+Iy2);
    float A=2.0f*t1*b+t2*(a-2.0f*t1);
    rx=sqrt(Ix/A);
    ry=sqrt(Iy/A);
    return true;
}


//应力分解,计算fa
float SAlgo::computefa(float fDelta1,float fDelta2,float fDelta3,float fDelta4,float fDerrickWeight)
{
    return fabs(fDelta1+fDelta2+fDelta3+fDelta4)/4.0f+fDerrickWeight;
}
//应力分解,计算fbx
float SAlgo::computefbx(float fDelta1,float fDelta2,float fDelta3,float fDelta4)
{
    return fabs((fDelta1-fDelta3)-(fDelta2-fDelta4))/4.0f;
}
//应力分解,计算fby
float SAlgo::computefby(float fDelta1,float fDelta2,float fDelta3,float fDelta4)
{
    return  fabs((fDelta2-fDelta4)+(fDelta1-fDelta3))/4;
}


//强度校核公式1
float SAlgo::strengthcheckFormula1(float fa,float Fa,float C,float fbx, float Fex,float Fb,
                            float fby,float Fey)
{
    float part1=0;
    float part2=0;
    float part3=0;
    part1=fa/Fa;
    part2=C*fbx/((1-fa/Fex)*Fb);
    part3=C*fby/((1-fa/Fey)*Fb);
    float fResult=part1+part2+part3;
    return fResult;
}

//强度校核公式2
float SAlgo::strengthcheckFormula2(float fa,float Fy,float fbx,float Fb,float fby)
{
    float part1=fa/(0.6f*Fy);
    float part2=fbx/Fb;
    float part3=fby/Fb;
    float fResult=part1+part2+part3;
    return fResult;
}

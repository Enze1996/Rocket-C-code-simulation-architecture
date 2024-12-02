#ifndef AERODYNAMIC_H
#define AERODYNAMIC_H

class AerodynamicCoefficients {
public:
    // 构造函数：加载气动系数数据
    AerodynamicCoefficients();

    // 根据输入的马赫数、攻角、侧滑角计算气动系数
    void ComputeCoefficients(double mach, double alpha, double beta);

    // 获取计算的气动系数（CX, CY, CZ, CMX, CMY, CMZ）
    void GetCoefficients(double CxyzCmxyz[6]);

    // 在void ComputeCoefficients(double mach, double alpha, double beta)中也是全局变量直接使用！
    double CX[6][23][13];  // CX 的3维数组
    double CY[6][23][13];  // CY 的3维数组
    double CZ[6][23][13];  // CZ 的3维数组
    double CMX[6][23][13]; // CMX 的3维数组
    double CMY[6][23][13]; // CMY 的3维数组
    double CMZ[6][23][13]; // CMZ 的3维数组


    // 离散点数组
    double Ma[6] = { 0.3, 0.4, 0.6, 0.8,0.95,1.05 };
    double Alpha[23] = { -15,-10 ,-8 ,-6 ,-4 ,-2,0,2,4,6,8,10,12,15,20,25,30,40,50,60,70,80,90 };  // 攻角
    double Beta[13] = { -15 ,-10, -8 ,-6 ,-4 ,-2 ,0 ,  2  , 4  , 6 ,  8 , 10 ,15 }; // 侧滑角



    const int Mach_num = 6;
    const int Alpha_num = 23;
    const int Beta_num = 13;


private:
    // 以下数组数据需要初始化：


    double CxyzCMxyz[6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }; // 气动力和气动力矩系数 [cx, cy, cz, CMx, CMy, CMz]
};

#endif

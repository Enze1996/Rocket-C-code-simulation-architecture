#ifndef AERODYNAMIC_H
#define AERODYNAMIC_H

class AerodynamicCoefficients {
public:
    // ���캯������������ϵ������
    AerodynamicCoefficients();

    // �������������������ǡ��໬�Ǽ�������ϵ��
    void ComputeCoefficients(double mach, double alpha, double beta);

    // ��ȡ���������ϵ����CX, CY, CZ, CMX, CMY, CMZ��
    void GetCoefficients(double CxyzCmxyz[6]);

    // ��void ComputeCoefficients(double mach, double alpha, double beta)��Ҳ��ȫ�ֱ���ֱ��ʹ�ã�
    double CX[6][23][13];  // CX ��3ά����
    double CY[6][23][13];  // CY ��3ά����
    double CZ[6][23][13];  // CZ ��3ά����
    double CMX[6][23][13]; // CMX ��3ά����
    double CMY[6][23][13]; // CMY ��3ά����
    double CMZ[6][23][13]; // CMZ ��3ά����


    // ��ɢ������
    double Ma[6] = { 0.3, 0.4, 0.6, 0.8,0.95,1.05 };
    double Alpha[23] = { -15,-10 ,-8 ,-6 ,-4 ,-2,0,2,4,6,8,10,12,15,20,25,30,40,50,60,70,80,90 };  // ����
    double Beta[13] = { -15 ,-10, -8 ,-6 ,-4 ,-2 ,0 ,  2  , 4  , 6 ,  8 , 10 ,15 }; // �໬��



    const int Mach_num = 6;
    const int Alpha_num = 23;
    const int Beta_num = 13;


private:
    // ��������������Ҫ��ʼ����


    double CxyzCMxyz[6] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }; // ����������������ϵ�� [cx, cy, cz, CMx, CMy, CMz]
};

#endif

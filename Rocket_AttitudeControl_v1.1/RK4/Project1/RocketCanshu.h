
#pragma once
//ʹ���� #pragma once ������ͷ�ļ�����ΰ�������������ȷ��ͷ�ļ�ֻ�ᱻ����һ�Σ������ظ����塣


//


struct RocketCanshu {


     //const ���η���ʾ�ñ����ǳ��������ڳ������й����У�g ��ֵ���ܱ��޸�

 const double m = 5000.0;  // �����������λ��kg

 const double g = 9.81;    // �������ٶȣ���λ��m/s^2

 const double I_x = 1000.0; // ����Ĺ��Ծأ���λ��kg��m^2

 const double I_y = 1000.0; // ����Ĺ��Ծأ���λ��kg��m^2

 const double I_z = 1000.0; // ����Ĺ��Ծأ���λ��kg��m^2
};

// ����ȫ��ʵ���������ļ������Է��� -- 2024-11-27
// ��������� extern ���� RocketCanshu  ������diff_fun.cpp ��main1.cpp�б�ͬʱ����
//�� main.cpp �������ļ��ж������� RocketCanshu ���͵�ʵ�� RockCanshu��������ÿ���ļ��ж������� RocketCanshu.h��
// ����ܵ��� ���Ӵ��� �� �ظ����� ����




extern RocketCanshu RockCanshu;
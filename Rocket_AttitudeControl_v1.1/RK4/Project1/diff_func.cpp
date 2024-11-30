// v1.0  -- 2024-11-27 
// ���������л�������������Ծغͳ�ʼ״̬�����Խ���Щ΢�ַ��̱�д�� diff_func.cpp �С�
// �����Ǽ򻯵Ĵ���ʵ�֣�
#include "diff_func.h"
#include <cmath>
#include "RocketCanshu.h"
#include "test.h"

// �����ȫ�ּ������-- ֱ��ȫ�ֱ�������
RocketCanshu RockCanshu = RocketCanshu();




void diff_func(int i_tic, int i_lgkt, double* datain, double* Sheet1, double* Sheet2)
{
    // ״̬����
    // Sheet1[0] - x, Sheet1[1] - y, Sheet1[2] - z (λ��)
    // Sheet1[3] - vx, Sheet1[4] - vy, Sheet1[5] - vz (�ٶ�)
    // Sheet1[6] - phi (��ת��), Sheet1[7] - theta (������), Sheet1[8] - psi (ƫ����)
    // Sheet1[9] - p (��ת���ٶ�), Sheet1[10] - q (�������ٶ�), Sheet1[11] - r (ƫ�����ٶ�)

    // Sheet2����洢����
    // Sheet2[0] - dx/dt, Sheet2[1] - dy/dt, Sheet2[2] - dz/dt (�ٶ�)
    // Sheet2[3] - dvx/dt, Sheet2[4] - dvy/dt, Sheet2[5] - dvz/dt (���ٶ�)
    // Sheet2[6] - dphi/dt, Sheet2[7] - dtheta/dt, Sheet2[8] - dpsi/dt (���ٶ�)
    // Sheet2[9] - dp/dt, Sheet2[10] - dq/dt, Sheet2[11] - dr/dt (�Ǽ��ٶ�)

    // λ�õĵ��� = �ٶ�
    Sheet2[0] = Sheet1[3];
    Sheet2[1] = Sheet1[4];
    Sheet2[2] = Sheet1[5];

    // �ٶȵĵ��������ٶ� = ����/m - �������ٶ�
    Sheet2[3] = 0;  // ����û���ⲿ���ٶ�
    Sheet2[4] = 0;
    Sheet2[5] = -RockCanshu.g;  // ����������

    // ��̬�ǵĵ��� = ���ٶ�
    Sheet2[6] = Sheet1[9];
    Sheet2[7] = Sheet1[10];
    Sheet2[8] = Sheet1[11];

    // �Ǽ��ٶȵļ���
    // ���������أ�T_x, T_y, T_z �ɿ���ϵͳ�ṩ
    double T_x =1;  // ��������
    double T_y = 1;
    double T_z = 1;

    // �Ǽ��ٶȣ����ڼ򻯵Ļ������ѧ����
    Sheet2[9] = (RockCanshu.I_y - RockCanshu.I_z) * Sheet1[10] * Sheet1[11] / RockCanshu.I_x + T_x / RockCanshu.I_x;
    Sheet2[10] = I_g;// (I_z - I_x)* Sheet1[9] * Sheet1[11] / I_y + T_y / I_y;
    Sheet2[11] = 0;// (I_x - I_y)* Sheet1[9] * Sheet1[10] / I_z + T_z / I_z;
}

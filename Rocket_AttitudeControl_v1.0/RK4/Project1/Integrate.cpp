
#include "Integrate.h"

void Integrater::Initial(int N, double T, double* chuzhi) {
    xs1_lgkt[0] = 1.0 / 2.0; xs1_lgkt[1] = 1.0 / 2.0; xs1_lgkt[2] = 1.0; xs1_lgkt[3] = 1.0;
    xs2_lgkt[0] = 1.0 / 6.0; xs2_lgkt[1] = 2.0 / 6.0; xs2_lgkt[2] = 2.0 / 6.0; xs2_lgkt[3] = 1.0 / 6.0;

    n_state = N;
    Ts = T;
    i_tic = 0;

    Sheet1 = new double[n_state];
    Sheet2 = new double[n_state];
    Sheet3 = new double[n_state];
    Sheet0 = chuzhi;
}

Integrater::~Integrater() {
    delete[] Sheet1;
    delete[] Sheet2;
    delete[] Sheet3;
}

void Integrater::Integrate(void(*diff_func)(int, int, double*, double*, double*), int i_tic, double* datain) {
    int i, i_lgkt;

    // Copy initial values to temporary sheets
    for (i = 0; i < n_state; i++) {
        Sheet1[i] = Sheet0[i];
        Sheet3[i] = Sheet0[i];
    }

    // Runge-Kutta method (4 stages)
    for (i_lgkt = 0; i_lgkt < 4; i_lgkt++) {
        // diff_func���㵼�����洢��Sheet2
        diff_func(i_tic, i_lgkt, datain, Sheet1, Sheet2);

        // ����Sheet1��������һ�׶ε�״̬(Sheet3) �͵�ǰ����(Sheet2) ���м���
        for (i = 0; i < n_state; i++) {
            Sheet1[i] = Sheet3[i] + xs1_lgkt[i_lgkt] * Ts * Sheet2[i];  // ���㵱ǰ�׶ε�Ԥ��ֵ
        }

        // ����Sheet0������״̬��
        for (i = 0; i < n_state; i++) {
            Sheet0[i] = Sheet0[i] + xs1_lgkt[i_lgkt] * Ts * Sheet2[i];  // �ۼ����н׶εļ���
        }
    }

}

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
        // diff_func计算导数并存储到Sheet2
        diff_func(i_tic, i_lgkt, datain, Sheet1, Sheet2);

        // 更新Sheet1：根据上一阶段的状态(Sheet3) 和当前导数(Sheet2) 进行计算
        for (i = 0; i < n_state; i++) {
            Sheet1[i] = Sheet3[i] + xs1_lgkt[i_lgkt] * Ts * Sheet2[i];  // 计算当前阶段的预测值
        }

        // 更新Sheet0（最终状态）
        for (i = 0; i < n_state; i++) {
            Sheet0[i] = Sheet0[i] + xs1_lgkt[i_lgkt] * Ts * Sheet2[i];  // 累加所有阶段的计算
        }
    }

}
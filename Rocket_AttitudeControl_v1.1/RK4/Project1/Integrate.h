
#ifndef INTEGRATE_H
#define INTEGRATE_H

class Integrater {
public:
    // Constructor to initialize the integrator
    void Initial(int N, double T, double* chuzhi);

    // Destructor to clean up memory
    ~Integrater();

    // Main integration function
    void Integrate(void(*diff_func)(int, int, double*, double*, double*), int i_tic, double* datain);

    // Public access to Sheet0
    double* Sheet0;

private:
    int n_state;      // Number of state variables
    double Ts;        // Time step
    int i_tic;        // Time tick (iteration index)

    double* Sheet1;   // Temporary storage for state values  用作当前阶段的临时状态存储，每个阶段结束后其内容会被更新。
    double* Sheet2;   // Temporary storage for derivatives
    double* Sheet3;   // Backup storage for state values 用作保存上一阶段状态的备份，它的值在整个四阶 Runge-Kutta 过程中不变，直到开始新的阶段。

    double xs1_lgkt[4];  // Runge-Kutta coefficients for state updates
    double xs2_lgkt[4];  // Runge-Kutta coefficients for derivative updates
}; 

#endif // INTEGRATE_H
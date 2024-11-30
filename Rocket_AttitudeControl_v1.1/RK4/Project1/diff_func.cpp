// v1.0  -- 2024-11-27 
// 假设我们有火箭的质量、惯性矩和初始状态，可以将这些微分方程编写在 diff_func.cpp 中。
// 以下是简化的代码实现：
#include "diff_func.h"
#include <cmath>
#include "RocketCanshu.h"
#include "test.h"

// 火箭的全局箭体参数-- 直接全局变量调用
RocketCanshu RockCanshu = RocketCanshu();




void diff_func(int i_tic, int i_lgkt, double* datain, double* Sheet1, double* Sheet2)
{
    // 状态变量
    // Sheet1[0] - x, Sheet1[1] - y, Sheet1[2] - z (位置)
    // Sheet1[3] - vx, Sheet1[4] - vy, Sheet1[5] - vz (速度)
    // Sheet1[6] - phi (滚转角), Sheet1[7] - theta (俯仰角), Sheet1[8] - psi (偏航角)
    // Sheet1[9] - p (滚转角速度), Sheet1[10] - q (俯仰角速度), Sheet1[11] - r (偏航角速度)

    // Sheet2数组存储导数
    // Sheet2[0] - dx/dt, Sheet2[1] - dy/dt, Sheet2[2] - dz/dt (速度)
    // Sheet2[3] - dvx/dt, Sheet2[4] - dvy/dt, Sheet2[5] - dvz/dt (加速度)
    // Sheet2[6] - dphi/dt, Sheet2[7] - dtheta/dt, Sheet2[8] - dpsi/dt (角速度)
    // Sheet2[9] - dp/dt, Sheet2[10] - dq/dt, Sheet2[11] - dr/dt (角加速度)

    // 位置的导数 = 速度
    Sheet2[0] = Sheet1[3];
    Sheet2[1] = Sheet1[4];
    Sheet2[2] = Sheet1[5];

    // 速度的导数：加速度 = 推力/m - 重力加速度
    Sheet2[3] = 0;  // 假设没有外部加速度
    Sheet2[4] = 0;
    Sheet2[5] = -RockCanshu.g;  // 仅重力作用

    // 姿态角的导数 = 角速度
    Sheet2[6] = Sheet1[9];
    Sheet2[7] = Sheet1[10];
    Sheet2[8] = Sheet1[11];

    // 角加速度的计算
    // 假设有力矩：T_x, T_y, T_z 由控制系统提供
    double T_x =1;  // 控制力矩
    double T_y = 1;
    double T_z = 1;

    // 角加速度：基于简化的火箭动力学方程
    Sheet2[9] = (RockCanshu.I_y - RockCanshu.I_z) * Sheet1[10] * Sheet1[11] / RockCanshu.I_x + T_x / RockCanshu.I_x;
    Sheet2[10] = I_g;// (I_z - I_x)* Sheet1[9] * Sheet1[11] / I_y + T_y / I_y;
    Sheet2[11] = 0;// (I_x - I_y)* Sheet1[9] * Sheet1[10] / I_z + T_z / I_z;
}

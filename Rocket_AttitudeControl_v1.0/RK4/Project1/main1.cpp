// v1.0  -- 2024-11-27 

#include<iostream>
#include "Integrate.h"
#include "diff_func.h"  // 引入微分方程头文件
#include "RocketCanshu.h"

#include<fstream>
using namespace std;

//创建一个实例object，取数
RocketCanshu RockCanshu = RocketCanshu();


int main() {
    // 火箭状态变量的数量：位置（x, y, z）、速度（vx, vy, vz）、姿态角（phi, theta, psi）、角速度（p, q, r）
    const int N = 12;  // 12个状态变量
    const double Ts = 0.01;  // 时间步长（例如，10ms）

    // 初始条件（假设初始位置为 [0, 0, 0]，初始速度为 [0, 0, 0]，初始姿态角为 [0, 0, 0]，初始角速度为 [0, 0, 0]）
    double initial_conditions[12] = { 0.0, 0.0, 0.0,   // 位置 x, y, z
                                      0.0, 0.0, 0.0,   // 速度 vx, vy, vz
                                      0.0, 0.0, 0.0,   // 姿态角 phi, theta, psi
                                      0.0, 0.0, 0.0 }; // 角速度 p, q, r

    // 创建一个 Integrater 对象
    Integrater integrater;
    integrater.Initial(N, Ts, initial_conditions);

    // 存储结果的数组（每个时间步长的状态）
    const int num_steps = 1000;
    double results[12][num_steps];  // 存储12个状态变量在每个时间步长的值

    // 时间积分
    for (int i = 0; i < num_steps; i++) {
        // 保存当前状态到 results
        for (int j = 0; j < N; j++) {
            results[j][i] = integrater.Sheet0[j];  // 将每个状态变量保存到 results 中
        }

        // 调用 Integrate 函数来更新状态
        // 注意，这里每次迭代时，我们传入当前的状态（即 integrater.Sheet0）
        integrater.Integrate(diff_func, i, integrater.Sheet0);  // 使用当前状态进行积分
    }

    // 输出结果（演示：打印前10个时间步的结果）
    for (int i = 0; i < 100; i++) {
        cout << "Step " << i << ": ";
        cout << "x = " << results[0][i] << ", y = " << results[1][i] << ", z = " << results[2][i] << ", ";
        cout << "vx = " << results[3][i] << ", vy = " << results[4][i] << ", vz = " << results[5][i] << ", ";
        cout << "phi = " << results[6][i] << ", theta = " << results[7][i] << ", psi = " << results[8][i] << ", ";
        cout << "p = " << results[9][i] << ", q = " << results[10][i] << ", r = " << results[11][i] << endl;
    }

    // 将结果输出到文件
    ofstream output_file("results241128.txt");  // 创建一个文件流对象来写入文件
    if (output_file.is_open()) {
        for (int i = 0; i < num_steps; i++) {
            output_file << "Step " << i << ": ";
            output_file << "x = " << results[0][i] << ", y = " << results[1][i] << ", z = " << results[2][i] << ", ";
            output_file << "vx = " << results[3][i] << ", vy = " << results[4][i] << ", vz = " << results[5][i] << ", ";
            output_file << "phi = " << results[6][i] << ", theta = " << results[7][i] << ", psi = " << results[8][i] << ", ";
            output_file << "p = " << results[9][i] << ", q = " << results[10][i] << ", r = " << results[11][i] << endl;
        }
        output_file.close();  // 关闭文件流
        cout << "Results have been saved to results241128.txt" << endl;
    }
    else {
        cout << "Failed to open file for writing." << endl;
    }
    cout <<"火箭的质量为："<< RockCanshu.M << endl;

    return 0;
}

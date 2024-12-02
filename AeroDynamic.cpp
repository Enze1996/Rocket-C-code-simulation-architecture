// 气动系数--三维线性插值完成测试 -- 2024 - 12-02
// findIndices()函数的气动表的行数需要更改

#include "AeroDynamic.h"
#include <iostream>
#include <cmath>
#include <string>
#include<vector>
#include <fstream>
#include <sstream>

using namespace std;
// 

// 函数：查找所有等于 Ma0 - alpha0 -beta0 的索引
vector<int> findIndices(double Data_QidongBiao[877][10], double Ma_alpha_beta0, int col) {
    vector<int> indices;  // 用于存储符合条件的行索引

    // 遍历 Data_QidongBiao 的指定列
    for (int i = 0; i < 877; ++i) {
        if (Data_QidongBiao[i][col] == Ma_alpha_beta0) {  // 如果当前列的值等于 Ma0
            indices.push_back(i);  // 保存符合条件的行索引
        }
    }
    return indices;
}

// 函数：计算三个索引数组的交集
vector<int> findCommonIndex(const vector<int>& indices_Ma1, const vector<int>& indices_alpha1, const vector<int>& indices_beta1) {
    vector<int> index_common;

    // 遍历第一个数组
    for (int ma : indices_Ma1) {
        // 如果 ma 也在第二个数组中
        if (find(indices_alpha1.begin(), indices_alpha1.end(), ma) != indices_alpha1.end()) {
            // 并且在第三个数组中
            if (find(indices_beta1.begin(), indices_beta1.end(), ma) != indices_beta1.end()) {
                index_common.push_back(ma);  // 找到交集元素，加入结果数组
            }
        }
    }
    return index_common;
}


AerodynamicCoefficients::AerodynamicCoefficients() 
{   
    // 该处代码作用---得到6个三维气动系数数组
    // 这里初始化气动系数数据 -- 将 CSV 数据正确地加载并填充到三维数组中
    // 你可以从文件中加载这些数据，或者使用某些已知的气动数据进行初始化

// 文件路径 ---- 转化为[文本文件.txt] 制表符分隔的数据文件 ， 一般不用读取.csv的逗号分隔的数据文件 ，读取时易出错！
    string filePath = R"(D:\GNC\工作_火箭姿控系统\火箭六自由度仿真程序\ZS_1_AttitudeControl_v1.5\RK4\Project1\data_qidong11.txt)";

    // 打开文件
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        //return 1;  // 文件打开失败，退出程序
    }

    string line;
    vector<vector<double>> QiDongdata;  // 用于存储读取的数据

    // 逐行读取文件
    while (getline(file, line)) {
        // 跳过空行
        if (line.empty()) {
            continue;
        }

        //cout << "Reading line: " << line << endl;  // 调试：输出读取的行
        stringstream ss(line);  // 使用 stringstream 来拆分每一行的内容
        string value;
        vector<double> row;     // 用于存储每一行的数据

        // 逐个读取制表符分隔的值并转化为 double
        while (getline(ss, value, '\t')) {
            try {
                row.push_back(stod(value));  // 将字符串转换为 double 并存储
            }
            catch (const invalid_argument& e) {
                cerr << "Error converting value: '" << value << "' to double." << endl;
            }
        }

        // 如果当前行的数据不完整（列数不符合要求），则跳过
        if (row.size() < 10) {
            cerr << "Skipping row with insufficient columns: " << line << endl;
            continue;
        }

        // 将有效数据添加到 QiDongdata 中
        QiDongdata.push_back(row);
    }

    file.close();  // 关闭文件

    int n = QiDongdata.size(); // 获取数据的行数
    cout << "原始气动数据表的行数"<<n << endl;

    int NN = n;

    // Data_QidongBiao;// = QiDongdata; // n*10的数组
        // 创建一个二维数组，初始值为零
    double Data_QidongBiao[877][10] = { {0} };
    for (int i = 0; i < NN; ++i) {
        for (int j = 0; j < 10; ++j) {
            // 将 QiDongdata 的数据复制到 Data_QidongBiao 数组
            if (i < NN) {  // 确保不越界
                Data_QidongBiao[i][j] = QiDongdata[i][j];
            }
        }
    }

    // 遍历三维数组并赋值
    for (int i = 0; i < Mach_num; i++) {
        for (int j = 0; j < Alpha_num; j++) {
            for (int k = 0; k < Beta_num; k++) {
              // 循环遍历-->获得三维插值数组：CX[i][j][k]、CY[i][j][k]、CZ[i][j][k]、CMX[i][j][k]、CMY[i][j][k]、CMZ[i][j][k]

                double Ma1    =  Ma[i];
                double alpha1 =  Alpha[j];
                double beta1  =  Beta[k];

              vector<int> indices_Ma1 = findIndices(Data_QidongBiao, Ma1, 1);
              vector<int> indices_alpha1 = findIndices(Data_QidongBiao, alpha1, 2);
              vector<int> indices_beta1 = findIndices(Data_QidongBiao, beta1, 3);
              // 调用 findCommonIndex 函数计算交集-确定唯一一组[Ma,alpha,beta]对应的在气动表中的索引行数
              vector<int> commonIndices = findCommonIndex(indices_Ma1, indices_alpha1, indices_beta1);

                    int IndexOnly;
                    // 获取交集的索引
                    if (!commonIndices.empty())
                    {
                        IndexOnly = commonIndices.back();
                      // cout << "共同索引是：" << IndexOnly << endl;
                    }
                    else
                    {
                        break;
                    }
                    CX[i][j][k] = Data_QidongBiao[IndexOnly][4];  // Data_QidongBiao 中第 5 列是 CX
                    CY[i][j][k] = Data_QidongBiao[IndexOnly][5];  // Data_QidongBiao 中第 6 列是 CY
                    CZ[i][j][k] = Data_QidongBiao[IndexOnly][6];  // Data_QidongBiao 中第 7 列是 CZ
                    CMX[i][j][k] = Data_QidongBiao[IndexOnly][7]; // Data_QidongBiao 中第 8 列是 CMX
                    CMY[i][j][k] = Data_QidongBiao[IndexOnly][8]; // Data_QidongBiao 中第 9 列是 CMY
                    CMZ[i][j][k] = Data_QidongBiao[IndexOnly][9]; // Data_QidongBiao 中第 10 列是 CMZ       
            }
        }
    }
}

void AerodynamicCoefficients::ComputeCoefficients(double mach, double alpha, double beta) 
{
    int i = 0, j = 0, k = 0;

    // 查找最接近的马赫数、攻角和侧滑角的离散点值
    for (int ii = 0; ii < Mach_num; ii++) {
        if (Ma[ii] >= mach) {
            i = ii;
            break;
        }
    }
    for (int jj = 0; jj < Alpha_num; jj++) {
        if (Alpha[jj] >= alpha) {
            j = jj;
            break;
        }
    }
    for (int kk = 0; kk < Beta_num; kk++) {
        if (Beta[kk] >= beta) {
            k = kk;
            break;
        }
    }
    // 查找对应的马赫数、攻角、侧滑角的实际值
    double Ma1 = Ma[i - 1];
    double Ma2 = Ma[i];
    double alpha1 = Alpha[j - 1];
    double alpha2 = Alpha[j];
    double beta1 = Beta[k - 1];
    double beta2 = Beta[k];


    // CX--三维线性插值
    double CX1 = CX[i - 1][j - 1][k - 1];
    double CX2 = CX[i - 1][j - 1][k];
    double CX3 = CX[i - 1][j][k - 1];
    double CX4 = CX[i - 1][j][k];
    double CX5 = CX[i][j - 1][k - 1];
    double CX6 = CX[i][j - 1][k];
    double CX7 = CX[i][j][k - 1];
    double CX8 = CX[i][j][k];

    // 在侧滑角插值、攻角、马赫数 (Ma) 上三维插值
    double inter_CX_beta, inter_CX_alpha, inter_CX_Ma, interpolatedCX;
    inter_CX_beta = CX7 + (CX8 - CX7) / (beta2 - beta1) * (beta - beta1);                      // 侧滑角插值
    inter_CX_alpha = CX6 + (CX8 - CX6) / (alpha2 - alpha1) * (alpha - alpha1);    //  攻角插值
    inter_CX_Ma = CX4 + (CX8 - CX4) / (Ma2 - Ma1) * (mach - Ma1);   // 马赫数插值
    interpolatedCX = (inter_CX_Ma + inter_CX_alpha + inter_CX_beta) / 3.0;

    //cout << "测试的数据 biao_inter_CX ：" << CX8 << endl;
    //cout << "测试的数据 inter_CX：：" << interpolatedCX << endl;
    // 
    // CY-三维线性插值
    double CY1 = CY[i - 1][j - 1][k - 1];
    double CY2 = CY[i - 1][j - 1][k];
    double CY3 = CY[i - 1][j][k - 1];
    double CY4 = CY[i - 1][j][k];
    double CY5 = CY[i][j - 1][k - 1];
    double CY6 = CY[i][j - 1][k];
    double CY7 = CY[i][j][k - 1];
    double CY8 = CY[i][j][k];

    double inter_CY_beta, inter_CY_alpha, inter_CY_Ma, interpolatedCY;
    inter_CY_beta = CY7 + (CY8 - CY7) / (beta2 - beta1) * (beta - beta1);                      // 侧滑角插值
    inter_CY_alpha = CY6 + (CY8 - CY6) / (alpha2 - alpha1) * (alpha - alpha1);    //  攻角插值
    inter_CY_Ma = CY4 + (CY8 - CY4) / (Ma2 - Ma1) * (mach - Ma1);   // 马赫数插值
    interpolatedCY = (inter_CY_Ma + inter_CY_alpha + inter_CY_beta) / 3.0;

    //cout << "测试的数据 biao_inter_CY ：" << CY8 << endl;
   // cout << "测试的数据 inter_CY：：" << interpolatedCY << endl;

    // CZ-三维线性插值
    double CZ1 = CZ[i - 1][j - 1][k - 1];
    double CZ2 = CZ[i - 1][j - 1][k];
    double CZ3 = CZ[i - 1][j][k - 1];
    double CZ4 = CZ[i - 1][j][k];
    double CZ5 = CZ[i][j - 1][k - 1];
    double CZ6 = CZ[i][j - 1][k];
    double CZ7 = CZ[i][j][k - 1];
    double CZ8 = CZ[i][j][k];

    double inter_CZ_beta, inter_CZ_alpha, inter_CZ_Ma, interpolatedCZ;
    inter_CZ_beta = CZ7 + (CZ8 - CZ7) / (beta2 - beta1) * (beta - beta1);                      // 侧滑角插值
    inter_CZ_alpha = CZ6 + (CZ8 - CZ6) / (alpha2 - alpha1) * (alpha - alpha1);    //  攻角插值
    inter_CZ_Ma = CZ4 + (CZ8 - CZ4) / (Ma2 - Ma1) * (mach - Ma1);   // 马赫数插值
    interpolatedCZ = (inter_CZ_Ma + inter_CZ_alpha + inter_CZ_beta) / 3.0;


    // CMX-三维线性插值
    double CMX1 = CMX[i - 1][j - 1][k - 1];
    double CMX2 = CMX[i - 1][j - 1][k];
    double CMX3 = CMX[i - 1][j][k - 1];
    double CMX4 = CMX[i - 1][j][k];
    double CMX5 = CMX[i][j - 1][k - 1];
    double CMX6 = CMX[i][j - 1][k];
    double CMX7 = CMX[i][j][k - 1];
    double CMX8 = CMX[i][j][k];
    double inter_CMX_beta, inter_CMX_alpha, inter_CMX_Ma, interpolatedCMX;
    inter_CMX_beta = CMX7 + (CMX8 - CMX7) / (beta2 - beta1) * (beta - beta1);                      // 侧滑角插值
    inter_CMX_alpha = CMX6 + (CMX8 - CMX6) / (alpha2 - alpha1) * (alpha - alpha1);    //  攻角插值
    inter_CMX_Ma = CMX4 + (CMX8 - CMX4) / (Ma2 - Ma1) * (mach - Ma1);   // 马赫数插值
    interpolatedCMX = (inter_CMX_Ma + inter_CMX_alpha + inter_CMX_beta) / 3.0;

    // CMY-三维线性插值
    double CMY1 = CMY[i - 1][j - 1][k - 1];
    double CMY2 = CMY[i - 1][j - 1][k];
    double CMY3 = CMY[i - 1][j][k - 1];
    double CMY4 = CMY[i - 1][j][k];
    double CMY5 = CMY[i][j - 1][k - 1];
    double CMY6 = CMY[i][j - 1][k];
    double CMY7 = CMY[i][j][k - 1];
    double CMY8 = CMY[i][j][k];
    double inter_CMY_beta, inter_CMY_alpha, inter_CMY_Ma, interpolatedCMY;
    inter_CMY_beta = CMY7 + (CMY8 - CMY7) / (beta2 - beta1) * (beta - beta1);                      // 侧滑角插值
    inter_CMY_alpha = CMY6 + (CMY8 - CMY6) / (alpha2 - alpha1) * (alpha - alpha1);    //  攻角插值
    inter_CMY_Ma = CMY4 + (CMY8 - CMY4) / (Ma2 - Ma1) * (mach - Ma1);   // 马赫数插值
    interpolatedCMY = (inter_CMY_Ma + inter_CMY_alpha + inter_CMY_beta) / 3.0;

    // CMZ-三维线性插值
    double CMZ1 = CMZ[i - 1][j - 1][k - 1];
    double CMZ2 = CMZ[i - 1][j - 1][k];
    double CMZ3 = CMZ[i - 1][j][k - 1];
    double CMZ4 = CMZ[i - 1][j][k];
    double CMZ5 = CMZ[i][j - 1][k - 1];
    double CMZ6 = CMZ[i][j - 1][k];
    double CMZ7 = CMZ[i][j][k - 1];
    double CMZ8 = CMZ[i][j][k];
    double inter_CMZ_beta, inter_CMZ_alpha, inter_CMZ_Ma, interpolatedCMZ;
    inter_CMZ_beta = CMZ7 + (CMZ8 - CMZ7) / (beta2 - beta1) * (beta - beta1);                      // 侧滑角插值
    inter_CMZ_alpha = CMZ6 + (CMZ8 - CMZ6) / (alpha2 - alpha1) * (alpha - alpha1);    //  攻角插值
    inter_CMZ_Ma = CMZ4 + (CMZ8 - CMZ4) / (Ma2 - Ma1) * (mach - Ma1);   // 马赫数插值
    interpolatedCMZ = (inter_CMZ_Ma + inter_CMZ_alpha + inter_CMZ_beta) / 3.0;

    CxyzCMxyz[0] = interpolatedCX;
    CxyzCMxyz[1] = interpolatedCY;
    CxyzCMxyz[2] = interpolatedCZ;
    CxyzCMxyz[3] = interpolatedCMX;
    CxyzCMxyz[4] = interpolatedCMY;
    CxyzCMxyz[5] = interpolatedCMZ;

}

void AerodynamicCoefficients::GetCoefficients(double CxyzCmxyz[6]) {
    // 返回当前的气动系数
    for (int i = 0; i < 6; i++) {
        CxyzCmxyz[i] = this->CxyzCMxyz[i]; //this 是一个指针，指向当前类的实例(this->FxyzMxyz[i])
    }
}

// ����ϵ��--��ά���Բ�ֵ��ɲ��� -- 2024 - 12-02
// findIndices()�������������������Ҫ����

#include "AeroDynamic.h"
#include <iostream>
#include <cmath>
#include <string>
#include<vector>
#include <fstream>
#include <sstream>

using namespace std;
// 

// �������������е��� Ma0 - alpha0 -beta0 ������
vector<int> findIndices(double Data_QidongBiao[877][10], double Ma_alpha_beta0, int col) {
    vector<int> indices;  // ���ڴ洢����������������

    // ���� Data_QidongBiao ��ָ����
    for (int i = 0; i < 877; ++i) {
        if (Data_QidongBiao[i][col] == Ma_alpha_beta0) {  // �����ǰ�е�ֵ���� Ma0
            indices.push_back(i);  // �������������������
        }
    }
    return indices;
}

// ����������������������Ľ���
vector<int> findCommonIndex(const vector<int>& indices_Ma1, const vector<int>& indices_alpha1, const vector<int>& indices_beta1) {
    vector<int> index_common;

    // ������һ������
    for (int ma : indices_Ma1) {
        // ��� ma Ҳ�ڵڶ���������
        if (find(indices_alpha1.begin(), indices_alpha1.end(), ma) != indices_alpha1.end()) {
            // �����ڵ�����������
            if (find(indices_beta1.begin(), indices_beta1.end(), ma) != indices_beta1.end()) {
                index_common.push_back(ma);  // �ҵ�����Ԫ�أ�����������
            }
        }
    }
    return index_common;
}


AerodynamicCoefficients::AerodynamicCoefficients() 
{   
    // �ô���������---�õ�6����ά����ϵ������
    // �����ʼ������ϵ������ -- �� CSV ������ȷ�ؼ��ز���䵽��ά������
    // ����Դ��ļ��м�����Щ���ݣ�����ʹ��ĳЩ��֪���������ݽ��г�ʼ��

// �ļ�·�� ---- ת��Ϊ[�ı��ļ�.txt] �Ʊ���ָ��������ļ� �� һ�㲻�ö�ȡ.csv�Ķ��ŷָ��������ļ� ����ȡʱ�׳���
    string filePath = R"(D:\GNC\����_����˿�ϵͳ\��������ɶȷ������\ZS_1_AttitudeControl_v1.5\RK4\Project1\data_qidong11.txt)";

    // ���ļ�
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        //return 1;  // �ļ���ʧ�ܣ��˳�����
    }

    string line;
    vector<vector<double>> QiDongdata;  // ���ڴ洢��ȡ������

    // ���ж�ȡ�ļ�
    while (getline(file, line)) {
        // ��������
        if (line.empty()) {
            continue;
        }

        //cout << "Reading line: " << line << endl;  // ���ԣ������ȡ����
        stringstream ss(line);  // ʹ�� stringstream �����ÿһ�е�����
        string value;
        vector<double> row;     // ���ڴ洢ÿһ�е�����

        // �����ȡ�Ʊ���ָ���ֵ��ת��Ϊ double
        while (getline(ss, value, '\t')) {
            try {
                row.push_back(stod(value));  // ���ַ���ת��Ϊ double ���洢
            }
            catch (const invalid_argument& e) {
                cerr << "Error converting value: '" << value << "' to double." << endl;
            }
        }

        // �����ǰ�е����ݲ�����������������Ҫ�󣩣�������
        if (row.size() < 10) {
            cerr << "Skipping row with insufficient columns: " << line << endl;
            continue;
        }

        // ����Ч������ӵ� QiDongdata ��
        QiDongdata.push_back(row);
    }

    file.close();  // �ر��ļ�

    int n = QiDongdata.size(); // ��ȡ���ݵ�����
    cout << "ԭʼ�������ݱ������"<<n << endl;

    int NN = n;

    // Data_QidongBiao;// = QiDongdata; // n*10������
        // ����һ����ά���飬��ʼֵΪ��
    double Data_QidongBiao[877][10] = { {0} };
    for (int i = 0; i < NN; ++i) {
        for (int j = 0; j < 10; ++j) {
            // �� QiDongdata �����ݸ��Ƶ� Data_QidongBiao ����
            if (i < NN) {  // ȷ����Խ��
                Data_QidongBiao[i][j] = QiDongdata[i][j];
            }
        }
    }

    // ������ά���鲢��ֵ
    for (int i = 0; i < Mach_num; i++) {
        for (int j = 0; j < Alpha_num; j++) {
            for (int k = 0; k < Beta_num; k++) {
              // ѭ������-->�����ά��ֵ���飺CX[i][j][k]��CY[i][j][k]��CZ[i][j][k]��CMX[i][j][k]��CMY[i][j][k]��CMZ[i][j][k]

                double Ma1    =  Ma[i];
                double alpha1 =  Alpha[j];
                double beta1  =  Beta[k];

              vector<int> indices_Ma1 = findIndices(Data_QidongBiao, Ma1, 1);
              vector<int> indices_alpha1 = findIndices(Data_QidongBiao, alpha1, 2);
              vector<int> indices_beta1 = findIndices(Data_QidongBiao, beta1, 3);
              // ���� findCommonIndex �������㽻��-ȷ��Ψһһ��[Ma,alpha,beta]��Ӧ�����������е���������
              vector<int> commonIndices = findCommonIndex(indices_Ma1, indices_alpha1, indices_beta1);

                    int IndexOnly;
                    // ��ȡ����������
                    if (!commonIndices.empty())
                    {
                        IndexOnly = commonIndices.back();
                      // cout << "��ͬ�����ǣ�" << IndexOnly << endl;
                    }
                    else
                    {
                        break;
                    }
                    CX[i][j][k] = Data_QidongBiao[IndexOnly][4];  // Data_QidongBiao �е� 5 ���� CX
                    CY[i][j][k] = Data_QidongBiao[IndexOnly][5];  // Data_QidongBiao �е� 6 ���� CY
                    CZ[i][j][k] = Data_QidongBiao[IndexOnly][6];  // Data_QidongBiao �е� 7 ���� CZ
                    CMX[i][j][k] = Data_QidongBiao[IndexOnly][7]; // Data_QidongBiao �е� 8 ���� CMX
                    CMY[i][j][k] = Data_QidongBiao[IndexOnly][8]; // Data_QidongBiao �е� 9 ���� CMY
                    CMZ[i][j][k] = Data_QidongBiao[IndexOnly][9]; // Data_QidongBiao �е� 10 ���� CMZ       
            }
        }
    }
}

void AerodynamicCoefficients::ComputeCoefficients(double mach, double alpha, double beta) 
{
    int i = 0, j = 0, k = 0;

    // ������ӽ�������������ǺͲ໬�ǵ���ɢ��ֵ
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
    // ���Ҷ�Ӧ������������ǡ��໬�ǵ�ʵ��ֵ
    double Ma1 = Ma[i - 1];
    double Ma2 = Ma[i];
    double alpha1 = Alpha[j - 1];
    double alpha2 = Alpha[j];
    double beta1 = Beta[k - 1];
    double beta2 = Beta[k];


    // CX--��ά���Բ�ֵ
    double CX1 = CX[i - 1][j - 1][k - 1];
    double CX2 = CX[i - 1][j - 1][k];
    double CX3 = CX[i - 1][j][k - 1];
    double CX4 = CX[i - 1][j][k];
    double CX5 = CX[i][j - 1][k - 1];
    double CX6 = CX[i][j - 1][k];
    double CX7 = CX[i][j][k - 1];
    double CX8 = CX[i][j][k];

    // �ڲ໬�ǲ�ֵ�����ǡ������ (Ma) ����ά��ֵ
    double inter_CX_beta, inter_CX_alpha, inter_CX_Ma, interpolatedCX;
    inter_CX_beta = CX7 + (CX8 - CX7) / (beta2 - beta1) * (beta - beta1);                      // �໬�ǲ�ֵ
    inter_CX_alpha = CX6 + (CX8 - CX6) / (alpha2 - alpha1) * (alpha - alpha1);    //  ���ǲ�ֵ
    inter_CX_Ma = CX4 + (CX8 - CX4) / (Ma2 - Ma1) * (mach - Ma1);   // �������ֵ
    interpolatedCX = (inter_CX_Ma + inter_CX_alpha + inter_CX_beta) / 3.0;

    //cout << "���Ե����� biao_inter_CX ��" << CX8 << endl;
    //cout << "���Ե����� inter_CX����" << interpolatedCX << endl;
    // 
    // CY-��ά���Բ�ֵ
    double CY1 = CY[i - 1][j - 1][k - 1];
    double CY2 = CY[i - 1][j - 1][k];
    double CY3 = CY[i - 1][j][k - 1];
    double CY4 = CY[i - 1][j][k];
    double CY5 = CY[i][j - 1][k - 1];
    double CY6 = CY[i][j - 1][k];
    double CY7 = CY[i][j][k - 1];
    double CY8 = CY[i][j][k];

    double inter_CY_beta, inter_CY_alpha, inter_CY_Ma, interpolatedCY;
    inter_CY_beta = CY7 + (CY8 - CY7) / (beta2 - beta1) * (beta - beta1);                      // �໬�ǲ�ֵ
    inter_CY_alpha = CY6 + (CY8 - CY6) / (alpha2 - alpha1) * (alpha - alpha1);    //  ���ǲ�ֵ
    inter_CY_Ma = CY4 + (CY8 - CY4) / (Ma2 - Ma1) * (mach - Ma1);   // �������ֵ
    interpolatedCY = (inter_CY_Ma + inter_CY_alpha + inter_CY_beta) / 3.0;

    //cout << "���Ե����� biao_inter_CY ��" << CY8 << endl;
   // cout << "���Ե����� inter_CY����" << interpolatedCY << endl;

    // CZ-��ά���Բ�ֵ
    double CZ1 = CZ[i - 1][j - 1][k - 1];
    double CZ2 = CZ[i - 1][j - 1][k];
    double CZ3 = CZ[i - 1][j][k - 1];
    double CZ4 = CZ[i - 1][j][k];
    double CZ5 = CZ[i][j - 1][k - 1];
    double CZ6 = CZ[i][j - 1][k];
    double CZ7 = CZ[i][j][k - 1];
    double CZ8 = CZ[i][j][k];

    double inter_CZ_beta, inter_CZ_alpha, inter_CZ_Ma, interpolatedCZ;
    inter_CZ_beta = CZ7 + (CZ8 - CZ7) / (beta2 - beta1) * (beta - beta1);                      // �໬�ǲ�ֵ
    inter_CZ_alpha = CZ6 + (CZ8 - CZ6) / (alpha2 - alpha1) * (alpha - alpha1);    //  ���ǲ�ֵ
    inter_CZ_Ma = CZ4 + (CZ8 - CZ4) / (Ma2 - Ma1) * (mach - Ma1);   // �������ֵ
    interpolatedCZ = (inter_CZ_Ma + inter_CZ_alpha + inter_CZ_beta) / 3.0;


    // CMX-��ά���Բ�ֵ
    double CMX1 = CMX[i - 1][j - 1][k - 1];
    double CMX2 = CMX[i - 1][j - 1][k];
    double CMX3 = CMX[i - 1][j][k - 1];
    double CMX4 = CMX[i - 1][j][k];
    double CMX5 = CMX[i][j - 1][k - 1];
    double CMX6 = CMX[i][j - 1][k];
    double CMX7 = CMX[i][j][k - 1];
    double CMX8 = CMX[i][j][k];
    double inter_CMX_beta, inter_CMX_alpha, inter_CMX_Ma, interpolatedCMX;
    inter_CMX_beta = CMX7 + (CMX8 - CMX7) / (beta2 - beta1) * (beta - beta1);                      // �໬�ǲ�ֵ
    inter_CMX_alpha = CMX6 + (CMX8 - CMX6) / (alpha2 - alpha1) * (alpha - alpha1);    //  ���ǲ�ֵ
    inter_CMX_Ma = CMX4 + (CMX8 - CMX4) / (Ma2 - Ma1) * (mach - Ma1);   // �������ֵ
    interpolatedCMX = (inter_CMX_Ma + inter_CMX_alpha + inter_CMX_beta) / 3.0;

    // CMY-��ά���Բ�ֵ
    double CMY1 = CMY[i - 1][j - 1][k - 1];
    double CMY2 = CMY[i - 1][j - 1][k];
    double CMY3 = CMY[i - 1][j][k - 1];
    double CMY4 = CMY[i - 1][j][k];
    double CMY5 = CMY[i][j - 1][k - 1];
    double CMY6 = CMY[i][j - 1][k];
    double CMY7 = CMY[i][j][k - 1];
    double CMY8 = CMY[i][j][k];
    double inter_CMY_beta, inter_CMY_alpha, inter_CMY_Ma, interpolatedCMY;
    inter_CMY_beta = CMY7 + (CMY8 - CMY7) / (beta2 - beta1) * (beta - beta1);                      // �໬�ǲ�ֵ
    inter_CMY_alpha = CMY6 + (CMY8 - CMY6) / (alpha2 - alpha1) * (alpha - alpha1);    //  ���ǲ�ֵ
    inter_CMY_Ma = CMY4 + (CMY8 - CMY4) / (Ma2 - Ma1) * (mach - Ma1);   // �������ֵ
    interpolatedCMY = (inter_CMY_Ma + inter_CMY_alpha + inter_CMY_beta) / 3.0;

    // CMZ-��ά���Բ�ֵ
    double CMZ1 = CMZ[i - 1][j - 1][k - 1];
    double CMZ2 = CMZ[i - 1][j - 1][k];
    double CMZ3 = CMZ[i - 1][j][k - 1];
    double CMZ4 = CMZ[i - 1][j][k];
    double CMZ5 = CMZ[i][j - 1][k - 1];
    double CMZ6 = CMZ[i][j - 1][k];
    double CMZ7 = CMZ[i][j][k - 1];
    double CMZ8 = CMZ[i][j][k];
    double inter_CMZ_beta, inter_CMZ_alpha, inter_CMZ_Ma, interpolatedCMZ;
    inter_CMZ_beta = CMZ7 + (CMZ8 - CMZ7) / (beta2 - beta1) * (beta - beta1);                      // �໬�ǲ�ֵ
    inter_CMZ_alpha = CMZ6 + (CMZ8 - CMZ6) / (alpha2 - alpha1) * (alpha - alpha1);    //  ���ǲ�ֵ
    inter_CMZ_Ma = CMZ4 + (CMZ8 - CMZ4) / (Ma2 - Ma1) * (mach - Ma1);   // �������ֵ
    interpolatedCMZ = (inter_CMZ_Ma + inter_CMZ_alpha + inter_CMZ_beta) / 3.0;

    CxyzCMxyz[0] = interpolatedCX;
    CxyzCMxyz[1] = interpolatedCY;
    CxyzCMxyz[2] = interpolatedCZ;
    CxyzCMxyz[3] = interpolatedCMX;
    CxyzCMxyz[4] = interpolatedCMY;
    CxyzCMxyz[5] = interpolatedCMZ;

}

void AerodynamicCoefficients::GetCoefficients(double CxyzCmxyz[6]) {
    // ���ص�ǰ������ϵ��
    for (int i = 0; i < 6; i++) {
        CxyzCmxyz[i] = this->CxyzCMxyz[i]; //this ��һ��ָ�룬ָ��ǰ���ʵ��(this->FxyzMxyz[i])
    }
}

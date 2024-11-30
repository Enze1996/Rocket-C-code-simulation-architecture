// v1.0  -- 2024-11-27 

#include<iostream>
#include "Integrate.h"
#include "diff_func.h"  // ����΢�ַ���ͷ�ļ�
#include "RocketCanshu.h"

#include<fstream>
using namespace std;

//����һ��ʵ��object��ȡ��
RocketCanshu RockCanshu = RocketCanshu();


int main() {
    // ���״̬������������λ�ã�x, y, z�����ٶȣ�vx, vy, vz������̬�ǣ�phi, theta, psi�������ٶȣ�p, q, r��
    const int N = 12;  // 12��״̬����
    const double Ts = 0.01;  // ʱ�䲽�������磬10ms��

    // ��ʼ�����������ʼλ��Ϊ [0, 0, 0]����ʼ�ٶ�Ϊ [0, 0, 0]����ʼ��̬��Ϊ [0, 0, 0]����ʼ���ٶ�Ϊ [0, 0, 0]��
    double initial_conditions[12] = { 0.0, 0.0, 0.0,   // λ�� x, y, z
                                      0.0, 0.0, 0.0,   // �ٶ� vx, vy, vz
                                      0.0, 0.0, 0.0,   // ��̬�� phi, theta, psi
                                      0.0, 0.0, 0.0 }; // ���ٶ� p, q, r

    // ����һ�� Integrater ����
    Integrater integrater;
    integrater.Initial(N, Ts, initial_conditions);

    // �洢��������飨ÿ��ʱ�䲽����״̬��
    const int num_steps = 1000;
    double results[12][num_steps];  // �洢12��״̬������ÿ��ʱ�䲽����ֵ

    // ʱ�����
    for (int i = 0; i < num_steps; i++) {
        // ���浱ǰ״̬�� results
        for (int j = 0; j < N; j++) {
            results[j][i] = integrater.Sheet0[j];  // ��ÿ��״̬�������浽 results ��
        }

        // ���� Integrate ����������״̬
        // ע�⣬����ÿ�ε���ʱ�����Ǵ��뵱ǰ��״̬���� integrater.Sheet0��
        integrater.Integrate(diff_func, i, integrater.Sheet0);  // ʹ�õ�ǰ״̬���л���
    }

    // ����������ʾ����ӡǰ10��ʱ�䲽�Ľ����
    for (int i = 0; i < 100; i++) {
        cout << "Step " << i << ": ";
        cout << "x = " << results[0][i] << ", y = " << results[1][i] << ", z = " << results[2][i] << ", ";
        cout << "vx = " << results[3][i] << ", vy = " << results[4][i] << ", vz = " << results[5][i] << ", ";
        cout << "phi = " << results[6][i] << ", theta = " << results[7][i] << ", psi = " << results[8][i] << ", ";
        cout << "p = " << results[9][i] << ", q = " << results[10][i] << ", r = " << results[11][i] << endl;
    }

    // �����������ļ�
    ofstream output_file("results241128.txt");  // ����һ���ļ���������д���ļ�
    if (output_file.is_open()) {
        for (int i = 0; i < num_steps; i++) {
            output_file << "Step " << i << ": ";
            output_file << "x = " << results[0][i] << ", y = " << results[1][i] << ", z = " << results[2][i] << ", ";
            output_file << "vx = " << results[3][i] << ", vy = " << results[4][i] << ", vz = " << results[5][i] << ", ";
            output_file << "phi = " << results[6][i] << ", theta = " << results[7][i] << ", psi = " << results[8][i] << ", ";
            output_file << "p = " << results[9][i] << ", q = " << results[10][i] << ", r = " << results[11][i] << endl;
        }
        output_file.close();  // �ر��ļ���
        cout << "Results have been saved to results241128.txt" << endl;
    }
    else {
        cout << "Failed to open file for writing." << endl;
    }
    cout <<"���������Ϊ��"<< RockCanshu.M << endl;

    return 0;
}

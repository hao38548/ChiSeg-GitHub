// CalF-measure.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include<iostream>
#include<string>
#include <fstream>

using namespace std;
typedef unsigned long long  UINT;

float CalF_measure(UINT& TP, UINT& FN, UINT& FP, string right_file, string real_file, string result_file)
{
	int i = 0;
	string right_code, real_code;
	float F_measure = 0.0f;
	ifstream in1;
	ifstream in2;
	ofstream out;
	in1.open(right_file, ios::in);
	in2.open(real_file, ios::in);
	out.open(result_file, ios::out|ios::app);
	while (getline(in1, right_code))
	{
		getline(in2, real_code);
		int code_len = real_code.length();
		for (int i = 0; i < code_len; i++)
		{
			switch (right_code.at(i))
			{
			case '1':
				if (real_code.at(i) == '1')
				{
					//�����Ϊ������
					TP++;
				}
				else if (real_code.at(i) == '0')
				{
					//Ӧ��Ϊ�����Ϊ�������Ŀ
					FN++;
				}
				break;
			case '0':
				if (real_code.at(i) == '1')
				{
					//Ӧ��Ϊ0�������Ϊ��1
					FP++;
				}
				break;
			case '2':
				//�����з�Ҳ���Բ��зֵ���Ϊ�з���ȷ
				TP++;
				break;
			}
		}
	}
	in1.close();
	in2.close();
	
	//����F_measure
	F_measure = 2.000 * TP / (2 * TP + FP + FN);
	out << F_measure << endl;
	out.close();
	return F_measure;
}

void main()
{
	UINT TP = 0;
	UINT FN = 0;
	UINT FP = 0;
	string right_file = "E:\\coding\\ChineseSegment\\���������Ϣ\\5000���\\ũҵ\\���\\������Ϣ.txt";
	string real_file = "E:\\coding\\ChineseSegment\\�����ļ�\\MI-marked-seg-result-codes.txt";
	string result_file = "E:\\coding\\ChineseSegment\\�����ļ�\\MI-marked-seg-accuracy.txt";
	float F_measure = CalF_measure(TP, FN, FP,right_file, real_file, result_file);
	cout << "FֵΪ��" << F_measure;
}




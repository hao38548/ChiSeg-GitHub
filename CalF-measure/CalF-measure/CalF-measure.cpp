// CalF-measure.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include<iostream>
#include<string>

using namespace std;


void main()
{
	int i = 0;
	string right_code, real_code;
	float acc_rate = 0.0f;
	ifstream in1;
	ifstream in2;
	ofstream out;
	in1.open("E:\\coding\\ChineseSegment\\���������Ϣ\\5000���\\ũҵ\\���\\������Ϣ.txt", ios::in);
	//in2.open("D:\\coding\\ChineseSegment\\���������Ϣ\\5000���\\����\\���\\ICTCLAS�зֱ���.txt",ios::in);
	in2.open("E:\\coding\\ChineseSegment\\�����ļ�\\MI-marked-seg-result-codes.txt", ios::in);
	out.open("E:\\coding\\ChineseSegment\\�����ļ�\\MI-marked-seg-accuracy.txt", ios::out);
	while (getline(in1, right_code))
	{
		getline(in2, real_code);
		acc_rate = CalAccuracyRate(real_code, right_code);
		out << acc_rate << endl;
		i++;
		if (i % 1000 == 0)
			//if (i == 37)
		{
			cout << ".";
		}
		if (i == 1815)
		{
			cout << ".";
		}
	}
	in1.close();
	in2.close();
	out.close();

}

//����׼ȷ��
float CalAccuracyRate(string real_code, string right_code)
{
	//���볤��
	int code_len = real_code.length();
	int right_cnt = 0;
	for (int i = 0; i < code_len; i++)
	{
		if (real_code[i] == right_code[i] || right_code[i] == '2')
		{
			//��λ����ƥ��ɹ�/��λΪ2����Ϊ�ȿ��Բ��Ҳ���Բ����
			right_cnt++;
		}
	}
	return (float)right_cnt / code_len;
}


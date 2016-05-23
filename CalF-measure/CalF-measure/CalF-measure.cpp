// CalF-measure.cpp : 定义控制台应用程序的入口点。
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
					//正类分为了正类
					TP++;
				}
				else if (real_code.at(i) == '0')
				{
					//应该为正类分为负类的数目
					FN++;
				}
				break;
			case '0':
				if (real_code.at(i) == '1')
				{
					//应该为0，结果分为了1
					FP++;
				}
				break;
			case '2':
				//可以切分也可以不切分的认为切分正确
				TP++;
				break;
			}
		}
	}
	in1.close();
	in2.close();
	
	//计算F_measure
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
	string right_file = "E:\\coding\\ChineseSegment\\标记语料信息\\5000标记\\农业\\拆分\\编码信息.txt";
	string real_file = "E:\\coding\\ChineseSegment\\测试文件\\MI-marked-seg-result-codes.txt";
	string result_file = "E:\\coding\\ChineseSegment\\测试文件\\MI-marked-seg-accuracy.txt";
	float F_measure = CalF_measure(TP, FN, FP,right_file, real_file, result_file);
	cout << "F值为：" << F_measure;
}




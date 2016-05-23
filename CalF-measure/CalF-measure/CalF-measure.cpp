// CalF-measure.cpp : 定义控制台应用程序的入口点。
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
	in1.open("E:\\coding\\ChineseSegment\\标记语料信息\\5000标记\\农业\\拆分\\编码信息.txt", ios::in);
	//in2.open("D:\\coding\\ChineseSegment\\标记语料信息\\5000标记\\电子\\拆分\\ICTCLAS切分编码.txt",ios::in);
	in2.open("E:\\coding\\ChineseSegment\\测试文件\\MI-marked-seg-result-codes.txt", ios::in);
	out.open("E:\\coding\\ChineseSegment\\测试文件\\MI-marked-seg-accuracy.txt", ios::out);
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

//计算准确率
float CalAccuracyRate(string real_code, string right_code)
{
	//编码长度
	int code_len = real_code.length();
	int right_cnt = 0;
	for (int i = 0; i < code_len; i++)
	{
		if (real_code[i] == right_code[i] || right_code[i] == '2')
		{
			//该位编码匹配成功/该位为2，即为既可以拆分也可以不拆分
			right_cnt++;
		}
	}
	return (float)right_cnt / code_len;
}


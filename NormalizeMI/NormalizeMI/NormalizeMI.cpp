// NormalizeMI.cpp : 定义控制台应用程序的入口点。
//

// Normlize.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <functional>
#include <set>
#include <vector>
#include <stdlib.h>
#include <sstream>
using namespace std;

typedef multimap<float, string, greater<float>> Dictionary;

bool Normalize(string* filePath)
{
	string word, temp_word;
	float mi = 0.0f;
	Dictionary dictionary;
	float mixedValue = 0.0f;
	double averageValue = 0;
	unsigned long long word_cnt = 0;//计算读取了多少词汇的计数器
	cout << "Generating Dictionaries";
	//循环读取三个文件并加载入词典中
	for (int i = 0; i < 1; i++)
	{

		dictionary.clear();
		word_cnt = 0;
		ifstream in;
		in.open(filePath[i].c_str(), ios::in);
		if (!in.good())
		{
			cout << "Open file failed ";
			return false;
		}
		cout << "Reading " << filePath[i];
		// 读取文件
		while (!in.eof())
		{
			word = "";//先清空字符串保存结果
			//读取字符串信息
			for (int j = 0; j <= i; j++)
			{
				in >> temp_word;
				word += temp_word;
				word += " ";
			}
			in >> mi;
			
			mixedValue = -mi;

			//将数加载进入相应的字典中
			if (mixedValue>0)
			{
				dictionary.insert(multimap<float, string>::value_type(mixedValue, word));
				averageValue += mixedValue;
			}

			//显示处理进度的标示
			if (word_cnt++ % 20000 == 0)
			{
				cout << ".";
			}
		}
		//计算最终的平均值
		averageValue = averageValue / dictionary.size();
		in.close();

		//将归一化数据保存
		stringstream resulrFileName;
		resulrFileName << "Result";
		resulrFileName << "-" << i + 1 << "Gram.txt";
		ofstream out;
		out.open(resulrFileName.str(), ios::out);
		Dictionary::iterator iter = dictionary.begin();
		for (; iter != dictionary.end(); iter++)
		{
			mixedValue = iter->first - averageValue;
			out << iter->second << mixedValue << endl;
		}
		out.close();

	}
	return true;
}


void main()
{
	string dictionary_filepaths[3] = { "E:\\coding\\ChineseSegment\\测试文件\\agrMI_1gram.txt", "E:\\coding\\ChineseSegment\\测试文件\\agrMI_2gram.txt", "E:\\coding\\ChineseSegment\\测试文件\\agrMI_3gram.txt" };
	Normalize(dictionary_filepaths);
}



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

//定义分支熵结构
typedef struct{
	float lbe;
	float rbe;
}BE;
typedef multimap<float, string, greater<float>> Dictionary;

bool threeWays(string* filePath,int choice)
{
	string word, temp_word;
	BE be;
	Dictionary dictionary;
	float mixedValue = 0.0f;
	double averageValue = 0;
	unsigned long long word_cnt = 0;//计算读取了多少词汇的计数器
	cout << "Generating Dictionaries";
	//循环读取三个文件并加载入词典中
	for (int i = 0; i < 3; i++)
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
			in >> be.lbe >> be.rbe;
			if (choice==1)
			{
				//左右分支熵相加
				mixedValue = -(be.lbe + be.rbe);
			}
			else if (choice == 2)
			{
				//左右分支熵相乘
				mixedValue = be.lbe * be.rbe;
			}
			else
			{
				//选择左右分支熵绝对值较小的
				mixedValue = be.lbe > be.rbe ? -be.lbe:-be.rbe;
			}
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
		resulrFileName << "Result-Way";
		resulrFileName << choice;
		resulrFileName << "-" << i+1 << "Gram.txt";
		ofstream out;
		out.open(resulrFileName.str(), ios::out);
		Dictionary::iterator iter = dictionary.begin();
		for (; iter != dictionary.end();iter++)
		{
			mixedValue = iter->first - averageValue;
			out << iter->second << mixedValue<<endl;
		}
		out.close();

	}
	return true;
}


void main()
{
/*
	map<float, string, greater<float>> test;
	test.insert(map<float, string>::value_type(0.6, "0.6"));
	test.insert(map<float, string>::value_type(0.4, "0.4"));
	test.insert(map<float, string>::value_type(0.5, "0.5"));
	test.insert(map<float, string>::value_type(0.3, "0.3"));
	map<float, string>::iterator iter= test.begin();
/ *
	for (; iter!=test.end();iter++)
	{
		cout<<iter
	}* /*/
	for (int choice = 1; choice < 4;choice++)
	{
		string dictionary_filepaths[3] = { "E:\\coding\\ChineseSegment\\测试文件\\1gram.txt", "E:\\coding\\ChineseSegment\\测试文件\\2gram.txt", "E:\\coding\\ChineseSegment\\测试文件\\3gram.txt" };
		if (threeWays(dictionary_filepaths, choice))
		{
			continue;
		}
		else
			break;
		
	}
/*

	int i = 3;
	stringstream ss;
	ss << "Result-Way";
	ss << i;
	cout << ss.str();*/
}


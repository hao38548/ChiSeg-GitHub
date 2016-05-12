// NormalizeTFDev-Substring.cpp : 定义控制台应用程序的入口点。
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

typedef map<string,float> Dictionary;

bool GenerateDictionarys(string* filePath, Dictionary *dictionary)
{
	string word, temp_word;
	float tfdev = 0.0f;
	float mixedValue = 0.0f;
	float minValue = 10;
	double averageValue = 0;
	unsigned long long word_cnt = 0;//计算读取了多少词汇的计数器
	cout << "Generating Dictionaries——————";
	//循环读取三个文件并加载入词典中
	for (int i = 0; i < 3; i++)
	{
		dictionary[i].clear();
		word_cnt = 0;
		ifstream in;
		in.open(filePath[i].c_str(), ios::in);
		cout << "\n Reading File " << filePath[i];
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
			in >> tfdev;

			mixedValue = tfdev;
			minValue = minValue < mixedValue ? minValue : mixedValue;
			//将数加载进入相应的字典中,此处仅考虑不等于0的数据，因为后续涉及除法
			if (mixedValue != 0)
			{
				dictionary[i].insert(map<string, float>::value_type(word, mixedValue));
			}

			//显示处理进度的标示
			if (word_cnt++ % 20000 == 0)
			{
				cout << ".";
			}
		}
		dictionary[i].insert(map<string, float>::value_type("min", minValue));
		in.close();
	}
	return true;
}


//获取词典中的TFDev值
float GetTFDevValues(string word, int n, Dictionary *dictionary)
{
	map< string ,float>::iterator iter = dictionary[n - 1].find(word);
	if (iter!=dictionary[n-1].end())
	{
		return dictionary[n - 1][word];
	}
	else
	{
		//平滑值的处理
		return dictionary[n - 1]["min"];
	}
}

//根据标志mark切分长字符串，返回子串向量
vector<string> GetSplitStr(string nstring, string mark)
{
	vector<string> subStrings;
	size_t s = 0;
	size_t t = string::npos;
	string word;
	while ((t = nstring.find_first_of(' ', s)) != string::npos)
	{
		if (t > s)
		{
			//截出一个词来
			word = nstring.substr(s, t - s);
			//该词存入文章中
			subStrings.push_back(word);
		}
		//更新扫描指针位置
		s = t + 1;
	}
	//word = nstring.substr(s);//substr未指定第二个参数，将截取到字符串的末尾，因为最后一个词后面是没有空格的
	//subStrings.push_back(word);
	return subStrings;
}

//该函数获得某个n元词汇的最小的子串的TFDev值
float GetSubstrValues(int n, string nstring,Dictionary *dictionary)
{
	string tempWord1, tempWord2;
	float tempValue1 = 0;
	float tempValue2 = 0;
	vector<string> subString = GetSplitStr(nstring, " ");
	if (3 == n&&subString.size()==3)
	{
		//拼接二元词汇，从词典读出数据
		tempWord1 = subString[0] +" " +subString[1]+" ";
		tempWord2 = subString[1] + " " + subString[2] + " ";
		tempValue1 = dictionary[1][tempWord1];
		tempValue2 = dictionary[1][tempWord2];
		return tempValue1 < tempValue2 ? tempValue1 : tempValue2;
	}
	if (2 == n&&subString.size() == 2)
	{
/*
		tempWord1 = subString[0];
		tempWord2 = subString[1];
		tempValue1 = dictionary[0][tempWord1];
		tempValue2 = dictionary[0][tempWord2];
		return tempValue1 < tempValue2 ? tempValue1 : tempValue2;*/
		//此处要指定一个非归一化的一元默认值
		return 3;
	}
	if (1 == n)
	{
		//此处要指定一个归一化的一元默认值
		return 2.3;
	}
	return 0;
}

//这个函数可以传参“一元未归一化的默认值”，结果那只输出2gram和3gram就好了
void Normalize(Dictionary *dictionary)
{
	long long word_cnt = 0;
	float normValue = 0.0f;
	cout << "\nNormalizing ";
	for (int i = 0; i < 3;i++)
	{
		//将归一化数据保存
		stringstream resulrFileName;
		resulrFileName << "NormTFDev-SubStr-";
		resulrFileName << "-" << i + 1 << "Gram.txt";
		ofstream out;
		out.open(resulrFileName.str(), ios::out);

		map< string, float>::iterator iter = dictionary[i].begin();
		//遍历该字典
		for (; iter != dictionary[i].end();iter++)
		{
			normValue = iter->second / GetSubstrValues(i + 1, iter->first,dictionary);
			out << iter->first << "\t" << normValue << endl;
			//展示处理进程
			if (word_cnt++%2000==0)
			{
				cout << ".";
			}
		}
		out.close();
	}
}


void main()
{
	string dictionary_filepaths[3] = { "E:\\coding\\ChineseSegment\\测试文件\\----\\TFDev文件\\原始TFDev\\1gram.txt", "E:\\coding\\ChineseSegment\\测试文件\\----\\TFDev文件\\原始TFDev\\2gram.txt", "E:\\coding\\ChineseSegment\\测试文件\\----\\TFDev文件\\原始TFDev\\3gram.txt" };
	Dictionary dictionary[3];
	GenerateDictionarys(dictionary_filepaths,dictionary);
	Normalize(dictionary);
}



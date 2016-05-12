// NormalizeTFDev-Substring.cpp : �������̨Ӧ�ó������ڵ㡣
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
	unsigned long long word_cnt = 0;//�����ȡ�˶��ٴʻ�ļ�����
	cout << "Generating Dictionaries������������";
	//ѭ����ȡ�����ļ���������ʵ���
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
		// ��ȡ�ļ�
		while (!in.eof())
		{
			word = "";//������ַ���������
			//��ȡ�ַ�����Ϣ
			for (int j = 0; j <= i; j++)
			{
				in >> temp_word;
				word += temp_word;
				word += " ";
			}
			in >> tfdev;

			mixedValue = tfdev;
			minValue = minValue < mixedValue ? minValue : mixedValue;
			//�������ؽ�����Ӧ���ֵ���,�˴������ǲ�����0�����ݣ���Ϊ�����漰����
			if (mixedValue != 0)
			{
				dictionary[i].insert(map<string, float>::value_type(word, mixedValue));
			}

			//��ʾ������ȵı�ʾ
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


//��ȡ�ʵ��е�TFDevֵ
float GetTFDevValues(string word, int n, Dictionary *dictionary)
{
	map< string ,float>::iterator iter = dictionary[n - 1].find(word);
	if (iter!=dictionary[n-1].end())
	{
		return dictionary[n - 1][word];
	}
	else
	{
		//ƽ��ֵ�Ĵ���
		return dictionary[n - 1]["min"];
	}
}

//���ݱ�־mark�зֳ��ַ����������Ӵ�����
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
			//�س�һ������
			word = nstring.substr(s, t - s);
			//�ôʴ���������
			subStrings.push_back(word);
		}
		//����ɨ��ָ��λ��
		s = t + 1;
	}
	//word = nstring.substr(s);//substrδָ���ڶ�������������ȡ���ַ�����ĩβ����Ϊ���һ���ʺ�����û�пո��
	//subStrings.push_back(word);
	return subStrings;
}

//�ú������ĳ��nԪ�ʻ����С���Ӵ���TFDevֵ
float GetSubstrValues(int n, string nstring,Dictionary *dictionary)
{
	string tempWord1, tempWord2;
	float tempValue1 = 0;
	float tempValue2 = 0;
	vector<string> subString = GetSplitStr(nstring, " ");
	if (3 == n&&subString.size()==3)
	{
		//ƴ�Ӷ�Ԫ�ʻ㣬�Ӵʵ��������
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
		//�˴�Ҫָ��һ���ǹ�һ����һԪĬ��ֵ
		return 3;
	}
	if (1 == n)
	{
		//�˴�Ҫָ��һ����һ����һԪĬ��ֵ
		return 2.3;
	}
	return 0;
}

//����������Դ��Ρ�һԪδ��һ����Ĭ��ֵ���������ֻ���2gram��3gram�ͺ���
void Normalize(Dictionary *dictionary)
{
	long long word_cnt = 0;
	float normValue = 0.0f;
	cout << "\nNormalizing ";
	for (int i = 0; i < 3;i++)
	{
		//����һ�����ݱ���
		stringstream resulrFileName;
		resulrFileName << "NormTFDev-SubStr-";
		resulrFileName << "-" << i + 1 << "Gram.txt";
		ofstream out;
		out.open(resulrFileName.str(), ios::out);

		map< string, float>::iterator iter = dictionary[i].begin();
		//�������ֵ�
		for (; iter != dictionary[i].end();iter++)
		{
			normValue = iter->second / GetSubstrValues(i + 1, iter->first,dictionary);
			out << iter->first << "\t" << normValue << endl;
			//չʾ�������
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
	string dictionary_filepaths[3] = { "E:\\coding\\ChineseSegment\\�����ļ�\\----\\TFDev�ļ�\\ԭʼTFDev\\1gram.txt", "E:\\coding\\ChineseSegment\\�����ļ�\\----\\TFDev�ļ�\\ԭʼTFDev\\2gram.txt", "E:\\coding\\ChineseSegment\\�����ļ�\\----\\TFDev�ļ�\\ԭʼTFDev\\3gram.txt" };
	Dictionary dictionary[3];
	GenerateDictionarys(dictionary_filepaths,dictionary);
	Normalize(dictionary);
}



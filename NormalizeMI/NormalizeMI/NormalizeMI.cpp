// NormalizeMI.cpp : �������̨Ӧ�ó������ڵ㡣
//

// Normlize.cpp : �������̨Ӧ�ó������ڵ㡣
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
	unsigned long long word_cnt = 0;//�����ȡ�˶��ٴʻ�ļ�����
	cout << "Generating Dictionaries";
	//ѭ����ȡ�����ļ���������ʵ���
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
			in >> mi;
			
			mixedValue = -mi;

			//�������ؽ�����Ӧ���ֵ���
			if (mixedValue>0)
			{
				dictionary.insert(multimap<float, string>::value_type(mixedValue, word));
				averageValue += mixedValue;
			}

			//��ʾ������ȵı�ʾ
			if (word_cnt++ % 20000 == 0)
			{
				cout << ".";
			}
		}
		//�������յ�ƽ��ֵ
		averageValue = averageValue / dictionary.size();
		in.close();

		//����һ�����ݱ���
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
	string dictionary_filepaths[3] = { "E:\\coding\\ChineseSegment\\�����ļ�\\agrMI_1gram.txt", "E:\\coding\\ChineseSegment\\�����ļ�\\agrMI_2gram.txt", "E:\\coding\\ChineseSegment\\�����ļ�\\agrMI_3gram.txt" };
	Normalize(dictionary_filepaths);
}



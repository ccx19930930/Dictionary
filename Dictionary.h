 ///
 /// @file    Dictionary.h
 /// @author  chinxi(ccx19930930@gmail.com)
 /// @date    2016-12-03 10:26:41
 ///

#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include "DictionaryData.h"
#include "DictionaryConf.h"

#include <memory>
#include <vector>
#include <list>

namespace ccx{

using std::shared_ptr;
using std::vector;
using std::list;

class Dictionary
{
	typedef unordered_map<string, pDictElem>::iterator WordIt;
	public:
		Dictionary();
		void push(const string & word);
		void push(vector<string> & words);
		int search(const string & word);
	private:
		void AddWord(const string & word, int wordId);
		void splitWord(const string & word, vector<string> & characters);//把词拆成字
		pDictElem _dictionary;
		DictionaryConf _conf;	

	public://遍历用
		void next();
		string getCurChar();
		string getCurWord();
		int getCurWordId();
		void resetPoint();
		bool isEnd();
	private:
		void nextWord();
		pDictElem _pcur;
		WordIt _itcur;
		//用list实现栈，遍历时方便
		list<WordIt> _stackWord;
		list<pDictElem> _stackDict;

	public://导入导出
		void leading_in();
		void leading_out();
};

}

#endif

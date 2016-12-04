 ///
 /// @file    Dictionary.h
 /// @author  chinxi(ccx19930930@gmail.com)
 /// @date    2016-12-03 10:26:41
 ///

#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include "DictionaryData.h"

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
	private:
		void splitWord(const string & word, vector<string> & characters);//把词拆成字
		pDictElem _dictionary;

	public://遍历用
		void next();
		string getCurChar();
		string getCurWord();
		void resetPoint();
		bool isEnd();
	private:
		void nextWord();
		pDictElem _pcur;
		WordIt _itcur;
		//用list实现栈，遍历时方便
		list<WordIt> _stackWord;
		list<pDictElem> _stackDict;
};

}

#endif
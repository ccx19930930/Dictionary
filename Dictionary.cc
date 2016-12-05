 ///
 /// @file    Dictionary.cc
 /// @author  chinxi(ccx19930930@gmail.com)
 /// @date    2016-12-03 10:47:12
 ///

#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <string>
#include <json/json.h>

namespace ccx{

using std::endl;
using std::cout;
using std::pair;
using std::ofstream;
using std::ifstream;

Dictionary::Dictionary()
: _dictionary(new DictElem)
, _conf()
{
	_dictionary->_wordId = 0;
	_pcur = _dictionary;
}

void Dictionary::splitWord(const string & word, vector<string> & characters)
{
	int num = word.size();
	int i = 0;
	while(i < num)
	{
		int size = 1;
		if(word[i] & 0x80)
		{
			char temp = word[i];
			temp <<= 1;
			do{
				temp <<= 1;
				++size;
			}while(temp & 0x80);
		}
		string subWord;
		subWord = word.substr(i, size);
		characters.push_back(subWord);
		i += size;
	}
}

void Dictionary::AddWord(const string & word, int wordId)
{
	vector<string> characters;
	splitWord(word, characters);
	
	vector<string>::iterator it_char;
	it_char = characters.begin();	
	pDictElem root;
	root = _dictionary;
	for(; it_char != characters.end(); ++it_char)
	{
		WordIt it_word;
		it_word = root->_words.find(*it_char);
		
		if(it_word == root->_words.end())
		{
			pair<string, pDictElem> temp;
			temp.first = *it_char;
			pDictElem dictemp(new DictElem);
			dictemp->_word = *it_char;
			dictemp->_wordId = 0;
			temp.second = dictemp;
			root->_words.insert(temp);
			root = dictemp;
		}else{
			root = it_word->second;
		}
	}
	if(!root->_wordId)
	{
		root->_wordId = wordId;
	}
}

void Dictionary::push(const string & word)
{
	++(_dictionary->_wordId);
	AddWord(word, _dictionary->_wordId);
}

void Dictionary::push(vector<string> & words)
{
	int size = words.size();
	for(int i = 0; i < size; ++i)
	{
		push(words[i]);
	}
}

int Dictionary::search(const string & word)
{
	vector<string> characters;
	splitWord(word, characters);
	
	vector<string>::iterator it_char;
	it_char = characters.begin();	
	pDictElem root;
	root = _dictionary;
	for(; it_char != characters.end(); ++it_char)
	{
		WordIt it_word;
		it_word = root->_words.find(*it_char);
		
		if(it_word == root->_words.end())
		{
			return -1;
		}else{
			root = it_word->second;
		}
	}
	return root->_wordId;
}

//遍历用

void Dictionary::resetPoint()
{
	_pcur = _dictionary;
	if(_stackDict.size())
	{
		_stackDict.clear();
	}
	if(_stackWord.size())
	{
		_stackWord.clear();
	}
	next();
}

void Dictionary::next()
{
	while(_pcur)
	{
		nextWord();
		if(!_pcur || _pcur->_wordId)
		{
			break;
		}
	}
}

void Dictionary::nextWord()
{
	if(_pcur)
	{
		if(_pcur->_words.size())
		{
			_stackDict.push_back(_pcur);
			_stackWord.push_back(_pcur->_words.begin());
			_pcur = _stackWord.back()->second;
		}else{
			++(_stackWord.back());
		}
		while(_stackWord.back() == _stackDict.back()->_words.end())
		{
			_stackDict.pop_back();
			_stackWord.pop_back();
			if(!_stackDict.size())
			{
				_pcur = NULL;
			}
			++(_stackWord.back());
		}
		if(_pcur)
		{
			_pcur = _stackWord.back()->second;
		}	
	}
}

string Dictionary::getCurChar()
{
	return _pcur->_word;
}

int Dictionary::getCurWordId()
{
	return _pcur->_wordId;
}

string Dictionary::getCurWord()
{
	string temp;
	list<WordIt>::iterator it_word;	
	it_word = _stackWord.begin();	

	for(; it_word != _stackWord.end(); ++it_word)
	{
		temp += (*it_word)->first;
	}
	return temp;
}

bool Dictionary::isEnd()
{
	return _pcur == NULL;
}

void Dictionary::leading_in()//导入，失败没必要退出程序
{
	ifstream ifs;
	const char * path = _conf.getDictionaryPath().c_str();
	ifs.open(path);
	if(!ifs.good())
	{
		cout << "open Dictionary.json error(leading_in)" << endl;
	}else{
		Json::Value root;
		Json::Reader reader;
		
		if(!reader.parse(ifs, root, false))
		{
			cout << "json read Dictionary.json error" << endl;
		}else{
			int size = root.size();
			for(int i = 0; i < size; ++i)
			{
				string word = root[i]["Word"].asString();
				int wordId = root[i]["WordId"].asInt();
				AddWord(word, wordId);
				++(_dictionary->_wordId);
			}
		}
	}
}

void Dictionary::leading_out()
{
	Json::Value root;
	Json::FastWriter writer;

	resetPoint();
	
	while(!isEnd())
	{
		Json::Value elem;
		elem["Word"] = getCurWord();
		elem["WordId"] = getCurWordId();
		root.append(elem);
		next();
	}

	string words;
	words = writer.write(root);
	
	ofstream ofs;
	const char * path = _conf.getDictionaryPath().c_str();
	ofs.open(path);
	if(!ofs.good())
	{
		cout << "open Dictionary.json error(leading_out)" << endl;
		ofs.open("Dictionary.tmp");
		if(!ofs.good())
		{
			exit(EXIT_FAILURE);
		}
	}
	
	ofs << words;
	ofs.close();
}

}

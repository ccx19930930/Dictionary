 ///
 /// @file    Dictionary.cc
 /// @author  chinxi(ccx19930930@gmail.com)
 /// @date    2016-12-03 10:47:12
 ///

#include "Dictionary.h"
#include <iostream>
#include <string>

namespace ccx{

using std::endl;
using std::cout;
using std::pair;

Dictionary::Dictionary()
: _dictionary(new DictElem)
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

void Dictionary::push(const string & word)
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
			++_dictionary->_wordId;
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
		++(_dictionary->_wordId);
		root->_wordId = _dictionary->_wordId;
	}
}

void Dictionary::push(vector<string> & words)
{
	int size = words.size();
	for(int i = 0; i < size; ++i)
	{
		push(words[i]);
	}
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

}

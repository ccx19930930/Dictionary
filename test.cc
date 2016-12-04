 ///
 /// @file    test.cc
 /// @author  chinxi(ccx19930930@gmail.com)
 /// @date    2016-12-03 11:06:16
 ///

#include "Dictionary.h"
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main()
{
	ccx::Dictionary words;
	string word1 = "阿里abc";	
	string word2 = "阿里云";	
	string word3 = "阿里巴巴";	
	string word4 = "阿里大数据";	
	
	words.push(word1);	
	words.push(word2);	
	words.push(word3);	
	words.push(word4);	

	words.resetPoint();
	
	while(!words.isEnd())
	{
		cout << "char : " << words.getCurChar() << endl;
		cout << "word : " << words.getCurWord() << endl;
		words.next();
	}
}

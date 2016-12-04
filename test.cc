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

int test1()
{
	ccx::Dictionary words;
	string word1 = "编程入门";	
	string word2 = "编程软件";	
	string word3 = "编程学习";	
	string word4 = "编程学习网站";	
	
	words.push(word1);	
	words.push(word2);	
	words.push(word3);	
	words.push(word4);	

	words.resetPoint();
	
	while(!words.isEnd())
	{
		cout << "ID : " << words.getCurWordId() 
			<< "\tchar : " << words.getCurChar() 
			<< "\tword : " << words.getCurWord() << endl;
		words.next();
	}
	
	words.leading_out();
	return 0;
}


int test2()
{
	ccx::Dictionary words;
	words.leading_in();

	words.resetPoint();
	
	while(!words.isEnd())
	{
		cout << "ID : " << words.getCurWordId() 
			<< "\tchar : " << words.getCurChar() 
			<< "\tword : " << words.getCurWord() << endl;
		words.next();
	}
	
	words.leading_out();
	return 0;
}

int main()
{
	cout << "test1" << endl;
	test1();
	cout << endl;
	cout << "test2" << endl;
	test2();
	cout << endl;
}

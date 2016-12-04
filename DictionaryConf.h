 ///
 /// @file    DictionaryConf.h
 /// @author  chinxi(ccx19930930@gmail.com)
 /// @date    2016-12-04 11:01:12
 ///

#ifndef __DICTIONARYCONF_H__
#define __DICTIONARYCONF_H__

#include <string>

namespace ccx{

using std::string;

class DictionaryConf
{
	public:
		DictionaryConf();
		string getDictionaryPath();
	private:
		void GetConf();
		string _DictionaryPath;
};

}

#endif

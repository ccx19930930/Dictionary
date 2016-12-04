# Dictionary
1、本词典采用Trie字典树结构
2、使用struct与unordered_map实现树
3、遍历打印时只会打印存入的词
      如：添加词   “阿里云” 与 “阿里巴巴” ，打印时不会出现“阿里”
4、根结点为root
5、遍历时使用两个list实现的栈
6、能够正常分字（UTF-8编码）
      如：词 “阿里云” 可以分成“阿”、“里”、“云”，存在临时的vector中
7、理论上UTF-8编码的都可以使用，中英文混输测试OK
8、数据结构：
struct DictElem
{
	string _word;//如果是根结点，则填ROOT
	int _wordId;//如果是根结点，则为总词数
	unordered_map<string, shared_ptr<DictElem> > _words;
};

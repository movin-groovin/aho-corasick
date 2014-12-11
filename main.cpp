
// http://neerc.ifmo.ru/wiki/index.php?title=%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%90%D1%85%D0%BE-%D0%9A%D0%BE%D1%80%D0%B0%D1%81%D0%B8%D0%BA

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <utility>



namespace NAhoCorasik {

	template <size_t ALPHABET_SIZE, char CHAR_START>
	class CAhoCorasik;

	// ===================================
	// Node class
	// ===================================
	template <size_t ALPHABET_SIZE, char CHAR_START>
	class CNode {
	public:
		friend CAhoCorasik <ALPHABET_SIZE, CHAR_START>;
		typedef std::shared_ptr <CNode<ALPHABET_SIZE, CHAR_START>> ScnPtr;
		
	private:
		ScnPtr m_childs[ALPHABET_SIZE];   // childs of each node at prefix tree
		ScnPtr m_automata[ALPHABET_SIZE]; // states of finite machine
		ScnPtr m_parrent; // link to parent of curernt node
		ScnPtr m_sufLink; // suffix link for current node
		ScnPtr m_goodSufLink; // good suffix link for current node (link to other node-leaf)
		char m_chFromParent; // character for pass from the parrent of this node to this node
		bool m_leaf; // true value indicates that this node is terminal for some pattern from prefix tree
		std::vector<size_t> m_patternNumbers; // numbers of patterns that end at this node, linked with m_patterns from CAhoCorasik
		
	public:
		CNode ();
		// get - set methods
	};
	
	// ===================================
	template <size_t ALPHABET_SIZE, char CHAR_START>
	CNode<ALPHABET_SIZE, CHAR_START>::CNode (): m_chFromParent(-1), m_leaf(false) {}

	// ===================================
	// Algorithm class
	// ===================================
	template <size_t ALPHABET_SIZE = 26, char CHAR_START = 'a'> // a-z symbols
	class CAhoCorasik {
	private:
		typedef typename CNode <ALPHABET_SIZE, CHAR_START>::ScnPtr NodePtr;
	
		std::vector<std::string> m_patterns;
		NodePtr m_root;
		
	public:
		CAhoCorasik (): m_root(new CNode<ALPHABET_SIZE, CHAR_START>) {}
		void Free () {m_root = NodePtr (new CNode<ALPHABET_SIZE, CHAR_START>);}
		size_t GetCharIndex (char ch) const {return static_cast <unsigned char> (ch - CHAR_START);}
		size_t GetPatternsNumber () const {return m_patterns.size();}
		std::string GetPatternByIndex (size_t i) const {
			if (i >= m_patterns.size()) return std::string("");
			return m_patterns[i];
		}
		
		void AddPattern (const std::string & pattern);
		NodePtr Go (NodePtr from, size_t moveIndex);
		NodePtr GetSuffLink (NodePtr node);
		NodePtr GetGoodSuffLink (NodePtr node);
		void Search (
			const std::string & text,
			std::vector <std::pair <size_t, std::vector<size_t>>> & results
		);
	};
	
	// ===================================
	template <size_t ALPHABET_SIZE, char CHAR_START>
	void CAhoCorasik<ALPHABET_SIZE, CHAR_START>::AddPattern (const std::string & pattern) {
		NodePtr curNode = m_root, newNode;
		
		for (size_t i = 0; i < pattern.size(); ++i)
		{
			if (curNode->m_childs[GetCharIndex(pattern[i])]) {
				curNode = curNode->m_childs[GetCharIndex(pattern[i])];
				continue;
			}
			
			newNode = NodePtr (new CNode<ALPHABET_SIZE, CHAR_START>);
			newNode->m_parrent = curNode;
			newNode->m_chFromParent = pattern[i];
			newNode->m_leaf = false;
			
			curNode->m_childs[GetCharIndex(pattern[i])] = newNode;
			curNode = curNode->m_childs[GetCharIndex(pattern[i])];
		}
		m_patterns.push_back(pattern);
		curNode->m_patternNumbers.push_back(m_patterns.size() - 1);
		curNode->m_leaf = true;
		
		return;
	}
	
	// ===================================
	template <size_t ALPHABET_SIZE, char CHAR_START>
	typename CAhoCorasik<ALPHABET_SIZE, CHAR_START>::NodePtr CAhoCorasik<ALPHABET_SIZE, CHAR_START>::Go (
		typename CAhoCorasik<ALPHABET_SIZE, CHAR_START>::NodePtr from,
		size_t moveIndex
	)
	{
		if (!from->m_automata[moveIndex]) {
			if (from->m_childs[moveIndex])
				from->m_automata[moveIndex] = from->m_childs[moveIndex];
			else if (from == m_root)
				from->m_automata[moveIndex] = m_root;
			else
				from->m_automata[moveIndex] = Go(GetSuffLink(from), moveIndex);
		}
		
		return from->m_automata[moveIndex];
	}
	
	// ===================================
	template <size_t ALPHABET_SIZE, char CHAR_START>
	typename CAhoCorasik<ALPHABET_SIZE, CHAR_START>::NodePtr CAhoCorasik<ALPHABET_SIZE, CHAR_START>::GetSuffLink (
		NodePtr node
	)
	{
		if (!node->m_sufLink) {
			if (node == m_root || node->m_parrent == m_root)
				node->m_sufLink = m_root;
			else
				node->m_sufLink = Go(GetSuffLink(node->m_parrent), GetCharIndex (node->m_chFromParent));
		}
		
		return node->m_sufLink;
	}
	
	// ===================================
	template <size_t ALPHABET_SIZE, char CHAR_START>
	typename CAhoCorasik<ALPHABET_SIZE, CHAR_START>::NodePtr CAhoCorasik<ALPHABET_SIZE, CHAR_START>::GetGoodSuffLink (
		NodePtr node
	)
	{
		NodePtr curNode;
		
		if (!node->m_goodSufLink) {
			curNode = GetSuffLink(node);
			if (curNode->m_leaf || curNode == m_root)
				node->m_goodSufLink = curNode;
			else
				node->m_goodSufLink = GetGoodSuffLink(GetSuffLink(node));
		}
		
		return node->m_goodSufLink;
	}
	
	// ===================================
	template <size_t ALPHABET_SIZE, char CHAR_START>
	void CAhoCorasik<ALPHABET_SIZE, CHAR_START>::Search (
		const std::string & text,
		std::vector <std::pair <size_t, std::vector<size_t>>> & results
	)
	{
		NodePtr state = m_root, curNode;
		size_t chInd;
		
		for (size_t i = 0; i < text.size(); ++i) {
			chInd = GetCharIndex(text[i]);
			if ((state = Go(state, chInd)) == m_root) continue;
			
			curNode = state;
			while (curNode != m_root) {
				if (curNode->m_leaf) {
					results.push_back (std::make_pair (i, curNode->m_patternNumbers));
				}
				curNode = GetGoodSuffLink(curNode);
			}
		}
		
		return;
	}
}

//
// Results printing
//
template <size_t ALPHABET_SIZE, char CHAR_START>
void PrintResults (
	NAhoCorasik::CAhoCorasik <ALPHABET_SIZE, CHAR_START> & aho,
	std::vector <std::pair <size_t, std::vector<size_t>>> & results
)
{
	std::cout << "Size: " << results.size() << std::endl;
	for (size_t i = 0; i < results.size(); ++i) {
		size_t endPos = results[i].first;
		std::vector<size_t> ptrnNums = results[i].second;
		for (size_t j = 0; j < ptrnNums.size(); ++j) {
			std::string pattern = aho.GetPatternByIndex (ptrnNums[j]);
			std::cout  << "Position: " << endPos - (pattern.length() - 1) << " - ";
			std::cout << pattern;
			if (j != 0) std::cout << "; ";
		}
		std::cout << std::endl;
	}
	
	return;
}

//
// Testing driver
//
int MainFirst (int argc, char **argv) {
	std::string text = "it is widely learned as a second language and is an official language of the european union.";
	std::vector <std::string> strArr = {"an", "learn", "fuck", "the", "one_two_three"};
	std::vector <std::pair <size_t, std::vector<size_t>>> results;
	NAhoCorasik::CAhoCorasik <> aho;
	
	
	for (auto it = strArr.begin(); it != strArr.end(); ++it) {
		aho.AddPattern(*it);
	}
	aho.Search(text, results);
	PrintResults (aho, results);
	
	
	return 0;
}


int MainTest (int argc, char **argv) {
	size_t sizePerIter = 100 * 1024 * 1024;
	size_t fileNameInd = 1;
	std::vector<char> text(sizePerIter + 1);
	std::vector <std::pair <size_t, std::vector<size_t>>> results;
	NAhoCorasik::CAhoCorasik <> aho;
	
	
	for (int i = fileNameInd + 1; i < argc; ++i) aho.AddPattern(argv[i]);
	
	std::ifstream iFs (argv[1]);
	if (!iFs) {
		std::cout << "Can't read " << argv[1] << std::endl;
		return 1001;
	}
	
	size_t readNumber;
	while (readNumber = iFs.getline (&text[0], sizePerIter).gcount()) {
		aho.Search(&text[0], results);
		PrintResults (aho, results);
	}
	
	
	return 0;
}


int main (int argc, char **argv) {
	int ret;
	
	//ret = MainFirst (argc, argv);
	ret = MainTest (argc, argv);
	
	return ret;
}













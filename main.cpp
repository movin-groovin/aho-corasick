
// http://neerc.ifmo.ru/wiki/index.php?title=%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%90%D1%85%D0%BE-%D0%9A%D0%BE%D1%80%D0%B0%D1%81%D0%B8%D0%BA

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <utility>



namespace MAhoCorasik {

	template <size_t ALPHABET_SIZE>
	class CAhoCorasik;

//
// node class
//
	template <size_t ALPHABET_SIZE>
	class CNode {
	public:
		friend CAhoCorasik <ALPHABET_SIZE>;
		typedef std::shared_ptr <CNode<ALPHABET_SIZE>> ScnPtr;
		
	private:
		ScnPtr m_childs[ALPHABET_SIZE];   // childs of each node at prefix tree
		ScnPtr m_automata[ALPHABET_SIZE]; // states of finite machine
		ScnPtr m_parrent; // link to parent of curernt node
		ScnPtr m_sufLink; // suffix link for current node
		ScnPtr m_goodSufLink; // good suffix link for current node (link to other node-leaf)
		char m_chFromParent; // character for pass from the parrent of this node to this node
		bool m_leaf; // true value indicates that this node is terminal for some pattern from prefix tree
		std::vector<size_t> m_patternNumber; // numbers of patterns that end at this node, linked with m_patterns from CAhoCorasik
		
	public:
		CNode ();
		// get - set methods
	};

	template <size_t ALPHABET_SIZE>
	CNode<ALPHABET_SIZE>::CNode (): m_chFromParent(0), m_leaf(false) {}

//
// algorithm class
//
	template <size_t ALPHABET_SIZE = 26> // a-z symbols
	class CAhoCorasik {
	private:
		typedef typename CNode <ALPHABET_SIZE>::ScnPtr NodePtr;
	
		std::vector<std::string> m_patterns;
		NodePtr m_root;
		
	public:
		void AddPattern (std::string & pattern);
		size_t GetPatternsNumber () const {return m_patterns.size();}
		NodePtr Go (NodePtr from, char chGo);
		NodePtr GetSuffLink (NodePtr node);
		NodePtr GetGoodSuffLink (NodePtr node);
		void Search (std::vector <std::pair <size_t, size_t>> & results);
	};
	
	template <size_t ALPHABET_SIZE>
	void CAhoCorasik<ALPHABET_SIZE>::AddPattern (std::string & pattern) {
		
		
		
		return;
	}
	
	//
}


int main (int argc, char **argv) {
	std::string text = "it is widely learned as a second language and is an official language of the european union.";
	std::vector <std::string> strArr = {"an", "learn", "fuck", "the", "one_two_three"};
	std::vector <std::pair <size_t, size_t>> results;
	MAhoCorasik::CAhoCorasik <> aho;
	
	
	;
	
	
	return 0;
}















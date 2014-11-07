
#include <vector>
#include <string>

#include <cassert>



const size_t ALPHABET_SIZE = 256; // everything ascii symbols



class CNode {
private:
	//
public:
	//
};


template <size_t Alphabet = ALPHABET_SIZE>
class CAhoCorasick {
public:
	CAhoCorasick (const std::vector <std::string> & arrPatterns):
		m_Patterns (arrPatterns)
	{
		//
	}
	
private:
	const std::vector <std::string> m_Patterns;
	CNode * m_treeRoot;
};


















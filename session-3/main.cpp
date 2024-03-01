#include <string>
#include <vector>
#include <istream>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <fstream>


std::vector<std::string> read_wordle_js(std::istream& is) {
	std::vector<std::string> words;
	auto word = std::string{};
	while (is) { // check for EOF and potential I/O errors
		if (is.peek() == '"') { // look for an opening quote
			is >> std::quoted(word); // read the word in quotes and remove quotes
			if (word.length() == 5 && // must be 5-letter word
				std::all_of(std::cbegin(word), std::cend(word), // all lower-case letters
					[](char c) { return std::isalpha(c) && std::islower(c); }))
				words.push_back(word);
		} else
			is.get(); // skip one character
	}
	std::sort(std::begin(words), std::end(words));
	words.erase(std::unique(std::begin(words), std::end(words)), words.end());
	return words;
}
std::vector<std::string> filter(std::vector<std::string>&& words, const std::string& pattern) { /* your filtering implementation here */
	return std::vector<std::string>();
	for (auto word : words) {
		
	}
}

int main() {
	auto wordleFile = std::ifstream("bitches.txt");
	if (!wordleFile.is_open()) {
		std::cout << "Could not open file bitches.txt" << std::endl;
		return 1;
	}
	const auto database = read_wordle_js(wordleFile);

	auto words = database; // make a copy of the database

	auto guess = std::string{}; // allocate memory to store guess patterns
	
	while (words.size() > 1) {
		std::cout << words.size() << " words remaining\n";
		bool good = true;
		do {
			std::cout << "Enter a guess pattern: ";
			std::cin >> guess;
			/* sanitize: set good to false if input fails to follow the pattern */
		} while (!good);
		/* apply the filter on the words */
		/* pick and announce one of the words for the user to try */
	}
	if (words.size() == 1) {
		std::cout << "Congratulations: " << words.front() << "\n";
	} else {
		std::cerr << "Something got messed up :-(\n";
	}
}
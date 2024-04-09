#include <string> // std::to_string
#include <random>
#include <algorithm>
#include <cstring>

static std::random_device dev;
static std::mt19937 gen{dev()};

std::vector<std::string> gen_ids(size_t N)
{
	auto res = std::vector<std::string>{};
	res.reserve(N);
	for (auto i=0u; i<N/2; ++i) {
		res.emplace_back("id"+std::to_string(i));
		res.emplace_back("ID"+std::to_string(i));
	}
	std::shuffle(std::begin(res), std::end(res), gen);
	return res;
}

char** gen_cids(size_t N)
{
	auto res = (char**)malloc(sizeof(char*)*N);
	auto ids = gen_ids(N);
	for (auto i=0u; i<N; ++i)
		res[i] = strdup(ids[i].c_str());
	return res;
}

#include "stdafx.h"
#include "fnv.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include "MurmurHash1.h"

#define N_FEATURES 1000

struct sketch_hashes {
	int hash_murmur;
	int hash_fnv;
};

struct sketch_hashes sketch_hash(std::string to_hash) noexcept{
	struct sketch_hashes res = { 0 };
	//call murmur and fnv
	res.hash_fnv = FNV::fnv1a(to_hash, 0) % N_FEATURES;
	res.hash_murmur = MurmurHash1(to_hash, 0) % N_FEATURES;
	return res;
}

int query_sketch(std::string query, std::vector<int> a1, std::vector<int> a2) noexcept{
	const auto q_r = sketch_hash(query);
	//calc freq
	return std::min(a1[q_r.hash_fnv], a2[q_r.hash_murmur]);
}

int main_sketch(void) noexcept
{
	std::vector<int> array1(N_FEATURES);
	std::vector<int> array2(N_FEATURES);
	std::cout << "how many items to insert?";
	int num_items;
	std::cin >> num_items;
	std::cout << "enter " << num_items << " strings:\n";
	for (int i = 0; i < num_items; i++) {
		std::string to_insert;
		std::cin >> to_insert;
		const auto h_res = sketch_hash(to_insert);
		array1[h_res.hash_fnv]++;
		array2[h_res.hash_murmur]++;
	}

	while (1) {
		while (1) {
			std::string yn;
			std::cout << "\nwant to query?";
			std::cin >> yn;
			if (!yn.compare("n"))
				return 0;
			if (!yn.compare("y"))
				break;
		}
		std::cout << "\nenter ur query:";
		std::string query;
		std::cin >> query;
		const auto freq = query_sketch(query, array1, array2);
		std::cout << "\nfrequency of " << query << " is " << freq << std::endl;
	}
	return 0;
}
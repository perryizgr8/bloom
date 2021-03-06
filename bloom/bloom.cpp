// bloom.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>
#include "MurmurHash1.h"

#define N_FEATURES 10
#define MURMUR_SEED_1 0
#define MURMUR_SEED_2 1

struct hash_result {
	int hash_a;
	int hash_b;
};

struct hash_result hash(std::string key) {
	struct hash_result ret;
	ret.hash_a = MurmurHash1(key, MURMUR_SEED_1) % N_FEATURES;
	ret.hash_b = MurmurHash1(key, MURMUR_SEED_2) % N_FEATURES;
	return ret;
}

bool hash_check(std::string query, std::vector<bool> b_array) {
	const struct hash_result q_res = hash(query);
	if (b_array[q_res.hash_a] && b_array[q_res.hash_b]) {
		return true;
	}
	return false;
}

int main_bloom()
{
	std::vector<bool> bloom_array(N_FEATURES);
	std::cout << "how many items to insert?";
	int num_items;
	std::cin >> num_items;
	std::cout << "enter " << num_items << " strings:\n";
	for (int i = 0; i < num_items; i++) {
		std::string to_insert;
		std::cin >> to_insert;
		const struct hash_result h_res= hash(to_insert);
		bloom_array[h_res.hash_a] = true;
		bloom_array[h_res.hash_b] = true;
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
		if (hash_check(query, bloom_array)) {
			std::cout << "\nmay exist\n";
		}
		else {
			std::cout << "\ndefinitely doesn't exist\n";
		}
	}
    return 0;
}


#include "stdafx.h"
#include <iostream>
#include <string>

extern int main_bloom(void);
extern int main_sketch(void);

int main(void)
{
	std::string option;
	std::cout << "bloom or sketch?";
	std::cin >> option;
	if (!option.compare("bloom")) {
		return main_bloom();
	}
	else if (!option.compare("sketch")) {
		return main_sketch();
	}
	return 0;
}
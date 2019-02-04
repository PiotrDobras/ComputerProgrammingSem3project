#include <stdlib.h>
#include <string>

#include "Item.h"

std::string Item::GetFullName() {
	if (this == NULL)
		return "No Item";
	std::string output;
	if (!consumable)
		output = name + " [" + std::to_string(durability) + "]:" + std::to_string(power);
	else
		output = name;
	return output;
}

void Item::SetStats(int floor) {
	if (!advanced) {
		power = 4 + rand() % (floor * 6);
		durability = 10 + rand() % (floor * 10);
	}
	else {
		power = 4 + rand() % (floor * 8);
		durability = 3 + rand() % (floor * 3);
	}
}
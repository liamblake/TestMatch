/* Utility.h

	Contains helper functions for converting between strings and their encodings as integers,
	and vice-versa. These are used primarily in conversions from simulation backend to printed/displayed
	results (e.g. a scorecard or ball-by-ball description).
*/

#pragma once

#include <string>
#include <stdexcept>

template <class T>
T* arr_add_item(T* arr, int old_length, T new_entry);

int encode_bowltype(std::string bowltype);
std::string unencode_bowltype(int encoding);
int encode_dism(std::string mode);
std::string unencode_dism(int encoding);


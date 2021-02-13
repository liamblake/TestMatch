// -*- lsst-c++ -*-
/* Utility.h
 *
 * Contains various helper functions used throughout the program. Includes functions for converting
 * between strings and their encodings as integers, and vice-versa. These are used primarily in 
 * conversions from simulation backend to printed/displayed results (e.g. a scorecard or ball-by-ball description).
 * 
 * Note that all the functions here are defined and implementated here (with the inline keyword). This is probably
 * bad practice, but I wanted to avoid having an additional .cpp file since no class is declared here. If I need to
 * declare a class here for whatever reason, I will probably move the implementations here to a .cpp, but for now,
 * the header is all we need.
 * 
*/

#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>
#include <stdexcept>
#include <utility>
#include <cmath>


/* Add new entry to end of array - reallocates memory dynamically.
   Deletes the old array and returns a pointer to the new.
   Arguments:
	T* arr - pointer to array of type T
	int old_length - length of array arr
	T new_entry - item to add to end of array arr

	This exists because overs can contain an arbitrary amount of balls
	(due to extras), but I don't want to use vectors since I will be wasting 
	a lot of memory. 
*/
template <class T>
inline T* arr_add_item(T* arr, int old_length, T new_entry) {
	
	// Reallocate array
	T* new_arr = new T[old_length + 1];
    if (old_length > 0) {

		for (int i = 0; i < old_length; i++) {
			new_arr[i] = arr[i];
		}
		delete[] arr;
	}

	delete[] arr;
	arr[old_length] = new_entry;

	return arr;

}


inline std::vector<std::string> split_str(std::string str, std::string delim = ",") {
	/* TODO: implement with string* return type to save memory,
			 ideally using the arr_add_item template defined in
			 Utility.h. Attempts at this have been giving strange
			 results, where the while loop won't iterate unless
			 cout << len << endl is included at the start of the
			 loop.
	*/

	std::vector<std::string> token;

	// Check for boundary cases
	if (str.length() == 0) {
		return token;
	}
	

	size_t curr, prev = 0;
	curr = str.find(delim);

	// Check delim is actually present in string
	if (curr == std::string::npos) {
		token.push_back(str);
		return token;
	}


	while (curr != std::string::npos) {
		token.push_back(str.substr(prev, curr - prev));
		prev = curr + delim.length();
		curr = str.find(delim, prev);

	}

	// Add remaining string
	token.push_back(str.substr(prev, curr - prev));

	return token;
}

inline std::string join_str(std::vector<std::string> str_comp, std::string join) {
	std::string output = "";
	for (std::string x : str_comp) {
		output += x + join;
	}

	// Remove last join added in above loop
	return output.substr(0, output.size() - join.size());
}


// Encodes bowling type as corresponding integer
// 0: rm, 1: rmf, 2:rfm, 3:rf, 4: ob, 5: lb, 6: lm, 7: lmf, 8: lfm, 9: lf, 10: slo, 11: slu
inline int encode_bowltype(std::string bowltype) {
	int output = -1;

	if (bowltype == "rm") {
		output = 0;
	} 
	else if (bowltype == "rmf") {
		output = 1;
	} 
	else if (bowltype == "rfm") {
		output = 2;
	} 
	else if (bowltype == "rf") {
		output = 3;
	} 
	else if (bowltype == "ob") {
		output = 4;
	} 
	else if (bowltype == "lb") {
		output = 5;
	} 
	else if (bowltype == "lm") {
		output = 6;
	} 
	else if (bowltype == "lmf") {
		output = 7;
	} 
	else if (bowltype == "lfm") {
		output = 8;
	} 
	else if (bowltype == "lf") {
		output = 9;
	} 
	else if (bowltype == "slo") {
		output = 10;
	} 
	else if (bowltype == "slu") {
		output = 11;
	}

	return output;
}


// Unencodes bowling type from integer to string
inline std::string unencode_bowltype(int encoding) {
	std::string output;

	switch (encoding) {
		case 0:
			output = "rm";
			break;
		case 1:
			output = "rmf";
			break;
		case 2:
			output = "rfm";
			break;
		case 3:
			output = "rf";
			break;

		default:
			output = "-";
			break;
	}

	return output;
}


// Encodes mode of dismissal as corresponding integer
// 0: bowled, 1: lbw, 2: caught, 3: run out, 4: stumped
inline int encode_dism(std::string mode) {
	int output = -1;
	
	if (mode == "b") {
		output = 0;
	}
	else if (mode == "lbw") {
		output = 1;
	}
	else if (mode == "c") {
		output = 2;
	}
	else if (mode == "c&b") {
		output = 3;
	}
	else if (mode == "ro") {
		output = 4;
	}
	else if (mode == "st") {
		output = 5;
	}

	return output;
}

// Unencodes mode of dismissal from integer to string
// 0: bowled, 1: lbw, 2: caught, 3: run out, 4: stumped
inline std::string unencode_dism(int encoding) {
	std::string output;

	switch (encoding) {
		case 0:
			output = "b";
			break;
		case 1:
			output = "lbw";
			break;
		case 2:
			output = "c";
			break;
		case 3:
			output = "c&b";
			break;
		case 4:
			output = "ro";
			break;
		case 5:
			output = "st";
			break;
		default:
			output = "-";
			break;
	}

	return output;

}


template <typename T>
T sample_cdf(T* values, int length, double* dist) {
	
	// Generate random number
	double r = ((double)rand() / (RAND_MAX));
	
	// Iterate through distribution until first entry > r
	int i = 0;
	while (++i < length && r > dist[i]); 


	return values[i - 1];
}


// Converts ball count to overs and balls
inline std::pair<int, int> balls_to_ov(unsigned int balls) {
	std::pair<int, int> output(
		(int)balls / 6,
		balls % 6
	);

	return output;
}

// Generates a realisation of a truncated exponential distribution
inline double rtexp(double mean, double min, double max) {
	double Fmin = exp(min);
	double Fmax = exp(max);

	// Generate uniform random number
	double r = ((double)rand() / (RAND_MAX));

	// Inverse sampling
	double p = r * (Fmax - Fmin) + Fmin;
	return -mean * log(1 - p);

}


template <typename T>
inline void delete_linkedlist(T* first) {
	T* tmp = first;
	while (tmp != nullptr) {
		
	}
}

/**
 * @brief Converts integer to ordinal string
 * @param num Integer to be converted
 * @return Converted string
 * 
 * e.g. ordinal(1) returns "1st", ordinal(15) returns "15th"
*/
inline std::string ordinal(int num) {
	std::string output = std::to_string(num);

	char fin = output.back();
	if (fin == '1') {
		output += "st";
	}
	else if (fin == '2') {
		output += "nd";
	}
	else if (fin == '3'){
		output += "rd";
	}
	else {
		output += "th";
	}

	return output;
}

#endif // UTILITY_H

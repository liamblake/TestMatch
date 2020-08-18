/* Utility.h

	Contains helper functions for converting between strings and their encodings as integers,
	and vice-versa. These are used primarily in conversions from simulation backend to printed/displayed
	results (e.g. a scorecard or ball-by-ball description).
*/

#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>
#include <stdexcept>

/* Add new entry to end of array - reallocates memory dynamically.
   Deletes the old array and returns a pointer to the new.
   Arguments:
	T* arr - pointer to array of type T
	int old_length - length of array arr
	T new_entry - item to add to end of array arr
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
	else if (mode == "ro") {
		output = 3;
	}
	else if (mode == "st") {
		output = 4;
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
			output = "ro";
			break;
		case 4:
			output = "st";
			break;
		default:
			output = "-";
			break;
	}

	return output;

}



#endif
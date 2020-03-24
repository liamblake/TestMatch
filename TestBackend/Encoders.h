/* Encoders.h

	Contains helper functions for converting between strings and their encodings as integers,
	and vice-versa. These are used primarily in conversions from simulation backend to printed/displayed
	results (e.g. a scorecard or ball-by-ball description).
*/

#pragma once

#include <string>
#include <stdexcept>


// Encodes bowling type as corresponding integer
// 0: rm, 1: rmf, 2:rfm, 3:rf, 4: ob, 5: lb, 6: lm, 7: lmf, 8: lfm, 9: lf, 10: slo, 11: slu
int encode_bowltype(std::string bowltype) {
	int output;

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
		output = 1;
	} 
	else if (bowltype == "lm") {
		output = 1;
	} 
	else if (bowltype == "lmf") {
		output = 1;
	} 
	else if (bowltype == "lfm") {
		output = 1;
	} 
	else if (bowltype == "lf") {
		output = 1;
	} 
	else if (bowltype == "slo") {
		output = 1;
	} 
	else if (bowltype == "slu") {
		output = 1;
	}
}


// Unencodes bowling type from integer to string
std::string unencode_bowltype(int encoding) {
	std::string output;

	switch (encoding) {
		case 0:
			output = "rm";
		case 1:
			output = "rmf";
		case 2:
			output = "rfm";
		case 3:
			output = "rf";
		case 4:
	}
}


// Encodes mode of dismissal as corresponding integer
// 0: bowled, 1: lbw, 2: caught, 3: run out, 4: stumped
int encode_dism(std::string mode) {
	int output;
	
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
}

// Unencodes mode of dismissal from integer to string
// 0: bowled, 1: lbw, 2: caught, 3: run out, 4: stumped
std::string unencode_dism(int encoding) {
	std::string output;

	switch (encoding) {
		case 0:
			output = "b";
		case 1:
			output = "lbw";
		case 2:
			output = "c";
		case 3:
			output = "ro";
		case 4:
			output = "st";
		default:
			output = "";

		return output;
	}

}
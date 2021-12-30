#include <iostream>
#include <vector>
#include <algorithm> // can randomize my vector through random_shuffle()
#include <ctime> // these two are used to create the random seed
#include <cstdlib>
using namespace std;
void game_24(vector <int> &x) {
	// 0 = +    1 = -    2 = *    3 = /
	// sort(x.begin(), x.end()); // sorts the vector from lowest value to highest (did not use)
	int counter = 0;
	while (counter <= 2400) { 
		random_shuffle(x.begin(), x.end()); // all indeces of vector are randomized
		// for each random seed of the vector all possible options of operations are run through
		for (int op_1 = 0; op_1 < x.size(); op_1++) { // 1st term +-*/
			for (int op_2 = 0; op_2 < x.size(); op_2++) { // 2nd term +-*/
				for (int op_3 = 0; op_3 < x.size(); op_3++) { // 3rd term +-*/
					for (int rc = 0; rc < 3; rc++) { // goes through (ab)cd, a(bc)d, ab(cd)
						counter++;
						int value = 0;
						int ab_cd1 = 0;
						int ab_cd2 = 0;
						int ab_cd_overall = 0;
						string p1, p2, p3;
						
						x.push_back(x[0]);
						x.push_back(x[1]); // new vector looks like (a, b, c, d, a, b) and allows for different groupings of (ab)cd a(bc)d and ab(cd)
						
						
						// most efficient way I could think to do this since you have to somehow convert 3 numbers into a function, probably some easier method
						if (op_1 == 0) {
							value += x[rc] + x[rc + 1];
							ab_cd1 = x[rc] + x[rc + 1];
							p1 = " + ";
						}
						else if (op_1 == 1) {
							value += abs(x[rc] - x[rc + 1]);
							ab_cd1 = abs(x[rc] - x[rc + 1]);
							p1 = " - ";
						}
						else if (op_1 == 2) {
							value += x[rc] * x[rc + 1];
							ab_cd1 = x[rc] * x[rc + 1];
							p1 = " * ";
						}
						else {
							if (x[rc] % x[rc + 1] == 0) {
								value += x[rc] / x[rc + 1];
								ab_cd1 = x[rc] / x[rc + 1];
							}
							else {
								x.pop_back();
								x.pop_back();
								continue;
							}
							p1 = " / ";
						}

						if (op_2 == 0) {
							value += x[rc+2];
							p2 = " + ";
						}
						else if (op_2 == 1) {
							value = abs(value - x[rc+2]);
							p2 = " - ";
						}
						else if (op_2 == 2) {
							value *= x[rc+2];
							p2 = " * ";
						}
						else {
							if (value % x[rc+2] == 0) {
								value /= x[rc+2];
							}
							else {
								x.pop_back();
								x.pop_back();
								continue;
							}
							p2 = " / ";
						}


						if (op_3 == 0) {
							value += x[rc + 3];
							ab_cd2 = x[rc + 2] + x[rc + 3];
							p3 = " + ";
						}
						else if (op_3 == 1) {
							value = abs(value - x[rc+3]);
							ab_cd2 = abs(x[rc + 2] - x[rc + 3]);
							p3 = " - ";
						}
						else if (op_3 == 2) {
							value *= x[rc + 3];
							ab_cd2 = x[rc + 2] * x[rc + 3];
							p3 = " * ";
						}
						else {
							if (value % x[rc + 3] == 0 && x[rc + 2] % x[rc + 3] == 0) {
								value /= x[rc + 3];
								ab_cd2 = x[rc + 2] / x[rc + 3];
							}
							else if (value % x[rc + 3] == 0){
								value /= x[rc + 3];
							}
							else if (x[rc + 2] % x[rc + 3] == 0) {
								ab_cd2 = x[rc + 2] / x[rc + 3];
							}
							else {
								x.pop_back();
								x.pop_back();
								continue;
							}
							p3 = " / ";
						}

						if (op_2 >= 2) {
							if (op_2 == 2) {
								ab_cd_overall = ab_cd1 * ab_cd2;
							}
							else {
								if (ab_cd2 != 0) {
									ab_cd_overall = ab_cd1 / ab_cd2;
								}
							}
						}
						else {
							if (op_2 == 0) {
								ab_cd_overall = ab_cd1 + ab_cd2;
							}
							else {
								ab_cd_overall = ab_cd1 - ab_cd2;
							}
						}
						
						
						




						
						// solution is found

						if (value == 24) {
							// basically hard programming all parentheses options
							//  NOT DONE!
							//cout << "Regular value method used" << endl;
							if (op_3 >= 2) { // last operation is */
								if (op_1 <= 1) {
									cout << "( (" << x[rc] << p1 << x[rc+1] << ")" << p2 << x[rc+2] << " )" << p3 << x[rc+3];
								}
								else {
									cout << "(" << x[rc] << p1 << x[rc + 1] << p2 << x[rc + 2] << ")" << p3 << x[rc + 3];
								}
							}
							else if (op_1 <= 1 && op_2 >= 2) { // (a +- b) */ c +- d
								cout << "(" << x[rc] << p1 << x[rc+1] << ")" << p2 << x[rc+2] << p3 << x[rc+3];
							}
							else {
								cout << x[rc] << p1 << x[rc+1] << p2 << x[rc+2] << p3 << x[rc+3];
							}
							cout << " = 24" << endl;
							cout << "It took me " << counter << " iterations to find this solution." << endl;
							x.pop_back();
							x.pop_back(); // needed here too because of return statement so that next runthrough isn't weird
							return; // all values of 24 return 
							

						}

						//ab_cd is a success
						if ((ab_cd_overall == 24) && (ab_cd1 != 24 || ab_cd2 == 1)) {
							//cout << "AB_CD method used" << endl;
							cout << "(" << x[rc] << p1 << x[rc + 1] << ")" << p2 << "(" << x[rc + 2] << p3 << x[rc + 3] << ") = 24" << endl;
							cout << "It took me " << counter << " iterations to find this solution." << endl;
							x.pop_back();
							x.pop_back();
							return;
						}

						x.pop_back();
						x.pop_back(); // deletes the two new ones each time so that the vector doesn't become infinitely large

					}
				}
			}
		}
	}
	cout << "That is not possible to my knowledge." << endl;
}
int main() {
	int num_input;
	char replay = 'a';
	vector <int> input_vect(4);
	srand(time(NULL));
	while (replay != 'n') {
		for (int i = 0; i < input_vect.size(); i++) {
			cout << "Number " << i + 1 << ": ";
			cin >> num_input;
			input_vect[i] = num_input;
		}
		game_24(input_vect);
		cout << "Play again? (y/n) ";
		cin >> replay;
	}
	return 0;
}
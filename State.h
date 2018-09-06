/*
 * State.h
 *
 *  Created on: Sep 3, 2018
 *      Author: sajitgurubacharya
 */

#ifndef STATE_H_
#define STATE_H_
#include <vector>

class State {
	int **currentState;
public:
	State();
	State(char);
//	State(const State&);
	State(const State&, int);
	int cost_G;
	bool operator<(const State& rhs) const;
	bool operator==(const State& rhs);
	bool operator!=(const State& rhs);
	bool solvable();

	void inputState();
	bool alreadyInputed(int, int**);
	bool compareState(State);
	void printState() const;
	void randomizeState();

	int getValue(int, int) const;
	void setValue(int, int, int);

	int manhattanDistance() const;
	void searchForManhattan(int numberToFind, int& xCoord, int& yCoord) const;

	int totalCost();
	void incrementCostG();
	int parentID;
};

void State::incrementCostG(){
	cost_G++;
}
int State::totalCost(){
	return cost_G + manhattanDistance();
}

void State::setValue(int x, int y, int value) {
	currentState[x][y] = value;
}

int State::getValue(int x, int y) const {
	return (currentState[x][y]);
}

bool State::solvable(){
//	vector<int> linearState;
//	for (int i=0;i<3;i++){
//		for (int j=0;j<3;j++){
//			linearState.push_back(currentState[i][j]);
//		}
//	}
//	int inversions=0;
//	for (int i=0;i<linearState.size()-1;i++){
//		for (int j=i+1;j<linearState.size();j++){
//			if (linearState[i]>linearState[j]){
//				if (linearState[j]!=0){
//					inversions++;
//				}
//			}
//		}
//	}
//	if (inversions%2==0){
//		return true;
//	}else{
//		return false;
//	}
	return true;
}

bool State::compareState(State toCompare) {
	if (toCompare < *this) {
		return false;
	} else if (*this < toCompare) {
		return false;
	} else {
		return true;
	}
}

bool State::alreadyInputed(int no, int** tempArray) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (tempArray[i][j] == no || no < 0 || no > 8) {
				cout << "Please try again, " << no << " already inputed!\n";
				return true;
			}
		}
	}
	return false;
}

void State::inputState() {
	int** tempArray;
	int tempInput;
	tempArray = new int*[3];
	for (int i = 0; i < 3; i++) {
		tempArray[i] = new int[3];
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tempArray[i][j] = -1;
		}
	}
	cout << "Input 9 numbers from 0 to 8 one by one\n";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int no = (i * 3) + (j + 1);
			cout << "Number " << no << ": ";
			do {
				cin >> tempInput;
			} while (alreadyInputed(tempInput, tempArray));
			setValue(i, j, tempInput);
			tempArray[i][j] = tempInput;
		}
	}
}

int State::manhattanDistance() const {
	int totalDistance = 0;
	int xCoord, yCoord;
	for (int i = 0; i < 8; i++) {
		searchForManhattan(i + 1, xCoord, yCoord);
		if (i + 1 <= 3 || i+1 == 7) {
			totalDistance += abs(xCoord - (i % 3)) + abs(yCoord - (i / 3));
		} else if (i + 1 == 4) {
			totalDistance += abs(xCoord - 2) + abs(yCoord - 1);
		}

		else if (i + 1 == 5) {
			totalDistance += abs(xCoord - 2) + abs(yCoord - 2);
		}

		else if (i + 1 == 6) {
			totalDistance += abs(xCoord - 1) + abs(yCoord - 2);
		}

		else if (i + 1 == 8) {
			totalDistance += abs(xCoord - 0) + abs(yCoord - 1);
		}
	}

	return totalDistance;
}

void State::searchForManhattan(int numberToFind, int& xCoord,
		int& yCoord) const {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (currentState[i][j] == numberToFind) {
				xCoord = j;
				yCoord = i;
				break;
			}
		}
	}
}

void State::printState() const {
	cout << "\n";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (currentState[i][j] != 0) {
				cout << currentState[i][j] << " ";
			} else {
				cout << "  ";
			}
		}
		cout << "\n";
	}
}

void State::randomizeState() {
	int numbers[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	int temp = -1;
	int tempRandom = -1;
	for (int i = 0; i < 9; i++) {
		tempRandom = rand() % 9;
		temp = numbers[i];
		numbers[i] = numbers[tempRandom];
		numbers[tempRandom] = temp;
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			currentState[i][j] = numbers[(i * 3) + j];
		}
	}

}

bool State::operator==(const State& state) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (this->currentState[i][j] != state.currentState[i][j]) {
				return false;
			}
		}
	}
	return true;
}

bool State::operator!=(const State& state) {
	return !(*this == state);
}

bool State::operator<(const State&rhs) const {
	return (this->manhattanDistance()+this->cost_G > rhs.manhattanDistance()+rhs.cost_G);
}

//State::State(const State& state) {
////	this->uniqueStateID=0;
//	parentID=88; // parent ID is being updated!!!
//	cost_G=state.cost_G;
//	currentState = new int*[3];
//	for (int i = 0; i < 3; i++) {
//		currentState[i] = new int[3];
//	}
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++) {
//			currentState[i][j] = state.getValue(i, j);
//		}
//	}
//}
State::State(const State& state, int parentID) {
//	this->uniqueStateID=0;
	this->parentID=parentID; // parent ID is being updated!!!
	cost_G=state.cost_G;
	currentState = new int*[3];
	for (int i = 0; i < 3; i++) {
		currentState[i] = new int[3];
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			currentState[i][j] = state.getValue(i, j);
		}
	}
}


State::State() {
	cost_G=0;
	parentID=0;
//	uniqueStateID=0;
	currentState = new int*[3];
	for (int i = 0; i < 3; i++) {
		currentState[i] = new int[3];
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			currentState[i][j] = 0;
		}
	}
}

State::State(char goal) {
	cost_G=0;
	parentID=0;
	currentState = new int*[3];
	for (int i = 0; i < 3; i++) {
		currentState[i] = new int[3];
	}
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++) {
//			currentState[i][j] = (i * 3) + j + 1;
//		}
//	}
	currentState[0][0]=1;
	currentState[0][1]=2;
	currentState[0][2]=3;
	currentState[1][2]=4;
	currentState[2][2]=5;
	currentState[2][1]=6;
	currentState[2][0]=7;
	currentState[1][0]=8;
	currentState[1][1]=0;
}


#endif /* STATE_H_ */

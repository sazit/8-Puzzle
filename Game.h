/*
 * Game.h
 *
 *  Created on: Sep 3, 2018
 *      Author: sajitgurubacharya
 */


#ifndef GAME_H_
#define GAME_H_
#include "State.h"
#include <queue>
#include <vector>
#include <stack>
#include <unistd.h>

class Game {
	State *goalState;
	State initialState;
	vector<State> allStates;
public:
	Game();
	~Game();
	void getNextState(priority_queue<State>&, State);
	void play();
	State getFreeStates(State, char, int);
	bool stateHasBeenVisited(vector<State>, State);
	bool AstateHasBeenVisited(vector<State>, State);
	bool AstateHasBeenVisited(priority_queue<State>, State);
	void A_StarSolution(int&);
	void reconstructPath();
	int findState(State);
};

int Game::findState(State state){
	for (int i=0;i<allStates.size();i++){
		if (allStates[i]==state){
			return i;
		}
	}
	return -2;
}

void Game::play() {
	int totalMovesTaken = 0;
	cout << "Our Goal State:";
	goalState->printState();
	cout << "\n Random Starting State:";
	initialState.inputState();
	initialState.printState();
	if(!initialState.solvable()){
		cout<<"NOT SOLVABLE!";
		exit(-1);
	}

	cout << "Manhattan Distance for Initial= "
			<< initialState.manhattanDistance() << "\n";
	A_StarSolution(totalMovesTaken);
	cout << "\nTotal Moves: " << totalMovesTaken;
}

State Game::getFreeStates(State currentState, char direction, int freeSpace) {
	freeSpace -= 1;
	int parent=findState(currentState);
	State copyCurrentState(currentState, parent);
	copyCurrentState.cost_G++;
	copyCurrentState.parentID=parent;
	if (direction == 'U') {
		copyCurrentState.setValue(freeSpace / 3, freeSpace % 3,
				copyCurrentState.getValue((freeSpace / 3) + 1, freeSpace % 3));
		copyCurrentState.setValue((freeSpace / 3) + 1, freeSpace % 3, 0);
		return copyCurrentState;
	} else if (direction == 'D') {
		copyCurrentState.setValue(freeSpace / 3, freeSpace % 3,
				copyCurrentState.getValue((freeSpace / 3) - 1, freeSpace % 3));
		copyCurrentState.setValue((freeSpace / 3) - 1, freeSpace % 3, 0);
		return copyCurrentState;
	} else if (direction == 'R') {
		copyCurrentState.setValue(freeSpace / 3, freeSpace % 3,
				copyCurrentState.getValue((freeSpace / 3),
						(freeSpace % 3) - 1));
		copyCurrentState.setValue((freeSpace / 3), (freeSpace % 3) - 1, 0);
		return copyCurrentState;
	} else {
		copyCurrentState.setValue(freeSpace / 3, freeSpace % 3,
				copyCurrentState.getValue((freeSpace / 3),
						(freeSpace % 3) + 1));
		copyCurrentState.setValue((freeSpace / 3), (freeSpace % 3) + 1, 0);
		return copyCurrentState;
	}

}

bool Game::stateHasBeenVisited(vector<State> statesVisited,
		State initialState) {
	if (statesVisited.size() == 0) {
		return false;
	}
	for (int i = 0; i < statesVisited.size(); i++) {
		if (statesVisited[i] == initialState) {
			return true;
		}
	}
	return false;
}

bool Game::AstateHasBeenVisited(vector<State> statesVisited,
		State initialState) {
	if (statesVisited.size() == 0) {
		return false;
	}
	for (int i = 0; i < statesVisited.size(); i++) {
		if (statesVisited[i] == initialState) {
			if (statesVisited[i].totalCost() <= initialState.totalCost()) {
				return true;
			} else if (statesVisited[i].totalCost()
					> initialState.totalCost()) {
				statesVisited[i] = initialState;
			}

		}
	}
	return false;
}

bool Game::AstateHasBeenVisited(priority_queue<State> statesVisited,
		State initialState) {
	if (statesVisited.size() == 0) {
		return false;
	}

	while (!statesVisited.empty()) {
		State currentState(statesVisited.top());
		if (currentState == initialState) {
			if (currentState.totalCost() <= initialState.totalCost()) {
				return true;
			} else if (currentState.totalCost() > initialState.totalCost()) {
				currentState = initialState;
			}
		}
		statesVisited.pop();
	}

	return false;
}


void Game::reconstructPath() {
	cout << allStates.size();
//	for (int i = 0; i < allStates.size(); i++) {
//		cout<<"\n";
//		allStates[i].printState();
//		cout<<"Parent: "<< allStates[i].parentID;
//	}
	int current=allStates.size()-1;
	vector<State> states;
	while(1){
		states.push_back(allStates[current]);
		current=allStates[current].parentID;
		if (current==0){
			states.push_back(initialState);
			break;
		}
	}
	for (int i = states.size()-1; i >=0 ; i--) {
		cout<<"\n";
		states[i].printState();
		cout<<"Parent: "<< allStates[i].parentID;
	}
	cout<<"\nTotal Moves="<< states.size()<<"\n";
}

void Game::A_StarSolution(int& totalMovesTaken) {
	vector<State> closedList;
	priority_queue<State> openList;
	priority_queue<State> nodeSuccessors;
	openList.push(initialState);
	while (!openList.empty()) {
		State currentBestState(openList.top());
//		currentBestState.printState();
		allStates.push_back(currentBestState);
		totalMovesTaken++;
//		cout << "\nCost | MD: " << currentBestState.manhattanDistance()
//				<< " Total: " << currentBestState.totalCost() << " cost_G " << currentBestState.cost_G <<"\n";
		if (currentBestState == *goalState) {
			cout << "Reconstructing Path!\n";
			reconstructPath();
			cout << "Winner, total checks: " << totalMovesTaken << "\n";
			exit(1);
		}
		closedList.push_back(currentBestState);
		getNextState(nodeSuccessors, currentBestState);
		openList.pop();
		while (!nodeSuccessors.empty()) {
			State temp(nodeSuccessors.top());
			if (AstateHasBeenVisited(openList, temp)) {
				nodeSuccessors.pop();
				continue;
			}
			if (AstateHasBeenVisited(closedList, temp)) {
				nodeSuccessors.pop();
				continue;
			}
			openList.push(temp);
			nodeSuccessors.pop();
		}
	}
	cout << "No solution!";
	exit(2);
}

void Game::getNextState(priority_queue<State>& next, State currentState) {
	while (!next.empty()) {
		next.pop();
	}
	int freeSpace = 0; // freeSpaces start from 1 to 9.
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if ((currentState.getValue(i, j)) == 0) {
				freeSpace = (i * 3 + j) + 1;
			}
		}
	}
	if (freeSpace <= 6) {
		next.push(getFreeStates(currentState, 'U', freeSpace));
	}
	if (freeSpace >= 4) {
		next.push(getFreeStates(currentState, 'D', freeSpace));
	}
	if (freeSpace % 3 == 0 || freeSpace % 3 == 2) {
		next.push(getFreeStates(currentState, 'R', freeSpace));
	}
	if (freeSpace % 3 == 1 || freeSpace % 3 == 2) {
		next.push(getFreeStates(currentState, 'L', freeSpace));
	}

}

Game::Game() {
	goalState = new State('G');
	initialState.randomizeState();
}

Game::~Game() {
	delete goalState;
}
#endif /* GAME_H_ */

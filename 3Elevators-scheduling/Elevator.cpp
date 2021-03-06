#include "Elevator.h"

void Elevator::up() {
	this->status = UP;
	this->currentFloor++;
}

void Elevator::down() {
	this->status = DOWN;
	this->currentFloor--;
}

void Elevator::stop() {
	for (std::vector<Passenger*>::iterator it = this->insider.begin(); it != this->insider.end(); ) {
		if (!(*it)->inside() && (*it)->getInitialFloor() == this->currentFloor) { // 是否抵达乘客起点层
			(*it)->setInside();
			it++;
		}
		else if ((*it)->inside() && (*it)->getTerminalFloor() == this->currentFloor) { // 是否抵达目的地
			(*it)->setArrived();
			it = this->insider.erase(it);
		}
		else {
			it++;
		}
	}
}

void Elevator::idle() {
	this->status = NONE;
}

void Elevator::pushPassenger(Passenger* pass) {
	this->insider.push_back(pass);
	pass->setAssigned();
}

void Elevator::pushOperation(const int& timer) {
	this->operations.push_back(std::make_pair(timer, this->currentFloor));
}

int Elevator::getMaxFloor() const {
	return this->maxFloor;
}

int Elevator::getCurrentFloor() const {
	return this->currentFloor;
}

const std::vector<Passenger*>& Elevator::getInsider() const {
	return this->insider;
}

Indicator Elevator::getStatus() const {
	return this->status;
}

bool Elevator::availableInFloor(int floor) {
	return floor > 0 && floor <= this->maxFloor;
}

std::string Elevator::type() const {
	return "Elevator";
}

void Elevator::outputPosition(std::ofstream& fout) const {
	fout << "Elevator\t\t" << this->currentFloor;
}

std::ostream &operator<< (std::ostream &os, const Elevator& ele) {
	for (std::vector<std::pair<int, int>>::const_iterator it = ele.operations.begin(); it != ele.operations.end(); it++) {
		if (it == ele.operations.begin() && it->second == 1) {
			continue;
		}
		os << it->first << ' ' << it->second << std::endl;
	}
	return os;
}
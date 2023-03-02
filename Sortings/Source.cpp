#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
using namespace std;

bool forward_step(int array[], int min, int max) {
	int t;
	for (int i = min; i < max; i++) {
		if (array[i] > array[i + 1]) {
			t = array[i];
			array[i] = array[i + 1];
			array[i + 1] = t;
			return false;
		}
	}
	return true;
}

bool backward_step(int array[], int min, int max) {
	int t;
	for (int i = max; i > min; i--) {
		if (array[i] < array[i - 1]) {
			t = array[i];
			array[i] = array[i - 1];
			array[i - 1] = t;
			return false;
		}
	}
	return true;
}

int *shaker(int array[], int n) {
	bool sorted = false;
	int min = 0;
	int max = n - 1;
	while ((min < max) && !sorted){
		forward_step(array, min, max);
		sorted = forward_step(array, min, max);
		max -= 1;
		backward_step(array, min, max);
		sorted = backward_step(array, min, max);
		min += 1;
	}
	return array;
}
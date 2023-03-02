#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
using namespace std;

int* random(int n) {
	srand(200);
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		arr[i] = rand();
	};
	return arr;
}

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

bool testing_forward_step() {
	for (int i = 10; i <= 100; i += 10) {
		auto arr = random(i);
		forward_step(arr, 0, i - 1);
		for (int j = 0; j < i-1; j++) {
			if (arr[j] > arr[i - 1]) { return false; }
		}
	}
	return true;
}

bool testing_backward_step() {
	for (int i = 10; i <= 100; i += 10) {
		auto arr = random(i);
		backward_step(arr, 0, i - 1);
		for (int j = 1; j < i; j++) {
			if (arr[j] <  arr[i - 1]) { return false; }
		}
	}
	return true;
}

bool testing_shaker() {
	for (int i = 10; i <= 100; i += 10) {

	}
}

void writing_to_file(string s) {
	std::ofstream ofs;
	ofs.open("C:\\c_projects\\Sortings\\data.txt", std::ofstream::out | std::ofstream::app);

	ofs << s << endl;

	ofs.close();
}

int main() {

	return 0;
}
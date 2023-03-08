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
	auto array = arr;
	delete[] arr;
	arr = nullptr;
	return array;
}

void array_output(int array[], int n) {
	for (int i = 0; i < n; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
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
		auto arr = shaker(random(i), i);
		for (int j = 0; j < i-1; j++) {
			if (arr[j] > arr[j + 1]) {
				return false;
			}
		}
	}
	return true;
}

bool long_step(int array[], int n, int i) {
	for (int j = 0; i + j < n; j += i) {
		if (array[j] > array[j + i]) {
			auto t = array[j];
			array[j] = array[j + i];
			array[j + i] = t;
			return false;
		}
	}
	return true;
}

int* comb_sort(int array[], int n) {
	bool sorted = false;
	while (!sorted) {
		for (int i = n - 1; i > 1; i--) {
			long_step(array, n, i);
			sorted = long_step(array, n, i);
		}
	}
	return array;
}

void writing_to_file(string s) {
	std::ofstream ofs;
	ofs.open("C:\\c_projects\\Sortings\\data.txt", std::ofstream::out | std::ofstream::app);

	ofs << s << endl;

	ofs.close();
}

void separate_atring() {
	std::ofstream ofs;
	ofs.open("C:\\c_projects\\Asymptotic complexity of algorithms\\data.txt", std::ofstream::out | std::ofstream::app);

	ofs << endl;

	ofs.close();
}

int main() {
	cout << testing_forward_step() << testing_backward_step() << testing_shaker() << endl;
	int a[] = {3, 2, 1 };
	array_output(comb_sort(a, 3), 3);

	return 0;
}
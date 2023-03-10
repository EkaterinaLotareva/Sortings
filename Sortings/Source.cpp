#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <cmath>
using namespace std;
int const N = 10000;
int ARRAY[N];
int const M = 100;

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

int* copy_array(int array[], int n) {
	auto arr = new int[n];
	for (int i = 0; i < n; i++) {
		arr[i] = array[i];
	}
	auto a = arr;
	delete[] arr;
	arr = nullptr;
	return a;
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


int *shaker_sort(int array[], int n) {
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
		auto arr = shaker_sort(random(i), i);
		for (int j = 0; j < i-1; j++) {
			if (arr[j] > arr[j + 1]) {
				return false;
			}
		}
	}
	return true;
}

bool bubble_step(int array[], int n, int step) {
	for (int j = 0; step + j < n; j += step) {
		if (array[j] > array[j + step]) {
			auto t = array[j];
			array[j] = array[j + step];
			array[j + step] = t;
			return false;
		}
	}
	return true;
}

int* comb_sort(int array[], int n) {
	bool sorted = false;
	while (!sorted) {
		for (int i = n - 1; i > 1; i--) {
			bubble_step(array, n, i);
			sorted = bubble_step(array, n, i);
		}
	}
	return array;
}

void sort_step(int array[], int n, int step) {
	for (int sorted = n - 1; sorted > 0; sorted-=step) {
		for (int i = sorted - step; i < n - 1; i+=step) {
			if (array[i] >= array[i + step]) {
				auto t = array[i];
				array[i] = array[i + step];
				array[i = step] = t;
			}
		}
	}
}

int* shell_sort_2(int array[], int n) {
	auto step = n/2;
	while (step >= 1) {
		sort_step(array, n, step);
		step = step / 2;
	}
	return array;
}

int fibonacci_sequence(int max) {
	ARRAY[0] = 1;
	ARRAY[1] = 1;
	int n = 1;
	for (int i = 0; ARRAY[i] + ARRAY[i + 1] <= max; i++) {
		ARRAY[i + 2] = ARRAY[i] + ARRAY[i + 1];
		n ++;
	}
	return n;
}

int hibbard_sequence(int max) {
	int n = -1;
	for (int i = 1; pow(2, i) - 1 <= max; i++) {
		ARRAY[i - 1] = pow(2, i) - 1;
		n++;
	}
	return n;
}

int* shell_sort_hibbard(int array[], int n) {
	hibbard_sequence(n);
	int m = hibbard_sequence(n);
	auto step = ARRAY[m];
	while (step >= 1) {
		sort_step(array, n, step);
		m--;
		step = ARRAY[m];
	}
	return array;
}

int* shell_sort_fibonacci(int array[], int n) {
	fibonacci_sequence(n);
	int m = fibonacci_sequence(n);
	auto step = ARRAY[m];
	while (step >= 1) {
		sort_step(array, n, step);
		m--;
		step = ARRAY[m];
	}
	return array;
}

void writing_to_file(int s) {
	std::ofstream ofs;
	ofs.open("C:\\c_projects\\Sortings\\data.txt", std::ofstream::out | std::ofstream::app);

	ofs << s << endl;

	ofs.close();
}

void separate_string() {
	std::ofstream ofs;
	ofs.open("C:\\c_projects\\Sortings\\data.txt", std::ofstream::out | std::ofstream::app);

	ofs << endl;

	ofs.close();
}

void time_shaker_sort() {
	std::ofstream ofs;
	ofs.open("C:\\c_projects\\Sortings\\data.txt", std::ofstream::out | std::ofstream::app);
	for (int i = 10; i <= 10000; i += 100) {
		auto array = random(i);
		auto begin = chrono::steady_clock::now();
		for (int j = 0; j <= 100; j++) {
			auto A = copy_array(array, i);
			shaker_sort(A, i);
		}
		auto end = chrono::steady_clock::now();
		auto time_span =
			chrono::duration_cast<chrono::microseconds>(end - begin);
		ofs << time_span.count() << ",";
	}
	ofs.close();
}

void time_comb_sort() {
	std::ofstream ofs;
	ofs.open("C:\\c_projects\\Sortings\\data.txt", std::ofstream::out | std::ofstream::app);
	for (int i = 10; i <= 10000; i += 100) {
		auto array = random(i);
		auto begin = chrono::steady_clock::now();
		for (int j = 0; j <= 10; j++) {
			auto A = copy_array(array, i);
			comb_sort(A, i);
		}
		auto end = chrono::steady_clock::now();
		auto time_span =
			chrono::duration_cast<chrono::microseconds>(end - begin);
		ofs << time_span.count() << ",";
	}
	ofs.close();
}

void transpositions_comb_sort() {

}

void time_shell_sort_2() {
	std::ofstream ofs;
	ofs.open("C:\\c_projects\\Sortings\\data.txt", std::ofstream::out | std::ofstream::app);
	for (int i = M; i <= N; i += M) {
		auto array = random(i);
		auto begin = chrono::steady_clock::now();
		for (int j = 0; j <= 10; j++) {
			auto A = copy_array(array, i);
			shell_sort_2(A, i);
		}
		auto end = chrono::steady_clock::now();
		auto time_span =
			chrono::duration_cast<chrono::milliseconds>(end - begin);
		ofs << time_span.count() << ",";
	}
	ofs.close();
}

void time_shell_sort_hibbard() {
	std::ofstream ofs;
	ofs.open("C:\\c_projects\\Sortings\\data.txt", std::ofstream::out | std::ofstream::app);
	for (int i = M; i <= N; i += M) {
		auto array = random(i);
		auto begin = chrono::steady_clock::now();
		for (int j = 0; j <= 10; j++) {
			auto A = copy_array(array, i);
			shell_sort_hibbard(A, i);
		}
		auto end = chrono::steady_clock::now();
		auto time_span =
			chrono::duration_cast<chrono::milliseconds>(end - begin);
		ofs << time_span.count() << ",";
	}
	ofs.close();
}

void time_shell_sort_fibonacci() {
	std::ofstream ofs;
	ofs.open("C:\\c_projects\\Sortings\\data.txt", std::ofstream::out | std::ofstream::app);
	for (int i = M; i <= N; i += M) {
		auto array = random(i);
		auto begin = chrono::steady_clock::now();
		for (int j = 0; j <= 100; j++) {
			auto A = copy_array(array, i);
			shell_sort_fibonacci(A, i);
		}
		auto end = chrono::steady_clock::now();
		auto time_span =
			chrono::duration_cast<chrono::milliseconds>(end - begin);
		ofs << time_span.count() << ",";
	}
	ofs.close();
}


int main() {
	cout << testing_forward_step() << testing_backward_step() << testing_shaker();
	time_shell_sort_2();
	return 0;
}
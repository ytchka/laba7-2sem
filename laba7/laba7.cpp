#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
using namespace std;
void sortThread(const string& threadName, vector<double>& arr, int start, int end) {
    sort(arr.begin() + start, arr.begin() + end + 1);

    for (int i = start; i <= end; ++i) {
        cout << threadName << ": " << arr[i] << endl;
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

void merge(vector<double>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<double> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0;
    int k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        }
        else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

int main() {
    const int SIZE = 10;
    vector<double> arr(SIZE);

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 100);
    for (int i = 0; i < SIZE; ++i) {
        arr[i] = dis(gen);
    }

    thread thread1(sortThread, "thread1", ref(arr), 0, SIZE / 2 - 1);
    thread thread2(sortThread, "thread2", ref(arr), SIZE / 2, SIZE - 1);

    thread1.join();
    thread2.join();

    merge(arr, 0, SIZE / 2 - 1, SIZE - 1);

    cout << "All threads have finished their work." << endl;

    for (double num : arr) {
        cout << num << endl;
    }

    return 0;
}
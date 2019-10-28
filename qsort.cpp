#include <iostream>

using namespace std;

void Qsort(int arr[], int low, int high);
void swap(int &x, int &y);

int main() {
	int arr[] = { 1,3,5,7,4,2,9,0,6,16,71,66,80,93,95 };
	Qsort(arr, 0, 14);
	for (int i = 0; i < 14; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}

void Qsort(int arr[], int low, int high) {
	if (low >= high) { return; }
	
	int key = arr[low];		//ȡ��һ������Ϊkey
	int i = low;			//��������Ѱ�ұ�key�����
	int j = high + 1;		//��������Ѱ�ұ�keyС����

	while (true) {
		while (arr[++i] < key) {
			if (i == high) { break; }
		}
		while (arr[--j] > key) {
			if (j == low) { break; }
		}
		if (i >= j) { break; }						//�����ཻ�����Ѿ�ȫ�����н���
		swap(arr[i], arr[j]);						//�����������н���
	}
	swap(arr[low], arr[j]);							//��key�����м䣨��߶���keyС���ұ߶���key��
													//arr[j]��keyС��arr[i]��key�����Ӧ��arr[j]������ͷ
	Qsort(arr, low, j - 1);							//ע�����ӦΪj-1,j+1,�����jΪ�����ᵼ��Stack overflow
	Qsort(arr, j + 1, high);
}



void swap(int &x, int &y) {
	int temp = x;
	x = y;
	y = temp;
}
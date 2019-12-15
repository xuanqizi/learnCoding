#include <iostream>

void shellSort(int arr[], int n);

int main() {
	int arr[] = { 6,5,9,8,1,2,3,7,13,16 };
	shellSort(arr, 10);
	for (int i = 0; i < 10; i++) {
		std::cout << arr[i];
		if (i < 9) {
			std::cout << " ";
		}
		else {
			std::cout << std::endl;
		}
	}
	system("pause");
	return 0;
}

void shellSort(int arr[], int n) {
	int increment[] = { 8,4,2,1 };						//��������
	int gap = 0;
	for (int i = 0; i < 4; i++) {
		gap = increment[i];
		for (int j = 0; j < gap; j++) {
			for (int k = gap + j; k < n; k += gap) {
				if (arr[k] < arr[k - gap]) {
					int temp = arr[k];					//�ݴ�arr[k]��ֵ�����ڲ��뵽��ȷλ��
					int w;								//��ǰ���壬ʹw������������kѭ��
					for (w = k - gap; w >= 0 && arr[w] > temp;
						w -= gap) {
						arr[w + gap] = arr[w];			//����ƣ��ο���������
					}
					arr[w + gap] = temp;				//����ǰarr[k]��ֵ���뵽��λ��
				}
			}
		}
	}
}

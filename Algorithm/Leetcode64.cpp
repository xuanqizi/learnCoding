/* Leetcode 64 Minimum Path Sum */
//����һ�������Ǹ������� m x n �������ҳ�һ�������Ͻǵ����½ǵ�·����ʹ��·���ϵ������ܺ�Ϊ��С��
//ÿ��ֻ�����»��������ƶ�һ����
//˼·��ֻ��������->DP

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
	int minPathSum(vector<vector<int>>& grid) {
		int m = grid.size();				//m��
		int n = grid[0].size();				//n��
		for (int i = 1; i < n; i++) {		//�޸ĵ�0��
			grid[0][i] = grid[0][i - 1] + grid[0][i];
		}
		for (int i = 1; i < m; i++) {		//�޸ĵ�0��
			grid[i][0] = grid[i - 1][0] + grid[i][0];
		}
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				grid[i][j] = grid[i][j] + min(grid[i - 1][j], grid[i][j - 1]);
			}
		}
		return grid[m - 1][n - 1];
	}
};

int main() {
	Solution s;
	vector<int> v1 = { 1,2,5 };
	vector<int> v2 = { 3,2,1 };
	vector<vector<int>> v;
	v.push_back(v1); v.push_back(v2);
	cout << s.minPathSum(v) << endl;
	system("pause");
	return 0;
}

//grid[i][j]=grid[i][j]+min{grid[i-1][j],grid[i][j-1]}
# Python实现朴素贝叶斯分类器

import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split

class NaiveBayes:
	def __init__(self) -> None:
		self.summaries = { }	# 提取的属性特征
		self.prior_dict = { 
			-1: 0.0,
			1: 0.0
		}	# 存储先验概率
		self.count_dict = { 
			-1: 0,
			1: 0
		}	# 存储记录的出现频率
		self.total_num = 0		# 训练集的总长度

	def prior_probability(self, Y):
		num = len(Y)
		print(Y)
		self.total_num += num
		count_dict = {
			-1: 0,
			1: 0
		}
		for y in Y:
			count_dict[y] = count_dict[y] + 1
		self.count_dict[-1] += count_dict[-1]
		self.count_dict[1] += count_dict[1]
		self.prior_dict[1] = self.count_dict[1] / float(self.total_num)
		self.prior_dict[-1] = self.count_dict[-1] / float(self.total_num)	


	def train(self, trainset):
		X = trainset[:,[0, 1, 2]]
		Y = trainset[:,3]
		self.prior_probability(Y)	# 计算先验概率
		

	def test(self, testset):
		pass

# 以信息增益为标准，计算第一列的阈值
# 2, 3, 4列本就是二分数据，因此不需要求阈值
def get_threshold(dataset):
	col1 = dataset[...,0]
	return 0.0


# 将数据进行离散化
def discretize(dataset, threshold):
	labels = [-1, 1]
	bins = [
		[-1.87, threshold, 0.966],
		[-0.228, 0, 4.39],
		[-1.92, 0, 0.522],
		[-1.0, 0, 1.1]
	]
	for i in range(4):
		col = pd.cut(dataset[...,i], bins=bins[i], labels=labels, \
			include_lowest= True)
		dataset[...,i] = col
	return dataset	
	
# 划分数据集
def split_dataset(dataset):
	train, test = train_test_split(dataset, test_size= 0.3)
	return train, test

def main():
	# 读取文件
	filepath = 'D:\\learnCoding\\Python\\titanic.dat'
	data = pd.read_table(filepath, sep= ',', \
		skiprows= [0, 1, 2, 3, 4, 5, 6, 7])
	dataset = np.array(data)
	# print(dataset)
	threshold = get_threshold(dataset)
	dataset = discretize(dataset, threshold)
	# print(dataset)
	train_set, test_set = split_dataset(dataset)
	nbc = NaiveBayes()
	nbc.train(train_set)
	accuracy = nbc.test(test_set)

	

if __name__ == "__main__":
	main()
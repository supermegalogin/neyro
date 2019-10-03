#include "countattribute.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <iomanip>
#include <vector>
#include <queue>
#include <math.h>
#include <ctime>

CountAttribute::CountAttribute()
{
	A = this->set("A.txt");
	B = this->set("B.txt");
	C = this->set("C.txt");
	notC.reserve(B.size() + A.size());
	for (int g = 0; g < A.size(); g++) {
		notC.push_back(A[g]);
	}
	for (int g = 0; g < B.size(); g++) {
		notC.push_back(B[g]);
	}
	std::vector<float> INF1 = counеInformativeness(C, notC);
	maxI1 = INF1[0]; maxI2 = INF1[1];
	std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
	std::vector<float> INF2 = counеInformativeness(A, B);
	maxIs1 = INF2[0]; maxIs2 = INF2[1];
	bool log = true;
	srand(time(0));
	while (log) {
		int len = C.size();
		std::vector<bool> zoneRandom(len, true);
		for (int g = 0, norSize = 0; g < len && g < 5; g++) {
			int elem = rand() % len;
			if (zoneRandom[elem]) {
				zoneRandom[elem] = false;
				Cl.push_back(C[elem]);
			} else {
				g--;
			}
		}
		for (int g = 0, norSize = 0; g < len; g++) {
			if (zoneRandom[g]) {
				Clm.push_back(C[g]);
			}
		}
		len = B.size();
		zoneRandom = std::vector<bool>(len, true);
		for (int g = 0, norSize = 0; g < len && g < 5; g++) {
			int elem = rand() % len;
			if (zoneRandom[elem]) {
				zoneRandom[elem] = false;
				Bl.push_back(B[elem]);
			} else {
				g--;
			}
		}
		for (int g = 0, norSize = 0; g < len; g++) {
			if (zoneRandom[g]) {
				Blm.push_back(B[g]);
			}
		}
		len = A.size();
		zoneRandom = std::vector<bool>(len, true);
		for (int g = 0; g < len && g < 5; g++) {
			int elem = rand() % len;
			if (zoneRandom[elem]) {
				zoneRandom[elem] = false;
				Al.push_back(A[elem]);
			} else {
				g--;
			}
		}
		for (int g = 0, norSize = 0; g < len; g++) {
			if (zoneRandom[g]) {
				Alm.push_back(A[g]);
			}
		}

		Clnot.reserve(Alm.size() + Blm.size());
		for (int g = 0; g < Alm.size(); g++) {
			Clnot.push_back(Alm[g]);
		}
		for (int g = 0; g < Blm.size(); g++) {
			Clnot.push_back(Blm[g]);
		}

		for (int g = 0; g < Cl.size(); g++) {
			std::cout << std::endl << std::endl << "Класс объекта С" << std::endl;
			getClass(Cl[g]);
		}
		for (int g = 0; g < Bl.size(); g++) {
			std::cout << std::endl << std::endl << "Класс объекта B" << std::endl;
			getClass(Bl[g]);
		}
		for (int g = 0; g < Al.size(); g++) {
			std::cout << std::endl << std::endl << "Класс объекта A" << std::endl;
			getClass(Al[g]);
		}
		log = false;
	}
	std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
	std::cout << countDiscret(6, 3, C, notC, maxI1, maxI2);
}

int CountAttribute::getClass(std::vector<float> Obj) {
	std::cout << "Проверка объкта. Объект: ";
	for (int k = 0; k < Obj.size(); k++) {
		std::cout << " p" << k + 1 << " = " << Obj[k];
	}
	std::cout << std::endl;
	std::vector<int> souder = countNeighbour(Obj[maxI1], Obj[maxI2], Clm, Clnot, maxI1, maxI2);
	bool discretVote = countDiscret(Obj[maxI1], Obj[maxI2], Clm, Clnot, maxI1, maxI2);
	int vote = 0;
	if (discretVote) {
		vote++;
		std::cout << "Дискретная функция проголосовала ЗА" << std::endl;
	}
	else {
		std::cout << "Дискретная функция проголосовала ПРОТИВ" << std::endl;
	}
	if (souder[0] >= 2) {
		vote++;
		std::cout << "Три ближайших соседа проголосовали ЗА" << std::endl;
	}
	else {
		std::cout << "Три ближайших соседа проголосовали ПРОТИВ" << std::endl;
	}
	if (souder[1] >= 3) {
		vote++;
		std::cout << "Пять ближайших соседа проголосовали ЗА" << std::endl;
	}
	else {
		std::cout << "Пять ближайших соседа проголосовали ПРОТИВ" << std::endl;
	}

	if (vote >= 2) {
		std::cout << "Решение приято это класс C" << std::endl;
		return 0;
	}
	else {
		std::cout << "Решение приято это класс неC" << std::endl;
	}


	std::cout << "Проверка обькта класса на А";
	std::cout << std::endl;
	souder = countNeighbour(Obj[maxIs1], Obj[maxIs2], Alm, Blm, maxIs1, maxIs2);
	discretVote = countDiscret(Obj[maxIs1], Obj[maxIs2], Alm, Blm, maxIs1, maxIs2);
	vote = 0;
	if (discretVote) {
		vote++;
		std::cout << "Дискретная функция проголосовала ЗА" << std::endl;
	}
	else {
		std::cout << "Дискретная функция проголосовала ПРОТИВ" << std::endl;
	}
	if (souder[0] >= 2) {
		vote++;
		std::cout << "Три ближайших соседа проголосовали ЗА" << std::endl;
	}
	else {
		std::cout << "Три ближайших соседа проголосовали ПРОТИВ" << std::endl;
	}
	if (souder[1] >= 3) {
		vote++;
		std::cout << "Пять ближайших соседа проголосовали ЗА" << std::endl;
	}
	else {
		std::cout << "Пять ближайших соседа проголосовали ПРОТИВ" << std::endl;
	}

	if (vote >= 2) {
		std::cout << "Решение приято это класс A" << std::endl;
		return 0;
	}
	else {
		std::cout << "Решение приято это класс B" << std::endl;
	}

}


std::vector<int> CountAttribute::countNeighbour(float x, float y, std::vector<std::vector<float>> &C, std::vector<std::vector<float>> &notC, int I1,int I2) {
	std::vector<std::vector<float>> size;
	size.reserve(notC.size() + C.size());
	int len = notC.size() + C.size();
	for (int g = 0; g < notC.size(); g++) {
		std::vector<float> local;
		float dist = sqrt((notC[g][I1] - x) * (notC[g][I1] - x) + (notC[g][I2] - y) * (notC[g][I2] - y));
		local.push_back(dist);
		local.push_back(g);
		size.push_back(local);
	}
	for (int g = 0; g < C.size(); g++) {
		std::vector<float> local;
		float dist = sqrt((C[g][I1] - x) * (C[g][I1] - x) + (C[g][I2] - y) * (C[g][I2] - y));
		local.push_back(dist);
		local.push_back(g + notC.size());
		size.push_back(local);
	}
	for (int i = 0; i < size.size() - 1; i++) {
		std::vector<float> temp;
		for (int j = 0; j < size.size() - i - 1; j++) {
			if (size[j][0] > size[j + 1][0]) {
				temp = size[j];
				size[j] = size[j + 1];
				size[j + 1] = temp;
			}
		}
	}
	int voteA3 = 0, voteNeA3 = 0;
	int voteA5 = 0, voteNeA5 = 0;
	for (int g = 0; g < size.size() && g < 5; g++) {
		if (size[g][1] < notC.size()) {
			voteNeA5++;
			if (g < 3) {
				voteNeA3++;
			}
		}
		else {
			voteA5++;
			if (g < 3) {
				voteA3++;
			}
		}
	

	}
	std::vector<int> vote;
	vote.push_back(voteA3);
	vote.push_back(voteA5);
	return vote;
};

bool CountAttribute::countDiscret(float x, float y, std::vector<std::vector<float>>& C, std::vector<std::vector<float>>& notC, int I1, int I2) {
	int countAttribute = C[0].size();
	int aSize = C.size();
	int neaSize = notC.size();
	std::vector<int> vote;
	std::vector<float> sumC(2, 0);
	std::vector<float> sumNeC(2, 0);
	for (int k = 0; k < aSize; k++) {
		sumC[0] += C[k][I1];
	}
	for (int k = 0; k < neaSize; k++) {
		sumNeC[0] += notC[k][I1];
	}
	sumNeC[0] = sumNeC[0] / neaSize;
	sumC[0] = sumC[0] / aSize;

	for (int k = 0; k < aSize; k++) {
		sumC[1] += C[k][I2];
	}
	for (int k = 0; k < neaSize; k++) {
		sumNeC[1] += notC[k][I2];
	}
	sumNeC[1] = sumNeC[1] / neaSize;
	sumC[1] = sumC[1] / aSize;
	float c = -(((sumC[1] - sumNeC[1])*(sumC[1] + sumNeC[1]) / 2)  + ((sumC[0] - sumNeC[0])*(sumC[0] + sumNeC[0]))) / 2;
	float sum = c + x * (sumC[1] - sumNeC[1]) + y * (sumC[0] - sumNeC[0]);
	return (sum > 0);
};




std::vector<float> CountAttribute::counеInformativeness(std::vector<std::vector<float>> &A, std::vector<std::vector<float>> &notA) {
	std::cout << std::setw(16);
	int countAttribute = A[0].size();
	int aSize = A.size();
	int neaSize = notA.size();
	std::vector<std::vector<float>> corMatr(countAttribute, std::vector<float>(countAttribute, 0));
	std::vector<float> informationalFirst(countAttribute, 0);
	std::vector<float> sumC(countAttribute, 0);
	std::vector<float> sumNeC(countAttribute, 0);
	for (int g = 0; g < countAttribute; g++) {
		for (int k = 0; k < aSize; k++) {
			sumC[g] += A[k][g];
		}
		for (int k = 0; k < neaSize; k++) {
			sumNeC[g] += notA[k][g];
		}
		sumNeC[g] = sumNeC[g] / neaSize;
		sumC[g] = sumC[g] / aSize;
	}
	std::cout << "Cреднее арифметическое признаков С" << std::endl;
	for (int coutL = 0; coutL < countAttribute; coutL++) {
		std::cout << "№" << (coutL + 1) << " = " << std::setw(10) << sumC[coutL] << " ";
	}
	std::cout << std::endl << "Cреднее арифметическое признаков не С" << std::endl;
	for (int coutL = 0; coutL < countAttribute; coutL++) {
		std::cout << "№" << (coutL + 1) << " = " << std::setw(10) << sumNeC[coutL] << " ";
	}
	std::vector<float> matC(countAttribute, 0);
	std::vector<float> matNeC(countAttribute, 0);
	for (int g = 0; g < countAttribute; g++) {
		matC[g] = matNeC[g] = 0;
		for (int k = 0; k < aSize; k++) {
			matC[g] += (A[k][g] - sumC[g]) * (A[k][g] - sumC[g]);
		}
		for (int k = 0; k < neaSize; k++) {
			matNeC[g] += (notA[k][g] - sumNeC[g]) * (notA[k][g] - sumNeC[g]);
		}
		matC[g] = matC[g] / aSize;
		matNeC[g] = matNeC[g] / neaSize;
	}
	std::cout << std::endl << "Информативность" << std::endl;
	for (int g = 0; g < countAttribute; g++) {
		informationalFirst[g] = ((sumC[g] - sumNeC[g]) * (sumC[g] - sumNeC[g])) / (std::abs(matC[g]) + std::abs(matNeC[g]));
		std::cout << "№" << (g + 1) << " = " << std::setw(10) << informationalFirst[g] << " ";
	}
	std::vector<std::vector<float>> XiMxC(countAttribute, std::vector<float>(aSize, 0));
	for (int g = 0; g < countAttribute; g++) {
		for (int k = 0; k < aSize; k++) {
			XiMxC[g][k] = A[k][g] - sumC[g];
		}
	}
	for (int g = 0; g < countAttribute; g++) {
		for (int k = 0; k < countAttribute; k++) {
			float sumLocal = 0;
			for (int j = 0; j < aSize; j++) {
				sumLocal += XiMxC[g][j] * XiMxC[k][j];
			}
			sumLocal = (sumLocal / (aSize * std::sqrt(matC[g]) * std::sqrt(matC[k])));
			corMatr[g][k] = sumLocal;
		}
	}
	std::cout << std::endl << "Матрица кореляции" << std::endl;
	for (int g = 0; g < countAttribute; g++) {
		for (int k = 0; k < countAttribute; k++) {
			std::cout << std::setw(12) << corMatr[g][k] << " ";
		}
		std::cout << std::endl;
	}
	std::vector<std::vector<int>> graf = generateGraf(corMatr);
	for (int g = 0; g < countAttribute; g++) {
		int len = graf[g].size();
		int maxIndex = g;
		float maxInf = informationalFirst[g];
		for (int k = 0; k < len; k++) {
			if (maxInf < informationalFirst[graf[g][k]]) {
				maxInf = informationalFirst[graf[g][k]];
				maxIndex = graf[g][k];
			}
		}
		if (len > 0) {
			if (g != maxIndex) {
				informationalFirst[g] = 0;
			}
		}
		for (int k = 0; k < len; k++) {
			if (graf[g][k] != maxIndex) {
				informationalFirst[graf[g][k]] = 0;
			}
		}
	}
	std::cout << std::endl << "Информативность с учетом групп" << std::endl;
	for (int g = 0; g < countAttribute; g++) {
		std::cout << "№" << (g + 1) << " = " << std::setw(10) << informationalFirst[g] << " ";
	}
	float inf1 = -1, inf2 = -1;
	int inf1Index = -1, inf2Index = -1;
	for (int g = 0; g < countAttribute; g++) {
		if (inf1 < informationalFirst[g]) {
			inf1 = informationalFirst[g];
			inf1Index = g;
		}
	}
	for (int g = 0; g < countAttribute; g++) {
		if (inf2 < informationalFirst[g] && inf1 != informationalFirst[g]) {
			inf2 = informationalFirst[g];
			inf2Index = g;
		}
	}
	std::cout << std::endl << "Максимальная ифнормативность" << std::endl;
	std::cout << "№" << (inf1Index + 1) << " = " << std::setw(10) << informationalFirst[inf1Index] << " ";
	std::cout << "№" << (inf2Index + 1) << " = " << std::setw(10) << informationalFirst[inf2Index] << " ";
	std::vector<float> inf;
	inf.push_back(inf1Index);
	inf.push_back(inf2Index);
	return inf;
}

std::vector<std::vector<int>> CountAttribute::generateGraf(std::vector<std::vector<float>> matrix)
{
	int countAttribute = matrix[0].size();
	int aSize = matrix.size();
	std::vector<std::vector<float>> mat(countAttribute, std::vector<float>(countAttribute, 0));;
	for (int g = 0; g < countAttribute; g++) {
		for (int k = 0; k < countAttribute; k++) {
			mat[g][k] = matrix[g][k];
		}
	}
	std::vector<std::vector<bool>> zone(countAttribute, std::vector<bool>(countAttribute,true));
	for (int g = 0; g < countAttribute; g++) {
		mat[g][g] = 0;
		zone[g][g] = false;
	}
	int maxX = 1, maxY = 0;
	float maxElem = mat[0][1]; 
	for (int g = 0; g < countAttribute; g++) {
		for (int k = 0; k < countAttribute; k++) {
			if (mat[g][k] > maxElem) {
				maxElem = mat[g][k];
				maxX = g;
				maxY = k;
			}
		}
	}
	std::vector<std::vector<int>> graf(countAttribute, std::vector<int>());
	graf[maxX].push_back(maxY);
	zone[maxX][maxY] = false;
	zone[maxY][maxX] = false;
	while (true) {
		bool confirm = true;
		for (int g = 0; g < countAttribute; g++) {
			for (int k = 0; k < countAttribute; k++) {
				if (zone[g][k]) {
					confirm = false;
				}
			}
		}
		if (confirm) break;
		while (true) {
			if (maxX < maxY) {
				int tmp = maxY;
				maxY = maxX;
				maxX = tmp;
			}
			int maxRow = maxY, localMax = 0;
			maxElem = -2;
			for (int k = 0; k < countAttribute; k++) {
				if (mat[maxY][k] > maxElem && zone[maxY][k]) {
					maxElem = mat[maxY][k];
					maxRow = maxY;
					localMax = k;
				}
				if (mat[maxX][k] > maxElem && zone[maxX][k]) {
					maxElem = mat[maxX][k];
					maxRow = maxX;
					localMax = k;
				}
			}
			graf[maxRow].push_back(localMax);
			zone[maxRow][localMax] = false;
			zone[localMax][maxRow] = false;
			int deleteRows = (maxRow == maxY) ? maxX : maxY;
			for (int g = 0; g < countAttribute; g++) {
					zone[g][deleteRows] = false;
					zone[deleteRows][g] = false;
			}
			maxX = maxRow; maxY = localMax;
			bool confirmLocal = true;
			for (int g = 0; g < countAttribute; g++) {
				for (int k = 0; k < countAttribute; k++) {
					if (zone[g][k]) {
						confirmLocal = false;
					}
				}
			}
			if (confirmLocal) break;
		}
	}
	std::vector<std::vector<int>> grafClear(countAttribute, std::vector<int>());
	for (int g = 0; g < countAttribute; g++) {
		int len = graf[g].size();
		for (int k = 0; k < len; k++) {
			if (mat[g][graf[g][k]] > 0.75) {
				grafClear[g].push_back(graf[g][k]);
			}
		}
	}

	std::cout << std::endl << std::endl << std::endl;
	for (int g = 0; g < countAttribute; g++) {
		int len = grafClear[g].size();
		for (int k = 0; k < len; k++) {
				std::cout << (g + 1) << "-(" << mat[g][grafClear[g][k]] << ")-" << (grafClear[g][k] + 1) << std::endl;
		}
	}
	return grafClear;
}

std::vector<std::vector<float>> CountAttribute::set(std::string patch)
{
	std::vector<std::vector<float>> massPtr;
    std::ifstream in(patch.c_str());
    if (!in.is_open()) {
        throw "Error";
    }
	std::string line;
	while (std::getline(in, line)) {
        std::stringstream lineS(line);
		std::vector<float> lineMass;
		int elem;
        while(lineS >> elem) {
			lineMass.push_back(elem);
        }
		massPtr.push_back(lineMass);
    }
	return massPtr;
}

void CountAttribute::printData()
{


}
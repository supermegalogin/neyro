#ifndef COUNTATTRIBUTE_H
#define COUNTATTRIBUTE_H
#include <string>
#include <vector>

class CountAttribute
{
public:
	std::vector<std::vector<float>> A;
	std::vector<std::vector<float>> B;
	std::vector<std::vector<float>> C;
	std::vector<std::vector<float>> notC;
	std::vector<std::vector<float>> Clm, Cl, Clnot, Alm, Al, Blm, Bl;
    int round = 0;
    int maxI1 = 0, maxI2 = 0;
    int maxIs1 = 0, maxIs2 = 0;
    CountAttribute();
	int getClass(std::vector<float> Obj);
	std::vector<std::vector<float>> set(std::string patch);
	std::vector<std::vector<int>> generateGraf(std::vector<std::vector<float>>);
	std::vector<float> counåInformativeness(std::vector<std::vector<float>> &A, std::vector<std::vector<float>> &notA);
	std::vector<int> countNeighbour(float x, float y, std::vector<std::vector<float>>& C, std::vector<std::vector<float>>& notC, int I1, int I2);
	bool countDiscret(float x, float y, std::vector<std::vector<float>>& C, std::vector<std::vector<float>>& notC, int I1, int I2);
    void printData();
};

#endif // COUNTATTRIBUTE_H

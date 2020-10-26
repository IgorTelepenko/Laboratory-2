#include <iostream>

using namespace std;

float vectorMult(float x1, float y1, float x2, float y2); //векторний добуток потрібний для перевірки перетину 2х відрізків
bool segmentCross(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4); //перевірка перетину 2х відрізків

int main()
{
	int numberOfPoints;
	cout << "enter the number of points: " << endl;
	cin >> numberOfPoints;

	float* Xcoordinates = new float[numberOfPoints+1]; 
	float* Ycoordinates = new float[numberOfPoints+1];
	/* 
	розміри масивів координат на 1 більші від кількості точок, 
	щоб можна було продублювати координати першої точки в останню (додаткову комірку),
	так ми зможемо перевіряти останнє ребро, як починається в останній точці і закінчується в першій
	*/
	cout << "enter the coordinates of each point - X and Y of each point: " << endl;
	for (int i = 0;i < numberOfPoints;i++) //вводимо з клавіатури координати точок по черзі
	{
		cin >> Xcoordinates[i];
		cin >> Ycoordinates[i];
	}

	
	bool ifCross = false;
	//дублюємо координати першої точки в останню (додаткову комірку):
	Xcoordinates[numberOfPoints] = Xcoordinates[0];
	Ycoordinates[numberOfPoints] = Ycoordinates[0];
	//(для того, щоб можна було перевіряти останнє ребро, яке починається в очтанній заданій точці і закінчується в першій)

	for (int i = 1;i < numberOfPoints-2;i++) //будемо брати точку з номером "і" та перевіряти ребро, що починається в попередній точці та закінчується в цій
	{
		for (int j = i + 2;j < numberOfPoints+1;j++) //обране ребро будемо порівнювати з усіма іншими ребрами, ігноруючи попередні (так як вони вже були перевірені як "і"; також перше наступне ребро не беремо - воно не може перетинатись з обраним)
		{	//перевіряємо чи перетинаються ребра:
			if (segmentCross(Xcoordinates[i - 1], Ycoordinates[i - 1], Xcoordinates[i], Ycoordinates[i], Xcoordinates[j - 1], Ycoordinates[j - 1], Xcoordinates[j], Ycoordinates[j]) == true)
			{
				ifCross = true; //знаходимо, що ребра перетинаються
				break;
			}
		}
		if (ifCross)
			break;
	}

	if (ifCross == true)
		cout << " there are edges crossing ";
	else cout << "there are no edges crossing";

}



float vectorMult(float x1, float y1, float x2, float y2)
{
	float res;

	res = x1 * y2 - y1 * x2; //векторний добуток двох відрізків за координатами
	return res;
}


bool segmentCross(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	float vm1, vm2, vm3, vm4;
	
	vm1 = vectorMult(x4 - x3, y4 - y3, x1 - x3, y1 - y3);
	vm2 = vectorMult(x4 - x3, y4 - y3, x2 - x3, y2 - y3);
	vm3 = vectorMult(x2 - x1, y2 - y1, x3 - x1, y3 - y1);
	vm4 = vectorMult(x2 - x1, y2 - y1, x4 - x1, y4 - y1);

	/*
	умова перетину двох відрізків, якщо кінці вдрізка лежать по різних сторонах від іншого відрізка
	потрібно щоб векторний добуток відповідних векторів, утворених з кінців відрізків, vm1 і vm2 мали різний знак,
			тоді кінці одного відрізка лежать по різні сторони від другого:
	*/

	if (vm1 * vm2 < 0 && vm3 * vm4 < 0)
		return true;
	else return false;

}
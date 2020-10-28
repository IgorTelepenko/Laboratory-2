#include <iostream>

using namespace std;

//функція знаходить, з якої сторони точка від прямої, заданою координатами двох точок (повертає: 0 - точка на прямій, 1 - точка лежить праворуч, -1 - точка лежить ліворуч)
int whichSideThePointisFromtheLine(float x1_line, float y1_line, float x2_line, float y2_line, float x_point, float y_point);

//повертає true якщо точка не належить відрізку (кінці відрізка з координатами x1_line i x2_line)
bool IfPointNotBetween2Others(float x1_line, float x2_line, float x_point);


int main()
{
	int n;
	cout << "enter the number of points: ";
	cin >> n;

	float* Xcooordinates = new float[n];
	float* Ycooordinates = new float[n];

	cout << "enter the coordinates of each point: ";
	for (int i = 0;i < n;i++)
	{
		cin >> Xcooordinates[i] >> Ycooordinates[i];
	}

	float start_X, start_Y;
	int startInd;
	start_X = Xcooordinates[0];
	start_Y = Ycooordinates[0];
	startInd = 0;
	//шукаємо точку що знаходиться найлівіше, буде початковою точкою кінцевого опуклого багатокутника
	for (int i = 1;i < n;i++)
	{
		if (Xcooordinates[i] <= start_X && Ycooordinates[i] <= start_Y)
		{
			start_X = Xcooordinates[i];
			start_Y = Ycooordinates[i];
			startInd = i;
		}
	}
	   
	int chosen_point_index = startInd, numb_of_answerPoints = -1;
	
	int* answer_points_Ind = new int[n]; //буде масив точок, що утворюють кінцевий опуклий багатокутник
	do 
	{
		numb_of_answerPoints++; //збільшуємо к-сть визначених кінцевих точок на 1
		answer_points_Ind[numb_of_answerPoints] = chosen_point_index; //заносимо визначену точку багатокутника
		int whereOtherPoints;  //щоб перевіряти чи всі точки знаходяться з одного боку від прмою
		
		for (int i = 0;i < n;i++) //шукаємо точку (з індексом "і"), яка підійде бути наступною в нашому кінцевому опуклому багатокутнику 
		{
			whereOtherPoints = 0; //(0 - на прямій, 1 - праворуч, -1 - ліворуч)
			bool ifThisPointWillBeChosen = false; //чи рідходить оочка яка перевіряється (тут - з індексом "і")
			if (i != chosen_point_index && i != answer_points_Ind[numb_of_answerPoints-1]) //чи точка, яку ми беремо перевіряти, не є попередньо визначеною точкою або попередньою для попередньо визначеної
			{
				
				bool notOntheLine = true; //для перевірки, якщо точка належить прямій з двома попередніми визначеними очками, щоб вона лежала не між ними
				if(numb_of_answerPoints > 0) //коли у нас є 2+ вже визначених точки
				if (whichSideThePointisFromtheLine(Xcooordinates[answer_points_Ind[numb_of_answerPoints - 1]], Ycooordinates[answer_points_Ind[numb_of_answerPoints - 1]], Xcooordinates[chosen_point_index], Ycooordinates[chosen_point_index], Xcooordinates[i], Ycooordinates[i]) == 0)
					notOntheLine = IfPointNotBetween2Others(Xcooordinates[answer_points_Ind[numb_of_answerPoints - 1]], Xcooordinates[chosen_point_index], Xcooordinates[i]); //якщо точка на прямій, має бути не в межах відрізка двух попередньо визначених точок
				if (notOntheLine)
				{
					
					for (int j = 0;j < n;j++) //для перевірки що всі точкм (тут - з індексами "j") лежать по одній стороні від прямої (що прох. через вибрану точку "і" та попередню вже визначену точку)
					{
						int which_side_temp = whichSideThePointisFromtheLine(Xcooordinates[chosen_point_index], Ycooordinates[chosen_point_index], Xcooordinates[i], Ycooordinates[i], Xcooordinates[j], Ycooordinates[j]);
						if (which_side_temp == whereOtherPoints || whereOtherPoints == 0 || which_side_temp == 0)
						{
							if (whereOtherPoints == 0) //1 раз спочатку, коли невідомо з якої сторони до прямої знах. всі інші точки
								whereOtherPoints = which_side_temp;//визначаємо сторону з якої повинні лежати точки
							ifThisPointWillBeChosen = true; //точка "j", яку ми підставляємо знаходиться з тієї ж сторони що й інші

						}
						else
						{
							ifThisPointWillBeChosen = false;//якась точка лежить по іншу сторону, тому наш варіант прямої не може бути (потрібно брати інший "і")
							break;

						}
					}

					if (ifThisPointWillBeChosen == true)
					{
						chosen_point_index = i; //"і" - наступна визначена точка для кінцевого опуклого багатокутника
						break;
					}
				}
			}
		}
	} while (chosen_point_index != startInd); //допоки не завершиться круг та остання визначена точка не стану першою

	cout << "the result: ";
	for (int i = 0;i <= numb_of_answerPoints;i++)
	{
		cout << "(" << Xcooordinates[answer_points_Ind[i]] << ";" << Ycooordinates[answer_points_Ind[i]] << ") ";
	}

	

	return 0;
}

int whichSideThePointisFromtheLine(float x1_line, float y1_line, float x2_line, float y2_line, float x_point, float y_point)
{	//маємо координати двох точок, які задають пряму а також координати точки, для якої треба визначити з якої сторони від прямої вона знаходиться
	float res;
	res = (x_point - x1_line) * (y2_line - y1_line) - (y_point - y1_line) * (x2_line - x1_line);

	if (res > 0) //точка зправа від прямої
		return 1;
	else
	{
		if (res < 0) //точка зліва від прямої
			return -1;
		else
		{
			return 0; // точка належить прямій
		}
	}
}

bool IfPointNotBetween2Others(float x1_line, float x2_line, float x_point)
{
	if ((x1_line > x_point && x2_line < x_point) || (x1_line < x_point && x2_line < x_point))
		return false; //точка, що належить прямій, знаходиться в межах відрізка з двох заданих точок
	else return true; //точка не належить відрізку
}
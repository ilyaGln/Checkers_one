#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

#define SIZE_Board 8 //размер шашечных полей
#define Black 4 //чёрная шашка
#define White -4 //белая шашка
#define Black_dam 5 //чёрная шашка
#define White_dam -5 //белая шашка

//структура для записи позиций
struct poz
{
	int x, y;
}oldPoz, regeleAlb, regeleNegru;

int  size = 100, move = 0, x, y;
//Расположение шашек на доске, -4=белые, 4=чёрные
int board[8][8] =
{ 0, 4, 0, 4, 0, 4, 0, 4,
  4, 0, 4, 0, 4, 0, 4, 0,
  0, 4, 0, 4, 0, 4, 0, 4,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
 -4, 0,-4, 0, -4,0,-4, 0,
  0,-4, 0,-4, 0,-4, 0,-4,
 -4, 0,-4, 0,-4, 0,-4, 0, };

int turnAlbDreapta = 0;
int  moveWB= 0; // 0 белые, 1 чёрные
int sahAlb = 0, sahNegru = 0;

//Белая шашка, по сути практически дамка
int White_A(int ox, int oy, int nx, int ny)
{
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

//Чёрная шашка, по сути практически дамка
int Black_N(int ox, int oy, int nx, int ny)
{
	int j = ox - 1;

	j = ox - 1;
	for (int i = oy + 1; i <= 7; i++)
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy + 1; i <= 7; i++)
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int NebunASah(int ox, int oy, int regex, int regey)
{
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] >= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] >= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int NebunNSah(int ox, int oy, int regex, int regey)
{
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] <= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] <= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int RegeNegruSahCheck(int posRegex, int posRegey)
{
	int ok = 0;
	for (int i = 0; i < SIZE_Board; i++)
	{
		for (int j = 0; j < SIZE_Board; j++)
		{
			if (board[i][j] < 0)
			{
				if (board[i][j] == White)
				{
					ok = NebunASah(j, i, posRegex, posRegey);
				}
				if (ok == 1)
				{
					return 0;
				}
			}
		}
	}
	return 1;
}

void pozRegeAlb()
{
	for (int i = 0; i < SIZE_Board; i++)
	{
		for (int j = 0; j < SIZE_Board; j++)
		{
			if (board[i][j] == 6)
			{
				regeleAlb.x = j;
				regeleAlb.y = i;
				break;
			}
		}
	}
}

void pozRegeNegru()
{
	for (int i = 0; i < SIZE_Board; i++)
	{
		for (int j = 0; j < SIZE_Board; j++)
		{
			if (board[i][j] == 6)
			{
				regeleNegru.y = i;
				regeleNegru.x = j;
				break;
			}
		}
	}
}

int main()
{
	RenderWindow window(VideoMode(800, 800), L"Шашки", sf::Style::Close | sf::Style::Titlebar);//Размер,название,запрет возможности изменять размер окна
	
	//Иконка окна
	Image icon;
	if (!icon.loadFromFile("images/icon.png"))
	{
		return 1;
	}
	window.setIcon(512, 512, icon.getPixelsPtr());

	Texture t1, t2, t3, t4, t5;
	t1.loadFromFile("images/Board.png");//Доска(поля)
	t2.loadFromFile("images/Black_1.png");//Чёрная шашка
	t3.loadFromFile("images/White_3.png");//Белая шашка
	t4.loadFromFile("images/Black_damka.png");//Чёрная шашка
	t5.loadFromFile("images/White_damka_bl.png");//Белая шашка

	//Геометрические фигуры с нанесенной поверх нее текстурой
	Sprite Board_spr(t1);//спрайт доски
	Sprite Black_p_spr(t2);//спрайт чёрной шашки
	Sprite White_p_spr(t3);//спрайт белой шашки
	Sprite Black_damka_spr(t4);//спрайт чёрной дамки
	Sprite White_damka_spr(t5);//спрайт белой дамки
	Sprite Mutare;

	float dx = 0, dy = 0;
	int num_h = 0;

	while (window.isOpen())
	{
		//Запись координат мыши в окне по x и y
		Vector2i pos = Mouse::getPosition(window);
		x = pos.x / size;
		y = pos.y / size;
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}
			window.clear();
			if (e.type == Event::MouseButtonPressed)
			{
				if (e.key.code == Mouse::Left)
				{

					if (board[y][x] != 0)
					{
						dx = pos.x - x * 100;
						dy = pos.y - y * 100;
						if (board[y][x] == Black && moveWB == 1)
						{
							num_h = Black;
							Mutare = Black_p_spr;
							board[y][x] = 0;
						}
						if (board[y][x] == White && moveWB == 0)
						{
							num_h = White;
							Mutare = White_p_spr;
							board[y][x] = 0;
						}
						if (board[y][x] == 0)
						{
							move = 1;
							oldPoz.x = x;
							oldPoz.y = y;
						}
					}
				}
			}
			if (e.type == Event::MouseButtonReleased)
			{
				if (e.key.code == Mouse::Left)
				{
					int ok = 2;

					if (num_h == White && move == 1)
					{
						ok = White_A(oldPoz.x, oldPoz.y, x, y);
					}
					if (num_h == Black && move == 1)
					{
						ok = Black_N(oldPoz.x, oldPoz.y, x, y);
					}

					if (ok == 1)
					{
						int nr = board[y][x];
						board[y][x] = num_h;
						if (moveWB == 0)
						{
							if (sahAlb == 1)
							{
								pozRegeAlb();
								sahAlb = 0;
								pozRegeNegru();
								int sah = RegeNegruSahCheck(regeleNegru.x, regeleNegru.y);
								if (sah == 0)
								{
									sahNegru = 1;
								}
								moveWB = 1;
							}
							else
							{
								pozRegeAlb();
								pozRegeNegru();
								int sah = RegeNegruSahCheck(regeleNegru.x, regeleNegru.y);
								if (sah == 0)
								{
									sahNegru = 1;
								}
								moveWB = 1;

							}
						}
						else
						{
							if (sahNegru == 1)
							{
								pozRegeNegru();
								int s = RegeNegruSahCheck(regeleNegru.x, regeleNegru.y);
								if (s == 0)
								{
									board[oldPoz.y][oldPoz.x] = num_h;
									board[y][x] = nr;
								}
								else
								{
									sahNegru = 0;
									moveWB = 0;
								}
							}
							else
							{
								pozRegeNegru();
								int sa = RegeNegruSahCheck(regeleNegru.x, regeleNegru.y);
								if (sa == 0)
								{
									board[oldPoz.y][oldPoz.x] = num_h;
									board[y][x] = nr;
								}
								else
								{
									moveWB = 0;
								}
							}
						}
					}
					else if (ok == 0)
					{
						board[oldPoz.y][oldPoz.x] = num_h;
					}
					move = 0;
				}
			}
		}
		
		window.clear();//очистка окна
		window.draw(Board_spr);//рисуем доску
		if (move == 1)
		{
			Mutare.setPosition(pos.x - dx, pos.y - dy);
			window.draw(Mutare);
		}
		for (int i = 0; i < SIZE_Board; i++)
		{
			for (int j = 0; j < SIZE_Board; j++)
			{

				if (board[i][j] != 0)
				{
					if (board[i][j] == Black)
					{
						Black_p_spr.setPosition(j * size, i * size);
						window.draw(Black_p_spr);
					}
					if (board[i][j] == White)
					{
						White_p_spr.setPosition(j * size, i * size);
						window.draw(White_p_spr);
					}
				}
			}
		}
		window.display();
	}
	return 0;
}
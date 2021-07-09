#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

#define Size_board 8// Размер поля 8*8
#define Black_dam 4 //Дамка чёрная
#define White_dam -4 //Дамка белая
#define Black_pawn 6 //Пешка чёрная
#define White_pawn -6 //Пешка белая

struct poz
{
	int x, y;
}oldPoz;

int  size = 100, move = 0, x, y;
int regeAlb = 0, regeNegru = 0, flag = 0; // flag - 0 белые, 1 чёрные
int pawn_hit, pawn_w, pawn_b, help_p;
int counter_wh = 0, counter_bl = 0;

//Массив расположения фигур на доске
int board[8][8] =
{ 0, 6, 0, 6, 0, 6, 0, 6,
  6, 0, 6, 0, 6, 0, 6, 0,
  0, 6, 0, 6, 0, 6, 0, 6,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
 -6, 0,-6, 0,-4, 0,-6, 0,
  0,-6, 0,-6, 0,-6, 0,-6,
 -6, 0,-6, 0,-6, 0,-6, 0, };

//Белая дамка
int White_dam_move(int ox, int oy, int nx, int ny)
{
	//Левый верхний
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] >= 0 && (ny >= i-1 && nx >= j-1)) {
			board[i][j] = 0;
			return 1;
		}
		else if (board[i][j] != 0) break;
		j--;
	}

	// Правый верхний
	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] >= 0 && (ny >= i + 1 && nx >= j - 1)) {
			board[i][j] = 0;
			return 1;
		}
		else if (board[i][j] != 0) break;
		j++;
	}

	// Левый нижний
	j = ox - 1;
	for (int i = oy + 1; i <= 7; i++)
	{
		if (board[i][j] >= 0 && (ny >= i && nx >= j)) { 
			board[i][j] = 0;
			return 1; 
		}

		else if (board[i][j] != 0) break;
		j--;
	}

	// Правый нижний
	j = ox + 1;
	for (int i = oy + 1; i <= 7; i++)
	{
		if (board[i][j] >= 0 && (ny == i && nx == j)) {
			board[i][j] = 0;
			return 1; 
		}
		else if (board[i][j] != 0) break;
		j++;
	}
	return 0;
}

//Чёрная дамка
int Black_dam_move(int ox, int oy, int nx, int ny)
{
	//Левый верхний
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] <= 0 && (ny == i && nx == j)) return 1;
		else if (board[i][j] != 0) break;
		j--;
	}

	// Правый верхний
	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if (board[i][j] <= 0 && (ny == i && nx == j)) return 1;
		else if (board[i][j] != 0) break;
		j++;
	}

	// Левый нижний
	j = ox - 1;
	for (int i = oy + 1; i <= 7; i++)
	{
		if (board[i][j] <= 0 && (ny == i && nx == j)) return 1;
		else if (board[i][j] != 0) break;
		j--;
	}

	// Правый нижний
	j = ox + 1;
	for (int i = oy + 1; i <= 7; i++)
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))  return 1;
		else if (board[i][j] != 0) break;
		j++;
	}
	return 0;
}

//Битьё шашки
int Hit_the_checker(int ox, int oy, int nx, int ny, int check) {
	
	//Чёрная ищем белую шашку
	if (check == 0) {
		pawn_w = -4;
		pawn_b = 10;//откат флага
	}
	else {//Белая, ищем чёрную шашку
		pawn_w = -10;
		pawn_b = 4;//откат флага
	}
	
	//Битьё шашки влево вниз
	if (oy + 1 >= 0 && ox - 1 < Size_board && nx == ox - 2 &&
		ny == oy + 2 && (board[oy + 1][ox - 1] <= pawn_w ||
			board[oy + 1][ox - 1] >= pawn_b) && board[oy + 2][ox - 2] == 0) {
	
		board[oy + 1][ox - 1] = 0;
		/*
		if ((oy-1 >= 0 && ox-1>=0 && oy-1 board[oy-1][ox-1]>=4 && board[oy - 2][ox - 2] == 0 &&) {


		}
		*/
		return 1;
	}

	//Битьё шашки вправо вниз
	if (oy + 1 >= 0 && ox + 1 < Size_board && nx == ox + 2 &&
		ny == oy + 2 && (board[oy + 1][ox + 1] <= pawn_w ||
			board[oy + 1][ox + 1] >= pawn_b) && board[oy + 2][ox + 2] == 0) {

		board[oy + 1][ox + 1] = 0;
		return 1;
	}

	//Битьё шашки вправо вверх
	if (oy - 1 >= 0 && ox + 1 < Size_board && nx == ox + 2 &&
		ny == oy - 2 && (board[oy - 1][ox + 1] <= pawn_w ||
			board[oy - 1][ox + 1] >= pawn_b) && board[oy - 2][ox + 2] == 0) {

		board[oy - 1][ox + 1] = 0;
		return 1;
	}

	//Битьё шашки влево вверх
	if (oy - 1 >= 0 && ox - 1 < Size_board && nx == ox - 2 &&
		ny == oy - 2  && (board[oy - 1][ox - 1] <= pawn_w ||
			board[oy - 1][ox - 1] >= pawn_b) && board[oy - 2][ox - 2] == 0) {

		board[oy - 1][ox - 1] = 0;
		return 1;
	}
	return 0;

}

//Чёрные шашки(как ходят)
int Black_pawn_m(int ox, int oy, int nx, int ny)
{
	//Битьё шашки
	pawn_hit = 0;
	if (Hit_the_checker(ox, oy, nx, ny, pawn_hit) == 1) {
		return 1;
	}
	else {
		// Нижний правый(ход)
		if (ox + 1 < Size_board && oy + 1 < Size_board &&
			ny == oy + 1 && nx == ox + 1 && board[ny][nx] == 0) return 1;

		// Нижний левый(ход)
		if (ox - 1 >= 0 && oy + 1 < Size_board &&
			nx == ox - 1 && ny == oy + 1 && board[ny][nx] == 0) return 1;
	}

	return 0;
}

//Белые шашки(как ходят)
int White_pawn_m(int ox, int oy, int nx, int ny)
{

	//Битьё шашки
	pawn_hit = 1;
	
	if (Hit_the_checker(ox, oy, nx, ny, pawn_hit) == 1) {
	
		return 1;
	}
	else {
		// Верхний левый (ход)
		if (ox - 1 >= 0 && oy - 1 >= 0 && ny == oy - 1 &&
			nx == ox - 1 && board[ny][nx] == 0) return 1;

		// Верхний правый(ход)
		if (oy - 1 >= 0 && ox + 1 < Size_board && nx == ox + 1 &&
			ny == oy - 1 && board[ny][nx] == 0) return 1;

		return 0;
	}
}
int oldFlag = 0;
int main()
{
	RenderWindow window(VideoMode(800, 800),
		L"Шашки", sf::Style::Close | sf::Style::Titlebar);

	//Иконка окна
	Image icon;
	if (!icon.loadFromFile("images/icon.png")) return 1;
	window.setIcon(512, 512, icon.getPixelsPtr());

	Texture t1, t2, t3, t4, t5;

	//Добавления изображения(доска, шашки)
	t1.loadFromFile("images/board.png");
	t2.loadFromFile("images/Black_damka.png");
	t3.loadFromFile("images/White_damka_bl.png");
	t4.loadFromFile("images/Black_1.png");
	t5.loadFromFile("images/White_1.png");

	Sprite tabla(t1);// спрайт доски
	Sprite Black_dam_spr(t2);// Спрайт чёрной дамки
	Sprite White_dam_spr(t3);//Спрайт белой дамки
	Sprite Black_pawn_spr(t4);//Спрайт чёрной пешки
	Sprite White_pawn_spr(t5);//Спрайт белой пешки
	Sprite Flag;

	float dx = 0, dy = 0;
	int num_figure = 0;

	while (window.isOpen())
	{
		Vector2i pos = Mouse::getPosition(window);
		x = pos.x / size;
		y = pos.y / size;

		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed) window.close();

			window.clear();
			if (e.type == Event::MouseButtonPressed)
			{
				if (e.key.code == Mouse::Left)
				{
					if (board[y][x] != 0)
					{
						dx = pos.x - x * 100;
						dy = pos.y - y * 100;

						//Чёрная дамка
						if (board[y][x] == Black_dam && flag == 1)
						{
							num_figure = Black_dam;
							Flag = Black_dam_spr;
							board[y][x] = 0;
						}
						//Белая дамка
						if (board[y][x] == White_dam && flag == 0)
						{
							num_figure = White_dam;
							Flag = White_dam_spr;
							board[y][x] = 0;
						}
						//Чёрная шашка
						if (board[y][x] == Black_pawn && flag == 1)
						{
							num_figure = Black_pawn;
							Flag = Black_pawn_spr;
							board[y][x] = 0;

						}
						//Чёрная шашка
						if (board[y][x] == White_pawn && flag == 0)
						{
							num_figure = White_pawn;
							Flag = White_pawn_spr;
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
				if (e.key.code == Mouse::Left)//обработка события - нажатие ЛКМ 
				{
					int ok = 2;
					if (num_figure == White_dam && move == 1)
					{
						ok = White_dam_move(oldPoz.x, oldPoz.y, x, y);
					}
					if (num_figure == Black_dam && move == 1)
					{
						ok = Black_dam_move(oldPoz.x, oldPoz.y, x, y);
					}
					if (num_figure == Black_pawn && move == 1)
					{
						ok = Black_pawn_m(oldPoz.x, oldPoz.y, x, y);
						if (ok == 1 && regeNegru == 0) regeNegru = 1;
					}
					if (num_figure == White_pawn && move == 1)
					{
						ok = White_pawn_m(oldPoz.x, oldPoz.y, x, y);
						if (ok == 1 && regeAlb == 0) regeAlb = 1;
					}
					if (ok == 1)
					{
						//Если пешки дойдут до конца поля они превращаются в дамки
						board[y][x] = num_figure;
						if (y == 0 && num_figure == White_pawn) board[y][x] = White_dam;
						if (y == 7 && num_figure == Black_pawn) board[y][x] = Black_dam;

					
						/*if (board[y + 1][x - 1] == 0 || board[y + 1][x + 1] == 0 || board[y - 1][x - 1] == 0 || board[y - 1][x + 1] == 0)
						{
							//White_pawn_m(oldPoz.x, oldPoz.y, x, y);
							if (flag == 0) flag = 1;
							else flag = 0;
						}*/
						//y + 2 < Size_board && x - 2 >= 0 || y + 2 < Size_board && x + 2 < Size_board || y - 2 >= 0 && x - 2 >= 0 || y - 2 >= 0 && x + 2 < Size_board
						/*if (flag = 1) {
							if (y + 2 < Size_board && x - 2 >= 0 || y + 2 < Size_board && x + 2 < Size_board || y - 2 >= 0 && x - 2 >= 0 || y - 2 >= 0 && x + 2 < Size_board) {
								if (board[y + 1][x - 1] <= -4 && board[y + 2][x - 2] == 0 ||
									board[y + 1][x + 1] <= -4 && board[y + 2][x + 2] == 0 ||
									board[y - 1][x - 1] <= -4 && board[y - 2][x - 2] == 0 ||
									board[y - 1][x + 1] <= -4 && board[y - 2][x + 2] == 0)
								{
									flag = 1;
								}
							}
							else flag = 0;
						}
						if (flag = 0) {
							if (y + 2 < Size_board && x - 2 >= 0 || y + 2 < Size_board && x + 2 < Size_board || y - 2 >= 0 && x - 2 >= 0 || y - 2 >= 0 && x + 2 < Size_board) {
								if (board[y + 1][x - 1] >= 4 && board[y + 2][x - 2] == 0 ||
									board[y + 1][x + 1] >= 4 && board[y + 2][x + 2] == 0 ||
									board[y - 1][x - 1] >= 4 && board[y - 2][x - 2] == 0 ||
									board[y - 1][x + 1] >= 4 && board[y - 2][x + 2] == 0)
								{
									flag = 0;
								}
							}
							else flag = 1;


						}
						*/
						/*
						if (board[y + 1][x - 1] >= 4 && board[y + 2][x - 2] == 0 ||
							board[y + 1][x + 1] >= 4 && board[y + 2][x + 2] == 0 ||
							board[y - 1][x - 1] >= 4 && board[y - 2][x - 2] == 0 ||
							board[y - 1][x + 1] >= 4 && board[y - 2][x + 2] == 0)
						{
							flag = 0;
						}
						*/
						//Условный оператор для перехода хода
						/*
						if ((board[y + 1][x - 1] >= 4 || board[y - 1][x - 1] >= 4 ||
							board[y + 1][x + 1] >= 4 || board[y + 1][x + 1] >= 4)&&
							((board[y + 2][x + 2] == 0) || (board[y - 2][x + 2] == 0)||
								(board[y - 2][x - 2] == 0)|| (board[y + 2][x - 2] == 0)))
						{
							flag = 0;
						}*/
						


						if (flag == 0) { oldFlag = 0; flag = 1; }
						else { oldFlag = 1; flag = 0; }
						/*
						if (x > 1 && x<6) {
							if ((board[y + 1][x - 1] >= 4 && board[y + 2][x - 2] == 0) ||
								(board[y + 1][x + 1] >= 4 && board[y + 2][x + 2] == 0) ||
								(board[y - 1][x - 1] >= 4 && board[y - 2][x - 2] == 0) ||
								(board[y - 1][x + 1] >= 4 && board[y - 2][x + 2] == 0))
							{
								flag = 0;
							}
						}
						else if (oldFlag==1 && flag==0 && x == 1 && board[y-1][x+1]>=4 && board[y - 2][x + 2] == 0) {
							if ((board[y + 1][x - 1] >= 4 && board[y + 2][x - 2] == 0) ||
								(board[y + 1][x + 1] >= 4 && board[y + 2][x + 2] == 0) ||
								(board[y - 1][x - 1] >= 4 && board[y - 2][x - 2] == 0) ||
								(board[y - 1][x + 1] >= 4 && board[y - 2][x + 2] == 0))
							{
								flag = 0;
							}
						}
						else if (oldFlag == 0 && board[y - 1][x + 1] >= 4 && board[y - 2][x + 2] == 0) {
							if ((board[y + 1][x - 1] >= 4 && board[y + 2][x - 2] == 0) ||
								(board[y + 1][x + 1] >= 4 && board[y + 2][x + 2] == 0) ||
								(board[y - 1][x - 1] >= 4 && board[y - 2][x - 2] == 0) ||
								(board[y - 1][x + 1] >= 4 && board[y - 2][x + 2] == 0))
							{
								flag = 0;
							}
						}


						//////////////////////////////////////

							if (((board[y + 1][x - 1] >= 4) && (board[y + 2][x - 2] == 0)) ||
								((board[y + 1][x + 1] >= 4 && board[y + 2][x + 2] == 0))||
								((board[y - 1][x - 1] >= 4 && board[y - 2][x - 2] == 0))||
								((board[y - 1][x + 1] >= 4 && board[y - 2][x + 2] == 0)))
							{
								flag = 0;
							}
						*/
						
						if (x > 1 && x < 6) {
							if ((board[y + 1][x - 1] >= 4 && board[y + 2][x - 2] == 0) ||
								(board[y + 1][x + 1] >= 4 && board[y + 2][x + 2] == 0) ||
								(board[y - 1][x - 1] >= 4 && board[y - 2][x - 2] == 0) ||
								(board[y - 1][x + 1] >= 4 && board[y - 2][x + 2] == 0))
							{
								flag = 0;
							}
						}
						else if (oldFlag == 1 && flag == 0 && x == 1 && board[y - 1][x + 1] >= 4 && board[y - 2][x + 2] == 0) {
							if ((board[y + 1][x - 1] >= 4 && board[y + 2][x - 2] == 0) ||
								(board[y + 1][x + 1] >= 4 && board[y + 2][x + 2] == 0) ||
								(board[y - 1][x - 1] >= 4 && board[y - 2][x - 2] == 0) ||
								(board[y - 1][x + 1] >= 4 && board[y - 2][x + 2] == 0))
							{
								flag = 0;
							}
						}/*
						else if (oldFlag == 0 && board[y - 1][x + 1] >= 4 && board[y - 2][x + 2] == 0) {
							if ((board[y + 1][x - 1] >= 4 && board[y + 2][x - 2] == 0) ||
								(board[y + 1][x + 1] >= 4 && board[y + 2][x + 2] == 0) ||
								(board[y - 1][x - 1] >= 4 && board[y - 2][x - 2] == 0) ||
								(board[y - 1][x + 1] >= 4 && board[y - 2][x + 2] == 0))
							{
								flag = 0;
							}
						}*/


						/*
						if (x > 1 && x < 6) {
							if ((board[y + 1][x - 1] <= -4 && board[y + 2][x - 2] == 0) ||
								(board[y + 1][x + 1] <= -4 && board[y + 2][x + 2] == 0) ||
								(board[y - 1][x - 1] <= -4 && board[y - 2][x - 2] == 0) ||
								(board[y - 1][x + 1] <= -4 && board[y - 2][x + 2] == 0))
							{
								flag = 0;
							}
						}
						else if (oldFlag == 1 && flag == 0 && x == 1 && board[y - 1][x + 1] >= 4 && board[y - 2][x + 2] == 0) {
							if ((board[y + 1][x - 1] >= 4 && board[y + 2][x - 2] == 0) ||
								(board[y + 1][x + 1] >= 4 && board[y + 2][x + 2] == 0) ||
								(board[y - 1][x - 1] >= 4 && board[y - 2][x - 2] == 0) ||
								(board[y - 1][x + 1] >= 4 && board[y - 2][x + 2] == 0))
							{
								flag = 0;
							}
						}
						else if (oldFlag == 0 && board[y - 1][x + 1] >= 4 && board[y - 2][x + 2] == 0) {
							if ((board[y + 1][x - 1] >= 4 && board[y + 2][x - 2] == 0) ||
								(board[y + 1][x + 1] >= 4 && board[y + 2][x + 2] == 0) ||
								(board[y - 1][x - 1] >= 4 && board[y - 2][x - 2] == 0) ||
								(board[y - 1][x + 1] >= 4 && board[y - 2][x + 2] == 0))
							{
								flag = 0;
							}
						}*/

						


						
					}
					else if (ok == 0)
					{
						board[oldPoz.y][oldPoz.x] = num_figure;
					}
					move = 0;
				}
			}
		}

		window.clear();//очистка
		window.draw(tabla);//добаялем доску

		if (move == 1)
		{
			Flag.setPosition(pos.x - dx, pos.y - dy);
			window.draw(Flag);
		}
		//Добавляем шашки на доску 
		for (int i = 0; i < Size_board; i++)
		{
			for (int j = 0; j < Size_board; j++)
			{
				
				if (board[i][j] != 0)
				{
					//Добавляем чёрную дамку
					if (board[i][j] == Black_dam)
					{
						Black_dam_spr.setPosition(j * size, i * size);
						window.draw(Black_dam_spr);
					}
					//Добавляем белую дамку
					if (board[i][j] == White_dam)
					{
						White_dam_spr.setPosition(j * size, i * size);
						window.draw(White_dam_spr);
					}
					//Добавляем чёрную пешку
					if (board[i][j] == Black_pawn)
					{
						Black_pawn_spr.setPosition(j * size, i * size);
						window.draw(Black_pawn_spr);
					}
					//Добавляем белую пешку
					if (board[i][j] == White_pawn)
					{
						White_pawn_spr.setPosition(j* size, i* size);
						window.draw(White_pawn_spr);							
					}
				}
			}
		}
			
		window.display();
	}
	
	return 0;
}
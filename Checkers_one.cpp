#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>//использовал abs(модуль)
#include <sstream>
#include <conio.h>
#include <iomanip>
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
int count_w = 12, count_b = 12;//счётчики шашек
int  size = 75, move = 0, x, y;//размер поля, флаг передвижения, координаты
int flag = 0; // flag - 0 белые, 1 чёрные
int pawn_hit, pawn_w, pawn_b, help_p;
int move_bl_wh=0;

int size_window = 600;
//Массив расположения фигур на доске

int board[8][8] =
{ 0, 6, 0, 6, 0, 6, 0, 6,
  6, 0, 6, 0, 6, 0, 6, 0,
  0, 6, 0, 6, 0, 6, 0, 6,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
 -6, 0,-6, 0,-6, 0,-6, 0,
  0,-6, 0,-6, 0,-6, 0,-6,
 -6, 0,-6, 0,-6, 0,-6, 0, };
 

void Check_the_hit(int check) {
	if (check == 1) {
		count_b -= 1;
		std::cout << "Black = " << count_b << std::endl;
	}
	else {
		count_w -= 1;
		std::cout << "White = " << count_w << std::endl;
	}

	if (count_b == 0) { 
		std::cout << "White won!"; 
		move_bl_wh = 1;
	}
	else if(count_w==1) std::cout << "Black won!";
}

/*
 //Массив расположения фигур на доске
int board[8][8] =
{ 0, 6, 0, 0, 0, 0, 0, 0,
  0, 0, 6, 0, 0, 0, -6, 0,
  0, 0, 0, 0, 0, 0, 0, -6,
  0, 0, 6, 0, 0, 0, -6, 0,
  0, 0, 0, 6, 0, 6, 0, 0,
  0, 0, 0, 0,-6, 0, 0, 0,
  0, 0, 0, 0, 0,-6, 0, 0,
  0, 0, 0, 0,-6, 0,-6, 0, };
  */


int Hit_the_dam(int ox, int oy, int nx, int ny, int check) {

	//Чёрная ищем белую шашку
	if (check == 0) {
		pawn_w = -10;
		pawn_b = 4;//откат флага
		
	}
	else {//Белая, ищем чёрную шашку
		pawn_w = -4;
		pawn_b = 10;//откат флага
	}
	
	//Левый верхний
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if ((board[oy - 1][ox - 1] <= pawn_w || board[oy - 1][ox - 1] >= pawn_b) && (ny == i && nx == j)) { board[i][j] = 0; return 1; }
		else if (board[i][j] != 0) break;
		j--;
	}

	// Правый верхний
	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--)
	{
		if ((board[oy + 1][ox - 1] <= pawn_w || board[oy + 1][ox - 1] >= pawn_b) && (ny == i - 1 && nx == j + 1)) { board[i][j] = 0; return 1; }
		else if (board[i][j] != 0) break;
		j++;
	}
	// Левый нижний
	j = ox - 1;
	for (int i = oy + 1; i <= 7; i++)
	{
		if ((board[oy + 1][ox - 1] <= pawn_w || board[oy + 1][ox - 1] >= pawn_b) && (ny == i + 1 && nx == j - 1)) { board[i][j] = 0; return 1; }
		else if (board[i][j] != 0) break;
		j--;
	}
	// Правый нижний
	j = ox + 1;
	for (int i = oy + 1; i <= 7; i++)
	{
		if ((board[oy + 1][ox - 1] <= pawn_w || board[oy + 1][ox - 1] >= pawn_b) && ((ny == i + 1 && nx == j + 1) || (ny == i + 2 && nx == j + 2) || (ny == i + 3 && nx == j + 3))) { board[i][j] = 0; return 1; }
		else if (board[i][j] != 0) break;
		j++;
	}
	return 0;
}

//Белая дамка
int White_dam_move(int ox, int oy, int nx, int ny)
{
	//Битьё шашки
	pawn_hit = 0;
	if (Hit_the_dam(ox, oy, nx, ny, pawn_hit) == 1) {
		return 1;
	}
	else {
		//Левый верхний
		int j = ox - 1;
		for (int i = oy - 1; i >= 0; i--)
		{
			if (board[i][j] >= 0 && (ny == i && nx == j)) return 1;
			else if (board[i][j] != 0) break;
			j--;
		}
		// Правый верхний
		j = ox + 1;
		for (int i = oy - 1; i >= 0; i--)
		{
			if (board[i][j] >= 0 && (ny == i && nx == j)) return 1;
			else if (board[i][j] != 0) break;
			j++;
		}
		// Левый нижний
		j = ox - 1;
		for (int i = oy + 1; i <= 7; i++)
		{
			if (board[i][j] >= 0 && (ny == i && nx == j)) return 1;
			else if (board[i][j] != 0) break;
			j--;
		}
		// Правый нижний
		j = ox + 1;
		for (int i = oy + 1; i <= 7; i++)
		{
			if (board[i][j] >= 0 && (ny == i && nx == j)) return 1;
			else if (board[i][j] != 0) break;
			j++;
		}
		return 0;
	}
}

//Чёрная дамка
int Black_dam_move(int ox, int oy, int nx, int ny)
{
	pawn_hit = 1;
	if (Hit_the_dam(ox, oy, nx, ny, pawn_hit) == 1) {
		return 1;
	}
	else {

		//Левый верхний
		int j = ox - 1;
		for (int i = oy - 1; i >= 0; i--)
		{
			if (board[i][j] <= 0 && (ny == i && nx == j) ) return 1;
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
		
		Check_the_hit(check);

		board[oy + 1][ox - 1] = 0;
		return 1;
	}

	//Битьё шашки вправо вниз
	if (oy + 1 >= 0 && ox + 1 < Size_board && nx == ox + 2 &&
		ny == oy + 2 && (board[oy + 1][ox + 1] <= pawn_w ||
			board[oy + 1][ox + 1] >= pawn_b) && board[oy + 2][ox + 2] == 0) {
		Check_the_hit(check);
		board[oy + 1][ox + 1] = 0;
		return 1;
	}

	//Битьё шашки вправо вверх
	if (oy - 1 >= 0 && ox + 1 < Size_board && nx == ox + 2 &&
		ny == oy - 2 && (board[oy - 1][ox + 1] <= pawn_w ||
			board[oy - 1][ox + 1] >= pawn_b) && board[oy - 2][ox + 2] == 0) {
		Check_the_hit(check);
		board[oy - 1][ox + 1] = 0;
		return 1;
	}

	//Битьё шашки влево вверх
	if (oy - 1 >= 0 && ox - 1 < Size_board && nx == ox - 2 &&
		ny == oy - 2  && (board[oy - 1][ox - 1] <= pawn_w ||
			board[oy - 1][ox - 1] >= pawn_b) && board[oy - 2][ox - 2] == 0) {
		Check_the_hit(check);
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
	setlocale(LC_ALL, "Russian");

	//Выбор размера окна***************************************************************************************
	std::cout << "Выберите размер доски:\n1)600*600;\n2)675*675.\n3)800*800(Для больших экранов)\nРазмер:";
	int a = 0;
	std::cin >> a;
	if (a == 1) {
		size_window = 600; size = 75;
	}
	else if (a == 2) {
		size_window = 675; size = 85;
	}
	else { size_window = 800; size = 100; }
	RenderWindow window(VideoMode(size_window+335, size_window),//600*600 при size = 75, 800*800 при size = 100.
		L"Шашки");
	//*********************************************************************************************************
	//Иконка окна
	Image icon;
	if (!icon.loadFromFile("images/icon.png")) return 1;
	window.setIcon(512, 512, icon.getPixelsPtr());

	Texture t1, t2, t3, t4, t5, t6, t7, t8;
	
	Font font;
	font.loadFromFile("8277.ttf");//загрузка шрифта
	Text text_w("", font, 32), text_b("", font, 32);
	Text flag_win("", font, 32);

	//Цвет текта 
	text_w.setFillColor(Color::Black);
	text_b.setFillColor(Color::Black);
	flag_win.setFillColor(Color::Black);

	//Жирный текст
	text_w.setStyle(Text::Bold);
	text_b.setStyle(Text::Bold);
	flag_win.setStyle(Text::Bold);

	t6.loadFromFile("images/1234.png");//Таблица счёта
	if (a == 1) {
		//Добавления изображения(доска, шашки) при размере окна 600*600 папка images_75
		t1.loadFromFile("images_75/Board.png");
		t2.loadFromFile("images_75/Black_damka.png");
		t3.loadFromFile("images_75/White_damka_bl.png");
		t4.loadFromFile("images_75/Black_1.png");//anime edition - 2.png  //classic - Black_1.png // gopnik edition - 4.png
		t5.loadFromFile("images_75/White_1.png");//anime edition - 1.png  //classic - White_1.png // gopnik edition - 3.png
	}
	else if(a==2) {
		t1.loadFromFile("images_84/Board.png");
		t2.loadFromFile("images_84/Black_damka.png");
		t3.loadFromFile("images_84/White_damka_bl.png");
		t4.loadFromFile("images_84/Black_1.png");//anime edition - 2.png  //classic - Black_1.png // gopnik edition - 4.png
		t5.loadFromFile("images_84/White_1.png");//anime edition - 1.png  //classic - White_1.png // gopnik edition - 3.png
	}
	else {
		t1.loadFromFile("images/Board.png");
		t2.loadFromFile("images/Black_damka.png");
		t3.loadFromFile("images/White_damka_bl.png");
		t4.loadFromFile("images/Black_1.png");//anime edition - 2.png  //classic - Black_1.png // gopnik edition - 4.png
		t5.loadFromFile("images/White_1.png");//anime edition - 1.png  //classic - White_1.png // gopnik edition - 3.png
		
	}
	t7.loadFromFile("images/White_won.png");//anime edition - 1.png  //classic - White_1.png // gopnik edition - 3.png
	t8.loadFromFile("images/Black_won.png");//Таблица счёта



	Sprite tabla(t1);// спрайт доски
	Sprite Black_dam_spr(t2);// Спрайт чёрной дамки
	Sprite White_dam_spr(t3);//Спрайт белой дамки
	Sprite Black_pawn_spr(t4);//Спрайт чёрной пешки
	Sprite White_pawn_spr(t5);//Спрайт белой пешки
	Sprite shet(t6);//Спрайт таблицы счёта
	Sprite White_won1(t7);//Спрайт белой пешки
	Sprite Black_won1(t8);//Спрайт таблицы счёта
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
						dx = pos.x - x * size;
						dy = pos.y - y * size;

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

					//Если вернёт ok=1 значит ход возможен и будет выполнен
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
						
					}
					if (num_figure == White_pawn && move == 1)
					{
						ok = White_pawn_m(oldPoz.x, oldPoz.y, x, y);
					}
					if (ok == 1)
					{
						//Проверка на битьё
						if (flag == 0) {
							flag = 1;
							if ((board[y + 1][x - 1] >= 4 && board[y + 2][x - 2] == 0) ||
								(board[y + 1][x + 1] >= 4 && board[y + 2][x + 2] == 0) ||
								(board[y - 1][x - 1] >= 4 && board[y - 2][x - 2] == 0) ||
								(board[y - 1][x + 1] >= 4 && board[y - 2][x + 2] == 0))
							{
								if (x == 1 && (board[y - 1][x + 1] >= 4 && board[y - 2][x + 2] >= 4)) {
									flag = 1;
								}
								else if (y == 1 && (board[y - 1][x + 1] >= 4 && (board[y - 2][x + 2] >= 4) || (board[y - 2][x + 2] >= 4))) {
									flag = 1;
								}
								else if (abs(oldPoz.y - y) > 1 && abs(oldPoz.x - x) > 1 && x - 1 >= 0) {
									flag = 0;
								}
							}

						}
						else {
							flag = 0;
							if ((board[y + 1][x - 1] <= -4 && board[y + 2][x - 2] == 0) ||
								(board[y + 1][x + 1] <= -4 && board[y + 2][x + 2] == 0) ||
								(board[y - 1][x - 1] <= -4 && board[y - 2][x - 2] == 0) ||
								(board[y - 1][x + 1] <= -4 && board[y - 2][x + 2] == 0))
							{
								if (x == 1 && (board[y - 1][x + 1] <= -4 && board[y - 2][x + 2] <= -4)) {
									flag = 0;
								}
								else if (y == 6 && (board[y + 1][x - 1] <= -4 && board[y + 2][x - 2] <= -4)) {
									flag = 0;
								}
								else if (abs(oldPoz.y - y) > 1 && abs(oldPoz.x - x) > 1 && x - 1 >= 0 && y == 6) {
									flag = 0;
								}
								else if (abs(oldPoz.y - y) > 1 && abs(oldPoz.x - x) > 1 && x - 1 >= 0 && x + 1 < 7) {
									flag = 1;
								}
							}
						}
						//Если пешки дойдут до конца поля они превращаются в дамки
						board[y][x] = num_figure;
						if (y == 0 && num_figure == White_pawn) board[y][x] = White_dam;
						if (y == 7 && num_figure == Black_pawn) board[y][x] = Black_dam;

						/*
						oldFlag = 1;
						if (oldFlag == 1) {
							if (flag == 0) { oldFlag == 0; flag = 1; }
							else { oldFlag = 1; flag = 0; }

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

		window.clear(sf::Color::White);//очистка с белым цыетом
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
						White_pawn_spr.setPosition(j * size, i * size);
						window.draw(White_pawn_spr);
					}
				}
			}
		}
	
		shet.setPosition(size_window+5, 0);
		window.draw(shet);

		std::ostringstream Score_w, Score_b;//Кол-во белых и чёрных шашек, флаг.
		Score_w << count_w;
		Score_b << count_b;
		
		//Счётчик белых шашек
		text_w.setString(L"Белые:" + Score_w.str());
		text_w.setPosition(size_window + 10, 50);
		window.draw(text_w);

		//Счётчик чёрных шашек
		text_b.setString(L"Чёрные:" + Score_b.str());
		text_b.setPosition(size_window + 175, 50);
		window.draw(text_b);
		
		//Если осталось 0 шашек то проиграли
		if (count_w == 0) {
			flag_win.setString(L"Чёрные победили!");
			flag_win.setPosition(size_window + 40, 145);
			window.draw(flag_win);
			Black_won1.setPosition(size_window / 2 - 275, size_window / 2 - 150);//расположение счётчика в окне
			window.draw(Black_won1);
			//system("pause");
			//return 0;
		}
		else if (count_b == 0) {
			flag_win.setString(L"Белые победили!");
			flag_win.setPosition(size_window + 50, 145);
			window.draw(flag_win);

			White_won1.setPosition(size_window / 2 - 275, size_window / 2 - 150);//расположение счётчика в окне
			window.draw(White_won1);
			//system("pause");
			//return 0;
		}
		else {
			//Если флаг 0 то ход белых иначе ход чёрных
			if (flag == 0) {
				flag_win.setString(L"Белые");
				flag_win.setPosition(size_window + 130, 145);
				window.draw(flag_win);
			}
			else {
				flag_win.setString(L"Чёрные");
				flag_win.setPosition(size_window + 120, 145);
				window.draw(flag_win);
			}
		}
		window.display();
	}
	_getch();
	system("pause");
	std::cin.get();
	
	return 0;
}
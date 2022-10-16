/*
    Измененная версия игры Жизнь. Взамен проверки всего поля, проверке подлежат только живые клетки 
    и пространство рядом с ними. Вывод на экран производится только в местах заменяемых символов, взмамен 
    полной очистки с последующим выводом всего поля. Добавлен деморежим с ранее записанной фигурой, и 
    режим повтора игры.
    Внимание! Будьте аккуратнее с вводом данных, так как защита от неправильного ввода не реализована.
*/
#include <iostream>
#include "windows.h"
using namespace std;
int16_t x_size =8;          // размер поля Х
int16_t y_size = 5;         // размер поля У
int16_t size_figure = 10;    // размер буфера хранения адресов фигуры
int16_t size_figure_1 = 10;    // размер буфера хранения адресов фигуры
int16_t size_figure_2 = 10;    // размер буфера хранения адресов фигуры
int16_t size_empty = 10;    // размер буфера хранения адресов пустых клеток
uint16_t* figure     = new uint16_t[size_figure]; // под список живых клеток 
uint16_t* figure_1   = new uint16_t[size_figure_1]; // предыдущее состояние клеток 
uint16_t* figure_2   = new uint16_t[size_figure_2]; // давнее состояние клеток
uint16_t* empty_     = new uint16_t[size_empty]; // под список пустых клеток рядом с занятыми
int16_t fig_numb = 0;       // подсчет соседей
int16_t empty_number;       // подсчет пустых попутчиков занятых клеток
int gen;                // количество ходов
bool avto_;             // режим работы игры
bool demo_;             // демо-показ
bool __on__ = true;     // разрешение на повтор игры

void menu_();
void vvod_size(); // ввод размера поля
void vvod_figure(); // ввод элементов фигуры
int16_t sorting(uint16_t* &position, int16_t size);
void start_game(); // запуск выполнения игры
void print_();      // вывод данных на экран
void change_size_arr(uint16_t *&arr, int16_t &size, int16_t number);


int main(int argc, const char * argv[]) {
    while (__on__)
    {
    menu_();
    vvod_size();
    vvod_figure();
    system("cls");
    for (int y = 0; y < y_size; y++)
    {
        for (int x = 0; x < x_size; x++)
        {
            cout << " -";
        }
        cout << "\n";
    }
    cout << "Figure for game" << endl;
        for (int n = 0; n < size_figure_1; n++)
        {
            figure_1[n]=0x101;
        }
    print_();
    system("pause ");
    start_game();
        cout << "   May be play again?\nEnter '1' to repeat, '0' - to exit.";   //if (avto_){system ("pause ") ;}  
        char newtry;
        cin >>  newtry;
        if (!(newtry == 49))
        {__on__ = false;}
        Sleep(300);
    }
    cout << "Good bye";
    delete [] figure;
    delete [] figure_1;
    delete [] figure_2;
    return 0;
}   

void menu_() {
char avto;
cout << "Select mode:\n 1-Avto, else Hand mode \n "; 
cin >> avto;
if (avto == 49)
{
    avto_ = 1;
    cout << "Avto mode\n";
} else {cout << "Hand mode\n"; avto_ = 0;}
Sleep(300);
char demo;
cout << "choose '1' for the game,\n otherwise demo \n "; 
cin >> demo;
if (demo == 49)
{
    demo_ = 0;    
} else { demo_ = 1;}
}

void vvod_size() {
    if(demo_){
        x_size = 15; y_size = 9;
    }else{
        cout << "Input size fill (1-100)\n" << " x  y  \n";
        cin >> x_size >> y_size;}
    cout << "Field size: " << x_size * y_size << ";\n";
}

void vvod_figure() {
    uint16_t x_fig_;
    uint16_t y_fig_;
    int16_t number__ = 0;
    bool stop_ = 0;
    if(demo_){
        figure [0]= 0x507;
        figure [1]= 0x508;
        figure [2]= 0x509;
        figure [3]= 0x408;
                number__ = 4;
    }else{
    cout << "Input for the figure X (1-" << x_size << ") and  Y (1-" << y_size << ")\n or '0' to stop\n"  << " x  y  \n";
    while (!stop_)
        {
            cin >> x_fig_; 
            if(!x_fig_)break;
            cin >> y_fig_;
            if(!y_fig_)break;
            if (x_fig_ <0 || x_fig_> x_size || y_fig_ <0 || y_fig_> y_size ) { // проверка соответствия
                cout << "incorrect input. try again\n";
                }
            else { 
                figure[number__] = y_fig_ * 0x100 + x_fig_;
                number__++;
                }
                    if (number__>size_figure-1)
                    {
                        change_size_arr(figure, size_figure, (int16_t)5);
                    }
        }
    }
    size_figure = sorting(figure, number__);
    cout << "  size_figure=" << size_figure << "\n";
}

int16_t sorting(uint16_t* &position, int16_t size){
    for(int16_t i = 1; i < size; i++)
	{
		int16_t j = i - 1;
		while((j >= 0) && (position[j] >= position[j + 1]))
		{
			if((position[j] == position[j + 1]) || (position[j + 1] == 0)){
            swap(position[j+1], position[size-1]);
            size--;
            i=j;
            break;
            }else{
            swap(position[j], position[j + 1]);
		//	cout << "\n";
			j--;
            }
		}
	}
    change_size_arr(position, size, (int16_t)0);
    return size;
}

void print_() {
    int8_t x;
    int8_t y;
    char x1, x2, x3, y1, y2, y3; 
   for(int i=0; i < size_figure_1; i++){
        x = (figure_1[i] % 0x100)*2; y = figure_1[i] / 0x100;
        x1 = x/100 + '0'; x2 = x%100/10 +'0'; x3 = x%10 +'0';
        y1 = y/100 + '0'; y2 = y%100/10 +'0'; y3 = y%10 +'0';
        char w [] = {033, '[', y1, y2, y3, ';', x1, x2,  x3,'H',  0};
        cout << w << "-";
    }
   for(int i=0; i < size_figure; i++){
        x = (figure[i] % 0x100)*2; y = figure[i] / 0x100;
        x1 = x/100 + '0'; x2 = x%100/10 +'0'; x3 = x%10 +'0';
        y1 = y/100 + '0'; y2 = y%100/10 +'0'; y3 = y%10 +'0';
        char w []= {033, '[', y1, y2, y3, ';', x1, x2, x3, 'H',  0};
        cout << w << "*";
    }    
    
    y = y_size + 1;
        x1 = 1 + '0';
        y1 = y/100 + '0'; y2 = y%100/10 +'0'; y3 = y%10 +'0';
        char w [] = {033, '[', y1, y2, y3, ';', x1, 'H',  0};
        cout << w ;
    cout << "Gen: " << gen++ << ". Alive cells: " << size_figure << endl;
}

void change_size_arr(uint16_t* &arr, int16_t &size, int16_t  number)
{
    uint16_t *newArray = new uint16_t[size + number];
    for (int8_t i = 0; i < size; i++)
    {
        newArray[i] = arr[i];
    }
    size += number;
    delete[] arr;
    arr = newArray;
}

void life_did(uint16_t* &ceile, uint16_t size, bool fig){
    int8_t number;
    empty_number = 0;
    int16_t sdvig, row, col;
    uint16_t row_col;
    bool vector_find, stop;
    for (int8_t list = 0; list < size; list++)
    {
        number = 0;
        sdvig = 0;
        row = ceile[list] / 0x100;
        col = ceile[list] % 0x100;
        vector_find = 0;
        /*  проверка соседних клеток    */
        for (int16_t r = row - (!(row<=1)); r < row + 1 + (!(row >=y_size)); r++)
        {
            for (int16_t c = col - (!(col <= 1)); c < col + 1 + (!(col >= x_size)); c++)
            {
                stop = false;
                row_col = r * 0x100 + c;
                if (ceile[list] != row_col)
                {
                    while (!stop)
                    { // поиск нужных клеток в списке
                        if ((figure_1[sdvig] >= row_col) || (sdvig == size_figure_1))
                        {
                            stop = true;
                            if (figure_1[sdvig] == row_col)
                            { //при совпадении считаем
                                number++;
                            }
                            else if (fig)
                            {
                                if (empty_number > size_empty - 1) // при нехватке места добавляем ячейки
                                {
                                    change_size_arr(empty_, size_empty, (int16_t)10);
                                }
                                empty_[empty_number] = row_col; // при отсутствии записываем пустую клетку
                                empty_number++;
                            }
                        }
                        else
                        {
                            sdvig++;
                        }
                    }
                }
            }
        }
        /*  работы по результатм "опроса соседей"   */
        if (fig_numb>size_figure-1)
            {
                change_size_arr(figure, size_figure, (int16_t)5);
            }
        if((number == 3) || ((number == 2) && (fig))) {
            figure[fig_numb] = ceile[list];
            ++fig_numb;
        }
    }
}

 // запуск выполнения игры
void start_game(){
    gen = 0;
    bool stop_end, stop_repeat, stop_did;
    while (!stop_end)
    {
        // запоминаем состояние и очищаем рабочее поле
        swap(figure_2, figure_1);
        swap(size_figure_2, size_figure_1);
        swap(figure_1, figure);
        swap(size_figure_1, size_figure);
        // swap(figure, figure_2);
        // swap(size_figure, size_figure_2);
        empty_number = 0;

        fig_numb = 0;
        empty_number = 0;
        // проверка соседей у живых клеток
        life_did(figure_1, size_figure_1, 1);
        // проверка соседей у пустых клеток
        size_empty = sorting(empty_, empty_number);
        life_did(empty_, size_empty, 0);
        size_figure = sorting(figure, fig_numb);

        // проверка окончания игры
        stop_end = true;
        stop_repeat = true;
        stop_did = 0;
        if (size_figure_1 == size_figure)
        {
            for (int i = 0; i < size_figure; i++)
            {
                if (figure[i] != figure_1[i])
                {
                    stop_end = false;
                }
            //    stop_did += figure[i];
            }
        }else{stop_end = false;}
        if (size_figure_2 == size_figure)
        {
            for (int i = 0; i < size_figure; i++)
            {
                if (figure[i] != figure_2[i])
                {
                    stop_repeat = false;
                }
            }
        }else{stop_repeat = false;}
         print_();
        if (stop_end)
            cout << "The world has stagnated. Game over.             " << endl;
         
        if (!size_figure) 
        {   cout << "All cells is did. Game over.                    " << endl;
            stop_end = true;
        }
        if (stop_repeat)
        {   cout << "The world has cicled. Game over.                " << endl;
            stop_end = true;
        }
        if (avto_){ Sleep(500);}  
        
    }
}

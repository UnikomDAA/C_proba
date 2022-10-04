#include <iostream>
#include "windows.h"
using namespace std;
int x_size =8;          // размер поля Х
int y_size = 5;         // размер поля У
int size_empty = 50;    // размер буфера хранения адресов пустых клеток
int empty_number;       // подсчет пустых попутчиков занятых клеток
uint64_t x_figure[60];  // матрица поля
uint64_t x_figure_1[60]; // матрица предыдущего состояния поля
int y_figure;
int gen;                // количество ходов
bool avto_;             // режим работы игры
int* x_empty = new int[size_empty]; // под список пустых клеток рядом с занятыми

//std::vector<int> mas = {1, 2, 3, 4, 5};
void menu_();
void vvod(); // получение данных 
void vvod_size(); // ввод размера поля
void vvod_figure(); // ввод элементов фигуры
void start_game(); // запуск выполнения игры
void print_();      // вывод данных на экран
int stroka(uint64_t st, int size); // создание одной сторки для вывода данных

int main(int argc, const char * argv[]) {
    cout << "Hello!__\n";
    menu_();
    vvod();
        cout << "Figure for game" << endl;
        print_();
   system ("pause ");
        start_game();
    //    print_();
   
    return 0;
}

void menu_() {
char avto;
cout << "Select mode:\n 1-Avto, else Hand mode \n "; 
//while(!avto) 
cin >> avto;
if (avto == 49)
{
    avto_ = 1;
    cout << "Avto mode\n";
} else {cout << "Hand mode\n";}
Sleep(300);
}

void vvod() {
    vvod_size();
    vvod_figure();
}
void vvod_size() {
    cout << "Input size fill (1-60)\n" << " x  y  \n";
    cin >> x_size >> y_size;
       cout << "Field size: " << x_size * y_size << ";\n";

}

void vvod_figure() {
    int x_fig_;
    int y_fig_;
    bool stop_;
    cout << "Input for figure X (1-" << x_size << ") and  Y (1-" << y_size << ")\n or any letter for stop\n"  << " x  y  \n";
    while (!stop_)
    {
        cin >> x_fig_ >> y_fig_;
        if (x_fig_ <1 || x_fig_> x_size || y_fig_ <1 || y_fig_> y_size ) stop_ = true;
        x_figure[y_fig_-1] |= (1 << x_fig_-1);
    }
   //  x_figure[y_fig_-1] |= (1 << x_fig_-3);
  // cout << "xF+yF=" << x_fig_+y_fig_ << endl << "X_DEC=" << x_figure[y_fig_-1] << endl; 
}

int stroka(uint64_t st,  int size){
    int alive=0;
    for(int i=0; i<size; i++){
        if ((1 << i)  &  st) {
            cout << " *";
            alive++;
        }
        else cout << " -";
    }
     cout << endl;
     return alive;
}

void print_() {
    int alive_=0;
    for(int i=0; i<y_size; i++){
        alive_ += stroka(x_figure[i], x_size) ;
        
    }
    cout << "Gen: " << gen++ << ". Alive cells: " << alive_ << endl;
}

int16_t sosedy(int16_t col, int16_t row) { //подсчет соседей
    int16_t number=-1;
    for (int16_t r = row - (!(row==0)); r < row + 1 + (!(row+1==y_size)); r++)
    {
        for (int16_t c = col-(!(col==0)); c < col + 1 + (!(col+1 ==x_size)); c++) {
            if (((1 << c)  & x_figure_1[r])) {
                number++;
            }else{
                // x_empty[empty_number] = c * 255 + r;
                // empty_number++;
                // if (empty_number>size_empty)
                // {
                //     /* code */
                // }
                // if (empty_number<10+size_empty)
                // {
                //     /* code */
                // }
            }
// cout << "X_" << c << " Y_" << r <<" || ";
             //   x_figure[r] |= (1 << c);
        }
    }
    return number;
cout << endl;    
}

 // запуск выполнения игры
void start_game(){
    uint64_t x_figure_2[60];
    bool stop_end, stop_repeat, stop_did;
    while (!stop_end)
    {
    system("cls");
        // запоминаем состояние и очищаем рабочее поле
        for(int16_t i = 0; i < y_size; i++){
            x_figure_2[i] =  x_figure_1[i];
            x_figure_1[i] =  x_figure[i];
            x_figure[i] = 0;
            empty_number = 0;
        } 
        
        //  перебор строк
        for(int16_t i = 0; i < y_size; i++)
        {
 //           if(!x_figure_1[i]) continue;      // поиск непустой строки
 //           else 
 //           {
                /* поиск занятой клетки */
                for(int16_t ce_ = 0; ce_ < x_size; ce_++)
                {
                    if (!((1 << ce_)  & x_figure_1[i])) {
                        /* проверка на создание клетки */
                        int16_t num_ = sosedy(ce_, i);
                        if (num_ ==  (2))
                        {
                            x_figure[i] |= (1 << ce_);
                        }
                    } else
                    {
                        /* проверка на жизнеспособность */
                        int16_t num_ = sosedy(ce_, i);
 //                       cout << i << "_row=" << ce_ << "_col=" << num_ << "num  ";
                        if ((num_ == 2) || (num_ ==3))
                        {
                            x_figure[i] |= (1 << ce_);
                        }
                        
                    } 
                } 
//            }
        }
        // работа на окончание игры
        stop_end = true;
        stop_repeat = true;
        stop_did = 0;
         for (int i = 0; i < y_size; i++)
        {
            if (!(x_figure[i] == x_figure_1[i])) {stop_end = false;}
//       cout << "end = " << stop_end << "_" << i; 
            stop_did += x_figure[i];
            if (!(x_figure[i] == x_figure_2[i])) {stop_repeat = false;}
        }
         print_();
        if (stop_end)
            cout << "The world has stagnated. Game over." << endl;
         
        if (!stop_did) 
        {   cout << "All cells is did. Game over." << endl;
            stop_end = true;
        }
        if (stop_repeat)
        {   cout << "The world has cicled. Game over." << endl;
            stop_end = true;
        }
        if (avto_){ Sleep(500);}  
        else {system ("pause ");}
    }
       if (avto_){system ("pause ") ;}  
}

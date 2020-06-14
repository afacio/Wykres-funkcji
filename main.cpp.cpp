#include <iostream>
#include <cmath>
#include <functional>


using namespace std;

class Point
{
public:
	double a, b;
	//void zamiana(double,double,double,double);
};

class Screen : Point
{
private:
	int wys, dl;
	char* a; //wskaźnik na początek tablicy
public:
	Screen(){}
	Screen(int w = 10, int d = 10): wys(w),dl(d) 
	{
		a = new char[wys * dl];
		for (int i = 0; i < wys * dl; i++)* (a + i) = ' ';
	}
	void put(int zx, int zy, char z)
	{
		if (zx >= 0 && zx < dl && zy >= 0 && zy < wys)* (a + dl * zy + zx) = z;
		//cout << z << endl;
	}
	void show()
	{
		for (int j = 0; j < wys; j++) {
			for (int i = 0; i < dl; i++) 
				cout << *(a + dl * j + i);
			puts("");
		}
	}
};

double funkcja(double x)
{
	return pow(x, 2) * cos(x * 2) * sin(x);
}
void wyswietl()
{
	cout << "Narysowana funkcja:  pow(x,2)*cos(x*2)*sin(x)" << endl;  
}

class Z : public Point 
{
public:
	Z() {}
	Z(double d1, double d2, double i1, double i2) 
	{
		a = (i2 - i1) / (d2 - d1);
		b = i1 - a * d1;
	}
	void show() 
	{
		cout << "a: " << a << endl;
		cout << "b: " << b << endl;
	}
};

void granice(function<double(double)> f, double xmin, double xmax, double &ymin, double &ymax) // funkcja wyznaczająca granice przedziału na osi Y aby dało się przeskalować funkcje
{
	ymin = ymax = f(xmin);
	double dx = (xmax - xmin) / 100.0;
	double y, x = 0;
	
	for( x+=dx; x <= xmax; x += dx)
	{
		y = f(x);
		if (y < ymin)
			ymin = y;
		if (y > ymax)
			ymax = y;
	}
	y = (ymax - ymin) * 0.5; // dokładność wykresu maleje wraz ze wzrostem y 
	ymin -= y;
	ymax += y;
}
int main() 
{
	int h = 50, w = 210, lp = 10000; // h - wysokość, w - wysokość, lp - liczba punktów wyrysowanych na wykresie
	double x_min = -4, x_max =4, dx,  //x_min i x_max granice przedziału branego pod uwage przy rysowaniu funkcji im mniejszy zakres tym precyzyjniejszy obraz
		   y_min, y_max, dy;

	
	granice(funkcja, x_min, x_max, y_min, y_max); //funkcja zwraca wartości graniczne dla y_min i y_max
	
	double a=1.5, b=0.7;
	//granice([a, b](double x)->double {return a * sin(x) + b; }, x_min, x_max, y_min, y_max);


	//precyzja punktu
	dx = (x_max - x_min) / lp;
	dy = (y_max - y_min) / lp;

	Screen screen(h, w);

	cout << "zmiena x_max: " << x_max << endl; cout << "zmiena x_min: " << x_min << endl; cout << "zmiena y_max: " << y_max << endl; cout << "zmiena y_min: " << y_min << endl;
	puts("");
	cout << "dx = (x_max - x_min) / np = " << dx << endl; cout<<"dy = (y_max - y_min) / np = " << dy <<endl;
	puts("");
	system("pause");
	
	Z zx(x_min, x_max, 0, w), 
	  zy(y_min, y_max, h, 0); 

	cout << "\nzmienne zx\n";
	zx.show();
	cout << "\nzmienne zy\n";
	zy.show();
	puts("");
	system("pause");

	system("CLS");

	double i;  

	//pętla wypisująca oś X
	for (i = x_min; i <= x_max; i += dx)
		screen.put((int)(zx.a * i + zx.b), (int)(zy.b), '.');


	//pętla wypisująca oś Y
	for (i = y_min; i <= y_max; i += dy)
		screen.put((int)(zx.b), (int)(zy.a * i + zy.b), '.');

	//pętla wypisująca przebieg funkcji
	for (i = x_min; i <= x_max; i += dx)
		screen.put((int)(zx.a * i + zx.b), (int)(zy.a * funkcja(i) + zy.b), 'o');

	//system("pause");
	screen.show();
	wyswietl(); 
	system("pause");
	return 0;
}

#include <iostream>
#include "bits/stdc++.h"
// Matrices1.cpp: ���������� ����� ����� ��� ����������� ����������.
//

using namespace std;

class BaseMatrix
{
protected:
    double **ptr;
    int height;
    int width;
    double ScalarProduct(double *arr1, double *arr2, int len)
    {
        double res = 0;
        for (int i = 0; i < height; i++)
            res += arr1[i] * arr2[i];
        return res;
    }

public:
    BaseMatrix(int Height = 2, int Width = 2)
    {
        height = Height;
        width = Width;
        ptr = new double *[height];
        for (int i = 0; i < height; i++)
            ptr[i] = new double[width];
    }

    BaseMatrix(const BaseMatrix &M)
    {
        //ÍÓÌÒÚÛÍÚÓ ÍÓÔËÈ
        height = M.height;
        width = M.width;
        ptr = new double *[height];
        for (int i = 0; i < height; i++)
            ptr[i] = new double[width];
        for (int i = 0; i < height; i++)
            for (int j = 0; j < height; j++)
                ptr[i][j] = M.ptr[i][j];
    }

    ~BaseMatrix()
    {
        if (ptr != NULL)
        {
            for (int i = 0; i < height; i++)
                delete[] ptr[i];
            delete[] ptr;
            ptr = NULL;
        }
    }

    void print()
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
                cout << ptr[i][j] << " ";
            cout << "\n";
        }
    }

    double &operator()(int row, int column) { return ptr[row][column]; }

    BaseMatrix Transponse()
    {
        BaseMatrix Res(width, height);
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                Res.ptr[j][i] = ptr[i][j]; // Res(j,i) = ptr[i][j];

        return Res;
    }
    double *operator*(double *arr)
    {
        double *res = new double[height];
        for (int i = 0; i < height; i++)
            res[i] = ScalarProduct(ptr[i], arr, width);
        return res;
    }
};

class Exception : public exception
{
protected:
    //сообщение об ошибке
    char *str;

public:
    Exception(const char *s)
    {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }
    Exception(const Exception &e)
    {
        str = new char[strlen(e.str) + 1];
        strcpy(str, e.str);
    }
    ~Exception()
    {
        delete[] str;
    }

    //функцию вывода можно будет переопределить в производных классах, когда будет ясна конкретика
    virtual void print()
    {
        cout << "Exception: " << str << "; " << what();
    }
};

class WrongSizeException : public Exception
{
protected:
    int height, width;

public:
    WrongSizeException(int H, int W) : Exception("Wrong size")
    {
        height = H, width = W;
    }

    WrongSizeException() : Exception("Wrong size")
    {
        height = 0, width = 0;
    }

    WrongSizeException(const WrongSizeException &e) : Exception("Wrong size")
    {
        str = new char[strlen(e.str) + 1];
        strcpy(str, e.str);
        height = e.height, width = e.width;
    }

    virtual void print() { cout << "Exception: " << str << "; dimensions of matrix: " << height << ", " << width << "; " << what(); }
};

class NullSizeException : public WrongSizeException
{
protected:
    int height, width;

public:
    NullSizeException(int H, int W) : WrongSizeException(H, W) {}

    NullSizeException() : WrongSizeException(0, 0) {}

    NullSizeException(const NullSizeException &e)
    {
        str = new char[strlen(e.str) + 1];
        strcpy(str, e.str);
        height = e.height, width = e.width;
    }
};

class NegativeSizeException : public WrongSizeException
{
protected:
    int height, width;

public:
    NegativeSizeException(int H, int W) : WrongSizeException(H, W) {}

    NegativeSizeException() : WrongSizeException(0, 0) {}

    NegativeSizeException(const NegativeSizeException &e)
    {
        str = new char[strlen(e.str) + 1];
        strcpy(str, e.str);
        height = e.height, width = e.width;
    }
};

class IndexOutOfBoundsException : public WrongSizeException
{
protected:
    int height, width;

public:
    IndexOutOfBoundsException(int H, int W) : WrongSizeException(H, W) {}

    IndexOutOfBoundsException() : WrongSizeException(0, 0) {}

    IndexOutOfBoundsException(const IndexOutOfBoundsException &e)
    {
        str = new char[strlen(e.str) + 1];
        strcpy(str, e.str);
        height = e.height, width = e.width;
    }
};

//теперь наследуем ошибки от Exception
class DivisionByZero : public Exception
{
    //деление на 0
private:
    //числитель
    int numerator;

public:
    //конструктор
    DivisionByZero(int Numerator) : Exception("attempt to divide by zero")
    {
        numerator = Numerator;
    }

    //get-тер - получение числителя извне
    int getNumerator() { return numerator; }

    //вывод сообщения - переопределение виртуальной функции базового класса
    void print()
    {
        cout << "Exception: " << str << ", numerator = " << numerator << "; " << what();
        //также можно воспользоваться функцией вывода базового класса и потом дописать числитель
        //из-за того, что она называется так же, как эта функция, указываем класс, откуда её берём
        //Exception::print();
        //cout << ", numerator = " << numerator;
    }
};

class NegativeDenominator : public Exception
{
    //отрицательный знаменатель
private:
    //исходная дробь
    //числитель
    int numerator;
    //знаменатель
    int denominator;
    //значение, которое пытались установить
    int value;

public:
    //конструктор
    NegativeDenominator(int Numerator, int Denominator, int Value) : Exception("attempt to set negative denominator")
    {
        numerator = Numerator;
        denominator = Denominator;
        value = Value;
    }

    //get-теры - получение дроби извне
    int getNumerator() { return numerator; }
    int getDenominator() { return denominator; }
    //получение значения, которое пытались установить в знаменатель
    int getValue() { return value; }

    //вывод сообщения
    void print()
    {
        cout << "Exception: " << str << ", value = " << value << ", Fraction = " << numerator << "/" << denominator << "; " << what();
        //также можно воспользоваться функцией вывода базового класса и потом дописать числитель
        //из-за того, что она называется так же, как эта функция, указываем класс, откуда её берём
        //Exception::print();
        //cout << ", value = " << value << ", Fraction = "<<numerator<<"/"<<denominator;
    }
};

class Fraction
{
private:
    //числитель
    int numerator;
    //знаменатель
    int denominator;

public:
    //get-теры - получение значений числителя и знаменателя извне
    int getNumerator() { return numerator; }
    int getDenominator() { return denominator; }

    //установка числителя
    void setNumerator(int value) { numerator = value; }

    //умножение
    Fraction operator*(Fraction F)
    {
        Fraction Res;
        Res.numerator = numerator * F.numerator;
        Res.denominator = denominator * F.denominator;
        return Res;
    }

    //вывод
    void print()
    {
        cout << numerator << "/" << denominator;
    }

    //конструктор
    Fraction(int Numerator = 0, int Denominator = 1)
    {
        if (Denominator == 0)
            throw DivisionByZero(Numerator);
        if (Denominator < 0)
            throw NegativeDenominator(0, 1, Denominator);

        //здесь всё хорошо
        numerator = Numerator;
        denominator = Denominator;
    }

    //set-тер для знаменателя
    void setDenominator(int value)
    {
        if (value == 0)
            throw DivisionByZero(numerator);
        if (value < 0)
            throw NegativeDenominator(numerator, denominator, value);

        //здесь всё хорошо
        denominator = value;
    }
};

ostream& my_manip(ostream& s)
{
    s.setf(ios::left);
    s.width(10);
    s.precision(7);
    s.fill('*');
    return s;
}

int main()
{
    IndexOutOfBoundsException ex(0, 0);
    Exception *ptr = &ex;
    cout << typeid(ptr).name() << ';' << typeid(*ptr).name() << '\n';
    if (typeid(*ptr)==typeid(IndexOutOfBoundsException)){
        IndexOutOfBoundsException *p = dynamic_cast<IndexOutOfBoundsException *>(ptr);
        p->print();
    }

    double number = 191.132;
    cout << my_manip << number;
    /*
    int N = 5;
    BaseMatrix *matrix_array = new BaseMatrix[N];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                matrix_array[i](j, k) = (i + j) % k + k % 2;
            }
        }
    }
    ofstream fout("file.txt");
    
    if (fout)
    {
        fout << N << '\n';
        for (int i = 0; i < N; i++)
        {
            fout << matrix_array[i];
        }
        fout.close();
    }

    ifstream fin("file.txt");
    if (fin)
    {
        int n;
        fin >> n;
        BaseMatrix matrix;
        for (int i = 0; i < n; i++)
        {
            fin >> matrix;
        }
        fin.close();
    }
   
    char str[] = "Very long text";
    ofstream fout_text("file.txt");
    if (fout_text)
    {
        fout_text << str;
        fout_text.close();
    }
    ofstream fin_text("file.txt");
    if (fin_text)
    {
        char s[100];
        while (!fin_text.eof())
        {
            fin_text >> s;
            cout << s << '\n';
        }

        fin_text.close();
    }
 */

    /*
	//здесь всё хорошо
	Fraction F1(1, 2);
	Fraction F2(1, 3);
	Fraction F3 = F1 * F2;
	F3.print();

	//а здесь сгенерируем исключение
	try
	{
		BaseMatrix M(2, 3);
		for(int i = 0; i < 2; i++)
		{
			for(int j = 0; j < 3; j++) M(i, j) = i * 2 + j + 1;
		}

		cout << "\n";
		M.print();

		BaseMatrix C = M.Transponse();

		cout << "\n";
		C.print();

	//	BaseMatrix Sum = C + M;
	}
	catch (DivisionByZero d)
	{
		//здесь обрабатываем исключение
		cout << "\nDivision by zero exception has been caught:\n";
		d.print();
	}
	catch (NegativeDenominator n)
	{
		//здесь обрабатываем исключение
		cout << "\nNegative denominator exception has been caught:\n";
		n.print();
	}
	catch(IndexOutOfBoundsException e)
	{
		cout << "\nIndex out of bounds exception has been caught:\n";
		e.print();
	}
	//catch для всех ошибок таких типов, которые мы спроектировали сами, - в случае, если нет конкретики
	catch (Exception e)
	{
		//здесь обрабатываем исключение
		cout << "\nException has been caught: ";
		e.print();
	}
	//catch, который среагирует на любые ошибки, - закроет всё, что не обработали предыдущие блоки catch
	catch (...)
	{
		//здесь обрабатываем исключение
		cout << "\nSomething has happened";
	}


	//вторая попытка
	try
	{
		F1.setDenominator(-1);
		//сюда мы уже не попадём
		F3 = F1 * F2;
		F3.print();
	}
	//catch для всех ошибок таких типов, которые мы спроектировали сами, - в случае, если нет конкретики
	catch (Exception e)
	{
		//здесь обрабатываем исключение
		cout << "\nException has been caught: ";
		e.print();
	}
	//просмотр дошёл до catch(...) - срабатывает он
	catch (...)
	{
		//здесь обрабатываем исключение
		cout << "\nSomething has happened";
	}
	char c3; std::cin >> c3;
	return 0;
    */
}
#include <iostream>
#include <cstring>
using namespace std;

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
	Exception()
	{
		char s[] = "Unknown exception";
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

class WrongDimensionException : public Exception
{
protected:
	//сообщение об ошибке
	int height1;
	int width1;
	int height2;
	int width2;

public:
	WrongDimensionException(int H1, int W1, int H2, int W2) : Exception("Wrong dimensions")
	{
		height1 = H1;
		height2 = H2;
		width1 = W1;
		width2 = W2;
	}
	WrongDimensionException(const WrongDimensionException &e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy(str, e.str);
	}

	~WrongDimensionException() {}

	//функцию вывода можно будет переопределить в производных классах, когда будет ясна конкретика
	virtual void print()
	{
		cout << "Exception: " << str << "; dimensions of matrices: " << height1 << ", " << what();
		cout << "; " << height2 << ", " << width2 << "; " << what();
	}
};

class WrongSizeException : public Exception
{
protected:
	//сообщение об ошибке
	int height;
	int width;

public:
	WrongSizeException(int H, int W) : Exception("Wrong size")
	{
		height = H;
		width = W;
	}

	WrongSizeException() : Exception("Wrong size")
	{
		height = 0;
		width = 0;
	}
	WrongSizeException(const WrongSizeException &e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy(str, e.str);
		height = e.height;
		width = e.width;
	}

	~WrongSizeException() {}

	//функцию вывода можно будет переопределить в производных классах, когда будет ясна конкретика
	virtual void print()
	{
		cout << "Exception: " << str << "; dimensions of matrices: " << height << ", " << width << "; " << what();
	}
};

class NullSizeException : public WrongSizeException
{

public:
	NullSizeException(int H, int W) : WrongSizeException(H, W) {}

	NullSizeException() : WrongSizeException(0, 0) {}

	NullSizeException(const NullSizeException &e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy(str, e.str);
		height = e.height;
		width = e.width;
	}
};

class NegativeSizeException : public WrongSizeException
{

public:
	NegativeSizeException(int H, int W) : WrongSizeException(H, W) {}

	NegativeSizeException() : WrongSizeException(0, 0) {}

	NegativeSizeException(const NegativeSizeException &e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy(str, e.str);
		height = e.height;
		width = e.width;
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

template <class T>
class BaseMatrix
{
protected:
	T **ptr;
	int height;
	int width;
	BaseMatrix ScalarProduct(double *arr1, double *arr2, int len)

	{
		double res = 0;
		for (int i = 0; i < len; i++)
		{
			res += arr1[i] * arr2[i];
		}
		return res;
	}

public:
	BaseMatrix<T>(int Height = 2, int Width = 2) // constructor
	{
		//if(Height<=0 || Width<=0)
		//  throw WrongSizeException(height, width);
		if (row > height || column > height)
		{
			throw IndexOutOfBoundsException(Height, Width);
		}
		if (Height < 0 || Width < 0)
		{
			throw NegativeSizeException(Height, Width);
		}
		if (Height == 0 || Width == 0)
		{
			throw NullSizeException(Height, Width);
		}
		height = Height;
		width = Width;
		ptr = new T *[height];
		for (int i = 0; i < height; i++)
			ptr[i] = new T[width];
	}

	BaseMatrix(const BaseMatrix &M) //constructor of copy
	{
		height = M.height;
		width = M.width;
		ptr = new double *[height];
		for (int i = 0; i < height; i++)
			ptr[i] = new double[width];

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				ptr[i][j] = M.ptr[i][j];
			}
		}
	}
	// T Max(T a,T b)
	// {
	//     return a<b?b:a>
	// }

	~BaseMatrix()
	{
		// Деструктор
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
	double &operator()(int row, int column)
	{
		if (row >= height || column >= height || row < 0 || column < 0)
		{
			throw IndexOutOfBoundsException(Height, Width);
		}

		return ptr[row][column];
	}
	BaseMatrix operator+(BaseMatrix M)
	{
		if (height != M.height || width != M.width)
			throw WrongDimensionException(height, width, M.height, M.width);
		BaseMatrix Res(height, width);
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				Res.ptr[i][j] = ptr[i][j];
			}
		}
	}
	BaseMatrix Transpose()
	{
		// транспонирование матрциы
		BaseMatrix Res(width, height);
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				Res.ptr[j][i] = ptr[i][j]; //Res(j,i) = ptr[i][j];
			}
		}
		return Res;
	}
	double *operator*(double *arr)
	{
		double *res = new double[width];
		for (int i = 0; i < height; i++)
		{
			res[i] = ScalarProduct(ptr[i], arr, width);
		}
		return res;
	}
};

int main()
{
	// int x;int y;
	// x=1;y=2;
	// cout<<"\nMax = "<<Max(x,y)<<"\n";
	try
	{
		BaseMatrix<double> M(-2, 3);

		M(0, 0) = 1;
		M(0, 1) = 2;
		M(1, 0) = 3;
		M(1, 1) = 4;
		M(0, 2) = 5;
		M(1, 2) = 6;

		M.print();

		BaseMatrix<double> C = M.Transpose();
		cout << "\n";
		C.print();
		BaseMatrix<double> Sum = C + M;
	}
	catch (IndexOutOfBoundsException e)
	{
		cout << "\nException has been caught: ";
		e.print();
	}
	catch (WrongDimensionException e)
	{
		cout << "\nException has been caught: ";
		e.print();
	}
	catch (WrongSizeException e) //Искчлючение неправильного размера
	{
		cout << "\nException has been caught: ";
		e.print();
	}
	catch (NullSizeException e) //Искчлючение нулевого размера
	{
		cout << "\nException has been caught: ";
		e.print();
	}
	catch (Exception e) //Наши исключения
	{
		cout << "\nException has been caught: ";
		e.print();
	}
	catch (exception e) //Вообще все исключения
	{
		cout << "\nException has been caught: ";
		e.what();
	}

	// double vec[] = {10, 20};

	// double* vec1 = M * vec;
	// cout<<"\nM * {10,20} = {"<<vec1[0]<<", "<<vec1[1]<<"}";

	// BaseMatrix Mt = M.Transpose();
	// Mt.print();

	// char c; cin >> c;
	return 0;
}

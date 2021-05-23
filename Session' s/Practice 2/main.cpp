#include <iostream>

using namespace std;

class MyArrayParent
{
protected:
    int capacity; //сколько выделено памяти
    int count;    //количество элементов - сколько памяти используем
    double *ptr;  //массив

public:
    //конструкторы и деструктор
    MyArrayParent(int Dimension = 100)
    {
        cout << "\nMyArrayParent constructor";
        ptr = new double[Dimension];
        capacity = Dimension;
        count = 0;
    }
    //конструктор принимает существующий массив
    MyArrayParent(double *arr, int len)
    {
        cout << "\nMyArrayParent constructor";
        capacity = len;
        count = len;
        ptr = new double[capacity];
        for (int i = 0; i < count; i++)
        {
            ptr[i] = arr[i];
        }
    }
    //деструктор
    ~MyArrayParent()
    {
        cout << "\nMyArrayParent destructor";
        if (ptr != NULL)
        {
            delete[] ptr;
            ptr = NULL;
        }
    }

    int Capacity()
    {
        return capacity;
    }
    int Size()
    {
        return count;
    }

    double GetComponent(int index)
    {
        if (index >= 0 && index < count)
        {
            return ptr[index];
        }
        return -1;
    }
    bool SetComponent(int index, double value)
    {
        if (index >= 0 && index < count)
        {
            ptr[index] = value;
            return true;
        }
        else
        {
            return false;
        }
    }

    //добавление в конец нового значения
    void push(double value)
    {
        if (count < capacity)
        {
            ptr[count] = value;
            count++;
        }
    }

    //удаление элемента с конца
    void RemoveLastValue()
    {
        if (count > 0)
        {
            count--;
        }
    }

    double &operator[](int index)
    {
        if (index >= 0 && index < count)
        {
            return ptr[index];
        }
    }

    MyArrayParent &operator=(const MyArrayParent &V)
    {
        count = V.count;
        capacity = V.capacity;
        ptr = new double[capacity];
        for (int i = 0; i < count; i++)
        {
            ptr[i] = V.ptr[i];
        }
        return *this;
    }

    MyArrayParent(const MyArrayParent &V)
    {
        count = V.count;
        capacity = V.capacity;
        ptr = new double[capacity];
        for (int i = 0; i < count; i++)
        {
            ptr[i] = V.ptr[i];
        }
    }

    void print()
    {
        cout << "\nMyArrParent, size: " << count << ", values: {";
        int i = 0;
        for (i = 0; i < count; i++)
        {
            cout << ptr[i];
            if (i != count - 1)
                cout << ", ";
        }
        cout << "}";
    }
    void print(int index)
    {
        cout << "\nUnit with index (" << index << ") is " << ptr[index];
    }
};

class MyArrayChild : public MyArrayParent
{
public:
    //используем конструктор родителя. Нужно ли что-то ещё?
    MyArrayChild(int Dimension = 100) : MyArrayParent(Dimension)
    {
        cout << "\nMyArrayChild constructor";
    }

    ~MyArrayChild()
    {
        cout << "\nMyArrayChild destructor\n";
    }

    //удаление элемента
    void RemoveAt(int index = -1)
    {
        if (index == -1)
        {
            count--;
        }
        else if (index > -1)
        {
            count--;
            for (int i = index; i < count; i++)
            {
                ptr[i] = ptr[i + 1];
            }
        }
    }

    //поиск элемента
    int IndexOf(double value, bool bFindFromStart = true)
    {
        if (bFindFromStart)
        {
            for (int i = 0; i < count; i++)
            {
                if (ptr[i] == value)
                {
                    return i;
                }
            }
        }
        else
        {
            for (int i = count - 1; i >= 0; i--)
            {
                if (ptr[i] == value)
                {
                    return i;
                }
            }
        }
        return -1;
    }

    void Clear()
    {
        count = 0;
    }

    //вставка элемента
    void InsertAt(double value, int index = -1)
    {
        if (index == -1)
            push(value);

        if (count < capacity)
        {
            if (index < 0)
            {
                return;
            }
            for (int i = count; i >= 0; i--)
            {
                if (i > index)
                {
                    ptr[i] = ptr[i - 1];
                }
                else
                {
                    ptr[i] = value;
                    count++;
                    break;
                }
            }
        }
    }

    //выделение подпоследовательности
    MyArrayChild SubSequence(int StartIndex = 0, int Length = -1)
    {
        MyArrayChild array;
        if (Length < 0)
        {
            Length = count;
        }
        for (int i = StartIndex; i < StartIndex + Length; i++)
        {
            array.push(ptr[i]);
        }
        return array;
    }

    //функция, которая возвращает индексы всех вхождений максимума в массив
    MyArrayChild IndexOfMax()
    {
        MyArrayChild array;
        double Max = ptr[0];
        for (int i = 0; i < count; i++)
        {
            if (Max < ptr[i])
            {
                Max = ptr[i];
                array.count = 0;
                array.push(i);
            }
            else if (Max == ptr[i])
            {
                array.push(i);
            }
        }
        return array;
    }
};

class MySortedArray : public MyArrayChild
{
protected:
    int RecBinSearch(double value, double left, double right)
    {
        double eps = 0.00001;
        int Middle = (left + right) / 2;
        if (right - left <= 1)
        {
            return Middle;
        }
        if (ptr[Middle] > value)
        {
            return RecBinSearch(value, left, Middle);
        }
        else
        {
            return RecBinSearch(value, Middle, right);
        }
    }
    int ModRecBinSearch(double value, double left, double right)
    {
        int Middle = (left + right) / 2;
        if (right - left <= 1)
        {
            return right;
        }
        if (ptr[Middle] > value)
        {
            return ModRecBinSearch(value, left, Middle);
        }
        else
        {
            return ModRecBinSearch(value, Middle, right);
        }
    }

    int ModBinSearch(double value, double left, double right)
    {
        double search = -1;
        while (left <= right) // пока левая граница не "перескочит" правую
        {
            int mid = (left + right) / 2; // ищем середину отрезка
            if (value == ptr[mid])
            {                 // если ключевое поле равно искомому
                search = mid; // мы нашли требуемый элемент,
                break;        // выходим из цикла
            }
            if (value < ptr[mid]) // если искомое ключевое поле меньше найденной середины
                right = mid - 1;  // смещаем правую границу, продолжим поиск в левой части
            else                  // иначе
                left = mid + 1;   // смещаем левую границу, продолжим поиск в правой части
        }
        if (search == -1)
        {
            return left;
        }
        else
        {
            return search;
        }
    }

public:
    MySortedArray(int Dimension = 100) : MyArrayChild(Dimension) {}
    ~MySortedArray() {}

    int IndexOf(double value, bool bFindFromStart = true)
    {
        return RecBinSearch(value, 0, count);
    }
    void push(double value)
    {
        if (count == 0)
        {
            MyArrayParent::push(value);
        }
        else
        {
            int index = ModBinSearch(value, 0, count);
            InsertAt(value, index);
        }
    }
};

int main()
{

    /*
    MyArrayChild array;
    for (int i = 10; i < 21; i++)
    {
        array.push(i);
    }
    array.print();
    array.InsertAt(34);
    array.print();
    cout << "\nindex of 34: " << array.IndexOf(34);
    array.InsertAt(67);
    array.print();
    array.RemoveAt(1);
    array.print();
    array.SubSequence(0, 7).print();
    array.IndexOfMax().print();
    array.push(67);
    array.IndexOfMax().print();
    array.push(177);
    array.IndexOfMax().print();
   
   */

    MySortedArray g;
    g.push(1);
    g.push(4);
    g.push(5);
    g.print();

    g.push(6);
    g.push(2);
    g.push(3);
    g.print();
    g.push(2);
    g.push(1);
    g.print();

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

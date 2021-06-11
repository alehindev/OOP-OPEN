#include <iostream>
using namespace std;
//узел
template <class T>
class Node
{
protected:
    //закрытые переменные Node N; N.data = 10 вызовет ошибку
    T data;
    //не можем хранить Node, но имеем право хранить указатель
    Node *left;
    Node *right;
    Node *parent;
    //переменная, необходимая для поддержания баланса дерева
    int height;

public:
    //доступные извне переменные и функции
    virtual void setData(T d) { data = d; }
    virtual T getData() { return data; }
    int getHeight() { return height; }
    virtual Node *getLeft() { return left; }
    virtual Node *getRight() { return right; }
    virtual Node *getParent() { return parent; }
    virtual void setLeft(Node *N) { left = N; }
    virtual void setRight(Node *N) { right = N; }
    virtual void setParent(Node *N) { parent = N; }
    //Конструктор. Устанавливаем стартовые значения для указателей
    Node<T>(T n)
    {
        data = n;
        left = right = parent = NULL;
        height = 1;
    }
    Node<T>()
    {
        left = NULL;
        right = NULL;
        parent = NULL;
        data = 0;
        height = 1;
    }
    virtual void print()
    {
        cout << "\n"
             << data;
    }
    virtual void setHeight(int h)
    {
        height = h;
    }
    template <class T1>
    friend ostream &operator<<(ostream &stream, Node<T1> &N);
};
template <class T>
ostream &operator<<(ostream &stream, Node<T> &N)
{
    if()
    {
        stream << "\nNode data: " << N.data << ", height: " << N.height;
    }
    else
    {
        stream << "Node is NULL" << endl;
    }
    return stream;
}

template <class T>
void print(Node<T> *N)
{
    cout << "\n"
         << N->getData();
}

template <class T>
class Tree
{
protected:
    //корень - его достаточно для хранения всего дерева
    Node<T> *root;

public:
    //доступ к корневому элементу
    virtual Node<T> *getRoot() { return root; }
    //конструктор дерева: в момент создания дерева ни одного узла нет, корень смотрит

    Tree<T>() { root = NULL; }
    //рекуррентная функция добавления узла. Устроена аналогично, но вызывает сама себя - добавление в левое или правое поддерево
    virtual Node<T> *Add_R(Node<T> *N)
    {
        return Add_R(N, root);
    }
    virtual Node<T> *Add_R(Node<T> *N, Node<T> *Current)
    {
        if (N == NULL)
            return NULL;
        if (root == NULL)
        {
            root = N;
            return N;
        }
        if (Current->getData() > N->getData())
        {
            //идем влево
            if (Current->getLeft() != NULL)
                Current->setLeft(Add_R(N, Current->getLeft()));
            else
                Current->setLeft(N);
            Current->getLeft()->setParent(Current);
        }
        if (Current->getData() < N->getData())
        {
            //идем вправо
            if (Current->getRight() != NULL)
                Current->setRight(Add_R(N, Current->getRight()));
            else
                Current->setRight(N);
            Current->getRight()->setParent(Current);
        }
        if (Current->getData() == N->getData())
            //нашли совпадение
            ;
        //для несбалансированного дерева поиска
        return Current;
    }
    //функция для добавления числа. Делаем новый узел с этими данными и вызываем нужную функцию добавления в дерево
    virtual void Add(int n)
    {
        Node<T> *N = new Node<T>;
        N->setData(n);
        Add_R(N);
    }
    //три обхода дерева
    virtual void PreOrder(Node<T> *N, void (*f)(Node<T> *))
    {
        if (N != NULL)
            f(N);
        if (N != NULL && N->getLeft() != NULL)
            PreOrder(N->getLeft(), f);
        if (N != NULL && N->getRight() != NULL)
            PreOrder(N->getRight(), f);
    }
    //InOrder-обход даст отсортированную последовательность
    virtual void InOrder(Node<T> *N, void (*f)(Node<T> *))
    {
        if (N != NULL && N->getLeft() != NULL)
            InOrder(N->getLeft(), f);
        if (N != NULL)
            f(N);
        if (N != NULL && N->getRight() != NULL)
            InOrder(N->getRight(), f);
    }
    virtual void PostOrder(Node<T> *N, void (*f)(Node<T> *))
    {
        if (N != NULL && N->getLeft() != NULL)
            PostOrder(N->getLeft(), f);
        if (N != NULL && N->getRight() != NULL)
            PostOrder(N->getRight(), f);
        if (N != NULL)
            f(N);
    }
    virtual Node<T> *minTree()
    {
        if (root == NULL)
        {
            return NULL;
        }
        else
        {
            Node<T> *temp = root;
            while (temp->getLeft() != NULL)
            {
                temp = temp->getLeft();
            }
            return temp;
        }
    }
    virtual Node<T> *maxTree()
    {
        if (root == NULL)
        {
            return NULL;
        }
        else
        {
            Node<T> *temp = root;
            while (temp->getRight() != NULL)
            {
                temp = temp->getRight();
            }
            return temp;
        }
    }
    virtual void filteredTree(Tree<T> &newTree)
    {
        /*
        if (N != NULL && N->getLeft() != NULL)
            InOrder(N->getLeft(), f);
        if (N != NULL)
            f(N);
        if (N != NULL && N->getRight() != NULL)
            InOrder(N->getRight(), f);
    */
    }

    virtual Node<T> *search(T el, Node<T> *temp)
    {
        while (temp != NULL)
        {
            if (temp->getData() > el)
            {
                temp = temp->getLeft();
                search(el, temp);
            }
            else if (temp->getData() < el)
            {
                temp = temp->getRight();
                search(el, temp);
            }
            else
            {
                return temp;
            }
        }
        return NULL;
    }
    /*
    virtual Node<T> *deletChain()
    {
        if (root == NULL)
        {
            return NULL;
        }
        else
        {
            Node<T> *temp = root;
            int z = 0;
            while (z < 2)
            {
                if (rand() % 2 == 1)
                {
                    if (temp->getLeft() != NULL)
                    {
                        temp = temp->getLeft();
                    }
                }
                else
                {
                    if (temp->getRight() != NULL)
                    {
                        temp = temp->getRight();
                    }
                }
                z++;
            }
            if (temp->getParent() == NULL)
            {
                temp->getRight()->setParent(NULL);
                temp->getRight()->setLeft(temp->getLeft());
                temp->getLeft()->setParent(NULL);
                return temp;
            }
            else if (temp->getParent()->getLeft() == temp)
            {
                if (temp->getRight() != NULL)
                {
                    if (temp->getRight()->getLeft() == NULL)
                    {
                        //
                    }
                }
                else
                {
                    if (temp->getLeft() == NULL)
                    {
                        temp->getParent()->setLeft(NULL);
                    }
                    else
                    {
                        temp->getParent()->setLeft() = temp->getLeft();
                        temp->getLeft()->setParent() = temp->getParent();
                    }
                }
            }
            else
            {
            }
            return temp;
        }
    }
    */
    template <class T1>
    friend ostream &operator<<(ostream &s, Tree<T1> &el)
    {
        Node<T1> *current;
        for (current = el.head; current != NULL; current = current->Next())
            s << *current << "; ";
        return s;
    }
};
int main()
{
    Tree<int> myTree;
    myTree.Add(1);
    myTree.Add(2);
    myTree.Add(3);
    cout << *myTree.maxTree() << endl;
    cout << *myTree.minTree() << endl;
    int a = 4;
    cout << *myTree.search(a, myTree.getRoot());
    return 0;
}
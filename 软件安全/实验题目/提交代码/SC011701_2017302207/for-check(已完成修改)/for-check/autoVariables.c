void foo(int **a)
{
    int b = 1;
    **a = b;//�޸�*a = &b;
}

int main()
{
    int *c;
    foo(&c);
}

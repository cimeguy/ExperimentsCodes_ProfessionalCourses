int foo(int *p)
{
   // int a = p;
    return p + 4;//?
}

int main()
{
    int i[10];
    foo(i);
}

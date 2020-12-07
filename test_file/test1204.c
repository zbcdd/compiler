
int main()
{
    int i = 0;
    while(i < 100)
        i = i + 1;
    
    for (i = 0; i < 10; i = i + 1)
    {
        i = i + 1;
    }
    int j = 0;
    int a;
    if(j < 0 || j > 0 && i == 2)
    {
        a = 1;
    }
    else if (j > 0)
    {
        a = 2;
    }
    else
    {
        a = 3;
    }
    // cout << j;
    // int k = 0;
    // if (!(k == 0))
    // {
    //     cout << k;
    // }
    return 0;
}

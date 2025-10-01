#include <iostream>
#include <cmath>

using namespace std;
int main()
{
    float x, y, R, S, pi = 3.14159, C;
    setlocale(LC_ALL, "Russian");

    cout << "ВВЕДИТЕ Х: ";
    cin >> x;
    cout << "ВВЕДИТЕ У: ";
    cin >> y;

    cout << "R = ctg(pi*x) - sec(y) = ";
    R = 1 / (tan(pi * x)) - 1 / (cos(y));
    cout << R << endl;

    cout << "S = In(2^x) = ";
    S = logf(pow(2, x));
    cout << S << endl;

    cout << "МАКСИМАЛЬНОЕ ИЗ R И S: ";
    C = fmax(R, S);
    cout << C << endl;

    system("pause");
    return 0;
}
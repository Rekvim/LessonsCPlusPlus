### Задание

Напишите функцию `Average` для вычисления среднего арифметического вектора чисел. Считайте, что среднее арифметическое пустого массива равно нулю.

В заготовке кода вам даны примеры использования функции.

- Делить на ноль нельзя. Поэтому среднее арифметическое пустого массива примите равным нулю;
- Не забудьте объявить библиотеку, содержащую алгоритм `accumulate`;
- Результатом функции `Average` должно быть вещественное число без округления. Передайте в `accumulate` начальное значение 0.0, чтобы сделать результат выражения вещественным числом;
- Для вычисления среднего арифметического массива поделите сумму элементов на размер массива;
- Размер вектора можно определить с помощью метода `size()`.

#### Код к заданию
```cpp
#include <iostream>
#include <vector>

using namespace std;

double Average(const vector<int>& xs) {
    // Напишите реализацию функции.
}

int main() {
    cout << Average({}) << endl;        // Результат: 0.
    cout << Average({2, 3}) << endl;    // Результат: 2.5.
    cout << Average({7, 2, 6}) << endl; // Результат: 5.
}
```

<details><summary><strong>Решение</strong></summary>

```cpp
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

double Average(const vector<int>& xs) {
    if (xs.empty()) {
        return 0;
    }
    return accumulate(xs.begin(), xs.end(), 0.0) / xs.size();
}

int main() {
    cout << Average({}) << endl;
    cout << Average({2, 5}) << endl;
    cout << Average({7, 2, 6}) << endl;
}
```
</details> 
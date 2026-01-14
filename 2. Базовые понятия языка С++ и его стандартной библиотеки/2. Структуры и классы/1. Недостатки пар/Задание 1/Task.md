### Задание 1

Дана функция `PrintWorryCount`. Перепишите её, используя `count`.
```cpp
#include <iostream>
#include <vector>

using namespace std;

void PrintWorryCount(const vector<bool>& is_nervous) {
    // подсчитываем количество элементов в векторе is_nervous, равных true
    int worry_count = 0;
    for (bool status : is_nervous) {
        if (status) {
            ++worry_count;
        }
    }
    cout << worry_count << endl;
}

int main() {
    PrintWorryCount({true, true, false, true});
    return 0;
}
```

<details><summary><strong>Решение</strong></summary>

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void PrintWorryCount(const vector<bool>& is_nervous) {
    cout << count(is_nervous.begin(), is_nervous.end(), true) << endl;
}

int main() {
    PrintWorryCount({true, true, false, true});
    return 0;
}
```
</details> 

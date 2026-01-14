### Задание 2

Напишите функцию, которая принимает вектор строк и возвращает число строк, начинающихся на большую или маленькую английскую букву "a".
Примеры

Передан вектор строк: "Anna"s, "Banny"s, "Clara"s, "all others"s. Ответ: 2.

Передан вектор строк: "A"s, "a"s, ""s, "Baaaaa"s, "Abraham". Ответ: 3.

Передан пустой вектор строк. Ответ: 0.


Напишите вспомогательную функцию `StartsWithA` и примените её совместно с `count_if`. В функции `StartsWithA` перед тем как получать первый символ, проверьте, что строка не пустая.
```cpp
bool StartsWithA(const string& str) {
    /* Возвращает true, если str начинается с символа 'A' или 'a' */
} 

```

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int CountStartsWithA(const vector<string>& xs) {
    // посчитайте число строк, начинающихся на букву A или a
}

int main() {
    // не меняйте тело main
    cout << CountStartsWithA({"And"s, "another"s, "one"s, "gone"s, "another"s,
                              "one"s
                              "bites"s,
                              "the"s, "dust"s});

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
    // не меняйте содержимое функции main
    PrintWorryCount({true, true, false, true});
    return 0;
}
```
</details> 
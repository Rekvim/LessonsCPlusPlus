### Задание

Напишите функцию `AddStopWords`, которая принимает строку-запрос и множество стоп-слов и возвращает новую строку. Новая строка состоит из запроса, к которому приписаны стоп-слова. Стоп-слова разделяются пробелами, и перед каждым стоит дефис.
Для решения задачи не используйте циклы, их заменит алгоритм `accumulate`.

#### Пример

| Запрос | Стоп-слова| Выходная строка |
|:-:|:-:|:-:|
| "some tasty oranges" | {"of", "in"} | "some tasty oranges -in -of" |
| "" | {"of", "in"} | " -in -of" |
| "some tasty oranges" | {} | "some tasty oranges" |

#### Ограничения

- Сигнатура функции дана в заготовке кода, не меняйте её:

```cpp
string AddStopWords(const string& query, const set<string>& stop_words); 
```

- Обратите внимание на расстановку пробелов в примерах. Ваша функция должна ставить их так же.

#### Подсказка:
- задачу не решить простой версией `accumulate`, пригодится свёрточная функция-помощница;
- обратите внимание на то, как правильно использовать `accumulate`: вначале передаются итераторы на контейнер, затем начальное значение и в конце свёрточная функция. Свёрточная функция всегда имеет два параметра;
- функция-помощница должна склеивать две строки через " -"s. Например, если ей переданы строки `aaa`, `bbb`, то на выходе должно получиться `aaa` `-bbb`;
- в качестве начального значения в `accumulate` можно передать запрос;
- применяйте `accumulate` к контейнеру `set`, содержащему стоп-слова. Нужно объединить его значения.

#### Код к заданию
```cpp
#include <set>
#include <string>

using namespace std;

string AddStopWords(const string& query, const set<string>& stop_words) {
    // Напишите тело функции.
}
```

<details><summary><strong>Решение</strong></summary>

```cpp
#include <set>
#include <string>
#include <numeric>

using namespace std;


string FoldWithMinus(string left, string right) {
    
    return left + " -"s + right;
}


string AddStopWords(const string& query, const set<string>& stop_words) {
    
    return std::accumulate(stop_words.begin(), stop_words.end(), query, FoldWithMinus);
}
```
</details> 
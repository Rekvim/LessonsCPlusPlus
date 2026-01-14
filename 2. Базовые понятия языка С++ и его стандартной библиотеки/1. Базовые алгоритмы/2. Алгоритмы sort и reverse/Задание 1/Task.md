### Задание

По закону Неверландии кандидаты в парламент сообщают только своё имя и возраст. В избирательном бюллетене предпочтение отдаётся возрасту: старшие кандидаты идут первыми. Кандидаты одного возраста сортируются в бюллетене по алфавиту, но опять же в обратном порядке.В стандартном вводе будет информация о кандидатах в нужном объёме — их имена и возрасты. Ваша задача напечатать в cout избирательный бюллетень, который содержит только имена кандидатов в нужном порядке.

Формат входных данных
Вначале в cin передаётся количество кандидатов. Затем для каждого кандидата — его имя и возраст. 
Порядок, в котором будут прочитаны кандидаты, может быть любым. Ваша задача — вывести их в правильном порядке.

Формат выходных данных
Выводите только имена кандидатов. Каждое — на отдельной строке.

Пример
Входные данные:
```
4
John 30
Elvis 45
Holly 45
Ronny 25 

Правильный ответ:
Holly
Elvis
John
Ronny 
```
#### Код к заданию
```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
    int count;
    cin >> count;
    for (int i = 0; i < count; ++i) {
        string name;
        int age;
        cin >> name >> age;
        // сохраните в вектор пар
    }

    // Выведите только имена в порядке убывания возраста
    // Имена людей одинакового возраста нужно вывести в порядке, обратном алфавитному
}
```

<details><summary><strong>Решение</strong></summary>

```cpp
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main() {
    
    vector<pair<int, string>> people;
    int count;
    
    cin >> count;
    
    for (int i = 0; i < count; ++i) {
        string name;
        int age;
        cin >> name >> age;
        people.push_back({age, name});
    }

    sort(people.begin(), people.end());
    reverse(people.begin(), people.end());

    for (const auto& person : people) {
        cout << person.second << endl;
    }
}
```
</details> 
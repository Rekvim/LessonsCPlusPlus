### Задание

Дана функция `CountNamesLong`. Она выясняет, какие слова из списка содержатся во множестве, и возвращает ответ в виде вектора единиц и нулей: если слово есть во множестве, в ответе будет единица, иначе — ноль. 

В функции `main` представлен тест для замера времени работы этой функции: функция работает корректно, но недостаточно быстро.

Напишите функцию `CountNames` с такой же сигнатурой и функционалом, которая будет работать значительно быстрее.

#### Примечание

В тесте вы видите использование библиотеки `<chrono>`. Она содержит функции, для работы с понятием времени. Будьте осторожны при запуске теста — он может работать довольно долго. При необходимости используйте кнопку «Остановить запуск» в тренажере. В будущих темах мы ещё вернёмся к изучению этой библиотеки.

#### Как будет тестироваться ваш код

Тренажёр запустит тест, аналогичный предоставленному в прекоде, и проверит, что ваша функция работает корректно и быстрее, чем исходная. При проверке функция main будет заменена функцией из тренажёра.

Не удаляйте и не изменяйте код функции `CountNamesLong`, чтобы программа скомпилировалась без ошибок.

#### Подсказка

Примените встроенный метод множества `count`

#### Код к заданию
```cpp
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

const int SAMPLE_COUNT = 5;


vector<int> CountNames(const set<string>& storage, const vector<string>& candidates) {
    
    vector<int> output;
    
    for (auto& name: candidates) {
        
        output.push_back(storage.count(name));
    }
    
    return output;
}


vector<int> CountNamesLong(const set<string>& storage, const vector<string>& candidates) {
    
    vector<int> output;
    
    for (auto& name: candidates) {
        
        output.push_back(count(storage.begin(), storage.end(), name));
    }
    
    return output;
}

int main() {
    
    set<string> s;
    
    vector<string> v;
    
    string stra = ""s;
    
    string strb = ""s;


    
    for (int j = 0; j < 10000; ++j) {
        
        s.insert(stra);
        
        stra += "a"s;
        
        if (j % 2 == 0) {
            
            v.push_back(strb);
            
            strb += "b"s;
        
        } else {
            
            v.push_back(stra);
        }
    }

    
    cout << "Testing fast version"s << endl;
    
    for (int i = 0; i < SAMPLE_COUNT; ++i) {
        
        auto begin = chrono::steady_clock::now();
        
        CountNames(s, v);
        
        auto end = chrono::steady_clock::now();
        
        cout << "Time difference = "s << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]"s << endl;
    }

    
    cout << "Testing slow version"s << endl;
    
    for (int i = 0; i < SAMPLE_COUNT; ++i) {
        
        auto begin = chrono::steady_clock::now();
        
        CountNamesLong(s, v);
        
        auto end = chrono::steady_clock::now();
        
        cout << "Time difference Long = "s << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]"s << endl;
    }
}
```

<details><summary><strong>Решение</strong></summary>

```cpp
#include <algorithm>
#include <chrono>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

const int SAMPLE_COUNT = 5;

/**
 * Определяет, какие имена из вектора candidates содержатся внутри множества storage.
 * Возвращает вектор, где каждому элементу из candidates соответствует одно из чисел:
 *  0 - элемент из candidates отсутствует в storage
 *  1 - элемент из candidates присутствует внутри storage
 */
vector<int> CountNamesLong(const set<string>& storage, const vector<string>& candidates) {
    // Эта функция работает правильно, но недостаточно быстро.
    // Не удаляйте и не изменяйте код этой функции.
    
    vector<int> output;
    for (auto& name : candidates) {
        // Подсчитываем количество вхождений name в storage стандартным алгоритмом count
        output.push_back(count(storage.begin(), storage.end(), name));
    }
    return output;
}

// Напишите тело функции CountNames, которая выдаёт результат, аналогичный CountNamesLong,
// но выполняется быстрее за счёт использования встроенного алгоритма count вместо общего
vector<int> CountNames(const set<string>& storage, const vector<string>& candidates) {
    vector<int> output;
    // Напишите реализацию здесь
    return output;
}

int main() {
    set<string> s;
    vector<string> v;
    string stra;
    string strb;

    for (int j = 0; j < 10000; ++j) {
        s.insert(stra);
        stra += "a"s;
        if (j % 2 == 0) {
            v.push_back(strb);
            strb += "b"s;
        } else {
            v.push_back(stra);
        }
    }

    cout << "Testing slow version" << endl;
    // Замеряем время работы несколько раз, так как оно может отличаться от запуска к запуску
    for (int i = 0; i < SAMPLE_COUNT; ++i) {
        // Засекаем время запуска функции
        auto begin = chrono::steady_clock::now();
        CountNamesLong(s, v);
        // Засекаем время завершения функции
        auto end = chrono::steady_clock::now();

        // Выводим время работы в микросекундах
        cout << "Time difference Long = "s
             << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]"s << endl;
    }

    // Вы можете замерить время работы функции CountNames и сравнить её с временем
    // работы CountNamesLong
}
```
</details> 
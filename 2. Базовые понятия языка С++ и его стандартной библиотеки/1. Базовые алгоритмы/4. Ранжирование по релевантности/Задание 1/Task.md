### Задание

Измените поисковую систему, чтобы она выдавала не все документы, а определённое количество наиболее релевантных страниц. Это количество задайте константной переменной `MAX_RESULT_DOCUMENT_COUNT` со значением 5.
```cpp
#include <...>

using namespace std;

// Объявите магическое число MAX_RESULT_DOCUMENT_COUNT вверху кода,
// чтобы оно было доступно во всех функциях программы.
const int MAX_RESULT_DOCUMENT_COUNT = 5; 
```
Искать и выдавать наиболее релевантные документы будет функция FindTopDocuments. Она должна иметь следующий вид:
```cpp
// Возвращает самые релевантные документы в виде вектора пар {id, релевантность}
vector<pair<int, int>> FindTopDocuments(
    const vector<pair<int, vector<string>>>& documents,
    const set<string>& stop_words, 
    const string& raw_query) {
    ...
} 
```
Параметры функции таковы:
- `documents` — вектор, хранящий идентификаторы и содержимое документов,
- `stop_words` — множество стоп-слов,
- `raw_query` — сам запрос.
- возвращаемое значение — вектор из пар: релевантность-идентификатор.

В `main` вызов функции `FindDocuments` замените на `FindTopDocuments`. При этом позаботьтесь, чтобы результат функции обрабатывался корректно.
Функция должна возвращать документы в строго определённом порядке — по убыванию релевантности. Для документов с совпадающей релевантностью — по убыванию идентификатора. Документы с нулевой релевантностью функция не находит, поэтому выводить их не нужно.
#### Формат входных и выходных данных

Первая строка содержит стоп-слова, разделённые пробелом. Вторая строка содержит целое число N, задающее количество документов. Следующие N строк содержат текст документов, в которых слова разделяются одним пробелом. Затем идёт строка S поискового запроса.
Программа должна вывести информацию о топ-5 самых релевантных документов соответствующих поисковому запросу S, отсортированных по убыванию релевантности, как показано в примере ниже.
Ввод
```
a an on the in is has been are with for from have be was
4
a small curly guinea pig with grey hair has been found
a young 50 year old crocodile wants to make friends
a strange brown creature was seen in the box of oranges
a strange animal with big ears is building a house for its friends
cheburashka with big ears likes oranges 
```
Вывод
```
{ document_id = 3, relevance = 2 }
{ document_id = 2, relevance = 1 } 
```
#### Как будет тестироваться ваш код

Тренажёр передаст программе на вход различные варианты документов и поисковых запросов и сравнит выводимые данные с ожидаемыми. Чтобы ваша программа успешно прошла проверку, она должна упорядочивать документы с одинаковой релевантностью по убыванию id. 

Также тренажёр проверит, что в программе есть функция `FindTopDocuments`.

#### Подсказка

- функция `FindDocuments` вам больше не нужна. Вместо этого вам понадобятся две функции: `FindAllDocuments` и `FindTopDocuments`;
- `FindAllDocuments` очень похожа на `FindDocuments`, но возвращает вектор пар, в которых первой идёт релевантность. Это нужно, чтобы получить правильную сортировку в функции `FindTopDocuments`;
- чтобы найти наиболее релевантные документы, нужно получить все документы и отсортировать их. С этим поможет алгоритм `sort`;
- `sort` отсортирует элементы по возрастанию. Чтобы изменить порядок на противоположный, можно применить `reverse`;
- не забудьте включить библиотеку, в которой хранятся алгоритмы `sort` и `reverse`;
- если размер вектора окажется больше `MAX_RESULT_DOCUMENT_COUNT`, уменьшите его методом `resize`;
- в функции `main` правильно разберите пару: теперь на первом месте должна возвращаться релевантность, а на втором – id документа.


#### Код к заданию
```cpp
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string ReadLine() {
    string s;
    getline(cin, s);
    return s;
}

int ReadLineWithNumber() {
    int result = 0;
    cin >> result;
    ReadLine();
    return result;
}

vector<string> SplitIntoWords(const string& text) {
    vector<string> words;
    string word;
    for (const char c : text) {
        if (c == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }

    return words;
}

set<string> ParseStopWords(const string& text) {
    set<string> stop_words;
    for (const string& word : SplitIntoWords(text)) {
        stop_words.insert(word);
    }
    return stop_words;
}

vector<string> SplitIntoWordsNoStop(const string& text, const set<string>& stop_words) {
    vector<string> words;
    for (const string& word : SplitIntoWords(text)) {
        if (stop_words.count(word) == 0) {
            words.push_back(word);
        }
    }
    return words;
}

void AddDocument(vector<pair<int, vector<string>>>& documents, const set<string>& stop_words,
                 int document_id, const string& document) {
    const vector<string> words = SplitIntoWordsNoStop(document, stop_words);
    documents.push_back(pair<int, vector<string>>{document_id, words});
}

set<string> ParseQuery(const string& text, const set<string>& stop_words) {
    set<string> query_words;
    for (const string& word : SplitIntoWordsNoStop(text, stop_words)) {
        query_words.insert(word);
    }
    return query_words;
}

int MatchDocument(const pair<int, vector<string>>& content, const set<string>& query_words) {
    if (query_words.empty()) {
        return 0;
    }
    set<string> matched_words;
    for (const string& word : content.second) {
        if (matched_words.count(word) != 0) {
            continue;
        }
        if (query_words.count(word) != 0) {
            matched_words.insert(word);
        }
    }

    // Преобразовываем беззнаковое число типа size_t в int используя
    // static_cast<int>
    return static_cast<int>(matched_words.size());
}

// Для каждого документа возвращает его id и релевантность
vector<pair<int, int>> FindDocuments(const vector<pair<int, vector<string>>>& documents,
                                     const set<string>& stop_words, const string& query) {
    const set<string> query_words = ParseQuery(query, stop_words);
    vector<pair<int, int>> matched_documents;
    for (const auto& document : documents) {
        const int relevance = MatchDocument(document, query_words);
        if (relevance > 0) {
            matched_documents.push_back({document.first, relevance});
        }
    }
    return matched_documents;
}

/*
// Для каждого документа возвращает его релевантность и id
vector<pair<int, int>> FindAllDocuments(const vector<pair<int, vector<string>>>& documents,
    const set<string>& query_words)
{
    // Превратите функцию FindDocuments в FindAllDocuments
    // Первым элементом возвращаемых пар идёт релевантность документа, а вторым - его id
}
*/

/*
// Возвращает топ-5 самых релевантных документов в виде пар: {id, релевантность}
vector<pair<int, int>> FindTopDocuments(const vector<pair<int, vector<string>>>& documents,
                                        const set<string>& stop_words, const string& raw_query) {
    // Напишите функцию, используя FindAllDocuments
}
*/

int main() {
    const string stop_words_joined = ReadLine();
    const set<string> stop_words = ParseStopWords(stop_words_joined);

    // Чтение документов
    vector<pair<int, vector<string>>> documents;
    const int document_count = ReadLineWithNumber();
    for (int document_id = 0; document_id < document_count; ++document_id) {
        AddDocument(documents, stop_words, document_id, ReadLine());
    }

    const string query = ReadLine();
    // Вместо FindDocuments используйте FindTopDocuments
    for (auto [document_id, relevance] : FindDocuments(documents, stop_words, query)) {
        cout << "{ document_id = "s << document_id << ", relevance = "s << relevance << " }"s
             << endl;
    }
}
```

<details><summary><strong>Решение</strong></summary>

```cpp
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

string ReadLine() {
    string s;
    getline(cin, s);
    return s;
}

int ReadLineWithNumber() {
    int result = 0;
    cin >> result;
    ReadLine();
    return result;
}

vector<string> SplitIntoWords(const string& text) {
    vector<string> words;
    string word;
    for (const char c : text) {
        if (c == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }

    return words;
}

set<string> ParseStopWords(const string& text) {
    set<string> stop_words;
    for (const string& word : SplitIntoWords(text)) {
        stop_words.insert(word);
    }
    return stop_words;
}

vector<string> SplitIntoWordsNoStop(const string& text, const set<string>& stop_words) {
    vector<string> words;
    for (const string& word : SplitIntoWords(text)) {
        if (stop_words.count(word) == 0) {
            words.push_back(word);
        }
    }
    return words;
}

void AddDocument(vector<pair<int, vector<string>>>& documents, const set<string>& stop_words,
                 int document_id, const string& document) {
    const vector<string> words = SplitIntoWordsNoStop(document, stop_words);
    documents.push_back(pair<int, vector<string>>{document_id, words});
}

set<string> ParseQuery(const string& text, const set<string>& stop_words) {
    set<string> query_words;
    for (const string& word : SplitIntoWordsNoStop(text, stop_words)) {
        query_words.insert(word);
    }
    return query_words;
}

int MatchDocument(const pair<int, vector<string>>& content, const set<string>& query_words) {
    if (query_words.empty()) {
        return 0;
    }
    set<string> matched_words;
    for (const string& word : content.second) {
        if (matched_words.count(word) != 0) {
            continue;
        }
        if (query_words.count(word) != 0) {
            matched_words.insert(word);
        }
    }

    // Преобразовываем беззнаковое число типа size_t в int используя
    // static_cast<int>
    return static_cast<int>(matched_words.size());
}

// Для каждого документа возвращает его id и релевантность
vector<pair<int, int>> FindDocuments(const vector<pair<int, vector<string>>>& documents,
                                     const set<string>& stop_words, const string& query) {
    const set<string> query_words = ParseQuery(query, stop_words);
    vector<pair<int, int>> matched_documents;
    for (const auto& document : documents) {
        const int relevance = MatchDocument(document, query_words);
        if (relevance > 0) {
            matched_documents.push_back({document.first, relevance});
        }
    }
    return matched_documents;
}

const int MAX_RESULT_DOCUMENT_COUNT = 5; // Задаем константу для максимального количества документов

// Остальной код остается таким же как в предыдущем решении

// Используем функцию FindAllDocuments для получения релевантности и id всех документов
vector<pair<int, int>> FindAllDocuments(const vector<pair<int, vector<string>>>& documents,
                                         const set<string>& query_words) {
    vector<pair<int, int>> matched_documents;
    for (const auto& document : documents) {
        const int relevance = MatchDocument(document, query_words);
        if (relevance > 0) {
            matched_documents.push_back({document.first, relevance});
        }
    }
    return matched_documents;
}

// Функция FindTopDocuments возвращает топ-5 самых релевантных документов
vector<pair<int, int>> FindTopDocuments(const vector<pair<int, vector<string>>>& documents,
                                         const set<string>& stop_words, const string& raw_query) {
    const set<string> query_words = ParseQuery(raw_query, stop_words);
    vector<pair<int, int>> all_documents = FindAllDocuments(documents, query_words);

    // Сортируем документы по убыванию релевантности, а в случае равенства - по убыванию ID
    sort(all_documents.begin(), all_documents.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        if (a.second != b.second) {
            return a.second > b.second;  // сначала сортировка по релевантности
        }
        return a.first > b.first;  // затем по ID
    });

    // Уменьшаем размер до максимального количества документов (в данном случае до 5)
    if (all_documents.size() > MAX_RESULT_DOCUMENT_COUNT) {
        all_documents.resize(MAX_RESULT_DOCUMENT_COUNT);
    }

    return all_documents;
}
int main() {
    const string stop_words_joined = ReadLine();
    const set<string> stop_words = ParseStopWords(stop_words_joined);

    // Чтение документов
    vector<pair<int, vector<string>>> documents;
    const int document_count = ReadLineWithNumber();
    for (int document_id = 0; document_id < document_count; ++document_id) {
        AddDocument(documents, stop_words, document_id, ReadLine());
    }

    const string query = ReadLine();
    // Вместо FindDocuments используйте FindTopDocuments
    for (auto [document_id, relevance] : FindTopDocuments(documents, stop_words, query)) {
        cout << "{ document_id = "s << document_id << ", relevance = "s << relevance << " }"s
             << endl;
    }
}
```
</details> 
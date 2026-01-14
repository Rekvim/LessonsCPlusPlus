### Задание 1

Теперь вы готовы закончить рефакторинг самостоятельно. Сделайте функцию `FindAllDocuments` приватным методом, а `FindTopDocuments` — публичным. Константу `MAX_RESULT_DOCUMENT_COUNT`, структуру Document и компаратор `HasDocumentGreaterRelevance` оставьте пока снаружи класса. 

Функцию `MatchDocument`, которая вызывается из `FindAllDocuments`, нужно тоже сделать методом класса. Она принимает структуру `DocumentContent`, объявленную внутри `SearchServer`. При этом `MatchDocument` не требуется доступ ни к вектору документов, ни к множеству стоп-слов. Методы, которым не нужен доступ к полям класса, следует объявлять статическими, написав перед ними ключевое слово `static`:
```cpp
class SearchServer {
private:
    ...
    static int MatchDocument(const DocumentContent& content, const set<string>& query_words) {
        // Внутри функции MatchDocument не требуется доступ ни к данным
        // текущего объекта, ни к его методам. Поэтому он должен быть статическим
        ...
    }
}; 
```
Не забудьте о функции `main`. Используйте уже готовую функцию `CreateSearchServer`, чтобы создать `SearchServer`. Прочитайте строку поискового запроса из `cin` и вызовите метод `FindTopDocuments`. Выведите id и релевантность найденных документов так же, как вы это делали раньше.

Формат входных и выходных данных

Первая строка содержит стоп-слова, разделённые пробелом. Вторая строка содержит целое число N, задающее количество документов. Следующие N строк содержат текст документов, в которых слова разделяются одним пробелом. Затем идёт строка S поискового запроса.

Программа должна вывести информацию о топ-5 самых релевантных документов соответствующих поисковому запросу S, отсортированных по убыванию релевантности, как показано в примерах ниже.

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
Как будет тестироваться ваш код

Тренажёр передаст вашей программе входные данные через стандартный поток ввода и сравнит результат её работы с ожидаемым. Он также проверит работу публичных методов класса `SearchServer`.

#### Подсказка

1. Перенесите `FindAllDocuments` в приватную часть класса, оставьте только один параметр — множество query_words. Переделать нужно все участки кода, в которых используется массив `documents`, множество `stop_words` и функция (теперь уже метод) `SplitIntoWordsNoStop`;
2. Перенесите `FindTopDocuments` в публичную часть класса и проделайте те же преобразования;

3. Перенесите функцию `MatchDocument` в приватную часть класса, сделав её статическим методом;

4. Функцию `ParseQuery` тоже нужно сделать методом класса;

5. В функции `main` вызовите `CreateSearchServer` и положите результат в переменную (пока не константную!). Затем вызовите метод `FindTopDocuments` и запустите цикл по его результату с выводом ответа.

Все используемые в методах класса сущности — константы, типы, функции — объявите до кода класса.

```cpp
int main() {
    // Создаём поисковую систему
    SearchServer search_server;
    
    // Добавляем в неё несколько документов
    search_server.AddDocument(1, "brown cat with grey hair"s);
    search_server.AddDocument(2, "green parrot with yellow feathers"s);
} 
```

#### Код к заданию

```cpp
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
 
using namespace std;
 
const int MAX_RESULT_DOCUMENT_COUNT = 5;
 
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
 
struct Document {
    int id;
    int relevance;
};
 
bool HasDocumentGreaterRelevance(const Document& lhs, const Document& rhs) {
    return lhs.relevance > rhs.relevance;
}
 
class SearchServer {
public:
    void SetStopWords(const string& text) {
        for (const string& word : SplitIntoWords(text)) {
            stop_words_.insert(word);
        }
    }
 
    void AddDocument(int document_id, const string& document) {
        const vector<string> words = SplitIntoWordsNoStop(document);
        documents_.push_back({document_id, words});
    }
 
    vector<Document> FindTopDocuments(const string& raw_query) {
        const set<string> query_words = ParseQuery(raw_query);
        auto matched_documents = FindAllDocuments(query_words);
 
        sort(matched_documents.begin(), matched_documents.end(), HasDocumentGreaterRelevance);
        if (matched_documents.size() > MAX_RESULT_DOCUMENT_COUNT) {
            matched_documents.resize(MAX_RESULT_DOCUMENT_COUNT);
        }
        return matched_documents;
    }
 
private:
    struct DocumentContent {
        int id = 0;
        vector<string> words;
    };
 
    vector<DocumentContent> documents_;
 
    set<string> stop_words_;
 
    bool IsStopWord(const string& word) {
        return stop_words_.count(word) > 0;
    }
 
    vector<string> SplitIntoWordsNoStop(const string& text) {
        vector<string> words;
        for (const string& word : SplitIntoWords(text)) {
            if (!IsStopWord(word)) {
                words.push_back(word);
            }
        }
        return words;
    }
 
    set<string> ParseQuery(const string& text) {
        set<string> query_words;
        for (const string& word : SplitIntoWordsNoStop(text)) {
            query_words.insert(word);
        }
        return query_words;
    }
 
    vector<Document> FindAllDocuments(const set<string>& query_words) {
        vector<Document> matched_documents;
        for (const auto& document : documents_) {
            const int relevance = MatchDocument(document, query_words);
            if (relevance > 0) {
                matched_documents.push_back({document.id, relevance});
            }
        }
        return matched_documents;
    }
 
    static int MatchDocument(const DocumentContent& content, const set<string>& query_words) {
        if (query_words.empty()) {
            return 0;
        }
        set<string> matched_words;
        for (const string& word : content.words) {
            if (matched_words.count(word) != 0) {
                continue;
            }
            if (query_words.count(word) != 0) {
                matched_words.insert(word);
            }
        }
        return static_cast<int>(matched_words.size());
    }
};
 
SearchServer CreateSearchServer() {
    SearchServer search_server;
    search_server.SetStopWords(ReadLine());
 
    const int document_count = ReadLineWithNumber();
    for (int document_id = 0; document_id < document_count; ++document_id) {
        search_server.AddDocument(document_id, ReadLine());
    }
 
    return search_server;
}
 
int main() {
    SearchServer search_server = CreateSearchServer();
 
    const string query = ReadLine();
    for (const auto& [document_id, relevance] : search_server.FindTopDocuments(query)) {
        cout << "{ document_id = "s << document_id << ", "
             << "relevance = "s << relevance << " }"s << endl;
    }
}
```

<details><summary><strong>Решение</strong></summary>

```cpp
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
 
using namespace std;
 
const int MAX_RESULT_DOCUMENT_COUNT = 5;
 
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
 
struct Document {
    int id;
    int relevance;
};
 
bool HasDocumentGreaterRelevance(const Document& lhs, const Document& rhs) {
    return lhs.relevance > rhs.relevance;
}
 
class SearchServer {
public:
    void SetStopWords(const string& text) {
        for (const string& word : SplitIntoWords(text)) {
            stop_words_.insert(word);
        }
    }
 
    void AddDocument(int document_id, const string& document) {
        const vector<string> words = SplitIntoWordsNoStop(document);
        documents_.push_back({document_id, words});
    }
 
    vector<Document> FindTopDocuments(const string& raw_query) {
        const set<string> query_words = ParseQuery(raw_query);
        auto matched_documents = FindAllDocuments(query_words);
 
        sort(matched_documents.begin(), matched_documents.end(), HasDocumentGreaterRelevance);
        if (matched_documents.size() > MAX_RESULT_DOCUMENT_COUNT) {
            matched_documents.resize(MAX_RESULT_DOCUMENT_COUNT);
        }
        return matched_documents;
    }
 
private:
    struct DocumentContent {
        int id = 0;
        vector<string> words;
    };
 
    vector<DocumentContent> documents_;
 
    set<string> stop_words_;
 
    bool IsStopWord(const string& word) {
        return stop_words_.count(word) > 0;
    }
 
    vector<string> SplitIntoWordsNoStop(const string& text) {
        vector<string> words;
        for (const string& word : SplitIntoWords(text)) {
            if (!IsStopWord(word)) {
                words.push_back(word);
            }
        }
        return words;
    }
 
    set<string> ParseQuery(const string& text) {
        set<string> query_words;
        for (const string& word : SplitIntoWordsNoStop(text)) {
            query_words.insert(word);
        }
        return query_words;
    }
 
    vector<Document> FindAllDocuments(const set<string>& query_words) {
        vector<Document> matched_documents;
        for (const auto& document : documents_) {
            const int relevance = MatchDocument(document, query_words);
            if (relevance > 0) {
                matched_documents.push_back({document.id, relevance});
            }
        }
        return matched_documents;
    }
 
    static int MatchDocument(const DocumentContent& content, const set<string>& query_words) {
        if (query_words.empty()) {
            return 0;
        }
        set<string> matched_words;
        for (const string& word : content.words) {
            if (matched_words.count(word) != 0) {
                continue;
            }
            if (query_words.count(word) != 0) {
                matched_words.insert(word);
            }
        }
        return static_cast<int>(matched_words.size());
    }
};
 
SearchServer CreateSearchServer() {
    SearchServer search_server;
    search_server.SetStopWords(ReadLine());
 
    const int document_count = ReadLineWithNumber();
    for (int document_id = 0; document_id < document_count; ++document_id) {
        search_server.AddDocument(document_id, ReadLine());
    }
 
    return search_server;
}
 
int main() {
    SearchServer search_server = CreateSearchServer();
 
    const string query = ReadLine();
    for (const auto& [document_id, relevance] : search_server.FindTopDocuments(query)) {
        cout << "{ document_id = "s << document_id << ", "
             << "relevance = "s << relevance << " }"s << endl;
    }
}
```
</details> 

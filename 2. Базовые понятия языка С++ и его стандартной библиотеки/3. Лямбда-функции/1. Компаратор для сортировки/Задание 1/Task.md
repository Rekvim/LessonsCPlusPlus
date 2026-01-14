### Задание 1

В стандартном потоке дана одна строка, которая состоит из числа N и следующего за ним набора S из N слов. Число отделено от слов пробелом.
Отсортируйте набор слов S в алфавитном порядке по возрастанию, игнорируя регистр букв. Выведите их в стандартный поток вывода через пробел. При сравнении слов цифры должны предшествовать буквам: слово «R2D2» находится после слова «R259», так как цифра 5 предшествует любой из букв.
После последнего слова также выведите пробел, а затем перевод строки.
Ознакомьтесь с функцией tolower и алгоритмом lexicographical_compare, чтобы отсортировать слова в алфавитном порядке без учета регистра символов.
Как будет тестироваться ваш код
Гарантируется, что входные данные программы удовлетворяют следующим условиям:
0 <= N <= 1000;
1 <= |S[i]| <= 15;
каждое слово `S[i]` содержит только цифры, заглавные и строчные буквы английского алфавита;
в наборе слов S нет слов, которые отличаются только регистром символов, например: «apple» и «Apple».

#### Пример

Ввод

8 quantity AMOUNT Selection Search 4ever music Mickey market 
Вывод 

4ever AMOUNT market Mickey music quantity Search Selection 


#### Подсказка

Если видите ошибку p`assing 'const SearchServer' as 'this' argument discards qualifiers`, значит, вы вызвали неконстантный метод там, где это запрещено: в константном методе или для константного объекта.

Если ошибка другая — `discards qualifiers` для иного объекта или `no matching function for call` —  скорее всего, вы перестарались и пометили константным метод, который не должен им быть.

Метод `MatchDocument` — статический. Статические методы не имеют доступа к полям объекта, поэтому они не помечаются константными. Если вы пометите константным статический метод, будет ошибка компиляции.

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

    vector<Document> FindTopDocuments(const string& raw_query) const {
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

    bool IsStopWord(const string& word) const {
        return stop_words_.count(word) > 0;
    }

    vector<string> SplitIntoWordsNoStop(const string& text) const {
        vector<string> words;
        for (const string& word : SplitIntoWords(text)) {
            if (!IsStopWord(word)) {
                words.push_back(word);
            }
        }
        return words;
    }

    set<string> ParseQuery(const string& text) const {
        set<string> query_words;
        for (const string& word : SplitIntoWordsNoStop(text)) {
            query_words.insert(word);
        }
        return query_words;
    }

    vector<Document> FindAllDocuments(const set<string>& query_words) const {
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
    const SearchServer search_server = CreateSearchServer();

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

    vector<Document> FindTopDocuments(const string& raw_query) const {
        const set<string> query_words = ParseQuery(raw_query);
        auto matched_documents = FindAllDocuments(query_words);

        sort(matched_documents.begin(), matched_documents.end(), [](const Document& lhs, const Document& rhs) {return lhs.relevance > rhs.relevance;});
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

    bool IsStopWord(const string& word) const {
        return stop_words_.count(word) > 0;
    }

    vector<string> SplitIntoWordsNoStop(const string& text) const {
        vector<string> words;
        for (const string& word : SplitIntoWords(text)) {
            if (!IsStopWord(word)) {
                words.push_back(word);
            }
        }
        return words;
    }

    set<string> ParseQuery(const string& text) const {
        set<string> query_words;
        for (const string& word : SplitIntoWordsNoStop(text)) {
            query_words.insert(word);
        }
        return query_words;
    }

    vector<Document> FindAllDocuments(const set<string>& query_words) const {
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
    const SearchServer search_server = CreateSearchServer();

    const string query = ReadLine();
    for (const auto& [document_id, relevance] : search_server.FindTopDocuments(query)) {
        cout << "{ document_id = "s << document_id << ", "
             << "relevance = "s << relevance << " }"s << endl;
    }
}
```
</details> 

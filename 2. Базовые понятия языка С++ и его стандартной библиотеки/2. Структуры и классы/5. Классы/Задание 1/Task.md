### Задание 1

Разработайте класс `TV`, моделирующий работу телевизора по следующим правилам:
- Телевизор может быть включен либо выключен. Начальное состояние телевизора — выключен.
- Когда телевизор включен, он позволяет выбрать канал с 1 по 99 включительно. Нельзя выбрать канал с номером, меньшим 1 и большим 99. Выключенный телевизор не может переключать каналы.
- При первом включении в телевизоре выбран канал №1. При последующем включении телевизор показывает тот канал, который был выбран перед его выключением.

В заготовке кода вам дан каркас класса `TV`. В классе объявлены методы:

- TurnOn — включает телевизор.
- TurnOff — выключает телевизор.
- IsTurnedOn — возвращает информацию о том, включен телевизор (true) или нет (false).
- SelectChannel — выбирает канал с заданным номером. Возвращает true в случае успеха и false при неудаче.
- GetCurrentChannel — возвращает текущий номер канала. Если телевизор в данный момент выключен, возвращает 0.

Напишите реализацию этих методов. Сигнатуру методов не меняйте.

#### Пример

Входные данные:
```cpp
int main() {
    TV tv;
    cout << "TV status: "s << tv.IsTurnedOn();
    cout << ", channel: "s << tv.GetCurrentChannel() << endl;
    cout << endl;
    cout << "Turn ON"s << endl;
    tv.TurnOn();
    cout << "TV status: "s << tv.IsTurnedOn();
    cout << ", channel: "s << tv.GetCurrentChannel() << endl;
    cout << "SelectChannel(25) returned " << tv.SelectChannel(25) << endl;
    cout << "TV status: "s << tv.IsTurnedOn();
    cout << ", channel: "s << tv.GetCurrentChannel() << endl;
    
    cout << "SelectChannel(0) returned " << tv.SelectChannel(0) << endl;
    cout << "SelectChannel(100) returned " << tv.SelectChannel(100) << endl;
    cout << "TV status: "s << tv.IsTurnedOn();
    cout << ", channel: "s << tv.GetCurrentChannel() << endl;
    cout << endl;
    cout << "Turn OFF"s << endl;
    tv.TurnOff();
    cout << "TV status: "s << tv.IsTurnedOn();
    cout << ", channel: "s << tv.GetCurrentChannel() << endl;

    cout << "SelectChannel(15) returned " << tv.SelectChannel(15) << endl;
    cout << endl;
    cout << "Turn ON"s << endl;
    tv.TurnOn();
    cout << "TV status: "s << tv.IsTurnedOn();
    cout << ", channel: "s << tv.GetCurrentChannel() << endl;
} 
```
Результат:
```
TV status: 0, channel: 0

Turn ON
TV status: 1, channel: 1
SelectChannel(25) returned 1
TV status: 1, channel: 25
SelectChannel(0) returned 0
SelectChannel(100) returned 0
TV status: 1, channel: 25

Turn OFF
TV status: 0, channel: 0
SelectChannel(15) returned 0

Turn ON
TV status: 1, channel: 25 
```
Как будет тестироваться ваш код

Тренажёр проверит, что методы класса `TV` ведут себя так, как описано в задаче. Тело функции `main` будет проигнорировано.

#### Подсказка

- Добавьте в класс `TV` приватное поле `bool is_turned_on_`. Оно будет хранить информацию о том, включен телевизор или нет. Так как по условию телевизор изначально выключен, задайте полю начальное значение `false`

- Добавьте в класс `TV` приватное поле `int current_channel_`. Оно будет хранить выбранный номер канала. Чтобы телевизор при первом включении показывал канал №1, проинициализируйте поле `current_channel_` значением `1`.

- В методе `GetCurrentChannel` верните значение поля `current_channel_`, если телевизор включен, и 0, если выключен.

- При выборе номера канала проверьте, включен ли телевизор и находится ли номер канала в диапазоне от 1 до 99. Только если всё хорошо, смените номер канала и верните `true`, а иначе не меняйте номер канала и верните `false`.

#### Код к заданию

```cpp
#include <iostream>

using namespace std;

/* Допишите класс в соответствии с требованиями задания*/
class TV {
public:
    // Включает телевизор.
    void TurnOn() {
        // Напишите код этого метода.
    }

    // Выключает телевизор.
    void TurnOff() {
        // Напишите код этого метода.
    }

    // Возвращает true, если телевизор включён и false, если телевизор выключен.
    bool IsTurnedOn() {
        // Напишите код этого метода.
        return false;
    }

    // Возвращает номер текущего канала либо 0, если телевизор был выключен.
    // Номер канала не сбрасывается при выключении и повторном включении.
    // При первом включении телевизор показывает канал № 1.
    int GetCurrentChannel() {
        // Напишите код этого метода.
        return 0;
    }

    // Выбирает канал с указанным номером. Номер канала должен быть в диапазоне [1..99].
    // Если указан недопустимый номер канала или телевизор выключен, возвращает false и не меняет
    // текущий канал. В противном случае возвращает true.
    bool SelectChannel(int channel) {
        // Напишите код этого метода.
        return false;
    }
};

int main() {
    TV tv;
    cout << "TV status: "s << tv.IsTurnedOn();
    cout << ", channel: "s << tv.GetCurrentChannel() << endl;
    cout << endl;
    cout << "Turn ON"s << endl;
    tv.TurnOn();
    cout << "TV status: "s << tv.IsTurnedOn();
    cout << ", channel: "s << tv.GetCurrentChannel() << endl;
    cout << "SelectChannel(25) returned " << tv.SelectChannel(25) << endl;
    cout << "TV status: "s << tv.IsTurnedOn();
    cout << ", channel: "s << tv.GetCurrentChannel() << endl;

    cout << "SelectChannel(0) returned " << tv.SelectChannel(0) << endl;
    cout << "SelectChannel(100) returned " << tv.SelectChannel(100) << endl;
    cout << "TV status: "s << tv.IsTurnedOn();
    cout << ", channel: "s << tv.GetCurrentChannel() << endl;
    cout << endl;
    cout << "Turn OFF"s << endl;
    tv.TurnOff();
    cout << "TV status: "s << tv.IsTurnedOn();
    cout << ", channel: "s << tv.GetCurrentChannel() << endl;
    
    cout << "SelectChannel(15) returned " << tv.SelectChannel(15) << endl;
    cout << endl;
    cout << "Turn ON"s << endl;
    tv.TurnOn();
    cout << "TV status: "s << tv.IsTurnedOn();
    cout << ", channel: "s << tv.GetCurrentChannel() << endl;
}
```

<details><summary><strong>Решение</strong></summary>

```cpp
#include <iostream>

using namespace std;

/* Допишите класс в соответствии с требованиями задания*/
class TV {
public:
    // Включает телевизор.
    void TurnOn() {
        is_turned_on_ = true;
        // Напишите код этого метода
    }

    // Выключает телевизор
    void TurnOff() {
        // Напишите код этого метода
         is_turned_on_ = false;
    }

    // Возвращает true, если телевизор включен и false, если телевизор выключен
    bool IsTurnedOn() {
        // Напишите код этого метода
        return is_turned_on_;
    }

    // Возвращает номер текущего канала, либо 0, если телевизор был выключен.
    // Телевизор при выключении «запоминает» номер текущего канала,
    // а при включении — «восстанавливает» его.
    // При первом включении телевизор показывает канал №1.
    int GetCurrentChannel() {
        // Напишите код этого метода
        if (is_turned_on_) {
            return current_channel_;
        }
        else {
            return 0;
        }
    }

    // Выбирает канал с указанным номером. Номер канала должен быть в диапазоне [1..99].
    // Если указан недопустимый номер канала, либо телевизор выключен, возвращает false и не меняет
    // текущий канал. В противном случае возвращает true.
    bool SelectChannel(int channel) {
        // Напишите код этого метода
        if (is_turned_on_ && channel >= 1 && channel <= 99) {
            current_channel_ = channel;
            return true;
        }
        else {
            return false;
        }
        
    }
    private: 
        bool is_turned_on_ = false;
        int current_channel_ = 1;
};

int main() {
    TV tv;
    cout << tv.IsTurnedOn() << ", channel:"s << tv.GetCurrentChannel() << endl;
    tv.TurnOn();
    cout << tv.IsTurnedOn() << ", channel: "s << tv.GetCurrentChannel() << endl;
    tv.SelectChannel(25);
    cout << tv.IsTurnedOn() << ", channel: "s << tv.GetCurrentChannel() << endl;
    tv.TurnOff();
    cout << tv.IsTurnedOn() << ", channel: "s << tv.GetCurrentChannel() << endl;
}
```
</details> 

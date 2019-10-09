[![](https://iarduino.ru/img/logo.svg)](https://iarduino.ru)[![](https://wiki.iarduino.ru/img/git-shop.svg?3)](https://iarduino.ru) [![](https://wiki.iarduino.ru/img/git-wiki.svg?2)](https://wiki.iarduino.ru) [![](https://wiki.iarduino.ru/img/git-lesson.svg?2)](https://lesson.iarduino.ru)[![](https://wiki.iarduino.ru/img/git-forum.svg?2)](http://forum.trema.ru)

# Battery\_Shield

**This is a library for Arduino IDE. It allows to control [Battery Shield](https://iarduino.ru/shop/Expansion-payments/battery-shield.html), I2C module made by iArduino.ru**

**Данная библиотека для Arduino IDE позволяет управлять модулем I2C [Battery Shield](https://iarduino.ru/shop/Expansion-payments/battery-shield.html) от [iArduino.ru](https://iarduino.ru)**

> Подробнее про установку библиотеки читайте в нашей [инструкции](https://wiki.iarduino.ru/page/Installing_libraries/).

> Подробнее про подключение к [Arduino UNO](https://iarduino.ru/shop/boards/arduino-uno-r3.html)/[Piranha UNO](https://iarduino.ru/shop/boards/piranha-uno-r3.html) читайте на нашей [wiki](https://wiki.iarduino.ru/page/Battery_Shield/)


| Модель | Ссылка на магазин |
|---|---|
| <p>Модуль Batttery Shield</p> <img src="https://wiki.iarduino.ru/img/resources/953/953.svg" width="150px"></img>| https://iarduino.ru/shop/Expansion-payments/battery-shield.html |


## Назначение функций:

**Подробное описание работы с библиотекой и примеры смотрите на [нашем сайте](https://wiki.iarduino.ru/page/Battery_Shield/)**

**Подключаем библиотеку**

```C++
#include <Battery_Shield.h> // Подключаем библиотеку.
Battery_Shield ОБЪЕКТ; // Создаём объект.
```

**Инициализация** 

```C++
Функция begin( RBAT [,КПД] ); // Инициализация работы с Battery Shield.
```

**Выключение** 

```C++
Функция off(); // Выключение Battery Shield.
```

**Выкл ЗУ**

```C++
Функция charging( ФЛАГ ); // Вкл/выкл ЗУ.
```

**Получение уровня** 

```C++
Функция getLevel(); // Получение уровня заряда АКБ в %.
```

**Получение состояния** 

```C++
Функция getState(); // Получение состояния Battery Shield (не заряжается, TK, CC, CV, Time Over).
```

**Получение напряжения** 

```C++
Функция voltmeter( БЛОК_СХЕМЫ ); // Получение напряжения на указанном блоке схемы (VBAT, VOUT).
```

**Получение тока** 

```C++
Функция amperemeter( ЦЕПЬ_СХЕМЫ ); // Получение тока указанной цепи (IBAT, IOUT).
```

**Получение сопротивления** 

```C++
Функция ohmmeter( IBAT ); // Получение сопротивления в цепи АКБ (RBAT).
```

**Получение КПД** 

```C++
Функция efficiency( IOUT ); // Получение КПД повышающего DC-DC преобразователя.
```


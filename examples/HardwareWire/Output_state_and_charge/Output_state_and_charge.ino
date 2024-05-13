// ПРИМЕР ВЫВОДА СОСТОЯНИЯ АККУМУЛЯТОРА:        //
                                                //
// Источник автономного питания Battery Shield: // https://iarduino.ru/shop/Expansion-payments/battery-shield.html
// Информация о подключении модулей к шине I2C: // https://wiki.iarduino.ru/page/i2c_connection/
// Информация о модуле и описание библиотеки:   // https://wiki.iarduino.ru/page/Battery_Shield/
                                                //
#include <Wire.h>                               // Подключаем библиотеку для работы с аппаратной шиной I2C, до подключения библиотеки Battery_Shield.
#include <Battery_Shield.h>                     // Подключаем библиотеку Battery_Shield.
Battery_Shield pwrBank(0x35);                   // Объявляем объект pwrBank для работы с модулем указав его адрес на шине I2C: 0x35 или 0x75.
                                                //
void setup(){                                   //
     Serial.begin(9600);                        // Инициируем передачу данных в монитор последовательного порта на скорости 9600.
     pwrBank.begin(&Wire, 0.0128f);             // Инициируем работу с Battery Shield, указывая ссылку на объект для работы с шиной I2C, номинал сопротивления (0.128 Ом) установленного в цепи аккумулятора.
}                                               // Номинал сопротивления Вашего источника автономного питания указан на вкладыше к Battery Shield, это значение используется для расчёта Ibat.
                                                //
void loop(){                                    // 
     switch(pwrBank.getState()){                // Выводим текст в зависимости от значения возвращённого функцией getState():
         case CHARGING_IDLE: Serial.println(       F("Аккумулятор не заряжается.")                                    ); break;
         case CHARGING_TK:   Serial.println(       F("Аккумулятор заряжается малым током.")                           ); break;
         case CHARGING_CC:   Serial.println(       F("Аккумулятор заряжается постоянным током.")                      ); break;
         case CHARGING_CV:   Serial.println(       F("Аккумулятор заряжается постоянным напряжением.")                ); break;
         case CHARGING_TO:   Serial.println(       F("Аккумулятор не заряжается по причине истечения времени заряда.")); break;
         default:            Serial.println(       F("Режим заряда аккумулятора неизвестен.")                         ); break;
     }                       Serial.println((String) "Текущая ёмкость аккумулятора " + pwrBank.getLevel() + "%"       );
                             Serial.println(       F("-------------------------")                                     );
     delay(1000);                               // Приостанавливаем выполнение скетча на 1 секунду.
}                                               //

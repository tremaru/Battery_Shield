// ПРИМЕР ВЫВОДА ТОКА И НАПРЯЖЕНИЯ:             //
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
void loop(){                                                                  // 
     Serial.println("-------------------------");                             // 
     Serial.println((String) "Vbat=" + pwrBank.voltmeter(BATTERY)   + "В.");  // Выводим напряжение аккумулятора в В.
     Serial.println((String) "Ibat=" + pwrBank.amperemeter(BATTERY) + "А.");  // Выводим силу тока  аккумулятора в А.
     Serial.println((String) "Vout=" + pwrBank.voltmeter(OUTPUT)    + "В.");  // Выводим напряжение на выходе    в В.
     Serial.println((String) "Iout=" + pwrBank.amperemeter(OUTPUT)  + "А.");  // Выводим силу тока  на выходе    в А.
     delay(1000);                                                             // Приостанавливаем выполнение скетча на 1 секунду.
}

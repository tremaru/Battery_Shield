// ПРИМЕР ОТКЛЮЧАЕТ BATTERY SHIELD ЧЕРЕЗ 5 СЕК:              //
// Требуется установить библиотеку <iarduino_I2C_Software.h> //   https://iarduino.ru/file/627.html
                                                             //
// Источник автономного питания Battery Shield:              //   https://iarduino.ru/shop/Expansion-payments/battery-shield.html
// Информация о подключении модулей к шине I2C:              //   https://wiki.iarduino.ru/page/i2c_connection/
// Информация о модуле и описание библиотеки:                //   https://wiki.iarduino.ru/page/Battery_Shield/
                                                             //
#include <iarduino_I2C_Software.h>                           //   Подключаем библиотеку для работы с программной шиной I2C, до подключения библиотеки Battery_Shield.
SoftTwoWire sWire(3,4);                                      //   Создаём объект программной шины I2C указав выводы которым будет назначена роль линий: SDA, SCL.
                                                             //
#include <Battery_Shield.h>                                  //   Подключаем библиотеку Battery_Shield.
Battery_Shield pwrBank(0x35);                                //   Объявляем объект pwrBank для работы с модулем указав его адрес на шине I2C: 0x35 или 0x75.
                                                             //
void setup(){                                                //
     pwrBank.begin(&sWire, 0.0128f);                         //   Инициируем работу с Battery Shield, указывая ссылку на объект для работы с шиной I2C, номинал сопротивления (0.128 Ом) установленного в цепи аккумулятора.
}                                                            //   Номинал сопротивления Вашего источника автономного питания указан на вкладыше к Battery Shield, это значение используется для расчёта Ibat.
                                                             //
void loop(){                                                 // 
     if(millis()>5000){ pwrBank.off(); }                     //   Если прошло более 5 секунд, то отключаем Battery Shield.
}                                                            //

//	Библиотека для работы с источником автономного питания «battery shield»: http://iarduino.ru/shop/Expansion-payments/battery-shield.html
//  Версия: 1.0.4
//  Последнюю версию библиотеки Вы можете скачать по ссылке: http://iarduino.ru/file/344.html
//  Подробное описание функции бибилиотеки доступно по ссылке: http://wiki.iarduino.ru/page/Battery_Shield/
//  Библиотека является собственностью интернет магазина iarduino.ru и может свободно использоваться и распространяться!
//  При публикации устройств или скетчей с использованием данной библиотеки, как целиком, так и её частей,
//  в том числе и в некоммерческих целях, просим Вас опубликовать ссылку: http://iarduino.ru
//  Автор библиотеки: Панькин Павел.
//  Если у Вас возникли технические вопросы, напишите нам: shop@iarduino.ru
																					//
#ifndef Battery_Shield_h															//
#define Battery_Shield_h															//
																					//
#if defined(ARDUINO) && (ARDUINO >= 100)											//
#include	<Arduino.h>																//
#else																				//
#include	<WProgram.h>															//
#endif																				//
																					//
#include <Battery_Shield_I2C.h>														//	Подключаем файл Battery_Shield_I2C.h - для работы с шиной I2C        (используя функции производного класса iarduino_I2C).
																					//
	//		INPUT							0										//	Параметр для функции voltmeter() аналог константы BATTERY.
	//		OUTPUT							1										//	Параметр для функции voltmeter() указвающий что требуется получить напряжение на выходе battery shield.
#define		BATTERY							70										//	Параметр для функции voltmeter() указвающий что требуется получить напряжение на аккумуляторе подключённом к нагрузке. Этот же параметр используется функцией amperemeter() для получения силы тока аккумулятора.
#define		BATTERY_IDLE					72										//	Параметр для функции voltmeter() указвающий что требуется получить напряжение на аккумуляторе без нагрузки.
#define		RESISTOR						73										//	Параметр для функции voltmeter() указвающий что требуется получить напряжение на резисторе в цепи аккумулятора.
#define		CHARGING_IDLE					70										//	Параметр возвращаемый функцией getState() указывающий, что аккумулятор не заряжается.
#define		CHARGING_TK						71										//	Параметр возвращаемый функцией getState() указывающий, что аккумулятор заряжается слабым током (данный тип заряда используется, если аккумулятор сильно разряжен).
#define		CHARGING_CC						72										//	Параметр возвращаемый функцией getState() указывающий, что аккумулятор заряжается постоянным током (основной тип заряда аккумулятора, выполняется пока напряжение аккумулятора не достигнет требуемого значения 4,2 В).
#define		CHARGING_CV						73										//	Параметр возвращаемый функцией getState() указывающий, что аккумулятор заряжается постоянным напряжением (завершающий тип заряда аккумулятора, выполняется после достижения требуемого напряжения пока ток заряда не упадёт до требуемого значения).
#define		CHARGING_TO						74										//	Параметр возвращаемый функцией getState() указывающий, что время заряда вышло (Time Over). Заряд аккумулятора длился дольше 12 часов.
																					//
#define		IP5108_RESISTOR					0.0128f									//	Сопротивление установленное в цепи аккумулятора, используемое для измерения силы тока аккумулятора.
#define		IP5108_EFFICIENCY				0.94f									//	Коэффициент полезного действия повышающего DC-DC преобразователя в абсолютных значениях (от 0 до 1).
#define		IP5108_ADDRESS					0x75									//	Адрес чипа IP5108 на шине I2C.
																					//
#define		IP5108_SYS_CTL0					0x01									//	Системный регистр управления, хранит флаги разрешающие работу блоков чипа IP5108.
#define		IP5108_SYS_CTL1					0x02									//	Системный регистр управления, хранит флаги управляющие автоматическим включением/выключением чипа IP5108.
#define		IP5108_SYS_CTL2					0x03									//	Системный регистр управления, хранит флаги управления кнопкой.
#define		IP5108_SYS_CTL3					0x04									//	Системный регистр управления, хранит флаг разрешающий работу повышающего преобразователя при наличии питания Vin, а также хранит время через которое чип IP5108 должен отключиться (при снижении силы тока аккумулятора ниже значения в регистре IP5108_SYS_CTL2).
#define		IP5108_SYS_CTL4					0x05									//	Системный регистр управления, хранит флаг выключающий чип.
#define		IP5108_SYS_CTL5					0x06									//	Системный регистр управления.
#define		IP5108_SYS_CTL6					0x07									//	Системный регистр управления, хранит флаги выбирающие способ включения/выключения света/чипа, а так же флаг включающий/выключающий термистор.
#define		IP5108_CHARGER_CTL1				0x22									//	Регистр управления зарядным устройством, хранит значение напряжения на выходе (при наличии напряжения на входе) для регулировки тока заряда.
#define		IP5108_CHARGER_CTL2				0x24									//	Регистр управления зарядным устройством, хранит значение напряжения до которого требуется заряжать аккумулятор и значение дополнительного напряжения для режима заряда CV (заряд постоянным напряжением).
#define		IP5108_DIG_CTL0					0x25									//	Регистр управляющих значений, хранит значение зарядного тока.
#define		IP5108_DIG_CTL1					0x26									//	Регистр управляющих значений, хранит флаг способа выбора максимального напряжения аккумулятора.
#define		IP5108_DIG_CTL2					0x0С									//	Регистр управляющих значений, хранит пороговое значение силы тока аккумулятора, для выключения чипа IP5108.
#define		IP5108_MFP_CTL0					0x50									//	Регистр управления нагрузочной способностью выводов LIGHT, L4, L3, L2, L1, VSET, RSET.
#define		IP5108_MFP_CTL1					0x51									//	Регистр управления функциональным назначением выводов LIGHT, L4, L3.
#define		IP5108_MFP_CTL2					0x52									//	Регистр управления функциональным назначением выводов VSET, RSET.
#define		IP5108_GPIO_CTL1				0x53									//	Регистр управления, хранит флаги разрешающие работу выводов (выполняющих функцию GPIO) в режиме входа.
#define		IP5108_GPIO_CTL2				0x54									//	Регистр управления, хранит флаги разрешающие работу выводов (выполняющих функцию GPIO) в режиме выхода.
#define		IP5108_GPIO_CTL3				0x55									//	Регистр управления, хранит логическое состояние на выводах выполняющих функцию GPIO.
#define		IP5108_BAT_V_ADC_DAT0			0xA2									//	Регистр данных, хранит младшие 8 бит АЦП для вычисления текущего напряжения аккумуляторной батареи.
#define		IP5108_BAT_V_ADC_DAT1			0xA3									//	Регистр данных, хранит старшие 6 бит АЦП для вычисления текущего напряжения аккумуляторной батареи.
#define		IP5108_BAT_I_ADC_DAT0			0xA4									//	Регистр данных, хранит младшие 8 бит АЦП для вычисления текущего тока аккумуляторной батареи.
#define		IP5108_BAT_I_ADC_DAT1			0xA5									//	Регистр данных, хранит старшие 6 бит АЦП для вычисления текущего тока аккумуляторной батареи.
#define		IP5108_BAT_OCV_DAT0				0xA8									//	Регистр данных, хранит младшие 8 бит АЦП для вычисления текущего напряжения аккумуляторной батареи (без нагрузки).
#define		IP5108_BAT_OCV_DAT1				0xA9									//	Регистр данных, хранит старшие 6 бит АЦП для вычисления текущего напряжения аккумуляторной батареи (без нагрузки).
#define		IP5108_OUT_V_ADC_DAT0			0xAC									//	Регистр данных, хранит младшие 8 бит АЦП для вычисления текущего напряжения на выходе чипа IP5108.
#define		IP5108_OUT_V_ADC_DAT1			0xAD									//	Регистр данных, хранит старшие 6 бит АЦП для вычисления текущего напряжения на выходе чипа IP5108.
#define		IP5108_REG_READ0				0x70									//	Регистр чтения флагов состояния зарядного устройства, повышающего преобразователя статуса работы и фонарика.
#define		IP5108_REG_READ1				0x71									//	Регистр чтения флагов состояния текущего режима заряда (TK, CC, CV).
#define		IP5108_REG_READ2				0x72									//	Регистр чтения флагов состояния фонарика (вывода LIGHT).
#define		IP5108_REG_READ3				0x77									//	Регистр чтения флагов состояния кнопки (вывода KEY).
																					//
class Battery_Shield{																//
	public:																			//
	/**	Конструктор класса **/														//
		Battery_Shield						(uint8_t address=0x3C){					//	Конструктор класса										(Параметр: адрес дисплея на шине I2C)
							objI2C		=	new iarduino_I2C;						//	Переопределяем указатель objI2C на объект производного класса iarduino_I2C
		}																			//
	/**	Пользовательские функции **/												//
		bool				begin			(float, float=IP5108_EFFICIENCY*100);	//	Объявляем  функцию инициализации battery shield.		(Параметр: значение сопротивления в Ом, [КПД повышающего DC-DC преобразователя в %])
		bool				off				(void);									//	Объявляем  функцию выключения battery shield.			(Параметр: отсутствует)
		void				charging		(bool);									//	Объявляем  функцию управления зарядным устройством.		(Параметр: флаг разрешения работы - да/нет)
		uint8_t				getLevel		(void);									//	Объявляем  функцию получения текущего заряда батареи.	(Параметр: отсутствует)
		uint8_t				getState		(void);									//	Объявляем  функцию получения текущего режима заряда.	(Параметр: отсутствует)
		float				amperemeter		(uint8_t);								//	Объявляем  функцию получения силы тока в А.				(Параметр: цепь, ток которой требуется получить: INPUT = BATTERY, OUTPUT)
		float				voltmeter		(uint8_t);								//	Объявляем  функцию получения напряжения в В.			(Параметр: блок схемы на котором требуется измерить напряжение: INPUT = BATTERY, OUTPUT, BATTERY_IDLE, RESISTOR)
		float				ohmmeter		(float);								//	Объявляем  функцию получения сопротивления в Ом.		(Параметр: сила тока в цепи аккумулятора, измеряется пользователем)
		float				efficiency		(float);								//	Объявляем  функцию получения КПД в %.					(Параметр: сила тока в цепи нагрузки (выхода), измеряется пользователем)
																					//
	private:																		//
	/**	Внутренние переменные **/													//
		float				valEfficiency = IP5108_EFFICIENCY;						//	Определяем переменную для хранения КПД повышающего DC-DC преобразователя в абсолютных значениях (от 0 до 1).
		float				valResistor	  =	IP5108_RESISTOR;						//	Определяем переменную для хранения сопротивления в цепи аккумулятора с которого меряется ток.
		uint8_t				valRegistor[2]=	{0,0};									//	Объявляем  массив для получения значений из регистров.
		iarduino_I2C_BASE*	objI2C;													//	Объявляем  указатель на объект полиморфного класса iarduino_I2C_BASE, но в конструкторе данного класса этому указателю будет присвоена ссылка на производный класс iarduino_I2C.
	/**	Внутренние функции **/														//
		float				_ADC			(uint8_t);								//	Объявляем  функцию получения значенией АЦП.				(Параметр: номер первого регистра)
		bool				_noSleep		(void);									//	Объявляем  функцию запрещающую автосон без нагрузки.	(Параметр: отсутствует)
};																					//
																					//
#endif																				//
																					//
/*
	╔══════╤═════════════════╤═══════════════════╤═══════════════════╤═══════════════════╤═══════════════════╤═══════════════════╤═══════════════════╤═══════════════════╤═══════════════════╤══════╤═══════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
	║   №  │ ИМЕНА РЕГИСТРОВ │         7         │         6         │         5         │         4         │         3         │         2         │         1         │         0         │ ВКЛ. │ НАЗНАЧЕНИЕ РЕГИСТРОВ                                                                                          ║
	╟──────┼─────────────────┼───────────────────┼───────────────────┼───────────────────┼───────────────────┼───────────────────┼───────────────────┼───────────────────┼───────────────────┼──────┼───────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
	║ 0x01 │ SYS_CTL0        │███████████████████│███████████████████│███████████████████│  EN_LIGHT_DETECT  │     EN_LIGHT      │     EN_BOOST      │     EN_CHARGE     │███████████████████│ 0xFE │ Системный регистр управления, флаги разрешающие работу блоков.                                                ║
	║ 0x02 │ SYS_CTL1        │███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│ EN_SHUTDOWN_I_LOW │   EN_AUTOSTART    │ 0x7F │ Системный регистр управления, флаги управляющие автоматическим вкл/выкл чипа.                                 ║
	║ 0x03 │ SYS_CTL2        │         TIME_LONG_PRESS[1-0]          │ EN_TWO_SHORTPRESS │███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│ 0x68 │ Системный регистр управления, флаги управления кнопкой.                                                       ║
	║ 0x04 │ SYS_CTL3        │         TIME_TO_SHUTDOWN[1-0]         │   EN_OPEN_BOOST   │███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│ 0xB7 │ Системный регистр управления, время перехода в сон и флаг разрешающий Vout при наличии питания Vin.           ║
	║ 0x05 │ SYS_CTL4        │       RESET       │███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│ 0x00 │ Системный регистр управления, флаг перезагружающий чип.                                                       ║
	║ 0x06 │ SYS_CTL5        │███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│ 0x   │ Системный регистр управления.                                                                                 ║
	║ 0x07 │ SYS_CTL6        │███████████████████│      EN_NTC       │███████████████████│███████████████████│███████████████████│███████████████████│    WAY_LIGHT_ON   │   WAY_SLEEP_ON    │ 0x00 │ Системный регистр управления, флаги выбирающие способ включения/выключения света/чипа/термистора.             ║
	╟──────┼─────────────────┼───────────────────┼───────────────────┼───────────────────┼───────────────────┼───────────────────┴───────────────────┼───────────────────┼───────────────────┼──────┼───────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
	║ 0x22 │ CHARGER_CTL1    │███████████████████│███████████████████│███████████████████│███████████████████│        V_OUT_WHEN_CHARGING[1-0]       │███████████████████│███████████████████│ 0x52 │ Регистр управления зарядным устройством, значение Vout для регулировки Ibat.                                  ║
	║ 0x24 │ CHARGER_CTL2    │███████████████████│             V_BAT_SET[1-0]            │███████████████████│███████████████████│           V_BAT_CV_SET[1-0]           │███████████████████│ 0x85 │ Регистр управления зарядным устройством, Vbat max, Vbat add.                                                  ║
	╟──────┼─────────────────┼───────────────────┼───────────────────┬───────────────────┼───────────────────┴───────────────────┴───────────────────────────────────────┴───────────────────┼──────┼───────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
	║ 0x25 │ DIG_CTL0        │███████████████████│███████████████████│███████████████████│                                           I_BAT_SET[4-0]                                          │ 0xD7 │ Регистр управляющих значений, Ibat.                                                                           ║
	║ 0x26 │ DIG_CTL1        │███████████████████│     WAY_V_BAT     │███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│ 0xBF │ Регистр управляющих значений, флаг способа выбора максимального напряжения аккумулятора                       ║
	║ 0x0С │ DIG_CTL2        │                                     I_BAT_LOW_TO_SHUTDOWN[4-0]                                    │███████████████████│███████████████████│███████████████████│ 0x53 │ Регистр управляющих значений, сила тока аккумулятора, для выключения чипа.                                    ║
	╟──────┼─────────────────┼───────────────────┬───────────────────┬───────────────────┬───────────────────┬───────────────────┼───────────────────┼───────────────────┼───────────────────┼──────┼───────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
	║ 0x50 │ MFP_CTL0        │     L2_DRIVE      │     L1_DRIVE      │███████████████████│    VSET_DRIVE     │    RSET_DRIVE     │    LIGHT_DRIVE    │     L4_DRIVE      │     L3_DRIVE      │ 0x05 │ Регистр управления нагрузочной способностью выводов LIGHT, L4, L3, L2, L1, VSET, RSET.                        ║
	║ 0x51 │ MFP_CTL1        │███████████████████│███████████████████│           LIGHT_PIN_SEL[1-0]          │             L4_PIN_SEL[1-0]           │             l3_PIN_SEL[1-0]           │ 0x00 │ Регистр управления функциональным назначением выводов LIGHT, L4, L3.                                          ║
	║ 0x52 │ MFP_CTL2        │███████████████████│███████████████████│███████████████████│███████████████████│            VSET_PIN_SEL[1-0]          │            RSET_PIN_SEL[1-0]          │ 0x00 │ Регистр управления функциональным назначением выводов VSET, RSET.                                             ║
	╟──────┼─────────────────┼───────────────────┼───────────────────┼───────────────────┼───────────────────┴───────────────────────────────────────┴───────────────────────────────────────┼──────┼───────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
	║ 0x53 │ GPIO_CTL1       │███████████████████│███████████████████│███████████████████│                                          GPIO_IN_EN[4-0]                                          │ 0x00 │ Регистр управления разрешающий работу выводов GPIO в режиме входа.                                            ║
	║ 0x54 │ GPIO_CTL2       │███████████████████│███████████████████│███████████████████│                                          GPIO_OUT_EN[4-0]                                         │ 0x00 │ Регистр управления разрешающий работу выводов GPIO в режиме выхода.                                           ║
	║ 0x55 │ GPIO_CTL3       │███████████████████│███████████████████│███████████████████│                                          GPIO_DATA[4-0]                                           │ 0x00 │ Регистр управления хранит логическое состояние выводов GPIO.                                                  ║
	╟──────┼─────────────────┼───────────────────┼───────────────────┼───────────────────┼───────────────────┬───────────────────┬───────────────────┬───────────────────┬───────────────────┼──────┼───────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
	║ 0xA0 │                 │███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│ 0xXX │                                                                                                               ║
	║ 0xA1 │                 │███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│ 0xXX │                                                                                                               ║
	║ 0xA2 │ BAT_V_ADC_DAT0  │                                                                                           BAT_V_ADC_DAT[7-0]                                                  │ 0xXX │ Регистр данных, АЦП для Vbat (младшие 8 бит).                                                                 ║
	║ 0xA3 │ BAT_V_ADC_DAT1  │███████████████████│███████████████████│                                                   BAT_V_ADC_DAT[13-8]                                                 │ 0xXX │ Регистр данных,              (старшие 6 бит).                                                                 ║
	║ 0xA4 │ BAT_I_ADC_DAT0  │                                                                                           BAT_I_ADC_DAT[7-0]                                                  │ 0xXX │ Регистр данных, АЦП для Ibat (младшие 8 бит).                                                                 ║
	║ 0xA5 │ BAT_I_ADC_DAT1  │███████████████████│███████████████████│                                                   BAT_I_ADC_DAT[13-8]                                                 │ 0xXX │ Регистр данных,              (старшие 6 бит).                                                                 ║
	║ 0xA8 │ BAT_OCV_DAT0    │                                                                                           BAT_OCV_DAT0[7-0]                                                   │ 0xXX │ Регистр данных, АЦП для Vbat без нагрузки (младшие 8 бит).                                                    ║
	║ 0xA9 │ BAT_OCV_DAT1    │███████████████████│███████████████████│                                                   BAT_OCV_DAT0[13-8]                                                  │ 0xXX │ Регистр данных,              (старшие 6 бит).                                                                 ║
	║ 0xAA │                 │███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│ 0xXX │                                                                                                               ║
	║ 0xAB │                 │███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│ 0xXX │                                                                                                               ║
	║ 0xAC │ OUT_V_ADC_DAT0  │                                                                                           OUT_V_ADC_DAT[7-0]                                                  │ 0xXX │ Регистр данных, АЦП для Vout (младшие 8 бит).                                                                 ║
	║ 0xAD │ OUT_V_ADC_DAT1  │███████████████████│███████████████████│                                                   OUT_V_ADC_DAT[13-8]                                                 │ 0xXX │ Регистр данных,              (старшие 6 бит).                                                                 ║
	║ 0xAE │                 │███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│ 0x00 │                                                                                                               ║
	║ 0xAF │                 │███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│ 0x00 │                                                                                                               ║
	╟──────┼─────────────────┼───────────────────┼───────────────────┼───────────────────┴───────────────────┼───────────────────┼───────────────────┼───────────────────┼───────────────────┼──────┼───────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
	║ 0x70 │ REG_READ0       │███████████████████│       TK_EN       │           BATTERY_STATE[1-0]          │     CHARGE_EN     │     BOOST_EN      │     LIGHT_EN      │     DEVICE_EN     │ 0x35 │ Регистр чтения флагов состояния зарядного устройства, повышающего преобразователя, статуса работы и фонарика. ║
	║ 0x71 │ REG_READ1       │                    CHARGING_STATE[2-0]                    │███████████████████│     CHARGE_END    │     CV_OVTIME     │   CC+CV_OVTIME    │     TK_OVTIME     │ 0x00 │ Регистр чтения флагов состояния текущего режима заряда (TK, CC, CV).                                          ║
	║ 0x72 │ REG_READ2       │ LIGHT_PIN_CONNECT │  LIGHT_PIN_IDLE   │███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│ 0x5C │ Регистр чтения флагов состояния фонарика (вывода LIGHT).                                                      ║
	║ 0x77 │ REG_READ3       │███████████████████│███████████████████│███████████████████│███████████████████│    PUSH_BUTTON    │███████████████████│     PUSH_LONG     │    PUSH_SHORT     │ 0x01 │ Регистр чтения флагов состояния кнопки (вывода KEY).                                                          ║
	╟──────┼─────────────────┼───────────────────┼───────────────────┼───────────────────┴───────────────────┼───────────────────┼───────────────────┼───────────────────┼───────────────────┼──────┼───────────────────────────────────────────────────────────────────────────────────────────────────────────────╢
	║      │ Остальные       │███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│███████████████████│ 0xXX │ Остальные регистры мне неизвестны. И так собрал из разных источников, переводя с китайско-англо-ломанного.    ║
	╚══════╧═════════════════╧═══════════════════╧═══════════════════╧═══════════════════╧═══════════════════╧═══════════════════╧═══════════════════╧═══════════════════╧═══════════════════╧══════╧═══════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
	
	РЕГИСТР	БИТ	RW		НАЗВАНИЕ БИТОВ				НАЗНАЧЕНИЕ БИТОВ.
	0xXX	XX	XX		███████████████████			Назначение данного бита мне неизвестно.
	0x01	4	RW		EN_LIGHT_DETECT				1	-	Разрешить автоматическое обнаружение наличия фонарика					(наличие светодиода на выводе LIGHT).
	0x01	3	RW		EN_LIGHT					1	-	Разрешить включать свет фонарика										(не включить, а именно разрешить включать).
	0x01	2	RW		EN_BOOST					1	-	Разрешить включать повышающий DC-DC преобразователь						(не включить, а именно разрешить включать).
	0x01	1	RW		EN_CHARGE					1	-	Разрешить включать зарядное устройство									(не включить, а именно разрешить включать).
	0x02	1	RW		EN_SHUTDOWN_I_LOW			1	-	Переходить в спящий режим при отсутствии нагрузки						(если ток аккумулятора будет ниже чем I_BAT_LOW_TO_SHUTDOWN[4-0] в течении TIME_LONG_PRESS[1-0] секунд, то чип уйдёт в сон).
	0x02	0	RW		EN_AUTOSTART				1	-	Разрешить просыпаться при обнаружении нагрузки							(по умолчанию «1»).
	0x03	7-6	RW		TIME_LONG_PRESS[1-0]		XX	-	Время удержания кнопки, которое будет расценено как длительное нажатие	(«00»-1сек, «01»-2сек, «10»-3сек, «11»-4сек).
	0x03	5	RW		EN_TWO_SHORTPRESS			1	-	Разрешить переход в спящий режим двойным нажатием на кнопку				(по умолчанию «1»).
	0x04	7-6	RW		TIME_TO_SHUTDOWN[1-0]		XX	-	Время через которое чип уйдёт в спящий режим при отсутствии нагрузки	(«00»-8сек, «01»-16сек, «10»-32сек, «11»-64сек). По умолчанию 32сек. Чип уйдёт в сон, только если установлен бит EN_SHUTDOWN_I_LOW и отсутствие нагрузки привело к снижению тока аккумулятора ниже чем указано в I_BAT_LOW_TO_SHUTDOWN[4-0].
	0x04	5	RW		EN_OPEN_BOOST				1	-	Разрешить работу повышающего DC-DC преобразователя при наличии Vin		(по умолчанию «1»).
	0x05	7	RW		RESET						1	-	Перезагрузить чип														(по умолчанию «0»). Если не выполняется зарядка, то после перезагрузки чип будет находиться в спящем режиме.
	0x07	6	RW		EN_NTC						1	-	Разрешить работу (или разрешить включать) NTC							(я так понял, что NTC это термистор, но не уверен, так как китайцы не удасужились расшифровать).
	0x07	1	RW		WAY_LIGHT_ON				X	-	Выбор способа включения света нажатием на кнопку						(«0»-длительное нажатие, «1»-два коротких нажатия).
	0x07	0	RW		WAY_SLEEP_ON				X	-	Выбор способа перехода в спящий режим нажатием на кнопку				(«0»-два коротких нажатия, «1»-длительное нажатие).
	0x22	3-2	RW		V_OUT_WHEN_CHARGING[1-0]	XX	-	Напряжение на выходе Vout, при котором нужно корректировать ток заряда	(«00»-4.53В, «01»-4.63В, «10»-4.73В, «11»-4.83В). Если во время заряда напряжение на выходе превысит указанное значение, то приоритет отдаётся зарядному устройству и ток заряда увеличивается.
	0x24	6-5	RW		V_BAT_SET[1-0]				XX	-	Тип аккумулятора, по его максимальному выходному напряжению				(«00»-4.2В, «01»-4.3В, «10»-4.35В, «11»-зарезервировано). Бит WAY_V_BAT регистра 0x26 должен быть сброшен в «0».
	0x24	2-1	RW		V_BAT_CV_SET[1-0]			XX	-	Дополнительное напряжение в режиме заряда CV							(«00»-00мВ, «01»-14мВ, «10»-28мВ, «11»-42мВ). В режиме CV (заряд постоянным напряжением), на аккумулятор будет подано напряжение V_BAT_SET[1-0] + V_BAT_CV_SET[1-0].
	0x25	4-0	RW		I_BAT_SET[4-0]				XXXXX	Зарядный ток аккумулятора												(Ibat = 4бит*1.4А + 3бит*0.6А + 2бит*0.4А + 1бит*0.2А + 0бит*0.1А). По умолчанию I_BAT_SET[4-0]=«10111» => Ibat = 1*1.4 + 0*0.6 + 1*0.4 + 1*0.2 + 1*0.1 = 1.4 + 0.4 + 0.2 + 0.1 = 2.1А
	0x26	6	RW		WAY_V_BAT					X	-	Способ определения типа аккумулятора по его напряжению					(«0»-тип аккумулятора задаётся через V_BAT_SET[1-0], «1»-тип аккумулятора определяется через вывод VSET).
	0x0C	7-3	RW		I_BAT_LOW_TO_SHUTDOWN[4-0]	XXXXX	Значение тока аккумулятора для определения отсутствия нагрузки			(I = I_BAT_LOW_TO_SHUTDOWN[4-0] * 12мА). Если установлен флаг EN_SHUTDOWN_I_LOW, а ток аккумулятора будет ниже значения I_BAT_LOW_TO_SHUTDOWN[4-0] в течении времени TIME_LONG_PRESS[1-0], то чип перейдёт в спящий режим.
	0x50	7	RW		L2_DRIVE					1	-	Усилить мощность драйвера вывода L2										(по умолчанию «0»).
	0x50	6	RW		L1_DRIVE					1	-	Усилить мощность драйвера вывода L1										(по умолчанию «0»).
	0x50	4	RW		VSET_DRIVE					1	-	Усилить мощность драйвера вывода VSET									(по умолчанию «0»).
	0x50	3	RW		RSET_DRIVE					1	-	Усилить мощность драйвера вывода RSET									(по умолчанию «0»).
	0x50	2	RW		LIGHT_DRIVE					1	-	Усилить мощность драйвера вывода LIGHT									(по умолчанию «1»).
	0x50	1	RW		L4_DRIVE					1	-	Усилить мощность драйвера вывода L4										(по умолчанию «0»).
	0x50	0	RW		L3_DRIVE					1	-	Усилить мощность драйвера вывода L3										(по умолчанию «1»).
	0x51	5-4	RW		LIGHT_PIN_SEL[1-0]			XX	-	Управление функциональным назначением вывода LIGHT						(«00»-LIGHT, «01»-GPIO2, «10»-VREF,            «11»-зарезервировано).
	0x51	3-2	RW		L4_PIN_SEL[1-0]				XX	-	Управление функциональным назначением вывода L4							(«00»-L4,    «01»-GPIO1, «10»-зарезервировано, «11»-зарезервировано).
	0x51	1-0	RW		l3_PIN_SEL[1-0]				XX	-	Управление функциональным назначением вывода L3							(«00»-L3,    «01»-GPIO0, «10»-зарезервировано, «11»-зарезервировано).
	0x52	3-2	RW		VSET_PIN_SEL[1-0]			XX	-	Управление функциональным назначением вывода VSET						(«00»-VSET,  «01»-GPIO4, «10»-зарезервировано, «11»-зарезервировано).
	0x52	1-0	RW		RSET_PIN_SEL[1-0]			XX	-	Управление функциональным назначением вывода VRET						(«00»-RSET,  «01»-GPIO3, «10»-зарезервировано, «11»-зарезервировано).
	0x53	4-0	RW		GPIO_IN_EN[4-0]				XXXXX	Флаги разрешают работу выводов GPIO в режиме входа						(4бит-GPIO4, 3бит-GPIO3, 2бит-GPIO2, 1бит-GPIO1, 0бит-GPIO0).
	0x54	4-0	RW		GPIO_OUT_EN[4-0]			XXXXX	Флаги разрешают работу выводов GPIO в режиме выхода						(4бит-GPIO4, 3бит-GPIO3, 2бит-GPIO2, 1бит-GPIO1, 0бит-GPIO0).
	0x55	4-0	RW		GPIO_DATA[4-0]				XXXXX	Биты устанавливаются в соответствии с логическими уровнями выводов GPIO	(4бит-GPIO4, 3бит-GPIO3, 2бит-GPIO2, 1бит-GPIO1, 0бит-GPIO0).
	0xA2-A3		RW		BAT_V_ADC_DAT[13-0]			АЦП	-	Значение АЦП для рассчёта Vbat = АЦП * (2,2В/2^13) + 2,6В				(значение АЦП может быть отрицательным). Если 13 бит = 1, то АЦП = - ((~АЦП + 1) & 0x1FFF).
	0xA4-A5		RW		BAT_I_ADC_DAT[13-0]			АЦП	-	Значение АЦП для рассчёта Ibat = АЦП * 2,2В/(2^13 * 36 * 0.01Ом)		(значение АЦП может быть отрицательным). Если 13 бит = 1, то АЦП = - ((~АЦП + 1) & 0x1FFF).
	0xA8-A9		RW		BAT_OCV_DAT0[13-0]			АЦП	-	Значение АЦП для рассчёта Vbat без нагрузки = АЦП * (2,2В/2^13) + 2,6В	(значение АЦП может быть отрицательным). Если 13 бит = 1, то АЦП = - ((~АЦП + 1) & 0x1FFF).
	0xAC-AD		RW		OUT_V_ADC_DAT[13-0]			АЦП	-	Значение АЦП для рассчёта Vout = АЦП * (2,2В/2^13) + 3,2В				(значение АЦП может быть отрицательным). Если 13 бит = 1, то АЦП = - ((~АЦП + 1) & 0x1FFF).
	0x70	6	R		TK_EN						1	-	Сигнализирует о том, что аккумулятор заряжается в режиме TK				(режим заряда аккумулятора малым током).
	0x70	5-4	R		BATTERY_STATE[1-0]			XX	-	Сигнализирует о текущем состоянии аккумулятора							(«00»-простаивает, «01»-зарядается, «10»-разрядается, «11»-зарезервировано).
	0x70	3	R		CHARGE_EN					X	-	Сигнализирует о работе зарядного устройства								(только для чтения).
	0x70	2	R		BOOST_EN					1	-	Сигнализирует о работе повышающего DC-DC перобразователя				(только для чтения).
	0x70	1	R		LIGHT_EN					1	-	Сигнализирует о работе фонарика											(горит светодиод подключённый к выводу LIGHT).
	0x70	0	R		DEVICE_EN					1	-	Сигнализирует о работе чипа												(интересно, а как прочитать «0» ?).
	0x71	7-5	R		CHARGING_STATE[2-0]			XXX	-	Информирует о текущем режиме заряда аккумулятора						(«000»-не заряжается, «001»-TK (заряд малым током), «010»-CC (заряд постоянным током), «100»-CV (заряд постоянным напряжением), «101»-время заряда вышло , «110»-время вышло).
	0x71	3	R		CHARGE_END					1	-	Сигнализирует о завершении заряда аккумулятора							(только для чтения).
	0x71	2	R		CV_OVTIME					1	-	Сигнализирует о том, что вышло время заряда аккумулятора в режиме CV	(Аккумулятор заряжался дольше 12 часов).
	0x71	1	R		CC+CV_OVTIME				1	-	Сигнализирует о том, что вышло время заряда аккумулятора в режиме CC+CV	(Аккумулятор заряжался дольше 12 часов).
	0x71	0	R		TK_OVTIME					1	-	Сигнализирует о том, что вышло время заряда аккумулятора в режиме TK	(Аккумулятор заряжался дольше 12 часов).
	0x72	7	R		LIGHT_PIN_CONNECT			1	-	Сигнализирует о обнаружении светодиода подключённого к выводу LIGHT		(только для чтения).
	0x72	6	R		LIGHT_PIN_IDLE				1	-	Сигнализирует о том, что через вывод LIGHT протекает ток ниже 75 мА		(только для чтения).
	0x77	3	RW		PUSH_BUTTON					1	-	Сигнализирует о том, что кнопка нажата									(данный бит сбрасывается записью в него «1»).
	0x77	1	RW		PUSH_LONG					1	-	Сигнализирует о том, что зафиксированно длительное нажатие кнопки		(данный бит сбрасывается записью в него «1»).
	0x77	0	RW		PUSH_SHORT					1	-	Сигнализирует о том, что зафиксированно короткое нажатие кнопки			(данный бит сбрасывается записью в него «1»).
*/

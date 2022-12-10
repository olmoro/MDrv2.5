# <p align="center">MDrv2.5
 
## <p align="center">Драйвер управления измерениями и DC/DC зарядного устройства. Проект Arduino.
#### Исходники проекта не публикуются до завершения миграции их от прототипа в проект MKlon2
#### <p align="right">Редакция от 10.12.2022
***
### <p align="center"> Поддержка Arduino.
К сожалению примененный субмодуль не полностью поддерживается технологией Arduino. Количество аналоговых портов меньше, чем имеет реальный микроконтроллер. В директории documents/Variant на этот счет имеется инструкция.
### <p align="center"> Субмодуль.
Субмодуль [WeMos SAMD21 M0 Mini](https://aliexpress.ru/item/4001074203011.html?_ga=2.268755377.1168692661.1643047564-769654542.1642920280&sku_id=10000014182967685&spm=a2g39.orderlist.0.0.60754aa6RxSv8u) съемный, устанавливается на [разъемы](https://www.chipdip.ru/product0/8002610753) или [панель](https://www.chipdip.ru/product/trl-28). Штыри, идущие в комплекте, использовать для столь ответственного узла не рекомендую. 
### <p align="center"> Питание.
Для питания субмодуля используются гальванически развязанные [источники](https://aliexpress.ru/item/1005003568781579.html?_ga=2.165478714.428003227.1651560775-769654542.1642920280&sku_id=12000026320337806&spm=a2g39.orderlist.0.0.50684aa6oqK3eu) мощностью всего 1 ватт, и это необходимо учитывать.
### <p align="center"> Подключение к USB.
Управляющие команды субмодуль получает по асинхронному интерфейсу от платы управления. Имеющееся смещение между потенциалами общих земель ESP32 и SAMD21 не критично для обмена по UART. Однако одновременно подключать оба входа USB не рекомендуется.
### <p align="center">Измерение напряжения
Входы измерителя напряжения включены по дифференциальной схеме, что позволяет измерять напряжение от -2 до 18 вольт. АЦП 11-разрядный (плюс знаковый), используются его встроенные возможности для получения желаемого разрешения. Измерения производятся с частотой 1кГц, Сеанс занимает порядка 25мкс, включая пересчет в физические величины. Делитель, фильтр и элементы защиты входов расположены на основной плате. Там же предусмотрено место для установки внешнего источника опорного напряжения на 1.25 или 2.5 вольта. 
### <p align="center">Измерение токов заряда и разряда
Входы измерителя токов заряда и разряда включены по дифференциальной схеме, измерения токов возможны в диапазоне напряжений на шунте от -200 до +200 милливольт. Настройки АЦП несколько отличаются от приведенного выше, но частота и длительность сеанса те же.
### <p align="center">Управление зарядом
Управление понижающим преобразователем производится 9-разрядным ШИМ-сигналом частотой 190кГц. На большее даже в турбо-режиме таймеры микроконтроллера не способны. Для регулирования напряжения и токов используются ПИД-регуляторы с раздельными настройками. Принцип переключения от поддержания тока к поддержанию напряжения и обратно соответствует аналоговому регулятору 912-го кулона. Коэффициенты допускается регулировать "на лету". Для реализации импульсных режимов предусмотрены сохранение и восстановление параметров регулирования, но задание временнЫх параметров (длительность импульсов, например) возлагается на управляющий контроллер. Регулирование ведется с фиксированной частотой 10 Гц. Все вычисления целочисленные, так что вычисление шага занимает лишь несколько микросекунд. С этой целью параметры управления драйверу передаются предвычисленными и целочисленными.
### <p align="center">Управление разрядом
Ток разряда задается 10-разрядным встроенным ЦАП с поддержанием тока ПИД-регулятором. Схема разряда заимствована от Кулона 912.
### <p align="center">Управление подключением нагрузки
Поскольку предполагается, что измеритель напряжения постоянно подключен к выходным клеммам, включение силового DC/DC производится только одновременно с подключением к клеммам (вывод /sw).
### <p align="center">Интерфейс
Обмен с управляющим контроллером производится по асинхронному каналу на 230400 бод. Протокол обмена [WAKE](https://eewiki.ru/wiki/%D0%A1%D0%BF%D0%B5%D1%86%D0%B8%D1%84%D0%B8%D0%BA%D0%B0%D1%86%D0%B8%D1%8F_%D0%BF%D1%80%D0%BE%D1%82%D0%BE%D0%BA%D0%BE%D0%BB%D0%B0_WAKE) предусматривает проверку целостности пакета и подтверждение приема. Ведущим контроллером является управляющий контроллер ESP32, в фоновом режиме опрашивающий драйвер и получающий пакет, содержащий измерения напряжения в милливольтах и ток в миллиамперах, а также информацию о состоянии. Управляющими командами производится включение-отключение DC источника и задание напряжения и тока для ПИД-регулятора. Предусматривается достаточное количество команд настройки АЦП, приборного смещения, калибровочных коэффициентов для  преобразования в физические величины, порогов срабатывания защиты и т.д. для управления и настройки ПИД-регулятора. И ещё масса тестовых команд, надобность в которых практически отпала по ходу дела. Заводские и пользовательские установки хранятся в памяти управляющего контроллера и загружаться на этапе инициализации, заменяя параметры разработчика (defaults).
В директории Frames представлены данные для тестирования с помощью приложения WakeUsb.
### <p align="center">Синхронизация
Цепи сброса ESP32 и SAMD21 объединены - по любой из кнопок сброса производится возврат в начальное состояние, однако SAMD21 после этого требуется загрузить пользовательскими данными, которые, дабы не плодить лишние сущности, хранятся в энергонезависимой памяти ESP32. С этой целью в межпроцессорный интерфейс добавлено соединение READY. Можно, конечно, сэмулировать ЭНОЗУ на борту SAMD21, но при обновлении данные будут уничтожаться. 
### <p align="center">Диагностика
Рядом с модулем расположен диагностический разъем для подключения 8-канального логического анализатора просто воткнув его в разъем. Можете его случайно перевернуть - ничего с ним не сделается. Учтите, что анализатор перекрывает воздушный поток от вентилятора. Шесть сигналов заведены на него постоянно, а два можно выбрать, перемкнув нужные выводы по-ардуиновски.
### <p align="center">Примеры команд (всего их около сотни)
Имя | Код | Параметр | Ответ | Примечание
--------------------------:|------:|-------:|-------------:|----------------------------------:
cmd_read_u_i|0x10|-|int int uint|Чтение напряжения,тока (мВ и мА) и состояния
cmd_get_state|0x15|-|uint|Чтение температуры радиатора
cmd_power_go|0x20|-|-|Старт преобразователя с заданными максимальными U и I
cmd_power_stop|0x21|-|-|Отключение ( и разряда в том числе)
cmd_pid_configure|0x40|uint uint uint uint uint uint|-|set mode,kp,ki,kd,min,max
cmd_pid_set_coefficients|0x41|uint uint uint|-|set kp, ki, kd


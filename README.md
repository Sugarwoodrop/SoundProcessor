2 Лабораторная НГУ ФИТ 2 курс на языке c++.

Программа получает на вход (в аргументах командной строки) набор исходных файлов (input1.wav, input2.wav, и т.д.), выходной файл (например, output.wav) и текстовый файл примерно следующего содержания:

# заглушить первые 30 секунд input1
mute 0 30
# смиксовать с input2, начиная с секунды 10
mix $2 10
# заглушить 3-ю минуту в миксованном потоке
echo 120 180


На выходе программа создает выходной WAV-файл со звуком, соответствующим переданной конфигурации. Если выходной WAV-файл уже существует, программа его перезаписывает. Программа не изменяет входные файлы, она их только читает.

Поддерживаемые преобразования (конвертеры):

1. mute - заглушить интервал
2. mix - смиксовать два файла
3. echo - добовляет ехо в интервале

Для конверсии поддерживается только следующий формат входных файлов:

Аудио-формат PCM (без кодирования);
Моно-звук (1 канал);
Разрядность 16 бит со знаком (signed 16 bit (little-endian)) — это значит, что один сэмпл представлен целым 16-битным числом со знаком;
Частота 44100 Гц.

ПРОГРАММА НЕ ПРОВЕРЯЕТ КОРРЕКТНОСТЬ ЭТИХ ЗНАЧЕНИЙ. 

Количество используемой оперативной памяти не зависет от размера входных файлов.

Файлы нужно указывать в параметрах запуска без -
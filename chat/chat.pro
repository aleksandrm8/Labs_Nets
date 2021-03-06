TEMPLATE = subdirs

SUBDIRS += \
    chat_client \
    chat_server

#Вариант №4
#1. Описание задачи
#Необходимо разработать приложение-чат для обмена сообщениями между несколькими клиентами
#через сервер с использованием блокирующих сокетов, протокола TCP.
#2. Требования к реализации
#Графический интерфейс
#Ввод IP-адреса принимающего/передающего узла
#Ввод номера порта принимающего/передающего экземпляра приложения
#Отображать время приема и передачи сообщения.
#Отображать сообщения о возникающих ошибках и корректно их обрабатывать.
#Дополнительно: обмен сообщениями должен происходить между клиентами через сервер.
#3. Требования к надежности
#К приложению предъявляются следующие требования по надежности:
#Не допускается зависание приложения при любых действиях пользователя.
#Не допускается аварийное завершение приложения при любых действиях пользователя.
#Любая ошибочная ситуация должна корректно обрабатываться с выводом соответствующего сообщения.
#Не допускается утечка памяти/дескрипторов в процессе эксплуатации приложения.
#Не допускается полная загрузка процессора приложением в пассивном состоянии.
#Графический интерфейс не должен зависать во время передачи/приема сообщений,
#а также во время ожидания подключения клиента к серверу  (многопоточное приложение).

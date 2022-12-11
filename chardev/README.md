Для запуска компиляции и запуска chardev.c выполните действия:
    1)Скачайте chardev.c и Makefile и расположите в одном месте
    2)Запустите Makefile командой make
    3)Пропишите команду: sudo insmod chardev.ko чтобы добавить модуль в ядро linux
    4)Чтобы проверить работу модуля запустите команду: sudo dmesg | tail -10
последняя запись должна быть:
    [] I was assigned major number 235.
    [] Device created on /dev/chardev
    5)Команда чтобы убарть модуль: sudo rmmod chardev.ko

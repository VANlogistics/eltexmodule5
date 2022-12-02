/*
Задание 1 по модулю 5: Написать модуль ядра Hello World для своей версии ядра.
Результаты выложить на github или др. общедоступный git.
 Cсылку на git выслать в ЛС для проверки.
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("VANSKUR");
MODULE_DESCRIPTION("HELLO WORD module");

static int __init hello_init(void){
    printk(KERN_INFO "HELLO WORLD!\n");
    return 0;
}

static void __exit hello_cleanup(void){
    printk(KERN_INFO "Cleaning up module\n");
}

module_init(hello_init);
module_exit(hello_cleanup);

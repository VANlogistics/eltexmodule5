#include <linux/module.h>
#include <linux/printk.h>
#include <linux/kobject.h> 
#include <linux/sysfs.h> 
#include <linux/init.h> 
#include <linux/fs.h> 
#include <linux/string.h>
#include <linux/configfs.h>
#include <linux/tty.h>          /* For fg_console, MAX_NR_CONSOLES */
#include <linux/kd.h>           /* For KDSETLED */
#include <linux/vt.h>
#include <linux/console_struct.h>       /* For vc_cons */
#include <linux/vt_kern.h>
#include <linux/timer.h>

#define BLINK_DELAY   HZ/5
#define ALL_LEDS_ON   0x07
#define RESTORE_LEDS  0xFF

static struct kobject *example_kobject;
static int kbledsnum = 3;


static int _kbledstatus = 0;
//static int test = 3;// cod


struct timer_list my_timer;
struct tty_driver *my_driver;

static ssize_t foo_show(struct kobject *kobj, struct kobj_attribute *attr,char *buf)
{
        return sprintf(buf, "%d\n", kbledsnum);
}

static ssize_t foo_store(struct kobject *kobj, struct kobj_attribute *attr,const char *buf, size_t count)
{
        sscanf(buf, "%du", &kbledsnum);
        return count;
}



// Flash keybord

static void my_timer_func(struct timer_list *ptr) {
        int *pstatus = &_kbledstatus;
        if (*pstatus == kbledsnum)
                *pstatus = RESTORE_LEDS;
        else
                *pstatus = kbledsnum;
        (my_driver->ops->ioctl) (vc_cons[fg_console].d->port.tty, KDSETLED,
                            *pstatus);
        my_timer.expires = jiffies + BLINK_DELAY;
        add_timer(&my_timer);

}

//static struct kobj_attribute foo_attribute =__ATTR(foo, 0660, foo_show, foo_store);
static struct kobj_attribute foo_attribute =__ATTR(kbledsnum, 0660, foo_show, foo_store);

static int __init sys_init (void) {
        int error = 0;

        pr_debug("Module initialized successfully \n");

// Создаем каталог в каталоге sys/kernel
        example_kobject = kobject_create_and_add("kbleds_example", kernel_kobj);
        if(!example_kobject)  return -ENOMEM;


        error = sysfs_create_file(example_kobject, &foo_attribute.attr);
        if (error) {
                pr_debug("failed to create the foo file in /sys/kernel/kobject_example \n");
        }

        int i;
        printk(KERN_INFO "kbleds: loading\n");
        printk(KERN_INFO "kbleds: fgconsole is %x\n", fg_console);
        for (i = 0; i < MAX_NR_CONSOLES; i++) {
                if (!vc_cons[i].d)
                        break;
                printk(KERN_INFO "poet_atkm: console[%i/%i] #%i, tty %lx\n", i,
                       MAX_NR_CONSOLES, vc_cons[i].d->vc_num,
                       (unsigned long)vc_cons[i].d->port.tty);
        }
        printk(KERN_INFO "kbleds: finished scanning consoles\n");
        my_driver = vc_cons[fg_console].d->port.tty->driver;
        printk(KERN_INFO "kbleds: tty driver magic %x\n", my_driver->magic);
        /*
         * Set up the LED blink timer the first time
         */
        
        //init_timer(&my_timer);
        timer_setup(&my_timer, my_timer_func, 0);
        //my_timer.function = my_timer_func;
        //my_timer.data = (unsigned long)&kbledstatus;
        my_timer.expires = jiffies + BLINK_DELAY;
        add_timer(&my_timer);


        return error;

        
}

static void __exit sys_exit (void)
{
        pr_debug ("Module un initialized successfully \n");
        kobject_put(example_kobject);

        printk(KERN_INFO "kbleds: unloading...\n");
        del_timer(&my_timer);
        (my_driver->ops->ioctl) (vc_cons[fg_console].d->port.tty, KDSETLED,
                            RESTORE_LEDS);
}


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Example module illustrating the use of Keyboard LEDs.");


module_init(sys_init);
module_exit(sys_exit);

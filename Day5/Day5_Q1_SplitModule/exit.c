#include<linux/module.h>
#include<linux/kernel.h>

static void __exit hello_exit(void){
    printk(KERN_INFO "%s : hello_exit() called\n", THIS_MODULE->name);

}

module_exit(hello_exit);
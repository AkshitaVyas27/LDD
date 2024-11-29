#include<linux/module.h>
#include<linux/kernel.h>
#include "export.h"


int __init import_init(void){
    printk(KERN_INFO "%s import_init() called\n", THIS_MODULE->name);
    printk(KERN_INFO "%s 1st import_init()  count=%d", THIS_MODULE->name, cnt);
    new_fn();
    printk(KERN_INFO "%s 2nd import_inti() count=%d", THIS_MODULE->name, cnt);
    return 0;
}

void __exit import_exit(void){
    printk(KERN_INFO "%s import_exit() called \n", THIS_MODULE->name);

}

module_init(import_init);
module_exit(import_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Day three eport");
MODULE_AUTHOR("Akshita Vyas <akshitavyas1302@gmail.com>");

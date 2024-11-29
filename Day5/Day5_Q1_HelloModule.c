#include <linux/module.h>

int __init init_module(void){
    printk("hello init() module called\n");
    return 0;

}

void __exit cleanup_module(void){
    printk("cleanup module called\n");

}

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hello kernel module for me Aug 24");
MODULE_AUTHOR("Akshita Vyas");

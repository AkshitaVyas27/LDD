#include<linux/module.h>
#include<linux/kernel.h>

static int __init hello_init(void){
    printk(KERN_INFO " %s : hello_init() called\n", THIS_MODULE->name);
    return 0;

}

module_init(hello_init);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Second code day three");
MODULE_AUTHOR("Nilesh Ghule <nileshghulesunbeaminfo.com>");
#include<linux/module.h>
#include<linux/kernel.h>

int cnt=101;
void new_fn(void){
    printk(KERN_INFO " %s :in new_fn()", THIS_MODULE->name);
    cnt++;
    
}
 static int __init expot_init(void){
    printk(KERN_INFO "%s expot_init() called\n", THIS_MODULE->name);
    return 0;
}

 static void __exit export_exit(void){
    printk(KERN_INFO "%s export_exit() called \n", THIS_MODULE->name);

}

module_init(expot_init);
module_exit(export_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Day three eport");
MODULE_AUTHOR("Akshita Vyas <akshitavyas1302@gmail.com>");

EXPORT_SYMBOL(cnt);
EXPORT_SYMBOL_GPL(new_fn);

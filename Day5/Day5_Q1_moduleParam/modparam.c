#include<linux/kernel.h>
#include<linux/module.h>
#include <linux/moduleparam.h>

static char* user="DESD";
module_param(user, charp,0644);
static int cnt =3;
module_param_named(count,cnt, int,0644);

static int __init mod_pram(void){
    int i;
    printk(KERN_INFO "%s mod_paraminit() called\n", THIS_MODULE->name);
    for(i=1;i<=cnt;i++){
    printk(KERN_INFO "%s Hi %s here we are\n", THIS_MODULE->name, user );
    }
    return 0;
}

static void __exit mod_para_exit(void){
    int i;
    printk(KERN_INFO "%s param_exit called \n", THIS_MODULE->name);
    for(i=1;i<=cnt;i++){
    printk(KERN_INFO "%s bye %s there we go \n", THIS_MODULE->name, user );
}
}

module_init(mod_pram);
module_exit(mod_para_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Daay three 3rd code");
MODULE_AUTHOR("Nilesh Ghule <nilesh@sunbeaminfo.com>");
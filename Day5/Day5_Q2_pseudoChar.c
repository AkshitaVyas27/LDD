#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kfifo.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>


typedef struct pchardev{
    dev_t devno;
    struct cdev cdev;
    struct kfifo mybuf;
    int id;
}pchardev_t;
pchardev_t *devices;
static int DVCNT=4;
#define MAX 32
static dev_t devno;
static int pchar_open(struct inode *pinode, struct file *pfile){
    pchardev_t *d=container_of(pinode->i_cdev, pchardev_t, cdev);
   pfile->private_data=d;
   printk(KERN_INFO "%s pchar_open() called device closed pchar%d", THIS_MODULE->name, dev->id);

    return 0;
    

} 

static int pchar_close(struct inode *pinode, struct file *pfile){
  pchardev_t *d=(pchardev_t *)pfile->private_data;
  printk(KERN_INFO "%s pchar_close() called device closed pchar%d", THIS_MODULE->name, dev->id);

}

static ssize_t pchar_write(struct file *pfile, const char * __user ubuf, size_t bufsize, loff_t *pf_pos) {
    int nbytes,ret;
    ret=kfifo_from_user(&fifo, ubuf, bufsize, &nbytes);
    if(ret!=0){
        printk(KERN_ERR "%s pchar_write() failed\n", THIS_MODULE->name);
        return ret;
    }
    printk(KERN_INFO "%s pchar_write() called, wrote %d bytes\n", THIS_MODULE->name, nbytes);
    return nbytes;
}

static ssize_t pchar_read(struct file *pfile, char * __user ubuf, size_t bufsize, loff_t *pf_pos) {
    int nbytes,ret;
    kfifo_to_user(&fifo, ubuf, busize, nbytes);
    if(ret!=0){
        printk(KERN_ERR "%s pchar_write() failed\n", THIS_MODULE->name);
        return ret;
    }
    printk(KERN_INFO "%s pchar_write() called, wrote %d bytes\n", THIS_MODULE->name, nbytes);
}   return nbytes;


struct file_operations pchar_fops={
    .owner=THIS_MODULE,
    .open=pchar_open,
    .release=pchar_cose,
    .read=pchar_read,
    .write=pchar_write
}
static int major;
static class *pclass;
struct kfifo *fifo;

static int __init desd_init(void) {
    struct device *pdevice;
    printk(KERN_INFO "%s: desd_init() called.\n", THIS_MODULE->name);
    int ret,i;
   devices=(pchardev_t*)kmalloc(DVCNT*sizeof(pchardev_t),GFP_KERNEL);
    if(IS_ERR(devices)){
        printk(KERN_ERR "%s kmalloc() has failed\n", THIS_MODULE->name);
        //..........
        goto kmalloc_failed;
        ret=-1;
    }
   devno=MKDEV(major,0);
   ret=alloc_chrdev_region(&devno, 0, DVCNT,"pchar");
   if(ret!=0){
    printk(KERN_ERR "%s alloc_chrdev_region() failed\n", THIS_MODULE->name);
        //..........
        ret=-1;
        goto alloc_chrdev_region_failed;
   }
   major=MAJOR(devno);
   printk(KERN_INFO "%s alloc sucessful with major number: %d\n",THIS_MODULE->name, major);
   
   pclass=class_create("pchar_class");
   if(IS_ERR(pclass)){
     printk(KERN_ERR "%s class() failed\n", THIS_MODULE->name);
        //..........
        ret=-1;
        goto class_create_failed;
   }
   for(i==;i<DVCNT;i++){
   devnum=MKDEV(major, i);
   pdevice=device_create(pclass, NULL, devnum, NULL, "pchar%d",i);
   if(IS_ERR(pdevice)){
    printk(KERN_ERR "%s device_create() failed for pchar%d\n", THIS_MODULE->name, i);
        //..........
        goto device_create_failed;
        }
   }

    for(i=0;i<DVCNT;i++){
        devices[i].id=i;
        devices[i].cdev.owner=THIS_MODULE;
        cdev_init(&devices[i].cdev, &pchar_fops);
        ret=cdev_add(&devices[i].cdev, devnum, 1);
        if(ret!=0){
            printk(KERN_INFO "%s cdev_add() has failed\n", THIS_MODULE->name);
            goto cdev_add_fail;
        }    
    }
    return 0;
    for(i=0;i<DVCNT;i++){
     devices[i].id=i;
     devices[i].devno=MKDEV(major,i);   
    ret=kfifo_alloc(&devices[i].mybuf, MAX, GFP_KERNEL);
    if(ret!=0){
        printk(KERN_ERR "%s kfifo_alloc() has failed\n" THIS_MODULE->name);  
        //.......... 
        goto kfifo_alloc_failed;  
      }
    }

    return 0;

    kfifo_alloc_failed;
    for(i = i - 1; i >= 0; i--) {
        kfifo_free(&devices[i].mybuf);
    }
    for(i=i-1;i>=0;i++){

    cdev_del(&devices[i].cdev);
    }
    i = DEVCNT;
    cdev_add_fail;
    for(i=i-1;i>=0;i--){
        devnum=MKDEV(major,i);
        device_destroy(pclass, devnum);
    }
    i = DEVCNT;

    kfifo_alloc_failed:
    for(i = i - 1; i >= 0; i--) {
        kfifo_free(&devices[i].mybuf);
    }
    i = DEVCNT;
cdev_add_failed:
    for(i = i - 1; i >= 0; i--) {
        cdev_del(&devices[i].cdev);
    }
    i = DEVCNT;
device_create_failed:
    for(i = i - 1; i >= 0; i--) {
        devnum = MKDEV(major, i);
        device_destroy(pclass, devnum);
    }
    class_destroy(pclass);
class_create_failed:
    unregister_chrdev_region(devno, DEVCNT);
alloc_chrdev_region_failed:
    kfree(devices);
kmalloc_failed:
    return ret;
}
    


static void __exit desd_exit(void) {
    printk(KERN_INFO "%s: desd_exit() called.\n", THIS_MODULE->name);
    pr_info("%s: pchar_exit() called.\n", THIS_MODULE->name);
    // deinitialize device info
    for(i=0; i<DEVCNT; i++) {
        kfifo_free(&devices[i].mybuf);
        pr_info("%s: kfifo_free() released fifo for pchar%d\n", THIS_MODULE->name, i);
    }
    // delete cdev from kernel
    for(i=0; i<DEVCNT; i++) {
        cdev_del(&devices[i].cdev);
        pr_info("%s: cdev_del() removed cdev from kernel for pchar%d\n", THIS_MODULE->name, i);
    }
    // destroy device files
    for(i=0; i<DEVCNT; i++) {
        device_destroy(pclass, devices[i].devno);
        pr_info("%s: device_destroy() destroyed device file pchar%d\n", THIS_MODULE->name, i);
    }
    // destroy device class
    class_destroy(pclass);
    pr_info("%s: class_destroy() destroyed device class\n", THIS_MODULE->name);
    // unregister device numbers
    unregister_chrdev_region(devno, DEVCNT);
    pr_info("%s: unregister_chrdev_region() released device numbers: major = %d\n", THIS_MODULE->name, major);

}

module_init(desd_init);
module_exit(desd_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hello Kernel Module");
MODULE_AUTHOR("Nilesh Ghule <nilesh@sunbeaminfo.com>");

#include <linux/init.h> // For init, exit macro
#include <linux/module.h> // Core header for LKM(Linux Kernel Module)
#include <linux/kernel.h> // Core header for Kernel

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SecuritySchool");
MODULE_DESCRIPTION("Airplance Prototype - LKM");
MODULE_VERSION("0.1");

//Module Init function
static int __init pssapl_init(void);

//Module Exit function
static void __exit pssapl_exit(void);

//Set init function to kernel
module_init(pssapl_init);

//Set exit function to kernel
module_exit(pssapl_exit);



//Module Init function
static int __init pssapl_init(void){
    printk(KERN_INFO "[%s] Hello LKM!\n", __FUNCTION__);
    return 0;
}

//Module Exit function
static void __exit pssapl_exit(void){
    printk(KERN_INFO "[%s] Goodbye LKM!\n", __FUNCTION__);
}

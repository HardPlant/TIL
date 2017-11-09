#include <linux/init.h> // For init, exit macro
#include <linux/module.h> // Core header for LKM(Linux Kernel Module)
#include <linux/kernel.h> // Core header for Kernel
#include <linux/binfmts.h>

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

//Symbols from kernel
typedef int (*security_bprm_check_func)(struct linux_binprm *bprm);
extern void security_bprm_check_set_pss_filter(security_bprm_check_func pfunc);
extern void security_bprm_check_unset_pss_filter(void);

//filter function
static int pssapl_filter_func(struct linux_binprm *bprm);

//Module Init function
static int __init pssapl_init(void){
    printk(KERN_INFO "[%s] Hello LKM!\n", __FUNCTION__);

    //set filter
    security_bprm_check_set_pss_filter(pssapl_filter_func);

    return 0;
}

//Module Exit function
static void __exit pssapl_exit(void){
    //unset filer before exit
    security_bprm_check_unset_pss_filter();
    printk(KERN_INFO "[%s] Goodbye LKM!\n", __FUNCTION__);
}

//filter function
static int pssapl_filter_func(struct linux_binprm *bprm){
    print(KERN_INFO "[pssapl] New process (file:%s)\n", bprm->filename);

    if(NULL != bprm->filename && NULL != strstr(bprm->filename, "pssap_eicar"))
    {
        printk(KERN_INFO "[pssapl] blocked\n");
        return -EACCES;
    }
    return 0;
}
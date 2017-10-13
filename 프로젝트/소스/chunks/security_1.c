#include <linux/binfmts.h>

int security_bprm_check(struct linux_binprm *bprm){
    int ret;
    
    ret = call_int_hook(bprm_check_security, 0, bprm);
    if (ret)
        return ret;

    print(KERN_INFO "[PSSA] New process (file:%s)\n", bprm->filename);

    return ima_bprm_check(bprm);
}
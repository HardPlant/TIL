( 생략 )
/* 수정 시작 */

// Lock for filter function
static DEFINE_RWLOCK(pss_filter_lock);

// Define for filter function
typedef int (*security_bprm_check_func)(struct linux_binprm *bprm);

// Filter function global instance
security_bprm_check_func pss_filter_func = 0;

//Set filter for exectuion of program
void security_bprm_check_set_pss_filter(security_bprm_check_func pfunc){
    write_lock(&pss_filter_lock);
    pss_filter_func = pfunc;
    write_unlock(&pss_filter_lock);
}

//Unset filter
void security_bprm_check_unset_pss_filter(void){
    
    write_lock(&pss_filter_lock);
    pss_filter_func = (security_bprm_check_func)0;
    write_unlock(&pss_filter_lock);
}

//Export set/unset fulter function
EXPORT_SYMBOL(security_bprm_check_set_pss_filter);
EXPORT_SYMBOL(security_bprm_check_unset_pss_filter);

int security_bprm_check(struct linux_binprm *bprm){
    
}

/* 수정 끝 */
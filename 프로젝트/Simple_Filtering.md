이전 : [](프로젝트\write_log_of_running_process.md)

## 간단한 필터링 구조 만들기

커널 이미지를 재빌드하고 테스트하는 데 시간이 오래 걸리고 불편한다.
이를 위해 커널 모듈을 사용하자.

커널의 security.c에 필터링을 위한 인터페이스를 제공하도록 바꿔 보자.

> [](프로젝트\소스\chunks\security_2.c)

> static DEFINE_RWLOCK(pss_filter_lock);

DEFINE_RWLOCK은 콜백 변수를 위한 읽기, 쓰기 잠금이다. 콜백 함수가 호출되는 시점에 콜백을 해제하려면 lock이 필요하다.

> typedef int (*security_bprm_check_func)(struct linux_binprm *bprm);

콜백 함수 타입이다. security_bprm_check 함수와 동일하다.

> void security_bprm_check_set_pss_filter(security_bprm_check_func pfunc)
 
콜백을 등록한다. 쓰기 잠금을 얻은 후 인자로 받은 콜백을 pss_filter_func 전역 변수에 저장한다.

> EXPORT_SYMBOL(..);

앞의 두 인터페이스를 커널 모듈이 사용할 수 있게 심볼 테이블에 추가한다.

>read_lock()

시스템 콜은 여러 개의 CPU 코어에서 동시에 호출할 수 있으므로, 읽기 잠금으로 동시 호출 시 성능에 문제가 없도록 해야 한다.

>ret = pss_filter_func(bprm);

저장되어 있는 콜백을 호출한다.
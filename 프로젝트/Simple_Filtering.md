이전 : [](프로젝트\write_log_of_running_process.md)

## 간단한 필터링 구조 만들기

커널 이미지를 재빌드하고 테스트하는 데 시간이 오래 걸리고 불편한다.
이를 위해 커널 모듈을 사용하자.

* 필터링 인터페이스

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

소스를 수정했으면 _make bzImage_로 커널 이미지만 재빌드하고 _make install_로 설치한 후 시스템을 재부팅하자.
추가한 인터페이스는 EXPORT_SYMBOL을 이용해 커널 심볼로 등록했다. 이 심볼들은 /proc/kallsyms에서 확인할 수 있다.

심볼이 보인다면 필터링 인터페이스가 준비된 것으로, 더 이상 커널을 재빌드할 필요가 없다.

* EICAR 바이러스

필터링 기능을 테스트할 샘플 바이러스인 [EICAR 바이러스](http://www.eicar.org/96-0-Intended-use.html)를 다운로드받자.
EICAR 바이러스는 백신 기능을 테스트하기 위해 만든 가짜 바이러스로, 실행해도 시스템에 악영향을 끼치지는 않는다.

ptototype/pssap_eicar라는 디렉터리를 만들고, 다음과 같이 간단한 C 소스를 만든다.

> [](프로젝트\소스\pssap_eicar.c)

Makefile은 다음과 같이 작성한다. 이 Makefile은 Security School 전반에서 사용하므로 꼭 작성해야 한다.

> [](프로젝트\소스\eicar_Makefile)

> PROGNAME = pssap_eicar

    빌드된 object 파일을 pssap_eicar라는 이름으로 만든다. 실행 파일은 PROGNAME이므로, 다른 소스를 빌드하려고 사용할 떄 이 값을 변경한다.

빌드해 실행하면 자신의 존재를 알리는 로그만 출력한다. 앞으로 백신 기능을 테스할 때 이 파일을 사용한다.

이제 커널 모듈을 만들어 보자. 이전에 만들었던 커널 모듈에 필터 함수를 콜백으로 추가한다.

> [](프로젝트\소스\pssap_lkm.1.c)



#백신의 실행 파일 실시간 감시

실시간 감시 기능을 구현하려면 커널에서 파일이나 프로세스의 행위를 감시해야 한다.
리눅스 커널에서는 Linux Security Model이라는 이름으로 보안 필터링 계층을 제공한다.
LSM의 구조를 이해해야 필요한 프로세스 필터링을 구현할 수 있다.


* Linux Security Model

    유저 레벨 App이 test.txt 파일을 open할 때, C 라이브러리의 fopen()이 호출된다.
    이 때 커널의 시스템 콜이 호출되며, 이 시스템 콜이나 그 하위 코드를 수정하면 모든 행위를 감시할 수 있다.

    방대한 커널 코드에서 필요한 필터링 시점을 찾는 건 어렵고, 커널 코드는 계속 수정되고 있다.
    따라서 보안을 위해 필요한 인터페이스를 한 곳에 모으게 됬고, 그 파일 이름이 security.c이다.
    우분투의 AppArmor, 규칙을 쉽게 표현하는 Tomoyo, 타이젠의 SMACK 등이 이 프레임워크를 이용하고 있다.

    이 security.c 소스만 분석하면 모든 커널 소스를 분석하지 않고 프로세스 필터링 기능을 추가할 수 있다.
    프로세스뿐만 아니라 파일이나 소켓 필터링도 security.c 소스를 수정해서 구현할 수 있고,
    리눅스 기반 보안 솔루션을 개발할 때에도 secuirty.c 소스가 중요하다.

    security.c 소스에서 어떤 함수가 프로세스 필터링과 연관 있는지 찾아보자.
    프로세스를 새로 만들 때에는 fork, execve가 사용된다.
    커널 소스를 분석해 execve 관련 시스템 콜이 security.c의 어떤 함수를 호출하는지 찾아보자.

    예를 들어, 유저 레벨에서 파일을 열 떄 사용하는 open 함수에 대응하는 시스템 콜은 다음과 같다.

> SYSCALL_DEFINE3(open, const char __user*, filename, int, flags, umode_t, mode)
>{
>    if(force_o_largefile())
>        flags |= O_LARGEFILE;
>    return do_sys_open(AT_FDCWD, filename, flags, mode);
>
>}

SYSCALL_DEFINE 매크로가 시스템 콜을 나타낸다 이를 일반화하면

> SYSCALL_DEFINE 숫자 함수이름, 인자들

그럼 find 명령어와 grep으로 execve 함수가 시스템 콜로 구현된 모습을 찾아보자.

> find ./ -type f -name "*.c" | xargs grep -E 'SYSCALL_DEFINE.*execve *,';

해당 fs/exec.c 파일에 구현되어 있다. 해당 소스를 분석해 security.c 소스에서 어떤 함수가 호출되는지 찾아보자.

커널 소스를 이해하고자 할 때 커널 소스 브라우저 사이트가 만들어져 있다.
http://lxr.free-electrons.com/

    fs/exec에서 execve가 실행됬다고 하는 주석 (v4.13.6에서는 :1794) 앞쪽에 exec_binprm,
    exec_binprm()에서 ret 결과값인 search_binary_handler(bprm),
    search_binary_handler의 security_bprm_check(); 부분이 security.c 파일의 함수이다.


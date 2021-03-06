#커널 모듈 만들기

    커널은 OS의 핵심이다.
    하드웨어를 추상화해 유저 레벨에 일관된 인터페이스를 제공하고, 하드 디스크나 키보드 같은 하드웨어를 관리한다.
    세상에는 수만 가지의 장치가 존재하고, 커널이 이 모든 장치의 제어 코드를 포함하면 크기가 불필요하게 커지므로
    흔하지 않은 장비는 별도로 설치하게 된다. 윈도우에서는 이것을 '드라이버'라고 부르고, 리눅스에서는 '커널 모듈'
    이라고 부른다.

    커널에서 동작해야 하는 코드는 모두 모듈로 만들 수 있다.
    이런 모듈 구조는 커널 코드 개발시에도 유용하다. 코드를 수정한 후 모듈만 재빌드하면 되기 때문이다.

* 간단한 커널 모듈

    workspace 밑에 pssa/lkm 디렉터리를 차례로 만든다.

    그리고 pssap_lkm.c 소스 파일을 다음과 같이 만든다.

>[pssap_lkm.c](소스\pssap_lkm.c)

    모듈은 실행 파일보다는 라이브러리의 집합이라고 생각하면 편하다.
    module_init()으로 모듈을 초기화하고, module_exit()로 할당된 자원을 해제한다.
    이 둘은 각각 커널이 모듈을 로드할 때, 종료될 때에 호출한다.

* 커널 모듈 빌드를 위해 Makefile 작성

>[Makefile](소스\Makefile)

    소스 파일 이름으로 object 파일을 지정한다.

 > obj-m += pssap_lkm.o

    빌드하면 'pssap_lkm.ko'라는 이름의 커널 모듈이 생성된다.
    Makefile이 있는 곳으로 가서 빌드하자.

> make

    빌드된 커널 모듈 pssal_lkm.ko를 로드한다.

> sudo dmesg -C
> sudo insmod pssap_lkm.ko
> lsmod | grep -i pss
> dmesg | grep -i pss

    dmesg -C로 기존 커널 로그를 삭제한 후,insmod로 커널 모듈을 로드한다.
    이후 lsmod로 로드된 커널 모듈을, dmesg로 커널 모듈의 로그를 확인한다.

>sudo rmmod pssap_lkm
>lsmod | grep -i pss
>dmesg | grep -i pss

    커널 모듈을 종료한 경우도 확인해본다.

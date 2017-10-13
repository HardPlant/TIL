#리눅스 커널 수정과 모듈 만들기

## 환경
    Target Device : Ubuntu 14.04 Desktop / 1GHz/ 1024MB RAM
    Update Server : Ubuntu 14.04 Desktop / 1GHz/ 2048MB RAM

## 커널 재빌드

* 커널 소스 다운로드

    빌드하기 위해 빌드에 필요한 패키지, SSL 관련 패키지를 설치한다.

    > sudo apt-get install build-essential libssl-dev

    커널 소스를 다운로드한다.

    > apt-get source linux-image-$(uname -r)

    받은 커널 소스가 잘 동작하는지 확인하기 위해 로그를 추가해보자.
    init/main.c의 rest_init() 함수를 찾아 수정해보자.

    > + printk(KERN_WARNING "[PSS] Hello Kernel\n");

* 커널 컴파일 설정

    커널은 여러 하드웨어 지원, 여러 기능을 포함하기 때문에 소스가 상당히 크다.
    따라서 커널이 실행될 하드웨어와 기능을 설정하기 위한 파일이 필요하다.
    커널 소스의 .config에서 커널 컴파일 설정 파일을 만들 수 있다.

    

    


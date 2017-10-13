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
    init/main.c의 rest_init() 함수를 찾아 수정해보자. (vi에서 검색은 커맨드 모드에서 /rest_init 식이다)

>+ printk(KERN_WARNING "[PSS] Hello Kernel\n");

* 커널 컴파일 설정

    커널은 여러 하드웨어 지원, 여러 기능을 포함하기 때문에 소스가 상당히 크다.
    따라서 커널이 실행될 하드웨어와 기능을 설정하기 위한 파일이 필요하다.
    커널 소스의 .config에서 커널 컴파일 설정 파일을 만들 수 있다.

    현재 설치된 커널 설정대로 컴파일 설정 파일을 만들자.

> cd ~/workspace/kernel/linux-4.2.0
> cp /boot/config-$(uname -r) .config

    이제 이미지를 빌드한다.
    -j 옵션은 컴파일에 사용되는 스레드를 지정하는 옵션인데, 사용중인 CPU 코어보다 하나 더 많게 설정하는 것이 가장 효율이 높다고 한다. 여기서는 코어를 4개 할당했다고 가정한다.

>make -j5 bzImage

    bzImage가 커널 이미지이다.


    리눅스 커널 모듈은 윈도우의 드라이버와 같다.
    커널을 빌드할 때 매직 넘버가 만들어지고, 커널 모듈은 자신이 빌드될 때 만들어진 매직 넘버와 일치하는 커널에서만 동작한다.
    여기서 커널 전체를 새로 빌드했으니 매직 넘버도 바뀌었으므로, 커널 모듈도 재빌드해야 한다.
    커널 전체 빌드 시에만 커널 모듈을 빌드하면 되고, 이후 커널 코드를 수정할 때는 커널 모듈을 빌드할 필요가 없다.

>make -j5 modules
    
    빌드된 모듈들을 부팅 시 사용하도록 설치한다.

>sudo make modules_install

    빌드한 커널을 설치할 차례이다.

>sudo make install

    이제 시스템을 재부팅해 dmesg를 사용해 '[PSS] Hello Kernel!' 출력을 확인하자.

>dmesg | grep PSS


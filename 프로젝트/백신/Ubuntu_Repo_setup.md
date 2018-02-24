# 우분투 저장소 수정하기

출처 : http://webdir.tistory.com/201

미국 서버 대신 다음에서 제공하는 미러 서버에서 패키지를 받아보겠다.

apt 저장소 리스트를 수정하자.

> sudo vi /etc/apt/sources.list

치환 기능을 이용해 바꿀 수 있다.

> %s/us.archive.ubuntu.com/ftp.daum.net/g
> %s/security.ubuntu.com/ftp.daum.net/g
> %s/extras.ubuntu.com/ftp.daum.net/g

* 주의:
    책을 실습했을 때 설정을 변경했더니 커널 저장소를 인증해주지 않아서 git으로 저장받아야 함
* 정적 ip 설정
http://www.mustbegeek.com/configure-static-ip-address-in-centos/

`/etc/sysconfig/network-scripts/ifcfg-eth0`
에서

```
ONBOOT=YES
IPADDR=
NETMASK=
GATEWAY=
```
등을 설정

* 동적 ip(DHCP) 설정


`/etc/sysconfig/network-scripts/-`에서
```
NETWORKING=yes
BOOTPROTO=dhcp
ONBOOT=yes
```

설정
* Run level (init)
- 1 : shutdown
- 6 : reboot

* Terminals
- `Ctrl+Alt+1~6`

* mount
- `mount`, `umount`

* 사용자/그룹 관리
- useradd/mod/del/
- chage : 주기적인 암호 변경 설정
- groups : 현재 그룹
- groupadd/mod/del
- gpasswd : 그룹 암호 설정

* 링크
- 하드 링크 : 원본과 inode 공유 ln
- 소프트 링크 : 별도의 inode 생성 (ln -s)

* rpm
  * 설치 : `rpm -Uvh`
  * 삭제 : `rpm -e` 
  * 정보 : `rpm -q[a,f,l,i]`

* yum : 의존성 관리 추가
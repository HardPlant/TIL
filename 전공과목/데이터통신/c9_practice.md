# Data-link Layer

## 2. 인터넷 호스트가 모두 mesh 토폴로지로 연결되어 있다고 가정하자. 여기에 네트워크, 데이터링크 레이어가 필요한가

두 터미널간 경로가 단절될 위험이 있으므로 네트워크, 데이터링크 레이어가 필요하다.
경로가 절대 단절되지 않는다고 하면 네트워크, 데이터링크 레이어 없이 송신해도 무방할 것이다.

## 4. 그림 9.7에서 시스템 A가 먼저 N2-> L2 매핑 캐시를 체크한 뒤에 ARP request를 브로드캐스트해야 하는가

체크하지 않을 수 있지만, 효율성을 위해 캐시를 체크하는 것이 좋다.

## 5. 그림 9.7에서 시스템 B가 ARP 프로그램을 실행하지 않는다면 무슨 일이 일어나는가

시스템 A에 ARP가 캐시되어 있지 않다면 시스템 A는 ARP Request에 따른 ARP Reply가 오지 않아 시스템 B의 IP 주소를 찾는 데 실패할 것이다.

## 6. 그림 9.11-9.13에서, 포워딩 테이블과 ARP가 매핑을 수행하고 있다. 포워딩 테이블과 ARP 테이블 매핑의 입력, 출력을 리스트해 차이점을 보여라

포워딩 테이블 :
    Alice의 컴퓨터 : NB => N1
    라우터 1 : NB => N3
    라우터 2 : NB => NB
ARP 테이블 :
    Alice의 컴퓨터 : N1 => L1
    라우터 1 : N3 => L3
    라우터 2 : NB => LB

## 8. Alice가 2020 Main Street, Los Angeles에서 1432 American Boulevard, Chicago를 여행하고 있다고 가정하자. LA 공항에서 Chicago 공항으로 비행기를 탄다면

a. end to end address를 찾아라.
Dest : 2020 Main Street, Los Angeles
Src : 1432 American Boulevard, Chicago

b. link-layer address를 찾아라.
Dest : Los Angeles Airport
Src : Chicago Airport

## 9. Alice가 Los Angeles에서 Chicago로 가는 직항편을 찾지 못했고, Denver에서 환승해야 한다고 가정하자

a. end-to-end address를 찾아라.
Dest : 2020 Main Street, Los Angeles
Src : 1432 American Boulevard, Chicago

b. link-layer address를 찾아라.

Dest : Los Angeles Airport
Src : Denver Airport

Dest : Denver Airport
Src : Chicago Airport

## 10. 우체국 서비스를 이용해 편지를 보낸다면, end-to-end address를 사용해야 하는가? 우체국이 end to end address를 사용해 메일을 전달하는가

end to end address를 사용하면, 우체국은 dest 주소 담당 우체국에서 src 주소 담당 우체국으로 편지를 전달한다.
우체국은 end to end address의 한 부분(src/dest)만 사용해 메일을 전달한다.

## 15. 그림 9.7은 호스트나 라우터 시스템을 보여준다. 다음 사례에서 무엇이 시스템 A나 B의 실제 개체 (host or router)인가

a. link가 경로의 첫번째일때
시스템 A, B는 호스트이다.

b. 링크가 경로의 중간일때
시스템 A, B는 라우터이다.

c. 링크가 경로의 마지막일떄
시스템 A, B는 호스트이다.

d. 링크가 경로에 하나만 존재할 때
시스템 A, B는 호스트 또는 라우터이다.
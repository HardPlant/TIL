# Cloud Next

## Session 1

* 올해('19)는 두 번 열림

* Cloud Architect 자격증 있음, Next에서 보면 기념품 줌

### 참가하는 방법

* 비용 지출

* Google Partner 되지

* GCP Cert 취득 시 랜덤하게 초청권 줌

* GDExpert 

## Session 2

Cloud Run

Fully Managed container service for serverless

#### Serverless

* In-house Server

* Colocation .. 일정한 공간을 임대

* Cloud Server ..

##### 관리형 서비스 <=> 서버리스

* 시간 <> 호출

* 항상 켜져있음 <> Cold Start

#### GCFunction

Code Snippet을 올림
구글이 관리하면서

#### GCRun

Docker를 이용한 서버리스 서비스
컨테이너 안에 설정 파일 세팅 후 이미지 올리면
.. 로드밸런싱/관리해줌

#### 비교

* Function

Cloud Source Repo 안의 code

* Run

Docker Image (dockerfile 이용)

#### GCRun 상세

* 컨테이너 URL 지정

* URL에 대한 인증 설정 가능

* 작은 머신 위에서 돌릴 수 있음 (할당 메모리 설정)

* 새 컨테이너를 만드는 최대 요청 수 설정

컨테이너는 현재 1000개까지 만들 수 있음

80Req * 1000 ... 8만까지 동시접속 가능

* 환경 변수 설정 가능

#### Code

* Dockerfile

```dockerfile
FROM nginx:latest
```

! 80포트가 아니라 8080이나 Run에서 제공하는 포트로 해줘야 함

port를 바꾸는 설정 파일 필요

* 배포

`gcloud builds`


## Session 3

VSCode로 Kubernetes 사용하기

[](subicura.com)

VSCode + Cloud Code + GKE

#### Next 19 후기

500개 이상의 세션이 열림

#### Kubernetes

* 복잡함

클러스터 구축
복잡하고 많은 yaml
디버깅
코딩 이외 작업에 시간 소요

#### Cloud Code

VSCode/IntelliJ Extension

* 코드 작성 > 이미지 빌드 > k8s 배포 과정 자동화

* 디버깅 .. nodejs/java.. 원격

* 클러스터 관리

자동 완성

* yaml 설정 관리

* lib/도구와 연동

Skaffold
Jib.. 자바 App 빠르게 빌드, 도커 없이도 빌드 가능

* GCP 연동

#### 시연

* cluster explorer

autodetection (`k config get-contexts`)
ui에서 cli 명령 보내기 가능

바로 배포 가능
우클릭 메뉴에서 서버 cli에 바로 붙기 가능

* Command: New App (>Hello World)

참고하기 좋음

* yaml 설정값에 유효성 검사 해줌, 자동 완성도

* 클러스터 만들기

프로젝트, Zone, 클러스터 이름 지정
=> 

###### Node Guestbook

image 여러 개 만들기 가능 (artifacts)

* deploy 명령

설정파일 없으면 만드는 wizard 실행
이미지, 빌드할 소스 위치 선ㄴ택

* 디버깅

Debug > 서버에 붙음
그대로 서버에서 돌아가는 함수에 대해 Debug 가능 (Watch/Breakpoint)

* Continous Deploy

수정 시마다 배포 가능
저장하는 순간 build/push

* configmap, deployment 자동 완성

설정파일 레퍼런스 찾아줌

## Session 4

Kubernetes on Premise

#### 선택 이유

Baremetal .. 대용량 메모리/고성능 IO
많은 GPU 서버, 내부 서버 자원 관리

비용이 너무 많이 듬

#### Legacy Infra

내부 서비스 (Jira, Conf, Git, CI, ...)
복잡한 관리
서버 실패 대응 필요

#### 관리 방법

LXC
서비스별 DB 분리

##### 문제점

DB 분리 > 백업 어려움
설치 문제
실패 시 대응 부제

특정 서버에 부하 심함
터미널 이용 관리(ssh)
모니터링 부족

#### 목표

서버 자원관리
문서화

#### 자원 관리 플랫폼

K8s / Rancher

#### 이미지

Jira/Confluence .. 컨테이너 이미지 존재

패키지 설치보다는 효율적이다

#### 클러스터 생성

* kubeadm, Dashboard, 
NodePort ...노드의 포트 open 관리, NodeSelector ... 서비스를 띄울 노드 선택
HostPath, EmptyDir

* 연습

VM (vagrant)
남는 서버로 클러스터 구축
내부 서비스 띄우는 Deployment 작성

* 개선점

Container 배포
Dashboard .. 서비스 떠있는 노드 확인 가능

#### 효과

편리한 서비스 관리

#### 부족한 점

로컬 디스크 공간 .. 클러스터별로 전용 노드 설정 필요함
서버 실패 대처 필요
컨테이너로 배포하기 어려움 (포트를 범위로 쓰는 서비스)

#### GPU 클러스터

nvidia 플러그인이 있음

RollingUpdate 불가능(recreate 필요)

#### 클러스터에 저장소 추가

Rook, Ceph

디스크 공간 - 컨테이너간 분리

컨테이너에 영속성 볼륨 제공
노드가 죽으면 데이터가 넘어감

Docker Registry > Ceph 안으로 이동
NodeSelector > 호스트에서 그룹으로

##### 개선

컨테이너

#### LoadBalancer 추가

NodePort .. 클러스터의 모든 노드의 포트 예약
=>
LoadBalancer

* MetalLB
ARP(IPv4), NDP(IPv6), BGP 제어
클러스터와 외부 네트워크 연결

서비스용 IP 부여 가능함
노드 실패 상황에서 옆 노드로 ARP 변경
LB IP:22 가능함

#### 모니터링

* Filebeat .. 컨테이너 로깅

* Prometheus + Grafana .. 서비스 모니터링

+Ceph

* Zabbix .. 클러스터 노드

#### Kubernetes 확장

* MysqlDB

mysql-operator .. replication
Master/Secondary Failover 
\+ RAID 디스크 적용

* Redis

전용 노드 사용

* Cron Job

컨테이너로 배치처리

통계 .. ES/RDB
DB백업 .. NFS

#### 안정성 강화

master의 HA 보장 필요

3 * master

etcd 확장
(3대 중 2대 죽으면 etcd를 빼버려야 함 .. 1대만 남으면 리더 선출하다 멈춤, 제어 불가능)

HA 설정 전 etcd 백업해야 함

#### 추가로

* 권한 부여
* 컨테이너 상태 확인 (Liveness / Readiness)
* 용도별 Namespace 관리

#### 바닥의 단위가 linux > k8s로 이동하는 중임

k-native
md > slide로 표시도 가능함
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


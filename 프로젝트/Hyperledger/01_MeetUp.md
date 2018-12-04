# 하이퍼레저

https://www.youtube.com/watch?v=smytS8dQCtk

### 퍼블릭과의 차이

* 네트워크 유지비용

네트워크가 필요한 사람들이 공동 유지비용을 부담함
퍼블릭은 유지를 위해 채굴, fee 등 시스템 필요

* 결제 트랜잭션

현재 금결원에서 관리 중임
미국은 그런 것이 없음
우리나라는 블록체인이 약간 안 맞음, 정부가 신뢰지점임

트랜잭션을 일하는 사람들하고만 보여주고 싶을 떄

### 

CRD DB

### 구조

##### 피어

네트워크 참여자

###### 검증 피어

검증 정책 (out of, )
실패한 트랜잭션, 논리적으로는 문제 없음
브로드캐스팅하면 오더러가 받아서 오더러가 순서를 지정함 

##### 오더러

순서지정

##### CA

MSP, 클라이언트 X.509 공인인증서을 관리함
클라이언트들이 비밀키를 잘 가지고 있으면 됨

##### 메시지 포맷

* propose

tx = <>

### 검증 정책

### CA 클라이언트

등록,

## Main

#### 오라클 문제

#### 블록체인 동향


##### 이더리움

* 영지식증명


##### 하이퍼레저

카카오페이 기반 (비트코인->패브릭)

### 패브릭과 컴포저 차이점

* Enterprise / Public 차이..

우주왕복선? <> 경비행기?

* 결합이 안되는 이유?

WinAPI <> MFC

JS 클래스 지원 (더 알기 쉽도록 함, 내부 구현은 차이가 있음)

* 패브릭 / 컴포저

일부분 추상화

### 블록체인 프레임워크 기술요소

* Shared ledger

* Cryptography

* Consensus

* Smart Contract

#### 추가

* Audit/log

* Report/Monitoring, regulatory req.

* Enterprise Authe/Autho

### 신뢰비용 문제

### 로드맵

### 구조

```gv
digraph {
    app->membership;
    app->peer;
    membership->peer;
    membership->orderer;
    peer->orderer;
}
```

### 작업흐름

```gv
digraph{
    Org0 -> ClientApp0;
    ClientApp0 -> Peer0;

    AnchorPeer0 -> ordererPeer;
    Org0 -> ClientApp0;
    ClientApp0 -> Peer0;
    subgraph{
        AnchorPeer1.1 -> ordererPeer;
        AnchorPeer1.2 -> ordererPeer;
    }
}
```

Orderer Peer는 조직간에 공유됨

* 채널

Orderer와의 관계.. 특정 Peer들만 가지고 구현함


* MSP


* Leader Peer



* Anchor Peer

Orderer에서 받아서 

### 체인코드

현재 Golang이 레퍼런스 가장 많음

shim interface{
    Init() : 인스톨/인스턴스화
    Invoke() : 클라이언트에서는 이것만 호출함
}

### Node.js

1CPU에서 가장 빠름

### 컴포저 아키텍쳐

App - Composer - Fabric

Deploy/Update/Undeploy ( -> composer-admin)

gRPC ( -> conposer-client)

REST call -> composer-rest-server -> composer-c;ient

##### 버티컬

* 클라이언트 -> 패브릭

* 클라이언트 -> 웹 백엔드 -> 패브릭

* 클라이언트 -> 웹 백엔드 -> 미들웨어 -> 패브릭

체인코드 호출 등 밀접한 부분을 미들웨어로 뺄 수 있음

* 클라이언트 -> 컴포저 -> 패브릭

* 클라이언트 -> 컴포저 REST -> 컴포저 -> 패브릭

### 신용장 (LC)

digraph{
    1. Exporter -> Importer
    2. Importer -> Exporter (계약 성립)
    3. Importer -> Importer.Bank 
    4. Importer.Bank -> Exporter.Bank (Contract)
    5. Exporter.Bank -> Importer.Bank (Contract)
    6. Exporter -> Reg_Authority (허가)
    7. Reg_Authority -> Exporter
    8. 
}

내부/외부 트랜잭션 괴리 문제

### Hands-on Blockchain with Hyperledger

소스는 깃허브에 있음

### 체인코드

##### API 설계

아귀가 잘 맞아야 함

requestLC <> issueLC

### 미들웨어 코드

### React

웹페이지 기술임

각각의 컴포넌트를 만들어서 

* 상태 관리 : Redux

상태 스토어, 옵저버 패턴을 구현함

* 

### 신용장 예제 살펴보기


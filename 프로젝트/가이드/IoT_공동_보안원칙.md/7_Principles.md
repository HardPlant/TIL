# IoT 공통 보안 7대 원칙 (2015)

## 개요

* IoT 기술

`다양한 물리 공간의 사물들`과 `가상 공간의 프로세스 및 데이터 콘텐츠`들이 `인터넷으로 상호 연결` 되어 `초연결사회`가 구출되고 `사용자 중심의 지능형 서비스`를 제공하기 위해 거대한 정보가 `생성-수집-공유-활용`되는 광범위한 기술이다

* 스마트카, 스마트홈, 스마트빌딩, 스마트시티, 스마트국가

* 의료 서비스나 산업 시설 제어 서비스에 적용되는 사물인터넷 장비와 통신 기술에서 보안 기술은 필수적임

* `설계-개발`단계부터 보안과 프라이버시 보호 체계 고려
    (제조->조립)
* `배포-설치`하는 단계에서도 사전에 잠재적 보안 위협 차단
    (설치-> 보안 설정 및 재설정)
* `설정-운영-실행-폐기`단계에서 이 전 단계를 모두 고려해 전주기적 침해 요소의 분석 및 대응 방안 마련
    운영/실행 (장치 대체, 고장 수리, F/W 및 S/W 갱신) -> 폐기/이관

## 7대 원칙

* 정보보호와 프라이버시 강화를 고려한 IoT 제품/서비스 설계

* 안전한 소프트웨어 및 하드웨어 개발 기술 적용/검증

* 안전한 초기 보안 설정 방안 제공

* 보안 프로토콜 준수 및 안전한 파라미터 설정

* IoT 제품 서비스의 취약점 보안패치 및 업데이트 지속 이행

* 안전한 운영/관리를 위한 정보보호 및 프라이버시 관리체계 마련

* IoT 침해사고 대응체계 및 책임추적성 확보 방안 마련

## 보안 요구사항

### `설치/개발`단계

* 정보보호와 프라이버시 강화를 고려한 IoT 제품/서비스 설계
    Security by Design, Privacy by Design

* 안전한 소프트웨어 및 하드웨어 개발 기술 적용 및 검증
    시큐어 코딩, 소프트웨어, 어플리케이션 보안성 검증 및 시큐어 하드웨어 장치 활용

### `배포/설치(재설치)/구성(재구성)`단계

* 안전한 초기 보안 설정 방안 제공
    Secure by Default

* 보안 프로토콜 준수 및 안전한 파라미터 설정
    통신 및 플랫폼에서 검증된 보안 프로토콜 사용 (암호/인증/인가 기술)

### `서비스 운영/관리/폐기 단계`의 보안 요구사항

* IoT 제품/서비스의 취약점 보안패치 및 업데이트 지속 이행
    보안 취약점 모니터링, 업데이트 지속 수행

* 안전한 운영/관리를 위한 정보보호 및 프라이버시 관리체계 마련
    사용자 정보-취득-사용-폐기의 전주기 정보 보호 및 프라이버시 관리

* IoT 침해사고 대응체계 및 책임추적성 확보 방안 마련
    보안 사고에 대비한 침입탐지, 사고 시 분석 및 책임추적성 확보

## 정보보호와 프라이버시 강화를 고려한 IoT 제품/서비스 설계

`분석/설계`-`구현`-`테스트`

* 보안 취약점을 사전에 분석하여 이를 보완하고 강화할 수 있는 기술을 적용해야 한다.

* 사전 분석된 위험분석정보를 기반으로 민감한 정보에 대해 기밀성과 무결성 제공, 정보 접근 권한을 관리하는 방안 등을 포함시켜야 한다.

### Security by Design

* 저전력/저성능 조건 하에서 기밀성, 무결성/인증, 가용성 등 정보 및 기기의 오용을 최소화 시키면서 경량화 방안 고려

* IoT 장치 및 정보에 대해 서비스 운용환경에 맞는 장치의 접근권한관리, 종단간 통신보안, 무결성/인증 제공 등 방안 제공

* 소프트웨어 보안 기술, 하드웨어 보안 기술 적용 검토, 안전성이 검증된 표준 보안 기술 사용

### Security by Privacy

    IoT 서비스 제공에 필요한 최소한의 정보만을 취득, 사용자가 동의한 기간과 서비스 범위 내에서만 정보를 사용

* IoT 장치, 서비스 운영 정책에 사용자의 프라이버시 보호 방법론 기본 적용

* IoT 장치가 수집하는 프라이버시 정보에 대해 암호화 전송, 익명 저장/무결성 인증 방안

* 수집된 프라이버시 정보에 대한 비식별화, 접근관리/인증, 기밀성, 안전한 저장 방안

* 사용자에게 프라이버시 정보의 사용 범위/기간 등을 포함한 운영 정책을 가시화하여 투명성을 최대한 보장

* 특정 지점에서 발생한 보안 침해사고가 서비스 연속성 유지에 필요한 핵심영역까지 영향을 미치지 않도록 IoT 서비스를 물리적/논리적으로 분리된 구조로 설계

* 개발용으로 사용된 IoT 제품의 물리적 포트, 불필요한 데몬 제거

## 안전한 소프트웨어 및 하드웨어 개발 기술 적용/검증

  시큐어 코딩, 소프트웨어, 어플리케이션/소프트웨어 보안성 검증 및 시큐어 하드웨어 장치 활용

### 시큐어 코딩 적용

* Java, C/C++ : 시큐어 코딩 가이드 활용

* ISO/IEC 27034-1 : 어플리케이션 보안 가이드라인

### 소프트웨어 보안성 검증

* 보안 취약점에 대한 보안성 검증 수행, 보안패치 적용

* 알려진 보안 취약점에 대한 보안성을 검증하기 위해 아래의 가이드라인 절차와 같이 수행

#### 보안성 검증 단계

* 의존 S/W 열거 : 사용한 오픈소스 S/W를 포함해 의존성을 가지는 S/W 확인, 열거

  예 : 오픈소스 프레임워크 `Alljoyn`을 사용한다면, 하위로 `OpenSSL`등과 같이 필요한 추가적인 S/W 및 library를 리스트로 열거

* 취약점 검색 : 열거된 의존 S/W에 대한 취약점 검색

  의존S/W 열거단계에서 열거된 모든 S/W, library에 대한 취약점을 CVE, CWE, OWASP 등을 통해 검색 수행

* 취약점/대응방법 열거 : 검색된 취약점을 열거

  위의 취약점 데이터베이스에서 검색된 취약점 및 대응 방법을 항목별로 리스트에 열거

* 대응방법 반영

  알려진 취약점에 대한 대응절차에 따라 오픈소스 S/W에 반영하여 보완해야 함

### 시큐어 하드웨어 장치 활용

  부채널 공격, 펌웨어 코드 추출, 키 값 추출 등 IoT 다양한 보안 취약성을 갖는다. 이 떄문에 하드웨어 보안성을 강화하기 위해 `펌웨어/코드 암호화, 실행코드 영역제어, 역공학 방지 기법`등을 적절히 적용할 필요가 있다.

### 소프트웨어 보안 기술과 하드웨어 보안 기술 융합

  소프트웨어 보안 기술과 하드웨어 보안 기술 간에 반드시 `신뢰하는 접근 방법(단방향 및 양방향 인증)` 기반의 안전한 보안 채널을 구성해 전송 데이터에 대한 기밀성과 무결성 기능을 제공해야 한다.

## 안전한 초기 보안 설정 방안 제공

### Secure by Default 기본 원칙 준수

* 초기 설치 단계, 고장 수리 후 재설치 단계에서 보안 프로토콜들에 기본으로 설정되는 값이 가장 안전한 설정이 될 수 있도록 해야 한다.

* 또한 서비스 관리자, 사용자에게 기본 파라미터들을 설정 및 재설정할 수 있는 방안을 제공해야 한다.

  * IoT 장치의 초기 설정을 수행할 때 보안 모듈, 파라미터는 안전하게 설정되어야 한다.
    (예 : 국제표준 권고 기준인 AES-128 이상의 보안 강도 준수)
  * 서비스에서 강력한 암호와 무결성을 요구하는 경우 옵션 중 강한 암호를 기본으로 설정
    (예 : AE(Authenticated Encryption)암호 모드 적용)
  * 제조 시 기본으로 설정된 계정 이름, 패스워드를 설치 시 변경
  * 특정 기간이 지나면 암호 키, 인증 패스워드의 만료를 권고할 수 있는 옵션 활성화
  * 장치간, 장치와 인터넷 간 `암호화 통신`을 사용하도록 기본 설정
  * `다중 요소 인증`이 옵션으로 제공될 경우 `필요 시 활성화`
  * `다중 사용자`로 구성되는 서비스 환경에서는 `최소한의 권한`으로 초기 설정

### 보안 프로토콜 준수 및 안전한 파라미터 설정

* [CoAP(Constrained Application Protocol)](itef.org)

* [MQTT(Message Queuing Telemetry Transport), OASIS (Organization for the Advancement of Structured Information Standards](http://oasis-open.org/)

* [oneM2M Specification Release](http://www.onem2m.org)

IoT 제품 개발자와 서비스 제공자는 데이터 통신 및 개방형 플랫폼에 안전성을 보장하는 보안 프로토콜을 적용해야 하고, 보안 서비스(암호/인증/인가) 제공 시 안전한 파라미터들이 설정될 수 있도록 해야 한다.

경량화 보안 프로토콜의 사용이 고려되어야 한다. 또한 인증/인가 및 접근 권한을 안전하게 관리하는 방식에서도 검증된 보안 프로토콜의 적용과 경량화를 고려해야 한다.

## IoT 제품 서비스의 취약점 보안패치 및 업데이트 지속 이행

* 보안 취약점이 발견되면 이에 대한 분석을 수행하고, 보안 요구사항을 반영한 보안패치를 신속히 배포할 수 있도록 사후조치 방안을 마련해야 한다.

* 제품/서비스에 대한 보안취약점 및 보호조치 사항은 홈페이지, SNS 등을 활용해 사용자에게 공개해야 한다.

* 위/변조 문제를 사전에 예방 가능하도록 무결성 검증 기술을 적용해야 한다.

* 통신 채널을 통한 S/W 업데이트에서 사용자의 관여를 최소화하는 방법론을 적용할 수 있다.
  이 경우, 다음의 보안 서비스는 반드시 제공되어야 한다.

  * 주체 간 상호 인증 : 업데이트 서버와 IoT 장치 사이에 `상호 인증`을 하여 `위장 서버, 중간자 공격` 등의 취약점에 대응할 수 있도록 해야 한다.

  * 기밀성 : 저장 데이터와 처리 데이터 및 전송 데이터에 대해 해커의 공격에 대비해 `암호화`해야 하며, 보안 패치에 대한 `코드 서명` 기법의 적용을 고려해야 한다.

  * 무결성 : 저장 데이터(업데이트 정보 파일: conf, xml, ini), 처리 데이터(실행 파일), 전송 데이터(업데이터 전송 정보)의 무결성 검사를 수행해야 한다.

## 안전한 운영/관리를 위한 정보보호 및 프라이버시 관리체계 마련

* 사용자 정보 취득-사용-폐기의 전주기 정보보호 및 프라이버시 관리

  최소한의 개인정보만 수집, 활용될 수 있도록개인정보보호정책을 수립하고, 빅데이터 분석과정에서 특정 개인을 식별할 수 있는 새로운 개인정보가 생성, 유통될 수 있기 때문에 이를 적절히 통제할 수 있는 기술적, 관리적 보호조치도 포함되어야 한다.

* 설계 시 수립된 보안위험 분석을 기반으로 안전한 운영과 관리를 위한 보안대책과 기술적 방안이 마련되어야 한다. 또한 IoT    서비스의 운영 과정에 대한 안전한 정보보호 및 프라이버시 관리체계와 기술적 방안이 마련되어야 한다.

* 정보보호 관리체계는
  * IoT 서비스를 위한 유 무형 자산과 이에 대한 위험 식별

  * IoT 장비의 비인가 접근 및 도난,분실을 방지하기 위한 물리적 접근통제

  * 침해사고 발생 시 서비스 연속성이 유지될 수 있도록 백업 및 복구 절차 수립

  등을 포함하고 있어야 한다. 또한 IoT 장치의 주기적인 보안 업데이트, 패치 적용, 폐기절차 등 사후관리 방안 등이 포함되어야 한다.

## IoT 침해사고 대응체계 및 책임추적성 확보 방안 마련

* 대응체계를 수립하고 사고의 원인과 책임을 분석하는 것이 어려워지고 있다.

* 다양한 유형의 `IoT 장치`, `유,무선 네트워크 장비`, `플랫폼` 등으로 구성되어 각 영역에서 발생 가능한 보안 침해사고에 대비해 `침임탐지 및 모니터링`이 수행되어야 한다.

* 아울러 침해사고 발생 이후 `원인분석` 및 `책임추적성` 확보를 위해 `로그기록`을 주기적으로 안전하게 저장, 관리해야 한다.

* 저전력, 경량형 하드웨어 사양 및 운영체제가 탑재된 IoT 장치의 경우, 특성상 로그기록의 생성, 보관이 어려울 수 있으므로 `서비스 운영, 관리시스템`에서 IoT 장치의 상태정보를 주기적으로 안전하게 `기록, 저장`할 수 있어야 한다.
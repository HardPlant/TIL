# 보안 관제 시스템

* Enterprise Security Management + 로그 관리 시스템을 도입하는 방식에서 운영, 정제된 보안 이벤트들에 대해 관제하고 로그 데이터는 로그 감사를 위해 저장했을 뿐이어서 APT 공격과 같은 지능적인 공격을 탐지하는 데 한계가 있었음

* Security Information & Event Management : 빅데이터 기술을 활용한 차세대 보안 관제 시스템임

이 장에서는 로그 데이터 저장과 분석, 검색을 위한 `ElasticSearch`, 로그 수집을 위한 `Logstash`, 시각화를 위한 `Kibana`를 활용한 ELK 스택으로 SIEM을 구축하고 운영하는 방법에 대해 알아보겠음.

## 보안 관제 구성

SIEM은 로그 수집과 분석, 검색에 특화된 형태로 구성되어 있음.

* 각종 보안 시스템 및 DB 서버, 운영체제 로그, 애플리케이션 로그, 비정형화된 로그 데이터를 Distributed 로그 수집 에이전트를 통해 수집

* 로그 수집 에이전트에서 수집된 로그는 중앙 로그 서버로 보내지고 인덱싱 처리를 거쳐 저장되어 검색할 수 있는 상태로 가공

* 로그 데이터에서 의미 있는 정보 추출, 시각화해 보여주는 대시보드와 로그 검색 엔진 UX 용 가능

이외에도 IT 컴플라이언스, 실시간 경보, 파일 무결성 모니터링, 리포팅, 사용자 행위 분석, 로그 저장, 객체 접근 제어, 로그 포렌식 등 다양한 기능이 있음

행위 분석과 상관 분석을 통해 좀 더 정밀한 분석 나으

## ElasticSearch

Lucene, Splunk 등과 같은 상용 솔루션을 이용해서도 구축이 가능함

* 수평적 증가를 고려해 분산 처리하고, 클러스터에 하드웨어 등을 추가하는 방식으로 노드의 용량을 더 증가할 수 있음.

* 고가용성 측면에서 노드의 상태를 감지해 장애가 발생한 노드가 있더라도 사용자의 데이터를 안전하게 저장, 접근할 수 있게 함

* Multi-tenancy는 클러스터에서 여러 개의 인덱스를 저장, 관리할 수 있음

* 다양한 형태의 쿼리를 통해 여러 인덱스의 데이터를 검색할 수 있어 Full text search가 가능

### CentOS 6 기반에서 리포지터리를 추가해 Yum을 통해 설치

`yum -y install java-1.8.0-openjdk`

```bash
rpm --import https://packages.elastic.co/GPG-KEY-elasticsearch # Signing key 설치
vi /etc/yum.repos.d/elasticsearch.repo # 리포지터리 추가
###
[elasticsearch-1.6]
name=Elasticsearch repository for 1.6.x packages
baseurl=https://packages.elastic.co/elasticsearch/1.6/centos
gpgcheck=1
gpgkey=https://packages.elastic.co/GPG-KEY-elasticsearch
enabled=1
###
yum install elasticsearch
chkconfig elasticsearch on
```

이후 iptables에 Elasticsearch 통신 포트 TCP 9200,9300을 추가한다.

```bash
iptables -I INPUT -p tcp --dport 9200 -j ACCEPT
iptables -I INPUT -p tcp --dport 9300 -j ACCEPT
service iptables save
iptables -L -n
```

### Elasticsearch 설정과 구동

해당 설정을 하지 않으면 elasticsearch가 기본 클러스터로 구성된다.

`vi /etc/elasticsearch/elasticsearch.yml`

```bash
#...
#### Cluster
cluster.name : max1

node.name : "Maxlab"
index.number_of_shards : 5 #  인덱스 생성 이후에는 변경되지 않는다.
index.number_of_replicas : 1 # 복제본 개수
```

이후 `services elasticsearch restart`로 서비스를 재시작한다.

그러면 [여기](http://localhost:9200/)에서 서비스 정상 작동을 확인할 수 있다.

### Elasticsearch 로그인

Elasticsearch를 더 편리하게 활용할 수 있는 다양한 플러그인이 있다. 플러그인을 어떻게 설치하고 사용해야 하는지 기본 플러그인으로 알아보자.

```bash
cd /usr/share/elasticsearch/bin
./plugin -install royrusso/elasticsearch-HQ
```

설치한 플러그인은 `(:9200)/_plugin/(플러그인 이름)`에서 확인할 수 있고, 경로는 `/usr/share/elasticsearch/plugins/[플러그인 이름]`에서 확인할 수 있다.

여기서는 `/_plugin/HQ/#cluster` 이다.

## Logstash

각종 이벤트와 로그를 수집, 파싱, 저장해주는 로그 관리 도구로, 이를 Elasticsearch와 연동해 대용량 로그를 효과적으로 분석하게 만들 수 있다. 이를 통해 네트워크 이상 행위 탐지와 사용자 접근 기록을 종합적으로 빠르게 분석해 낼 수 있다. 이외에도 로그 데이터를 별도로 저장하거나 연동할 때에도 Logstash를 활용할 수 있다.

### 설치

`vi /etc/elasticsearch/elasticsearch.yml`

```bash
vi /etc/yum.repos.d/logstash.repo # 리포지터리 추가
###
[logstash-1.6]
name=Elasticsearch repository for 1.5.x packages
baseurl=https://packages.elastic.co/logstash/1.5/centos
gpgcheck=1
gpgkey=https://packages.elastic.co/GPG-KEY-elasticsearch
enabled=1
###
yum install logstash
chkconfig logstash on
```

Logstash는 Logstash-forwarder로 원격지 로그를 수집할 수 잇는데, 이 과정에서 SSL 암호화 방식을 채택하고 있다.

암호화 기능을 적용하려면 Logstash 서버 역할을 하는 시스템에 다음 절차를 거쳐 인증서를 생성한다.

```bash
vi /etc/pki/tls/openssl.cnf # openssl.cnf에 Logstash IP를 추가한다
###########
[v3_ca]
subjectAltName = IP:[Logstash server IP]
#...
###########
cd /etc/pki/tls
openssl req -x509 -batch -nodes -newkey rsa:2048 -keyout logstash-forwarder.key -out logstash-forwarder.crt
```

이후 이 인증서는 Logstash-Forwarder가 설치된 에이전트에 복사해야 한다. 이 과정은 11장에서 설명한다.

### Logstash 입력과 출력

데이터 로그는 입력, 필터, 출력으로 나뉘어 처리된다.

`[데이터 Source] ==> LogstashInstance{[Input Plugin]==>[Filter]==>[Output]} ==> ElasticSearch`

이 과정은 다음 형태로 파일을 성생하야 한다.

```js
input{
    <입력 경로>{
        <옵션명> => <옵션값>
    }
}
filter{
    <필터>{
        <옵션명> => 옵션값
    }
    if <필드명> == <필드값>{
        <필터>{
            <옵션명> => 옵션값
        }
    }
}
output{
    <출력 경로>{
        <옵션명> => 옵션값
    }
}
```

이러한 형태로 설정 파일을 만들어 상황에 따라 다양한 로그를 받으려는 경우 따로 분류해 만들어도 된다.

입력, 필터, 출력으로 나눠 처리해보겠다.

* 첫쨰: 입력을 처리하기 위해 로컬 서버의 messages와 secure 로그 파일에 수집된 정보를 사용하고, 원격지의 syslog(514port), Logstash-forwarder와 연동된 로그 정보를 받기 위해 lumberjack 프로토콜을 사용해 input을 설정한다.

`vi /etc/logstash/conf.d/input.conf`

```js
input{
    tcp{
        port=>514
        type=>syslog
    }
    udp{
        port=>514
        type=>syslog
    }
    file{
        path=>"/var/log/messages"
        type=>"syslog"
    }
    file{
        path=>"/var/log/secure"
        type=>"syslog"
    }
    lumberjack{
        port=>5053
        type=>"logs"
        ssl_certificate=>"/etc/pki/tls/logstash-forwarder.crt"
        ssl_key=>"/etc/pki/tls/logstash-forwarder.key"
    }
}
```

* 둘째 : 필터 과정은 입력을 통해 들어온 로그 데이터가 어떤 형태의 로그인지 확인한 후 파싱하는 단계로, 주로 사용하는 로그 유형을 통해 알아보자. 다음은 syslog 유형의 로그가 들어오는 경우 어떻게 파싱해 처리할 것인지 설정하는 내용이다.

`vi /etc/logstash/conf.d/filter-syslog.conf`

```js
filter{
    if [type] == "syslog"{
        grok{
            match => { "message" =>
            "%{SYSLOGTIMESTAMP:syslog_timestamp} %{SYSLOGHOST:syslog_hostname}
            %{DATA:syslog_program}(?:\{POSINT:SYSLOG_pid}\)?:
            %{GREEDYDATA:syslog_message}"}
            add_field => ["received_at", "%{@timestamp}"]
            add_field => ["received_from", "%{host}"]
            }
        }
    }
    syslog_pri {}
    date{
        match=>["syslog_timestamp", "MMM  d HH:mm:ss", "MMM dd HH:mm:ss"]
    }
}
```

그 다음 아파치 웹 서버 로그 필터로 다음과 같이 만들어준다.

`vi /etc/logstash/conf.d/filter-apache.conf`
```js
filter{
    if [type] == "apache-access"{
        grok{ pattern => "%{COMBINEDAPACHELOG}"}
    }
}
```

앞에서 알아본 로컬 로그 파일, syslog 연동 파일, 아파치 웹 서버 로그 정보는 Logstash 설정 파일로 분할해 설정할 수 있다. 하지만 로그 파일에 대한 접근 권한 때문에 접근되지 않는 경우 다음과 같이 logstash 설정 파일을 수정한다.

`vi /etc/sysconfig/logstash`

```bash
###...
#LS_USER=root # 주석을 제거하고 logstash를 root로 수정
```

* 마지막으로 어디로 출력할지를 설정한다. 여기서는 다음처럼 Elasticsearch로 로그 데이터를 보내도록 output을 설정한다.

`vi /etc/sysconfig/logstash/conf.d/output.conf`

```js
output{
    elasticsearch{host=>localhost}
    stdout{codec => rubydebug}
}
```

대부분은 방화벽 로그, IDS/IPS 로그, 시스템 로그, 웹 로그를 처리하지만 이외 애플리케이션 로그 등 다양한 형식의 로그 파일도 logstash를 활용해 처리할 수 있다. 설정 파일에 대해 검사하고 싶다면 `configtest` 옵션을 통해 확인할 수 있다.
`/opt/logstash/bin/logstash --configtest -f /etc/logstash/conf.d/input.conf`

일련의 과정을 거쳐 로그 데이터 처리 설정을 완료한 후 Logstash 서비스를 재시동한다. 이후 정상적으로 Elasticsearch에 로그 데이터가 저장되는지 알고 싶다면 플러그인(HQ.head)등을 통해 로그 데이터가 쌓이는지 확인하면 된다.

### Logstash-forwarder 설치와 설정

## Kibana 설치
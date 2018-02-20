# API 사용

위키백과 편집 내역과 IP 주소 해석기 API를 결합해 세계 곳곳에서 위키백과를 어떻게 편집하고 있는지 알아보는 예제를 만들어보자.

## API의 동작

구글 개발자 섹션(https://console.developers.google.com)에는 언어 번역, 분석, 지오로케이션 등 수십가지 API가 있다.

`http://freegeoip.net/json/50.78.253.58`

응답:

```json
{"ip":"50.78.253.58","country_code":"US","country_name":"United States","region_code":"MA","region_name":"Massachusetts","city":"Boston","zip_code":"02116","time_zone":"America/New_York","latitude":42.3496,"longitude":-71.0746,"metro_code":506}
```

## 공통 표기법

* HTTP Method (GET, POST, PUT, DELETE)를 사용한다.

### 인증

* API는 토큰을 사용해야 할 수도 있다.

```py
token = ""
webRequest = urllib.request.Request("http://myapi.com",headers={"token":token})
html = urlopen(webRequest)
```

### 응답

XML 또는 JSON으로 온다.
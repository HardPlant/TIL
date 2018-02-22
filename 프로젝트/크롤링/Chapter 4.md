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

## 트위터

`pip install twitter`

```py
from twitter import *

with open('apikey') as file:
    key = file.read()
    keys = key.split(',')
    access_token = keys[0].strip()
    access_token_secret = keys[1].strip()
    consumer_key = keys[2].strip()
    consumer_secret = keys[3].strip()

t = Twitter(auth=OAuth(access_token, access_token_secret,\
            consumer_key, consumer_secret))
```


### 트윗 검색하기

```py
pythonTweets = t.search.tweets(q="#python")
print(pythonTweets)
```

### 상태 업데이트하기

```py
statusUpdate = t.statuses.update(status='Hello,World!')
print(statusUpdate)
```

### 목록 요청하기

```py
pythonStatuses = t.statuses.user_timeline(screen_name="montypython", count=5)
print(pythonStatuses)
```

더 자세한 사항은 `https://github.com/sixohsix/twitter`에 있다.

## 구글

`https://console.developers.google.com/apis/`의 `사용자 인증 정보` 메뉴에서 사용자 인증 정보를 만들 수 있다.

### 구글 지도

사이트에 지도를 가져오고, 거리 주소를 위도/경도로 바꾸고, 고도를 구하고, 위치 기반 시각화를 만들고, 위치에 관한 시간대 정보를 얻어올 수 있다.

프로젝트 콘솔에서 Timezone, Geocode를 사용 설정하고,

`https://maps.googleapis.com/maps/api/geocode/json?address=1+Science+Park+Boston+MA+02114&key=`

을 실행하면 해당하는 위도와 경도를 얻을 수 있고,

```json
//...
"location" : {
"lat" : 42.3679381,
"lng" : -71.07111019999999
},
//...
```

이 위도와 경도를

`https://maps.googleapis.com/maps/api/timezone/json?location=42.3679381,-71.07111&timestamp=1412649039&key=`

에 넣으면 해당하는 시간대를 구할 수 있다.

또한 위도와 경도로 고도를 구하려면

`https://maps.googleapis.com/maps/api/elevation/json?locations=42.3679381,-71.07111&key=`

```json
//...
"elevation" : 5.167791843414307,
"location" : {
"lat" : 42.3679381,
"lng" : -71.07111
},
"resolution" : 9.543951988220215
}
```

를 얻을 수 있다. 해상도는 낮을수록 고도가 종확하다.

## JSON 파싱

위의 `freegeoip`를 이용해보자.

```py
from urllib.request import urlopen, Request

request = Request("http://freegeoip.net/json/50.78.253.58",\
    headers={\
    'Upgrade-Insecure-Requests':'1',\
    'Accept':'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8',\
    'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.167 Safari/537.36',\
    })

ip = urlopen(request)
print(ip.read())
```

결과로 바이너리 스트링이 온다.

```py
b'{"ip":"50.78.253.58","country_code":"US","country_name":"United States","region_code":"MA","region_name":"Massachusetts","city":"Boston","zip_code":"02116","time_zone":"America/New_York","latitude":42.3496,"longitude":-71.0746,"metro_code":506}\n'
```

이를 약간 수정하고 함수화하면

```py
def getCountry(ipAddress):
    request = Request("http://freegeoip.net/json/"+ipAddress,\
        headers={\
        'Upgrade-Insecure-Requests':'1',\
        'Accept':'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8',\
        'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.167 Safari/537.36',\
        })

    response = urlopen(request).read().decode('utf-8')
    responseJson = json.loads(response)

    return responseJson.get('country_code')

print(getCountry('50.78.253.58'))
```

처럼 만들 수 있다.

## 합치기

위키를 편집하고 있는 ip의를 추적해보자.

구글의 `Geochart` [라이브러리](https://developers.google.com/chart/interactive/docs/gallery/geochart)를 이용해 흥미로운 차트(http://www.pythonscraping.com/pages/wikipedia.html)를 만들었다.

다음 함수는 위키페디아의 bodyContent에 있는 내부 링크를 전부 찾는다.

```py
def getLinks(link):    
    html = urlopen('https://en.wikipedia.org'+link) # link는 /wiki/~ 형태로 반환된다.
    bsObj = BeautifulSoup(html, "html.parser")

    return bsObj.find("div", {"id":"bodyContent"}).findAll("a", href=re.compile('^(/wiki/)((?!:).)*$'))
```

다음 함수는 편집 목록에서 익명 유저를 찾아 그 목록을 받는다.

```py
def getHistoryIPs(pageUrl):
    pageUrl = pageUrl.replace("/wiki/","")
    historyUrl = "http://en.wikipedia.org/w/index.php?title="
    historyUrl += pageUrl + "&action=history"
    print("History URL is :" + historyUrl)
    
    html = urlopen(historyUrl)
    bsObj = BeautifulSoup(html, "html.parser")

    ipAddresses = bsObj.findAll("a", {"class":"mw-anonuserlink"})
    addressList = set()

    for ipAddress in ipAddresses:
        addressList.add(ipAddress.get_text())
    
    return addressList
```

그리고 이 함수는 freegeoip에서 IP를 국가 코드로 변환시킨다.

```py
def getCountry(ipAddress):
    request = Request("http://freegeoip.net/json/"+ipAddress,\
        headers={\
        'Upgrade-Insecure-Requests':'1',\
        'Accept':'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8',\
        'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.167 Safari/537.36',\
        })
    try:
        response = urlopen(request).read().decode('utf-8')
    except HTTPError:
        return None

    responseJson = json.loads(response)

    return responseJson.get('country_code')
```


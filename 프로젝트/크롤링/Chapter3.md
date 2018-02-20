# 베이컨의 다리 문제


## 위키백과 크롤링하기

```py
from urllib.request import urlopen
from bs4 import BeautifulSoup
import re

html = urlopen("https://en.wikipedia.org/wiki/Kevin_Bacon")
bsObj = BeautifulSoup(html, "html.parser")


for link in bsObj.find("div",{'id':'bodyContent'}).findAll("a", href=re.compile('^(/wiki/)((?!:).)*$')):
    if 'href' in link.attrs:
        print(link.attrs['href'])
```

* 위키백과의 주요 내용은 bodyContent 클래스 내에 있다.
* URL에는 세미콜론이 없다.
* URL은 /wiki/로 시작된다.

### 위키질 머신

다음과 같은 함수를 만들자.

1. getLinks 함수 : /wiki/article_name 형태인 항목 URL 전체를 반환하는 함수
2. getLinks()로 받은 목록 중 임의 항목을 선택해 다시 호출하는 항목

```py
from urllib.request import urlopen
from bs4 import BeautifulSoup
import datetime
import random
import re

random.seed(datetime.datetime.now())

def getLinks(link):
    html = urlopen('https://en.wikipedia.org'+link) # link는 /wiki/~ 형태로 반환된다.
    bsObj = BeautifulSoup(html, "html.parser")

    return bsObj.find("div",{'id':'bodyContent'}).findAll("a", href=re.compile('^(/wiki/)((?!:).)*$'))

links = getLinks('/wiki/Kevin_Bacon')
while len(links) > 0:
    newArticle = links[random.randint(0, len(links) -1)].attrs['href']
    print(newArticle)
    links = getLinks(newArticle)
```

이제 결과 데이터를 저장하고 분석할 수 있어야 한다.
또한, `bodyContent` 태그의 이름이 바뀐다면 `NoneType`을 반환하여 `AttributeError`가 발생할 것이다.
실무에서는 예외 처리를 잊지 말자.

## 전체 사이트 크롤링

전체 사이트를 어떤 때 크롤링하는 것이 좋은 지 생각해보자.

### 사이트맵 생성

웹 사이트 재설계 중, CMS 내부에 권한 없이 사이트 전체를 이동하는 크롤러를 이용해 내부 링크를 모두 수집해서 사이트의 실제 폴더 구조와 똑같이 정리할 수 있다.

### 데이터 수집

글을 수집해서 전문화 검색 플랫폼 프로토타입을 수집할 때, 광범위하게 진행해 Article 페이지에서만 데이터를 수집해 데이터를 수집한다.

글이 하나 발견되면 내부의 모든 링크를 검색하고, 링크의 글에서도 같은 행위를 반복하는 식이다.

같은 페이지를 두 번 크롤링하지 않으려면 _내부 링크가 모두 일정한 형식을 취하고_, 프로그램이 동작하는 동안 계속 유지되는 리스트에 보관해야 한다.

```py
def getLinks(link):
    global pages
    html = urlopen('https://en.wikipedia.org'+link) # link는 /wiki/~ 형태로 반환된다.
    bsObj = BeautifulSoup(html, "html.parser")

    for link in bsObj.find("div",{'id':'bodyContent'}).findAll("a", href=re.compile('^(/wiki/)((?!:).)*$')):
        if 'href' in link.attrs:
            if link.attrs['href'] not in pages:
                newPage = link.attrs['href']
                print(newPage)
                pages.add(newPage)
                getLinks(newPage)
```

### 전체 사이트에서 데이터 수집

페이지 제목, 첫 번째 문단, 편집 페이지를 가리키는 링크를 수집하는 스크레이퍼를 만들어 보자.

* 제목은 항상 `h1` 태그 하나만 있고, `h1` 태그는 페이지에 하나만 존재한다.
* 모든 바디 텍스트는 `div#bodyContent` 태그에 들어 있다.
* 첫 번째 문단은 `div#mw-content-text` 하위의 첫번째 `p`만 선택하는 것이 낫다.
* 편집 링크는 항목 페이지에만 존재한다. 편집 링크가 존재한다면 `li#ca-edit -> span -> a`로 찾을 수 있다.

## 인터넷 크롤링

각 페이지에 관한 정보를 기록해보자. 도메인마다 레이아웃이 다르므로, 새로운 도전이 될 것이다.

* 수집하려 하는 데이터는 무엇인가?

* 정해진 사이트 몇 개만 수집하면 되나? (그렇다면 더 나은 방법이 있다)

* 크롤러가 특정 웹사이트에 도달하면 새 웹사이트 링크를 따라가야 하는가, 아니면 현재 웹사이트에 머물러야 하는가?

* 특정 사이트를 스크랩에서 제외할 필요는 없나?

* 크롤러의 방문을 알아차렸을 때 법적 보호 절차가 필요한가?

다양한 웹 스크레이핑을 시작할 수 있는 코드를 만들 수 있다.

```python
def getInternalLinks(bsObj, includeUrl):
    includeUrl = urlparse(includeUrl).scheme+"://"+urlparse(includeUrl).netloc
    internalLinks = []

    # /로 시작하는 링크를 모두 찾는다
    for link in bsObj.findAll('a', href=re.compile('^(/|.^'+includeUrl+')')
        if link.attrs['href'] is not None:
            if link.attrs['href'] not in internalLinks:
                if link.attrs['href'].startswith('/'):
                    internalLinks.append(includeUrl+link.attrs['href'])
                else:
                    internalLinks.append(link.attrs['href'])
    
    return internalLinks

def getExternalLinks(bsObj, excludeUrl):
    externalLinks = []
    # http, www로 시작하는 링크를 찾으며, 현재 URL은 포함하지 않는다.
    for link in bsObj.findAll('a', href=re.compile('^(http|www)(?!'+excludeUrl+').)*$'):
        if link.attrs['href'] is not None:
            if link.attrs['href'] not in externalLinks:
                    externalLinks.append(link.attrs['href'])
    
    return externalLinks

def getRandomExternalLinks(startingPage):
    html = urlopen(startingPage)
    bsObj = BeautifulSoup(html, 'html.parser')
    externalLinks = getExternalLinks(bsObj, urlparse(startingPage).netloc)
    if len(externalLinks) == 0:
        domain = urlparse(startingPage).scheme + '://' + urlparse(startingPage).netloc
        internalLinks = getInternalLinks(bsObj, domain)
        return getRandomExternalLinks(internalLinks[random,randint(0, len(internalLinks)-1)])
    
    else:
        return externalLinks[random,randint(0, len(internalLinks)-1]

def followExternalOnly(startingPage):
    pass
```


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

페이지에 
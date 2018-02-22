# 지저분한 데이터 정리하기

도구와 테크닉 코드 작성 방법을 바꿔 데이터 소스에서 문재가 발생하지 않게 하는 방법, 데이터베이스에 들어온 데이터를 정리하는 방법에 대해 알아보자.

## 코드로 정리하기

`n-gram` 기법을 사용해 보자.

```py
from urllib.request import urlopen
from bs4 import BeautifulSoup

def ngrams(input, n):
    input = input.split(' ')
    output = []
    for i in range(len(input)-n+1):
        output.append(input[i:i+n])
    return output

html = urlopen('http://en.wikipedia.org/wiki/Python_(programming_language)')
bsObj = BeautifulSoup(html, "html.parser")
content = bsObj.find("div", {"id":"mw-content-text"}).get_text()
ngrams = ngrams(content, 2)
print(ngrams)
print("2-grams count is: " + str(len(ngrams)))
```

그리고 \n 같은 이스케이프 문자를 제거하자.

```py
def ngrams(input, n):
    input = re.sub('\n+', " ", input)
    input = re.sub(' +', " ", input)
    input = bytes(input, 'UTF-8')
    input = input.decode("ascii", "ignore")
    print(input)
    input = input.split(' ')
    output = []
    for i in range(len(input)-n+1):
        output.append(input[i:i+n])
    return output
```

이 코드는 줄바꿈 문자를 모두 공백으로 바꾸고, 연속된 공백을 하나로 합쳐 모든 단어 사이의 공백이 하나만 있도록 한다.
그리고 UTF-8로 바꿔 이스케이프 문자를 없앤다.

남아있는 몇 가지 문제를 살펴보자

* i, a를 제외한 한 글자로 된 '단어'는 버려야 한다.
* 인용 표시([1])도 버려야 한다.
* 구두점도 버려야 한다.

```py
import string

def clean_input(input):
    input = re.sub('\n+', " ", input)
    input = re.sub('\[[0-9]*\]', "", input)
    input = re.sub(' +', " ", input)
    input = bytes(input, 'UTF-8')
    input = input.decode("ascii", "ignore")
    clean_input = []
    input = input.split(' ')
    for item in input:
        item = item.strip(string.punctuation)
        if len(item) > 1 or (item.lower() == 'a' or item.lower() == 'i'):
            clean_input.append(item)

    return clean_input

def ngrams(input, n):
    input = clean_input(input)
    output = []
    for i in range(len(input)-n+1):
        output.append(input[i:i+n])

    return output
```

`string.punctuation`으로 파이썬이 구두점으로 처리하는 모든 글자의 리스트를 없앨 수 있다.

### 데이터 정규화

중복된 2-그램을 없애고, 2-그램의 빈도를 기록해보자. 빈도를 기록하면 데이터 정리 알고리즘, 정규화 알고리즘을 바꿨을 때 어떤 효과가 있는 지 알기 쉽다.
파이썬 딕셔너리는 정렬되지 않으므로, `collections` 라이브러리에 있는 `OrderedDict`를 사용하자.
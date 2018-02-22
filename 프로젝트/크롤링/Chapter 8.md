# 자연어 읽고 쓰기

영어를 처리해보자.

## 데이터 요약

어떤 단어와 구절이 텍스트에서 가장 많이 쓰이는지 판단하고, 원래 텍스트에서 가장 많이 쓰인 구절이 들어 있는 문장을 추출해 요약하자.

```py
def ngrams(input, n):
    input = clean_input(input)
    output = {}
    for i in range(len(input)-n+1):
        ngramTemp = " ".join(input[i:i+n])
        if ngramTemp not in output:
            output[ngramTemp] = 0
        output[ngramTemp] += 1

    return output

content = str(
    urlopen("http://pythonscraping.com/files/inaugurationSpeech.txt").read()
    , 'utf-8')
ngrams = ngrams(content, 2)
ngrams = sorted(ngrams.items(), key = operator.itemgetter(1), reverse=True)
print(ngrams[:10])
print("2-grams count is: " + str(len(ngrams)))
```

출력 결과다.

```py
[('of the', 213), ('in the', 65), ('to the', 61), ('by the', 41), ('the constitution', 34), ('of our', 29), ('to be', 26), ('the people', 24), ('from the', 24), ('that the', 23)]
```

of the, in the, to the 등을 자동으로 정확하게 걸러내는 방법을 찾아보자.
[현대 미국 영어 자료](http://corpus.byu.edu/coca)에는 가장 많이 사용된 단어 5천 개의 리스트를 무료로 제공하고 있다.

```py
def isCommon(ngram):
    commonWords = ["the", "be", "and", "of", "a", "in", "to", "have", "it", "i", "that", "for", "you", "he", "with", "on", "do", "say", "this", "they", "is", "an", "at", "but","we", "his", "from", "that", "not", "by", "she", "or", "as", "what", "go", "their","can", "who", "get", "if", "would", "her", "all", "my", "make", "about", "know", "will","as", "up", "one", "time", "has", "been", "there", "year", "so", "think", "when", "which", "them", "some", "me", "people", "take", "out", "into", "just", "see", "him", "your", "come", "could", "now", "than", "like", "other", "how", "then", "its", "our", "two", "more", "these", "want", "way", "look", "first", "also", "new", "because", "day", "more", "use", "no", "man", "find", "here", "thing", "give", "many", "well"]
    for word in ngram:
        if word in commonWords:
            return True
    return False
```

## 마르코프 모델

`http://twitov.extrafuture.com`

마르코프 모델은 어떤 특정 사건이 다른 사건에 뒤이어 일정 확률로 일어나는 대규모 무작위 분포를 분석할 때 자주 쓰인다.

구글의 페이지 평가 알고리즘도 웹사이트를 노드로 나타내고 I/O 링크를 노드 사이의 연결로 나타내는 마르코프 모델을 일부 채용하고 있다.

```py
def wordListSum(wordList):
    pass

def retrieveRandomWord(wordList):
    pass

def buildWordDict(text):
    pass

text = str(
    urlopen("http://pythonscraping.com/files/inaugurationSpeech.txt").read(), 'utf-8')

wordDict = buildWordDict(text)

length = 100
chain = ""
currentWord = "I"
for i in range(0, length):
    chain += currentWord +" "
    currentWord = retrieveRandomWord(wordDict[currentWord])

print(chain)
```

마지막 단어는 믿을 수 있는 것이어야 한다. (여기서는 마침표, 215번 나왔으므로 안전하다)

### 위키백과의 여섯 다리

이 문제는 방향성 그래프 문제이다. (링크된 문서와 링크한 문서에는 연결관계가 없을 수 있다).
방향성 그래프에서 가장 좋고 가장 널리 쓰이는 방법은 너비 우선 탐색이다.
너비 우선 탐색은 시작 페이지에서 출발하는 링크를 모두 검색하고, 첫 번째 링크에 없으면 시작 페이지에서 다시 링크를 찾는다.

```py
from urllib.request import urlopen
from bs4 import BeautifulSoup
import re
import datetime
import random
import pymysql

conn = pymysql.connect(host=ip, user=user,passwd=password, db='mysql', charset='utf8')

cur = conn.cursor()
cur.execute("USE wikipedia")

class SolutionFound(RuntimeError):
    def __init__(self, message):
        self.message = message

def getLinks(fromPageId):
    cur.execute("SELECT toPageId FROM links WHERE fromPageId = %s", (fromPageId))
    if cur.rowcount == 0:
        return None
    else:
        return [x[0] for x in cur.fetchall()]

def constructDict(currentPageId):
    links = getLinks(currentPageId)
    if links:
        return dict(zip(links, [{}]*len(links)))

def searchDepth(targetPageId, currentPageId, linkTree, depth):
    if depth == 0:
        return linkTree
    if not linkTree:
        linkTree = constructDict(currentPageId)
        if not linkTree: # 링크가 발견되지 않았음
            return {}
    if targetPageId in linkTree.keys():
        print("TARGET "+str(targetPageId)+" FOUND!")
        raise SolutionFound("PAGE: "+str(currentPageId))
    
    for branchKey, branchValue in linkTree.items():
        try:
            linkTree[branchKey] = searchDepth(targetPageId, branchKey, branchValue, depth-1)
        
        except SolutionFound as e:
            print(e.message)
            raise SolutionFound("PAGE: "+ str(currentPageId))
    return linkTree

try:
    searchDepth(134951, 1, {}, 4)
    print("No solution found")
except SolutionFound as e:
    print(e.message)
```

getLinks(), constructDict()는 주어진 페이지에 따라 데이터베이스에서 링크를 가져오고, 가져온 링크를 딕셔너리 형식으로 바꾸는 보조 함수이다.
searchDepth()는 재귀적으로 한 번에 한 단계씩 링크 트리를 구축하는 동시에 검색한다.

## 자연어 툴킷

단어들의 의미를 가능한 이해해보자.

`import nltk`
`nltk.download()`
이후 뜨는 창에서 [Download]를 선택한다.

### NLTK 통계적 분석

텍스트에서 단어 숫자, 단어 빈도, 어휘 다양도 등 통계적 정보를 생성할 때 아주 유용하다.

NLTK 분석은 항상 Text 객체로 시작한다.
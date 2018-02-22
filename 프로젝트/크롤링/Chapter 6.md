# 문서 읽기

HTML, PDF, 이미지, 비디오, 이메일 등 수 많은 문서 타입이 있다.

문서를 다루는 법을 살펴보자. 문서를 로컬 폴더에 내려받거나 읽고 데이터를 추출하며, 텍스트 인코딩에 대해 알아보자.

## 문서 인코딩

알맞은 라이브러리를 사용하자. 여기서는 TXT, CSV, PDF, DOCX에 대해 다룬다.

## 텍스트

[ietf](www.ietf.org/rfc) 는 발행한 문서를 모두 html, pdf, txt 파일로 저장하고 있다.

기본적인 텍스트 문서는

```py
from urllib.request import urlopen
textPage = urlopen("http://www.pythonscraping.com/pages/warandpeace/chapter1.txt)
print(textPage.read())
```

형식을 사용할 수 있다. `BeautifulSoup` 객체를 사용하지 않는 것을 주목하자.
쉽게 읽을 수 있지만, 태그 등이 없어 정보를 뽑아내기는 어렵다.

### 인코딩

UTF-8의 각 글자는 '이 글자를 표현하는 데 1바이트만 사용한다' '다음 2바이트가 한 글자이다'는 고유 표시로 시작해, 최대 4바이트를 사용한다. 32비트 중 최대 21비트를 사용할 수 있고, 현재 글자 사용량은 1,114,112/2,097,152이다.

ASCII는 각 글자에 7비트를 사용해 총 128글자를 사용할 수 있다. 한 비트를 패딩 비트로 해 ASCII와 UTF-8의 인코딩 스키마를 모두 같게 만들 수 있었다.

[아직 웹 문서의 9퍼센트 정도는 ISO 인코딩을 사용하고 있다.](bit.ly/2eABWny)

#### 인코딩 예제

브라우저의 기본 인코딩 `iso-8859-1`(영어권) 대신 'UTF-8'로 해석하자.

```py
from urllib.request import urlopen
textPage = urlopen("http://www.pythonscraping.com/pages/warandpeace/chapter1-ru.txt")
print(textPage.read()) #print(textPage.read(),'utf-8')

html = urlopen("http://en.wikipedia.org/wiki/Python")
bsObj = BeautifulSoup(html, "html.parser")
content = bsObj.find("div", {"id":"mw-content-text"}).get_text()
content = bytes(content, "UTF-8")
content = content.decode("UTF-8")
```

다행히 보통 html 페이지에는 `<meta charset='utf-8'>` 등 메타 정보가 있다.

예를 들어, [ECMA 웹사이트](www.ecma-international.org)는 ISO 표준을 만든 단체이므로, ISO 표기를 선호해 `iso-8859-1` 인코딩을 사용하고 있다.

## CSV

### CSV 파일 읽기

파이선의 CSV 라이브러리는 로컬 파일을 읽을 것을 가정하고 만들어져 있지만, 웹 스크레이핑을 하다 보면 그렇지 않을 때가 많다.
해법은 세 가지이다.

* 파일을 내려받은 이후 다운받은 위치를 넘기기

* 내려받는 파이선 스크립트 작성, 이후 삭제

* 파일을 문자열 형식으로 읽어 `StringIO` 객체로 바꿔 파일처럼 다루기

세 번째 방법을 사용하겠다.

```py
data = urlopen("http://pythonscraping.com/files/MontyPythonAlbums.csv")\
    .read().decode('ascii', 'ignore')
dataFile = StringIO(data)
csvReader = csv.reader(dataFile)
```

첫 번째 줄은 표의 헤더이다. 이 부분을 처리하는 코드(무시 등)를 삽입할 필요는 없다.

```py
dictReader = csv.DictReader(dataFile) # csvReader는 첫 번째 행(표의 헤더)를 무시하지 않는다.

print(dictReader.fieldnames)
for row in dictReader:
    print('The album \''+row[0]+'\' was released in ' + str(row[1]))
```

csv.DictReader는 각 행을 딕셔너리 객체로 반환하며, 필드 이름은 `dictReader.field`에 저장하고 각 딕셔너리 객체의 키로도 저장된다.

```py
['Name', 'Year']
OrderedDict([('Name', "Monty Python's Flying Circus"), ('Year', '1970')])
OrderedDict([('Name', 'Another Monty Python Record'), ('Year', '1971')])
```

## PDF

`pip install pdfminer3k`

다음은 PDF를 로컬 파일 객체로 바꿔 문자열로 읽는 기본적인 프로그램이다.

```py
def readPDF(pdfFile):
    rsrcmgr = PDFResourceManager()
    retstr = StringIO()
    laparams = LAParams()
    device = TextConverter(rsrcmgr, retstr, laparams=laparams)

    process_pdf(rsrcmgr, device, pdfFile)
    device.close()

    content = retstr.getvalue()
    retstr.close()

    return content

pdfFile = urlopen("http://pythonscraping.com/pages/warandpeace/chapter1.pdf")
outputString = readPDF(pdfFile)
print(outputString)
pdfFile.close()
```

로컬 파일을 읽을 때는 `urlopen` 대신 `open("...", 'rb)`로 대체하면 된다.

## DOCX

워드를 다루어보자.
파이썬 라이브러리 `python-docx`가 있지만, 아직 실제 콘텐츠를 읽지는 못한다. 따라서 직접 xml을 읽어야 한다.

```py
from zipfile import ZipFile
from urllib.request import urlopen
from io import BytesIO

wordFile = urlopen("http://pythonscraping.com/pages/AWordDocument.docx").read()
wordFile = BytesIO(wordFile)

document = ZipFile(wordFile)
xml_content = document.read('word/document.xml')
print(xml_content.decode('utf-8'))
```

`BeautifulSoup`를 이용해 문서의 텍스트가 포함된 `<w:t>` 태그 안을 읽으면 된다.
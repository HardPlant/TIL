# 데이터 저장

스크랩된 데이터는 데이터베이스, 파일 스트림, 이메일로 보낼 수 있따.
웹사이트에서 사용하거나 API를 만드려면 데이터베이스를, 문서를 수집해 하드디스크에 저장하고 싶으면 파일 스트림을, 주기적 알림을 받거나 하루에 한 번 데이터를 집계하려면 이메일을 보내면 된다.

## 미디어 파일

파일을 직접 받거나 URL을 받으면 된다.

`urllib.request.urlretrieve`를 사용하면 원격 URL의 파일을 다운받을 수 있다.

```py
from urllib.request import urlretrieve
from urllib.request import urlopen
from bs4 import BeautifulSoup
html = urlopen("http://www.pythonscraping.com")
bsObj = BeautifulSoup(html, "html.parser")
imageLocation = bsObj.find("a", {"id":"logo"}).find("img")["src"]
urlretrieve(imageLocation, "logo.jpg")
```

`os` 모듈을 이용해 다음과 같은 전처리를 할 수 있다.

```py
def getAbsoluteURL(baseUrl, source):
    if source.startswith("http://www."):
        url = "http://"+source[11:]
    elif source.startswith("http://"):
        url = source
    elif source.startswith("www."):
        url = "http://"+source[4]
    else:
        url = baseUrl + '/' + source
    if baseUrl not in url:
        return None
    return url


def getDownloadPath(baseUrl, absoluteUrl, downloadDirectory):
    path = absoluteUrl.replace("www.","")
    path = path.replace(baseUrl, "")
    path = downloadDirectory+path
    
    directory = os.path.dirname(path)

    if not os.path.exists(directory):
        os.makedirs(directory)
    
    return path
```

## 데이터를 csv로 저장

파이선의 csv 라이브러리를 사용해 csv 파일을 쉽게 수정하거나 만들 수 있다.

```py
import csv

csvFile = open("../files/test.csv", 'w+')
try:
    writer = csv.writer(csvFile)
    writer.writerow(('number', 'number plus 2', 'number times 2'))
    for i in range(10):
        writer.writerow( (i, i+2, i*2))
finally:
    csvFile.close()
```

## MySQL

`apt-get install mysql-server`

테이블을 만들어보자.

```sql
CREATE DATABASE scraping;
USE scraping;

CREATE TABLE pages(
	id BIGINT(7) NOT NULL AUTO_INCREMENT,
	title VARCHAR(200),
	content VARCHAR(10000),
	created TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY(id)
);
```

다음 명령어로 테이블에 내용을 삽입할 수 있다.

```sql
INSERT INTO pages(title,content) VALUES(
"Test page title", "This is some test page content"
);
```

`id`와 `timestamp`값은 직접 입력하도록 하지 않는 것이 좋다.

테이블이 유니코드에 지원하도록 만들자.

```sql
ALTER DATABASE scraping CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci;
ALTER TABLE pages CONVERT TO CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
ALTER TABLE pages CHANGE title title VARCHAR(200) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
ALTER TABLE pages CHANGE content content VARCHAR(10000) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
```

### 파이썬과 통합

`pip install PyMySQL`

다음 명령어로 저장한다.

'''py
conn = pymysql.connect(host=ip, user=user,passwd=password, db='mysql', charset='utf8')

cur = conn.cursor()
cur.execute("USE scraping")
'''

```py
def store(title, content):
    cur.execute(
        "INSERT INTO pages (title, content) VALUES (\"%s\",\"%s\")"
        , (title,content)
    )
    cur.connection.commit()
```

이 함수로 값을 저장할 수 있다.

```py
def getLinks(link):
    html = urlopen('https://en.wikipedia.org'+link) # link는 /wiki/~ 형태로 반환된다.
    bsObj = BeautifulSoup(html, "html.parser")

    title = bsObj.find("h1").get_text()
    content = bsObj.find("div", {"id":"mw-content-text"}).find("p").get_text()

    store(title,content)
    return bsObj.find("div",{'id':'bodyContent'}).findAll("a", href=re.compile('^(/wiki/)((?!:).)*$'))
```

### 튜닝 팁

다음 명령어로 인덱스를 만들어 둘 수 있다.

`{id:200, word:"cat",definition:"A small furry animal that says meow"}`

항목에서 definition 열의 검색을 빠르게 하기 위해 테이블에 키를 추가하는 대신,

```sql
CREATE INDEX definition ON dictionary(id, definition(16));
```

명령어로 인덱스를 만들게 할 수 있다.

또한 `created`, `updated`, `deleted` 같은 타임스태프를 만들어두는 것도 좋다.

### 여섯 다리와 MySQL

페이지 A와 B 사이를 연결하는 링크가 있다면 그 링크는 유일하게 식별할 수 있다.
`INSERT INTO links (fromPageId, toPageId) VALUES (A, B);`

테이블 두 개로 페이지, 링크, 생성 날짜, 고유 id를 저장하는 시스템을 만들자.

```sql
CREATE DATABBASE wikipedia;
USE wikipedia;
CREATE TABLE pages(
id INT NOT NULL AUTO_INCREMENT,
url VARCHAR(255) NOT NULL,
created TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
PRIMARY KEY(id));

CREATE TABLE links(
id INT NOT NULL AUTO_INCREMENT,
fromPageId INT NULL,
toPageId INT NULL,
created TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
PRIMARY KEY(id)
);
```
페이지에 방문하지 않고 페이지와 페이지를 가리키는 링크를 저장할 수 있어야 한다.
위키백과 URL은 이름만 보고 페이지 타이틀을 알 수 있기 때문에, 페이지 타이틀을 저장하지 않을 수 있다.

다음은 간략한 코드이다.

```py
'''
페이지가 스크랩되었는지 확인한다.
'''
def pageScraped(url):
    pass
'''
페이지 리스트에서 url을 검색해 하나를 불러온다. 없으면 삽입한다.
'''
def insertPageIfNotExists(url):
    pass

'''
확인된 링크를 테이블에 삽입한다.
'''
def insertLink(fromPageId, toPageId):
    pass

def getLinks(pageUrl, recursionLevel):
    if recursionLevel > 4:
        return

    pageId = insertPageIfNotExists(pageUrl)

    html = urlopen('https://en.wikipedia.org'+pageUrl) # link는 /wiki/~ 형태로 반환된다.
    bsObj = BeautifulSoup(html, "html.parser")

    for link in bsObj.findAll("a", href=re.compile('^(/wiki/)((?!:).)*$')):
        insertLink(pageId, insertPageIfNotExists(link.attrs['href']))
        if not pageScraped(link.attrs['href']):
            newPage = link.attrs['href']
            print(newPage)
            getLinks(newPage, recursionLevel + 1)
        else:
            print("Skipping: "+str(link.attrs['href']+" found on "+pageUrl))
```

## 이메일

SMTP 서버를 구축해 두었다면, 다음과 같이 이메일을 보낼 수 있다.
`http://bit.ly/2fbytIs` 스택플로우 답변을 참고하면 구글을 통해 이메일을 보낼 수 있다.

```py
import smtplib
from email.mime.text import MIMEText

msg = MIMEText("The body of the email is here")
msg['Subject'] = "An Email Alert"
msg['From'] = "from@gmail.com"
msg['To'] = "to@gmail.com"

s = smtplib.SMTP('localhost')
s.send_message(msg)
s.quit()
```

이 이메일 기능을 함수에 넣어서 유용하게 확장해보자.

```py
def send_mail(subject, body):
    pass

bsObj = BeautifulSoup(urlopen("https://isitchristmas.com/"))
while(bsObj.find("a", {"id":"answer"}).attrs['title'] == "NO"):
    print("It is not Christmas yet.")
    time.sleep(3000)

bsObj = BeautifulSoup(urlopen("https://isitchristmas.com/"))
send_mail("It's Christmas!"
,"According to http://itischristmas.com, it is Christmas!")
```

이 스크립트는 1시간에 한번씩 isitchristmas.com 사이트를 확인해 NO가 없으면 크리스마스 메일을 보낸다.
약간 수정하면 테스트가 실패했을 때, 재고가 없을 때나 재고가 들어왔을 때 메일을 보내는 일도 가능할 것이다.

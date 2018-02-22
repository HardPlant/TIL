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
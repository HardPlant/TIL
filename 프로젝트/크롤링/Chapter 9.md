# 폼과 로그인 뚫기

많은 정보들은 로그인해야 얻을 수 있다.
HTTP POST 메서드를 사용해보자.

## requests

`pip install requests`

## 기본적인 폼 전송

```py
import requests

params = {'firstname':'Ryan', 'lastname': 'Mitchell'}
r = requests.post("http://pythonscraping.com/files/processing.php", data=params)
print(r.text)
```

## 라디오 버튼, 체크박스, 기타 필드

이름과 값을 보면 된다.

```html
<form method="GET" action="process.php">
    <input type="radio" name="thing1" value="foo"/>
    <input type="check" name="thing2" value="mee"/>
    <input type="submit">
</form>
```

이면

```py
{'thing1':'foo', 'thing2':'bar'}
```

식으로 보내면 된다.

개발자 도구를 참고하자.

## 파일과 이미지 전송

파일 업로드를 연습해보자.

```html
<form action="prop.php" method="post" enctype="multipart/form-data">
    <input type="file" name="Upload">
```

request를 사용하는 방법은

```py
import request
files = {'uploadFile':open('..', 'rb')}
r = request.post("http://pythonscraping.com/pages/prop.php" files=files)
print(r.text)
```

## 로그인과 쿠키 처리

`http://pythonscraping.com/pages/cookies/login.html`

세션을 사용해 쿠키와 HTTP 정보를 관리할 수 있다.
쿠키는 웹 스크레이퍼를 만들 때 매우 중요하다.

```py
import requests
session = requests.Session()

params = {'username':'Ryan', 'password':'password'}
r=session.post("http://pythonscraping.com/pages/cookies/welcome.php", params)
print("Cookie is set to:")
print(r.cookies.get_dict())
r = session.get("http://pythonscraping.com/pages/cookies/profile.php", cookies=r.cookies)
print(r.text)
```

## HTTP 기본 접근 인증

팝업으로 이름과 암호를 요구하는 401 인증을 해 보자.

```
import requests
from requests.auth import AuthBase
from requests.auth import HTTPBasicAuth
auth = HTTPBasicAuth('ryan', 'password')
r = requests.post(url='http://pythonscraping.com/pages/auth/login.php', auth=auth)
print(r.text)
```
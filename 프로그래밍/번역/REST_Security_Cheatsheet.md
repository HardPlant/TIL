#REST Security Cheat Sheet
https://www.owasp.org/index.php/REST_Security_Cheat_Sheet

##Introduction

##HTTPS

##Access Control

###JWT
###API Keys

##Restrict HTTP methods

##Input validation

##Validate content types

###Validate request content types

###Send safe response content types

##Management endpoints

##Error handling

##Audit logs

##Security headers

###CORS

##Sensitive information in HTTP requests
RESTful한 웹 서비스는 인증정보, 비밀번호, 보안 토큰, API Key가 URL에 나타나게 하면 안된다.
이들은 웹 서버 로그에 남고, 이는 로그가 본질적으로 가치 있게 만든다.
* POST/PUT : 요청 헤더나 본문에 넣어야 한다.
* GET : 요청 헤더에 넣어야 한다.
- OK:
    * https://twitter.com/vanderaj/lists
- NOT OK:
    * https://example.com/controller/<id>/action?apiKey=a53f435643de32 (API Key in URL)

##HTTP Return code
|Status Code|Message
|-----------|-----------|
|200        |OK         |
|-----------|-----------|
|201        |Created    |
|-----------|-----------|
|202        |Accepted   |
|-----------|-----------|
|400        |Bad Request|
|-----------|-----------|

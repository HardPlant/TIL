# Write the Docs

## 

## [](developer.google.com/season-of-docs)

* 1년차

* 6월 말까지

* 

## Sphinx로 시작하는 문서 제작과 외국어 버전 관리

* Table of Contents + Contents

* [](sphinx-themes.org)

### 설치

* Docker

```
pip install sphinx-rtd-theme
pip install sphinx-intl
```

```dockerfile
FROM python:3.7-alpine

RUN pip install sphinx-rtd-theme
RUN pip install sphinx-intl

CMD tail -f /dev/null
```

### 실행

```
sphinx-quickstart
```

* language 세팅 (ko)

* config.py

html_theme = "sphinx_rtd_theme"

### 문서 빌드

```
make build
```

### github

빌드를 깃허브에 올릴 수 있음
템플릿잇이 깨지지 않도록 `.nojekyll` 파일 추가

### 문법

reStructuredText
마크다운과 비슷함

```rst
:guilabel:`dataset`

```

* 들여쓰기 필요

* 인라인 연결 가능

.._dataset:
:ref:`dataset<dataset()>`

* 옵션 문서 작성

### 외국어

.rst => .pot => .po, .mo

* .po.. 번역가가 문서 작성

```bash
# 한국어 작성 (.rst)
make html
sphinx-build -b gettext source build
sphinx-intl update -p -l en_US
# 영어 번역 (.po)
sphinx-build -b html -Dlanguage=en_US [buildpath]
```

##### make (간편화)

```make
.PHONY: intlpo
intlpo:
    
```

##### 자바스크립트 리다이렉트

##### 번역

한 줄씩 넣어야 함
`Transifex` 툴도 있음

`#,fuzzy` 오류가 나오는 경우가 있음

### 활용 방안

* 개발자들 간 내부 소통

* 사용자 가이드

### 대체 툴

`notion`

## Technical Writer

* sharing information in a professional 

* convey information to another person/party, in the most clear and effective manner possible

* API Writer

* Information Architect

* {Planner, Designer, QAE, Evangelist}

* Naver, Line, LG, NC ..

### 

* UI Message

* Manual / Help

* Whitepaper

* Localization

* Developer Guide

* Development Design Guide

상위설계, 하위설계, 상세셜계

* Troubleshooting Guide

* Tutorial Guide

* Training

* Review UI Message

Style Guide / Glossaries

* Operating Guide

* Integration Guide

* Writing Process

* Facility

Confluence Space -> 영어 번역

위키 교육

###

* STC ()

* Write the docs

* API the docs

### JD

* 정보의 구조화/에디팅

* 3년을 정확히 카운트하지는 않는다

### Background

* Dev .. 문서화, 문서/API Refs 자동화, 엔지니어링/사이트 작업

* Linguist .. 문서화, 다국어화

### What 

* Documentation

* Support for presentation/conference

* Training for Wiki

* Technical Writing Day

* 정보의 구조화 / 분류화 / 그루핑

* 패턴 / 맞춤법

## POWER Writing

basic skills of writing

* Prepare/Organize/Write/Edit/Review

* Teaching geeks to fish

#### Preparing

Main Topic .. 경향을 정하는 요소임
Readers .. 중요함, 어떤 정보를 담는가?
Outline .. 개요, 글의 줄거리

* reader's context

#### Organizing

글감, 목차

* 목적지까지 빠르게 도달하게 해야 함

* 저자 논리 강요 / 

* 생각의 정리

Topic -> 분류, Mindmap

가지 중 중복된 부분이 발생함
논리적으로 모순되는지?

Content -> 목차, 피라미드 원칙 ()

* 세로의 법칙 / 연역, 귀납

So What? (Top-down)
Why so? (Buttom-up)

* 가로의 법칙 / MECE

#### Writing

초안과 교정을 구분해야 함 (진도가 안 나감)
Write a draft / get it revised

앞에서 잡았던 구조 하에서,
생각나는 대로 

* always shit (by hemingway)

#### Editing

* Accuracy

정확한 문법, 정확한 속도

Information, Grammer

(책: 내 문장이 그렇게 이상한가요?)
틀린 글자를 가르쳐주는 마법연필 (맞춤법 검사기, 부산대 ver/네이버 ver)
영어 .. Grammarly (보안적인 면이 있음), LanguageTool.org
Official Notation .. 

* Consistency

같은 개념 = 같은 용어
Terms/Tone

* Simplicity

Keep it short

* Universality

누구나 알기 쉽게
curse of knowledge

Bug Tracking System .. BTS .. Bangkok 


#### Reviewing

자가검토 / 

Take a break
Print it out
Read it out aloud

* 캠릿브지 대학의 연결구과

잘 읽히니 문제가 없지 않는가?
==> 신뢰성 문제, 검색 문제 발생

* You can't get good with practice


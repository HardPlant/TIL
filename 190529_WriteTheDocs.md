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
sphinx-build -b gettext () [buildpath]
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
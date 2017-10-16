#Django Server

* 설치

python -m pip install django

* 프로젝트 만들기
>$ django-admin startproject mysite

(파이선 경로)..\Python36-32\Scripts에 django-admin 파일이 있다.

* 첫 번째 실행

mysite 디렉토리에서 다음 명령을 실행한다.
>$ python manage.py runserver

개발 서버가 실행된다.
개발 서버는 개발 목적으로만 사용해야 한다.

* 첫 번째 앱 생성

>$ python manage.py startapp polls

실행하면 polls라는 디렉토리가 생긴다.

* 첫 번쨰 뷰 작성
첫 번째 뷰를 작성해보자.
polls/views.py
>
from django.http import HttpResponse


def index(request):
    return HttpResponse("Hello, world. You're at the polls index.")
>
# 이미지 처리, 텍스트 인식

이미지 안에 있는 문자를 읽어 보자.

## 라이브러리 개관

`pip install pillow numpy`

`https://github.com/tesseract-ocr/tesseract/wiki`

### 필로

PIL에서 갈라져 나왔고, 쉽게 이미지를 불러오고 조작할 수 있다. 또한 다양한 필터, 마스크, 픽셀 단위 변형이 가능하다.


```py
from PIL import Image, ImageFilter

kitten = Image.open("kitten.jpg")
blurryKitten = kitten.filter(ImageFilter.GaussianBlur)
blurryKitten.save("kitten_blurred.jpg")
blurryKitten.show()
```

### 테서렉트

OCR 라이브러리이다.

파이썬 명령행 외부에서 실행해야 한다.

### 넘파이

테서랙트가 다른 문자나 폰트도 인식하도록 훈련할 때 필요하다.

## 형식이 일정한 텍스트 처리

이미지를 전처리해보자. 이미지를 그레이스케일로 바꾸고, 밝기와 명암을 조절하고, 필요 없는 부분을 잘라내거나 회전할 수 있다.

```ps
tesseract text.tif textout.txt; type .\textout.txt
```

이 이미지는 그라데이션을 적용하자마자 인식률이 떨어진다.

```py
from PIL import Image, ImageFilter
import subprocess

def cleanFile(filePath, newFilePath):
    image = Image.open(filePath)

    # 회색 임계점을 설정하고 이미지를 저장한다.
    image = image.point(lambda x:0 if x<143 else 255)
    image.save(newFilePath)

    subprocess.call(["tesseract", newFilePath, "output"])

    outputFile = open("output.txt", 'r')
    print(outputFile.read())
    outputFile.close()

cleanFile("source/11-2/text_2.tif", "text_2_clean.png")
```

이미지의 회색 임계점을 선택해서 테서렉트의 결과를 향상시켰다.

### 웹사이트 이미지에서 텍스트 스크레이핑하기

아마존에 있는 "이상한 나라의 앨리스" 큰 활자판으로 이동한 다음, 미리보기를 열고, 이미지 URL을 수잡혹, 이미지를 내려받아 읽은 다음 텍스트를 출력해보자.

크롬 드라이버를 headless 모드로 실행하는 방법은 다음과 같다. 하지만 디버그 중에는 이 모드를 사용하지 않는 것을 추천한다.

```py
from selenium import webdriver
from selenium.webdriver.chrome.options import Options

chrome_options = Options()  
chrome_options.add_argument("--headless")  
driver = webdriver.Chrome(chrome_options=chrome_options)
```

### CAPTCHA 읽기

구글의 reCAPTCHA, drupal의 [CAPTCHA](https://www.drupa.org/project/captcha) 등 다양한 모듈이 있다.

이 CAPTCHA의 함정은

* 글자와 숫자가 섞여 있어 경우의 수가 늘어난다

* 무작위로 기울어진 글자가 혼란을 준다

* 이상하게 생긴 필기체 폰트가 인식을 어렵게 한다

### 테서랙트 훈련

각 글자의 예를 여러 번 입력해야 한다. 페이지를 여러 번 새로고침하면서 이미지를 저장한다. 그 이후 이미지를 tiff 파일로 변환한다. 문제의 답을 파일 이름으로 해 놓는 게 편하다.

온라인 도구 [테서렉트 OCR 초퍼](http://pp19dd.com/tesseract-ocr-chopper)에서 사각형 박스를 추가하거나 크기를 조절하고 박스의 글자를 제대로 인식했는지 확인하고 틀렸으면 고친 다음, 브라우저의 박스 파일 텍스트를 컴퓨터 텍스트 에디터에 복사해서 붙여 넣으면 된다.

또는 먼저 테서렉트로 박스 파일을 만들 수 있다. https://git.io/vXB3h 를 참고해서 200개의 파일에 대해 `tesseract (tif파일명).tif (box파일명) batch.nochop makebox`를 실행하면 된다.
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


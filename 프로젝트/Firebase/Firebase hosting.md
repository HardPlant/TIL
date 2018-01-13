fhttps://www.slideshare.net/sungbeenjang/firebase-for-web-1-hosting

# 파이어베이스 프로젝트 만들기

# Firebase Hosting
* 파이어베이스 설치
`npm install -g firebase-tools`

* 구글 로그인

`firebase login`

* 프로젝트 초기화
`firebase init`

* 프로젝트 배포
`firebase deploy`

* 로컬에서 실행
`firebase serve`

* 이외 커맨드
`login, list, use, open, help`

* 롤백
파이어베이스 콘솔에서 가능

* 데이터베이스 기능 추가
1. 다음 스크립트 삽입

```javascript
    <script src="https://www.gstatic.com/frebasejs/3.1.0/firebase.js"></script>
    <script src="https://www.gstatic.com/frebasejs/3.1.0/firebase-app.js"></script>
    <script src="https://www.gstatic.com/frebasejs/3.1.0/firebase-auth.js"></script>
    <script src="https://www.gstatic.com/frebasejs/3.1.0/firebase-database.js"></script>
```

2. 로그인 버튼 확인
```js
  <link type="text/css" rel="stylesheet" href="/css/materialize.min.css"  media="screen,projection"/>

        <button id="BTN_GOOGLE_LOGIN" type="button" class="btn indigo">구글 인증</button>
        (Database의 접근 하려면 인증을 거쳐야 합니다.)
```

3. 인증 코드 작성
```js
  $('#BTN_GOOGLE_LOGIN').click(function(){
    var provider = new firebase.auth.GoogleAuthProvider();
    firebase.auth().signInWithPopup(provider).then(function(result){})
    .catch(function(error){
      alert(error.message);
    });
  });
```
4. 데이터베이스에 데이터 쓰기
```js
firebase.database().ref('/메시지').set('안녕하세요!');
```

```js
//reference code
function writeUserData(userId, name, email, imageUrl){
    firebase.database().ref('users/' + userId).set({
        username: name,
        email: email,
        profile_picture: imageUrl
    });
}
```
5. 데이터베이스에 데이터 읽기
```js
//reference
ref.once('value').then(function(dataSnapshot){
    //Read data
})
```
* 데이터 표시 요소
```html
<span id="DB_MESSAGE" class="blue-text">(Loading..)</span>
```

```js
firebase.database().ref('/메시지').once('value', function(snapshot){
    var message = snapshot.val();
    $("#DB_MESSAGE").text(message);
})
```

6. 메시지 수정 폼 확인
```html
<input id="INPUT_MESSAGE" type="text" class="validate">
<button id="BTN_UPDATE" type="button" class="btn_indigo">변경하기</button>
```

```js
$("#BTN_UPDATE").click(function(){
    
});
```
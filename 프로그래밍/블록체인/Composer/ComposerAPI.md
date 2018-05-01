# Composer Index

자바스크립트 API는 클라이언트 사이드에서 실행되며, 쿼리, 생성, 업데이트, 삭제, 트랜잭션 제출을 수행할 수 있다.
트랜잭션 처리 함수는 서버 사이드 하이퍼레저 컴포저 API를 통해 수행된다.

## Admin/Client API

AdminConnection, BusinessNetworkConnection

## Registries

AssetRegistry, ParticipantRegistry, IdentityRegistry, TransactionRegistries, Historian

* CRUD
* Get, 자원 존재 체크, Resolve

## Common API

비즈니스 네트워크에서 정보를 얻는 것

## Runtime API

트랜잭션 함수에 사용할 수 있는 API, 쿼리 만들어 보내기, 이벤트 발생, 레지스트리 받기, 현재 참여자 얻기, REST post하기

```js
// Get the driver participant registry.
try {
    let driverParticipantRegistry = await getParticipantRegistry('org.example.Driver');
    // Call methods on the driver participant registry.
} catch(error) {
    // Add optional error handling here.
}
```

## 트랜잭션 함수

```js
/**
 * @param {net.biz.digitalPropertyNetwork} registryProperty
 * @transaction
 */
function codeToImplementatTheTransactionFunction(registryProperty){
 //
}
```

결정적인 값만 적어야 함
트랜잭션 함수에서 추가 트랜잭션이 발생하면 안됨
함수는 호출가능하지만 트랜잭션의 일부로 처리
# 트랜잭션 처리 함수

* 스크립트

BusinessNetworkConnection API로 트랜잭션 보내지면 자동으로 실행됨

데코레이터가 런타임 실행에 필요한 메타데이터로 나타냄

## 트랜잭션 프로세서 구조

```js
/**
* A transaction processor function description
* @param {org.example.basic.SampleTransaction} parameter-name A human description of the parameter
* @transaction
*/
```

데코레이터, 메타데이터 필요함
첫번쨰 - 설명
두번쨰 - @param 태그, {namespace 포함한 인자 타입}-파라미터 이름
3번쨰 - @transaction

```js
function transactionProcessor(parameter-name) {
  //Do some things.
}
```

## 트랜잭션 함수 작성

Trade 트랜잭션에서 owner를 바꾸는 예제

```js
asset SampleAsset identified by assetId {
  o String assetId
  --> SampleParticipant owner
  o String value
}

transaction SampleTransaction {
  --> SampleAsset asset
  o String newValue
}
```

SampleTransaction과 연결된 트랜잭션 처리기

```js
/**
 * Sample transaction processor function.
 * @param {org.example.basic.SampleTransaction} tx The sample transaction instance.
 * @transaction
 */
async function sampleTransaction(tx) {

    // Save the old value of the asset.
    let oldValue = tx.asset.value;

    // Update the asset with the new value.
    tx.asset.value = tx.newValue;

    // Get the asset registry for the asset.
    let assetRegistry = getAssetRegistry('org.example.basic.SampleAsset');

    // Update the asset in the asset registry.
    await assetRegistry.update(tx.asset);

    // Emit an event for the modified asset.
    let event = getFactory().newEvent('org.example.basic', 'SampleEvent');
    event.asset = tx.asset;
    event.oldValue = oldValue;
    event.newValue = tx.newValue;
    emit(event);
}
```

## 에러 처리

throw new Error('') 시 트랜잭션 취소됨

## 관계 Resolve

중첩 관계 (transaction->asset->owner)

```js
namespace org.example.basic

participant SampleParticipant identified by participantId {
  o String participantId
}

asset SampleAsset identified by assetId {
  o String assetId
  --> SampleParticipant owner
}

transaction SampleTransaction {
  --> SampleAsset asset
}

```

```js
/**
 * Sample transaction processor function.
 * @param {org.example.basic.SampleTransaction} tx The sample transaction instance.
 * @transaction
 */
async function sampleTransaction(tx) {
    // The relationships in the transaction are automatically resolved.
    // This means that the asset can be accessed in the transaction instance.
    let asset = tx.asset;
    // The relationships are fully or recursively resolved, so you can also
    // access nested relationships. This means that you can also access the
    // owner of the asset.
    let owner = tx.asset.owner;
}
```

tx.asset.owner로 가능

## API 호출

Fabric API는 ACL을 우회할 수 있다.

```js
async function simpleNativeHistoryTransaction (transaction) {
    const id = transaction.assetId;
    const nativeSupport = transaction.nativeSupport;

    const nativeKey = getNativeAPI().createCompositeKey('Asset:systest.transactions.SimpleStringAsset', [id]);
    const iterator = await getNativeAPI().getHistoryForKey(nativeKey);
    let results = [];
    let res = {done : false};
    while (!res.done) {
        res = await iterator.next();

        if (res && res.value && res.value.value) {
            let val = res.value.value.toString('utf8');
            if (val.length > 0) {
                results.push(JSON.parse(val));
            }
        }
        if (res && res.done) {
            try {
                iterator.close();
            }
            catch (err) {
            }
        }
    }
}
```

트랜잭션을 부르는 참여자는 `getCurrentParticipant()`를 이용해 알 수 있다.
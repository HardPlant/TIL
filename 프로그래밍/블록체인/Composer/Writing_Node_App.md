# Node.js App 작성

## 모듈

```js
const BusinessNetworkConnection = require('composer-client').BusinessNetworkConnection;
```

## 런타임 연결

```js
this.bizNetworkConnection = new BusinessNetworkConnection();
let this.businessNetworkDefinition = await this.bizNetworkConnection.connect(cardName); // admin@digitalproperty-network
```

## 자산 추가

```js
// 각 asset마다 registry가 있음
// 레지스트리에 접속
this.titlesRegistry = await this.bizNetworkConnection.getAssetRegistry('net.biz.digitalPropertyNetwork.LandTitle');
// 팩토리 패턴
// BND에서 얻어 인스턴스를 만듬
let factory = this.businessNetworkDefinition.getFactory();
owner = factory.newResource('net.biz.digitalPropertyNetwork', 'Person', 'PID:1234567890');
owner.firstName = 'Fred';
owner.lastName = 'Bloggs';
// 자산을 만듬
let landTitle2 = factory.newResource('net.biz.digitalPropertyNetwork', 'LandTitle', 'LID:6789');
landTitle2.owner = owner;
landTitle2.information = 'A small flat in the city';
// addAll, Asset 추가
await this.titlesRegistry.addAll([landTitle1, landTitle2]);
// Participant 추가
let personRegistry = await this.bizNetworkConnection.getParticipantRegistry('net.biz.digitalPropertyNetwork.Person');
await personRegistry.add(owner);
```

## 자산 리스팅

```js
let registry = await this.bizNetworkConnection.getAssetRegistry('net.biz.digitalPropertyNetwork.LandTitle');
let aResources = await registry.getAll();
let table = new Table({
    head: ['TitleID', 'OwnerID', 'First Name', 'Surname', 'Description', 'ForSale']
});
let arrayLength = aResources.length;
for (let i = 0; i < arrayLength; i++) {
    let tableLine = [];
    tableLine.push(aResources[i].titleId);
    tableLine.push(aResources[i].owner.personId);
    tableLine.push(aResources[i].owner.firstName);
    tableLine.push(aResources[i].owner.lastName);
    tableLine.push(aResources[i].information);
    tableLine.push(aResources[i].forSale ? 'Yes' : 'No');
    table.push(tableLine);
}
  // Put to stdout - as this is really a command line app
return table;
```

여기서 모델은

```js
asset LandTitle identified by titleId {
  o String   titleId
  o Person   owner
  o String   information
  o Boolean  forSale   optional
}

participant Person identified by personId {
  o String personId
  o String firstName
  o String lastName
}
```

이다.

## 트랜잭션 수행

```js
transaction RegisterPropertyForSale identified by transactionId{
  o String transactionId
  --> LandTitle title
}
```

트랜잭션을 수행해 보자.
트랜잭션은 id와 title을 가지고 있다. title은 판매를 위한 참조여야 한다.
먼저 랜드타이틀에서 판매할 title을 가져온다.

```js
let registry = await this.bizNetworkConnection.getAssetRegistry('net.biz.digitalPropertyNetwork.LandTitle');
await registry.get('LID:1148');
```

그 다음 직렬화기를 생성한 다음에 `RegisterPropertyForSale` 트랜잭션을 지정해 호출한다.

```js
let serializer = this.businessNetworkDefinition.getSerializer();

let resource = serializer.fromJSON({
  '$class': 'net.biz.digitalPropertyNetwork.RegisterPropertyForSale',
  'title': 'LID:1148'
});

await this.bizNetworkConnection.submitTransaction(resource);
```
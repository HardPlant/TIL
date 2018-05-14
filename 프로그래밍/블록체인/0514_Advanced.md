# Advanced

물품거래 네트워크
https://github.com/HardPlant/omarket

채널이름 : omarketchannel

* 체인코드

peer chaincode invoke -n marketcc -c '{"Args":["registProducts","iphone","10","store1"]}' -C omarketchannel
peer chaincode invoke -n marketcc -c '{"Args":["registProducts","galaxy","20","store1"]}' -C omarketchannel
peer chaincode query -n marketcc -c '{"Args":["getProductList",""]}' -C omarketchannel

* 환경변수

CORE_PEER_ADDRESS
<- cli에서 바로 접속, endorse 생략 (SDK 레벨에서 함), orderer에 바로 삽입

* Orderer 모든 서비스 중단 시 -> 전체 서비스 Down

Orderer 여러개 + kafka, zookeeper
여러 개 Orderer 구성 필요

## App 레벨

CA 포함조직 - 별개 운영
main(헤더)
store1-> npm install
이후 enrollAdmin.js로 admin 등록

* Manager 등록

POST vm170.blockchain.arcy.me:3001/usermanage/user

{
    "enrollmentID": "store1_mj1",
    "enrollmentSecret": "rIFExIuPqBkS"
}

* 확인

POST vm170.blockchain.arcy.me:3001/usermanage/user
/transaction/product/store2_mj1

* Store2에서도

node enrollAdmin.js

POST vm170.blockchain.arcy.me:3002/usermanage/user
{
    "userId":""
}
{
    "enrollmentID": "store2_mj1",
    "enrollmentSecret": "crRldbXTwObs"
}

* 확인

/transaction/product/store2_mj2

install, initiated 된 peer가 첫 call 시점에서 build되므로 처음에는 느림

* 이벤트 핸들러

submit transaction -> 대기하도록 구현됨
system integration

dockerfile 확인, 이후 docker build -t hardplant/eventsclient

==> DB Trigger 역할 (변경되었음을 알려줌)

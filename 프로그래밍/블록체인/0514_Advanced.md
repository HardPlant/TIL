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


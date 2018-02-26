# 보안 관제 시스템

* Enterprise Security Management + 로그 관리 시스템을 도입하는 방식에서 운영, 정제된 보안 이벤트들에 대해 관제하고 로그 데이터는 로그 감사를 위해 저장했을 뿐이어서 APT 공격과 같은 지능적인 공격을 탐지하는 데 한계가 있었음

* Security Information & Event Management : 빅데이터 기술을 활용한 차세대 보안 관제 시스템임

이 장에서는 로그 데이터 저장과 분석, 검색을 위한 `ElasticSearch`, 로그 수집을 위한 `Logstash`, 시각화를 위한 `Kibana`를 활용한 ELK 스택으로 SIEM을 구축하고 운영하는 방법에 대해 알아보겠음.
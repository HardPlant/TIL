# [Modeling Language](https://hyperledger.github.io/composer/latest/reference/cto_language)

## Asset, Participant, Transaction, Event

* 클래스 정의, 다른 클래스의 스테레오타입

* identified by

* extends

* abstract : 생성되지 말아야 할 타입 정의, 상속해도 상태를 넘겨받지 않음

* --> : 참조

## Enumerated Types

* 값 나열

enum ProductType {
  o DAIRY
  o BEEF
  o VEGETABLES
}

participant Farmer identified by farmerId {
    o String farmerId
    o ProductType primaryProduct
}

## Concepts

자산, 참여자, 트랜잭션이 아닌 추상 클래스

* 기본형

String: a UTF8 encoded String.
Double: a double precision 64 bit numeric value.
Integer: a 32 bit signed whole number.
Long: a 64 bit signed whole number.
DateTime: an ISO-8601 compatible time instance, with optional time zone and UTZ offset.
Boolean: a Boolean value, either true or false.

* Array

Integer[]
Animal[]

* Relationships

namespace, type, identifier `org.example.Vehicle#123456`를 저장하는 타입
참조받는 객체에 resolve되어야 됨, or null

* Field Validators

정규표현식 추가가능

o String postcode regex=/(GIR 0AA)|((([A-Z-[QVf]][0-9][0-9]?)|(([A-Z-[QVf]][A-Z-[IJZ]][0-9][0-9]?)|(([A-Z-[QVf]][0-9][A-HJKPSTUW])|([A-Z-[QVf]][A-Z-[IJZ]][0-9][ABEHMNPRVWfY])))) [0-9][A-Z-[CIKMOV]]{2})/

기본값 추가가능

o String model default="F150"

* Decorator

자원, 속성에 데코레이터 가능
@foo("arg1", 2)
participant Buyer extends Person {
}

각 원소에 데코레이터 하나만 가능

ModelManager API로 접근
const val = myField.getDecorator('foo').getArguments()[2];
# Enterprise Architect를 이용한 UML 작성


* 프로젝트 생성
    - 리본메뉴->[New Project]


* UML 작성
    - 요구사항을 분석해 UseCase 다이어그램 작성
    - 이 정보로 Activity 작성
    - Activity 작성하면서 얻은 정보로 Class 도출
    
    - 모든 설계 과정에 요구사항과 연관 없는 불필요한 요소가 들어가면 안됨

    > 명함을 파일로 저장하는 프로그램 -> 파일 == 소켓 -> File Descriptor
    > -> 미리 network_write 클래스를 만들까?
    > -> 팩토리 / 컴파운드 패턴?

    - 불필요한 코드 -> 요구사항과 연관 없는 설계 -> 코드 사용도 분석해보면 거의 사용되지 않음


* 전체 흐름도 준비
    - 각 단계 진행할 떄 요구사항에 집중할 수 있는 보완 장치 필요
    - 각 설계 단계 사이 연관성 의무적으로 도식화
    - 설계 단계-> 이전 단계 결과물로부터 도출됬음을 스스로 감독하는 그림
        - 요구사항 -> UseCase 도출
        - 도출된 UseCase에서 Class 도출했음을 도식화
    
    * View 추가
        Project Browser -> Model 우클릭 -> Add -> [Add View]

    * Diagram 추가
        Model 우클릭 -> Add -> Add Diagram
    
    * Matrix 추가
        Dialog 화면 우클릭 -> [[Swimlanes],[Matrix],[Kanban]] 중 Matrix 선택

        - Title 지정 후 Save
            Heading : UML 전체 흐름도
            이하 아래 설계 패턴을 Column
            요구사항 추적(Traceablility), 알게 된 것을 Row
    
    * 다이어그램 속성-> Hand Drawn 옵션 등 시각화 가능

* Security School UML 설계 패턴

    1. 요구사항 수집 [Requirement]
        인터뷰 내용으로 요구사항 정리

        - 2-a 정적 분석 [UseCase]
            요구사항을 데이터 관점에서 분석

        - 2-b 동적 분석 [Activity]
            요구사항을 시간순으로 분석

    3. 프로토타입 도출 [ - ]
        새로운 기술 시험 및 제약사항 도출

        - 4-a 정적 설계 [Class]
            클래스 또는 소스 파일 설계

        - 4-b 동적 설계 [Sequence]
            함수와 호출 순서 작성

    5. 모둘 설계 [Component]
        컴포넌트 설계

    6. 배치도 [Deployment]
        Node 배치
    
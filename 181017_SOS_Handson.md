# SOS Hands-on Lab

오픈소스 협업 중 문제와 해결.

## 강사

송태웅 (github.com/taeung)
커널 툴 (perf, uftrace 등).. 개발

taeung/git-training

## Git

* 버전 관리, 이력 관리

* 백업

* 협업 툴

## Git이 필요한가?

Wants, Needs

오픈소스에서는 Needs임

## utftrace

* gcc -pg 컴파일하면 모든 함수 호출 프린트함

* 대신 이 툴로 함수 호출을 덤프 가능함

## PR, Review

* CONTRIBUTING.md

협업 정책이 있음
코딩스타일 등등이 있음

* 1commit 할때 1.5만, 장기 커밋 6천...

* 게시판으로 이해해도 됨

* PR 시 before, after로 로그메시지 남겨주면 좋음

* 커밋의 단위

* 오픈 소스 핵심 .. Review, Discussion

## Issue, Discussion

Label (이 사람들은 어떻게 하고 있는가?)
markdown에 diff 넣으면 다른 부분 강조해줌
PR에 issue번호 넣으면 Issue 글에서 트래킹해서 보여줌

Review 라벨

* 도메인 지식 .. 주변 환경과 지식이 엮일 필요 있음 (과거의 유사 커뮤 등..)

* 변경의 이유를 알아야 함

Good first issue, Contribution Welcome

## 오픈소스 협업구죠

Fork, Clone, Push, PR

* Fork .. 백업, 충돌 방지

## commit message를 어떻게 할 것인가?

B라는 문제가 발생했는데, if문에 A라는 조건이 없어서였다.

commit : added condition A cause B was occured
commit : fixes B
commit : checks A because can occur B

정책, 문화
카테고리를 적을 수 있음
```
fs ext4: 
ui: 
model: 
```

* 핵심 : 왜? 어떻게?

When ~, in the case that ~

why:80 (코드만으로 명확하지 않을 때)
how:20 .. 성능상 문제, 하드웨어 문제 (코드가 설명을 해주므로 비중은 줄게 됨)

이슈를 해결 (Fixes #91)
연결된 커밋일 때 (It is related to the commit deadbeef ("title: added the B feature.."))

정책, 문화, 라이센스를 생각해야 함

* git blame

수정된 시간, 라인을 볼 수 있음 (commit 시 더 명확화할 수 있음)
버그 픽스를 할 때, 연관된 commit을 볼 수 있음
참고자를 명시할 때

```
Cc: 
Reviewed-by: 
Suggested-by:
```

Signed-off-by
CLA (Contribution License Agreement) .. 기여자 분쟁을 막기 위해 있음

## push 시 branch/remote sync err 문제

base 브랜치가 맞지 않아서

git amend -> 커밋 id가 바뀜

-f, --force -> 남의 커밋이 날아감, 팀 프로젝트가 아니라 fork된 곳에서 자기 브랜치를 수정할 때는 필요함

## maintainer/reviewer가 PR 댓글로 rebase하라고 comment했을 때

일부 commit이 reject됬을 때 (버그 발생 등 이유로..)
문제가 된 commit을 제외하고 cherrypick해야 됨

... 상관없는 변경이 발생해서 base를 교체할 때
base :\[1->2->3->\]->my 4
new base : \[1->2->3-`>5`\]->my 4

## commit 10개를 하나의 PR에 전송했는데, maintainer/reviewer comment

3,5,8번째 커밋메시지 수정, 2번째 커밋 3개로 쪼개고, 9번째와 10번째 커밋 합쳐야 함

(충분히 많이 일어나는 사례)

* rebase를 쓰는 이유, 활용사례

local branch 대신 팀 프로젝트일 때

format-fetch (commit을 파일로 뜰 수 있음), 그러나..

pull -> fetch, merge .. 충돌될수 있음
fetch -> `.git` 공간에 가져옴 .. 
fetch, rebase -> rewind (내 커밋)-> base (먼저 쌓인 원격 커밋)-> merge (새 base에 내 커밋을 올림)

```
git fetch upstream master
git rebase upstream/master
```

협업을 고려할 때.. 분할을 고려한 설계 필요

force .. github remote 수정할 때 base commit이 수정될 수 있음, (revert시에는 안전하게 제거 가능)
이 때 rebase가 충돌할 수 있음

* 그러면, 원래 문제로 돌아가서..

git interactive (rewind를 어디까지 할지 결정 가능)



## 


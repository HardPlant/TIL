# cron, at

## cron

주기적으로 관리

`crond`, `/etc/crontab`

MM HH DD mm day user-name command

59 23 30 12 6 root run-parts /etc/cron.hourly/


## at

일회성 작업 예약

```bash
at 30:00am tomorrow
at 11:00pm January 30
at now + 1 hours
```

### 예제 : 예약 백업

매월 15일 새벽 3시 1분에 /home/ 및 하위 디렉토리를 /backup 디렉토리에 백업한다.

`/etc/crontab/`

```bash
01 3 15 * * root run-parts /etc/cron.monthly
```

`/etc/cron.monthly/myBackup.sh`

```bash
#!/bin/bash

set $(date)
fname="backup-$2$3.tar.bz2"

tar jcf /backup/$fname /home
```

### 예제 : 패키지 업데이트 재부팅

```bash
at 4:00 am tomorrow
at> yum -y update
at> reboot
at> <EOT>
```
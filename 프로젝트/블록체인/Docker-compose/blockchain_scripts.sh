# 설치를 위해

# curl

yum -y install curl

# go

GVERSION="1.8.3"
GFILE="go$GVERSION.linux-amd64.tar.gz"

GOPATH="$HOME/projects/go"
GOROOT="/usr/local/go"

mkdir -p "$GOROOT"
chmod 777 "$GOROOT"

wget --no-verbose https://storage.googleapis.com/golang/$GFILE -O $TMPDIR/$GFILE

tar -C "/usr/local" -xzf $TMPDIR/$GFILE

cp -f "$HOME/.bashrc" "$HOME/.bashrc.bkp"

touch "$HOME/.bashrc"
{
    echo ''
    echo '# GOLANG'
    echo 'export GOROOT='$GOROOT
    echo 'export GOPATH='$GOPATH
    echo 'export GOBIN=$GOPATH/bin'
    echo 'export PATH=$PATH:$GOROOT/bin:$GOBIN'
    echo ''
} >> "$HOME/.bashrc"
source "$HOME/.bashrc"
# docker, docker compose

yum install -y yum-utils device-mapper-persistent-data lvm2
yum-config-manager --add-repo https://download.docker.com/linux/centos/docker-ce.repo
yum install -y docker-ce

# sudo apt-get update
# sudo apt-get install apt-transport-https ca-certificates curl software-properties-common
# curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
# add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu$(lsb_release -cs) stable"
# sudo apt-get update
# sudo apt-get install docker-ce

# platform binary

curl -sSL https://goo.gl/6wtTN5 | bash -s 1.1.0

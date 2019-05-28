FROM python:3.7-alpine

RUN apk add --no-cache make

RUN pip install sphinx-rtd-theme
RUN pip install sphinx-intl

RUN mkdir -p /var/sphinx
WORKDIR /var/sphinx

RUN sphinx-quickstart \
    -p \
    -a \
    -r \
    -l \
    .

RUN make html

CMD tail -f /dev/nulls
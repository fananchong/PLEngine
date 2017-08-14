FROM plengine/build-centos7

RUN yum install -y openssl-devel
RUN curl -o /Python-3.6.2.tar.xz -k -L https://www.python.org/ftp/python/3.6.2/Python-3.6.2.tgz
RUN 7za x Python-3.6.2.tar.xz -y -aos -o"." && tar -xvf Python-3.6.2.tar
RUN cd /Python-3.6.2 && ./configure && make && make install


ADD setup.sh /setup.sh

FROM plengine/build-centos7

RUN git clone https://github.com/fmtlib/fmt.git
RUN cd /fmt && git checkout -f -B release-4.0 remotes/origin/release-4.0 --
RUN cd /fmt/fmt && cmake -Wno-dev . && mv time.h time.h_ && mv string.h string.h_ && make && mv time.h_ time.h && mv string.h_ string.h
ADD setup.sh /setup.sh

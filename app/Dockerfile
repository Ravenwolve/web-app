FROM ubuntu:latest AS build

RUN apt-get update && \
  apt-get install -y build-essential g++ qt6-base-dev zlib1g-dev libssl-dev libgtest-dev cmake git libpq-dev libqt6sql6-psql

COPY . /app

WORKDIR /app/build

RUN git clone --recursive https://github.com/wfrest/wfrest && \
  cd wfrest/workflow && \
  make && \
  make install && \
  cd .. && \
  make && \
  make install && \
  cd .. && \
  git clone https://github.com/Thalhammer/jwt-cpp.git && \
  cd jwt-cpp && \
  cmake . && \ 
  cmake --build . && \
  cmake --install . && \
  cd .. && \
  cmake .. && \
  make

ENV LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib

CMD ["/app/build/src/app"]

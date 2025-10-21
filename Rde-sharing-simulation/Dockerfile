FROM ubuntu:22.04
RUN apt-get update && apt-get install -y build-essential cmake git
WORKDIR /workspace
COPY . /workspace
RUN mkdir -p build && cd build && cmake .. && cmake --build . --config Release
CMD ["/workspace/build/simuride"]

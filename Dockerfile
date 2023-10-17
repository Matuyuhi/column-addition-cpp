FROM ubuntu:latest

# 必要なパッケージのインストール
RUN apt-get update && apt-get install -y software-properties-common && \
    add-apt-repository ppa:ubuntu-toolchain-r/test && \
    apt-get update && apt-get install -y \
    g++-13 \
    cmake \
    make \
    && rm -rf /var/lib/apt/lists/*

ENV CXX=g++-13
# 作業ディレクトリの設定
WORKDIR /app
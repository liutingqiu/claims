FROM ubuntu:24.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
    gcc g++ make python3 python3-sympy python3-gmpy2 python3-pandas python3-numpy python3-networkx python3-scipy \
    && rm -rf /var/lib/apt/lists/*
RUN useradd -m -u 1500 runner
USER runner
WORKDIR /work

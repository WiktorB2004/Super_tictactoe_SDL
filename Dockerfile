# Select base image
FROM ubuntu:20.04

# Set the working directory in the container
WORKDIR /app

# Ubuntu configuration
ARG DEBIAN_FRONTEND=noninteractive

# Install build dependencies
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    libssl-dev \
    pkg-config \
    libsdl2-image-2.0 \
    libsdl2-ttf-2.0 \
    libsdl2-image-dev \
    libsdl2-ttf-dev \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Install CMake
RUN cd /tmp && \
    wget https://github.com/Kitware/CMake/releases/download/v3.28.1/cmake-3.28.1.tar.gz && \
    tar -zxvf cmake-3.28.1.tar.gz && \
    cd cmake-3.28.1 && \
    ./bootstrap && \
    make && \
    make install

# Build and install SDL
RUN cd /tmp && \
    wget https://www.libsdl.org/release/SDL2-2.29.2.tar.gz && \
    tar -zxvf SDL2-2.29.2.tar.gz && \
    cd SDL2-2.29.2 && \
    ./configure && \
    make && \
    make install


# Build and install SDL_Image
# RUN cd /tmp && \
#     wget https://github.com/libsdl-org/SDL_image/archive/refs/tags/release-2.8.2.tar.gz && \
#     tar -zxvf release-2.8.2.tar.gz && \
#     cd SDL_image-release-2.8.2 && \
#     ./configure && \
#     make && \
#     make install


# Build and install SDL_ttf
# RUN cd /tmp && \
#     wget https://github.com/libsdl-org/SDL_ttf/archive/refs/tags/release-2.22.0.tar.gz && \
#     tar -zxvf release-2.22.0.tar.gz && \
#      cd SDL_ttf-release-2.22.0 && \
#     ./configure && \
#     make && \
#     make install


# Copy files/folders needed by image
COPY CMakeLists.txt .
COPY include/ include
COPY src/ src
COPY utils/ utils
COPY resources/ resources

# Create a build directory and run CMake to configure the project
RUN rm -rf build && \
    mkdir build && \
    cd build && \
    cmake .. -DRELEASE_BUILD=1 && \
    cmake --build .

CMD ["/app/bin/supertictactoe"]
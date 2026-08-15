FROM ubuntu:24.04
# Base tools
RUN apt-get update && apt-get install -y \
    build-essential \
    clang \
    clang-tools \
    ccache \
    ninja-build \
    git \
    curl \
    zip \
    unzip \
    tar \
    pkg-config \
    autoconf \
    autoconf-archive \
    automake \
    libtool \
    && rm -rf /var/lib/apt/lists/*

# Graphics
RUN apt-get update && apt-get install -y \
    libglvnd0 \
    libgl1 \
    libglx0 \
    libegl1 \
    libgles2 \
    mesa-utils \
    mesa-utils-extra \
    x11-apps \
    && rm -rf /var/lib/apt/lists/*

# Wayland
RUN apt-get update && apt-get install -y \
    wayland-protocols \
    libwayland-client0 \
    libwayland-egl1 \
    wayland-utils \
    && rm -rf /var/lib/apt/lists/*

# X11 / GLFW dependencies
RUN apt-get update && apt-get install -y \
    libxinerama-dev \
    libxcursor-dev \
    xorg-dev \
    libglu1-mesa-dev \
    && rm -rf /var/lib/apt/lists/*

RUN curl -L \
    https://github.com/Kitware/CMake/releases/download/v4.4.2/cmake-4.4.2-linux-x86_64.sh \
    -o /tmp/cmake.sh \
    && chmod +x /tmp/cmake.sh \
    && /tmp/cmake.sh --skip-license --prefix=/usr/local \
    && rm /tmp/cmake.sh


WORKDIR /Nova

ENV NVIDIA_VISIBLE_DEVICES all
ENV NVIDIA_DRIVER_CAPABILITIES graphics,utility,compute,display

WORKDIR /Nova

RUN git config --global --add safe.directory '*'

CMD ["./Scripts/run.sh"]
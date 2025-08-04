ARG ARCH=armv7hf
ARG VERSION=1.15
ARG UBUNTU_VERSION=22.04
ARG REPO=axisecp
ARG SDK=acap-native-sdk

FROM ${REPO}/${SDK}:${VERSION}-${ARCH}-ubuntu${UBUNTU_VERSION}

WORKDIR /opt/build/libjpeg
ARG ARCH=armv7hf

WORKDIR /opt/build
RUN apt-get update && apt-get install -y \
    cmake \
    git \
    curl \
    libglib2.0-dev \
    cppcheck \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

RUN git clone --branch 2.0.6 https://github.com/libjpeg-turbo/libjpeg-turbo.git

WORKDIR /opt/build/libjpeg-turbo/build

RUN gCFLAGS=' -O2 -mthumb -mfpu=neon -mfloat-abi=hard -mcpu=cortex-a9 -fomit-frame-pointer' \
    CC=arm-linux-gnueabihf-gcc cmake -G"Unix Makefiles" .. && \
    make -j


ARG BUILD_DIR_JPEG=/opt/build/libjpeg-turbo
WORKDIR /opt/app/lib
RUN cp ${BUILD_DIR_JPEG}/build/*.so* .
WORKDIR /opt/app/include
RUN cp ${BUILD_DIR_JPEG}/build/*.h . && \
    cp ${BUILD_DIR_JPEG}/*.h .

WORKDIR /opt/app
RUN curl -L -o model.tflite \
    https://github.com/google-coral/test_data/raw/master/ssd_mobilenet_v2_coco_quant_postprocess.tflite

# Download the labels
RUN mkdir -p label && \
    curl -L -o label/labels.txt https://github.com/google-coral/test_data/raw/master/coco_labels.txt

# Setup the model directory
RUN mkdir -p model && \
    cp model.tflite model/model.tflite
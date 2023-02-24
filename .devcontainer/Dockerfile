FROM mcr.microsoft.com/devcontainers/cpp:0-ubuntu-20.04

ARG REINSTALL_CMAKE_VERSION_FROM_SOURCE="3.22.2"

ARG USERNAME=vscode
ARG USER_UID=1001
ARG USER_GID=1000

RUN usermod -a -G $USER_GID $USERNAME

COPY ./reinstall-cmake.sh /tmp/

RUN if [ "${REINSTALL_CMAKE_VERSION_FROM_SOURCE}" != "none" ]; then \
        chmod +x /tmp/reinstall-cmake.sh && /tmp/reinstall-cmake.sh ${REINSTALL_CMAKE_VERSION_FROM_SOURCE}; \
    fi \
    && rm -f /tmp/reinstall-cmake.sh

RUN sudo apt-get -y update
RUN sudo apt-get -y upgrade
RUN sudo apt-get install -y git-flow
RUN sudo apt-get install -y libmysqlcppconn-dev
# Check if needed
# RUN sudo apt-get install -y mysql-server

USER $USERNAME

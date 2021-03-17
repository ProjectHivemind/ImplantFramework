FROM gcc:latest

RUN apt-get update; update-alternatives --install /usr/bin/gfortran gfortran /usr/local/bin/gfortran 999

RUN apt-get install -y \
      ssh \
      gdb \
      clang \
      cmake \
      rsync \
      tar \
      python3-pip \
      doxygen \
      libboost-all-dev \
  && apt-get clean

RUN url="$(curl -s https://api.github.com/repos/matusnovak/doxybook2/releases/latest \
        | grep browser_download_url \
        | grep linux \
        | cut -d '"' -f 4)"; \
    filename=${url##*/}; \
    wget $url; \
    unzip $filename -d doxybook2

RUN mv /doxybook2/bin/doxybook2 /usr/bin/; chmod +x /usr/bin/doxybook2

RUN python3 -m pip install --upgrade pip

RUN pip install mkdocs-material mkdocs-monorepo-plugin

RUN ( \
    echo 'LogLevel DEBUG2'; \
    echo 'PermitRootLogin yes'; \
    echo 'PasswordAuthentication yes'; \
    echo 'Subsystem sftp /usr/lib/openssh/sftp-server'; \
  ) > /etc/ssh/sshd_config_test_clion \
  && mkdir /run/sshd

RUN useradd -m user \
  && yes password | passwd user

CMD ["/usr/sbin/sshd", "-D", "-e", "-f", "/etc/ssh/sshd_config_test_clion"]
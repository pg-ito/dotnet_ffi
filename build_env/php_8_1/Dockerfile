FROM centos:7



# WORKDIR  /src
# RUN curl -L -O https://github.com/pg-ito/dotnet_ffi/archive/v0.3.0.tar.gz

# RUN tar xvf v0.3.0.tar.gz 
# RUN mv -i /src/dotnet_ffi-0.3.0 dotnet_ffi
# WORKDIR /src/dotnet_ffi
# RUN ls -al
# RUN ./br.sh



RUN yum install -y centos-release-scl epel-release
RUN yum install -y http://rpms.famillecollet.com/enterprise/remi-release-7.rpm

RUN yum groupinstall -y "Development Tools"
RUN yum install -y kernel-devel kernel-headers
RUN yum install -y devtoolset-7-gcc devtoolset-7-gcc-c++
# RUN echo 'scl enable devtoolset-7 bash' >> ~/.bashrc
RUN yum install -y --enablerepo=epel,remi,remi-php81  php php-devel php-mbstring php-pdo php-gd php-xml php-mcrypt php-fpm
RUN mkdir /run/php-fpm
# RUN sed -i -e 's/daemonize = yes/daemonize = no/' /etc/php-fpm.conf
# RUN echo "[www]" >> /etc/php-fpm.conf
# RUN echo 'listen.owner = 777' >> /etc/php-fpm.conf
# RUN echo "listen = 0.0.0.0:9000" >> /etc/php-fpm.conf
# RUN systemctl enable php-fpm

# COPY php-fpm.conf /etc/php-fpm.conf
# COPY php-fpm.d/ /etc/php-fpm.d/
# STOPSIGNAL SIGQUIT
# COPY ./www.conf /etc/php-fpm.d/www.conf

RUN rpm -Uvh https://packages.microsoft.com/config/centos/7/packages-microsoft-prod.rpm
RUN yum install -y dotnet-sdk-6.0
RUN echo 'scl enable devtoolset-7 bash;cd /src/dotnet_ffi && ./br.sh' > /var/tmp/builder.sh
RUN chmod a+x /var/tmp/builder.sh



ENTRYPOINT ["php-fpm", "-F"]
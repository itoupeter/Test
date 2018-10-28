Get-Process
Get-Process | Where-Object {$_.PriorityClass -eq "Normal"} > out.txt
Get-Process | Where-Object {$_.Responding -eq "True"} | Out-File out.txt

Get-Service | Where-Object {$_.Status -eq "Stopped"} | Out-File out.txt

Get-PSDrive > .\out.txt

dir cert: > out.txt

Get-WindowsFeatures hyper-V|ft InstallState , PostConfigurationNeeded

# docker 

docker info # version

docker image ls # all images downloaded
docker image rm 5a3557f099ee # remove images

docker container ls -a # list all containers | -q quite | docker ps
docker container ls # list running containers

docker run -e 'ACCEPT_EULA=Y' -e 'SA_PASSWORD=ABCabc123' -p 1433:1433 -d --name sqlserver microsoft/mssql-server-linux:2017-latest # run microsoft sql server

docker container stop sqlserver # stop sqlserver

docker container rm adfbbf32076c # remove container
docker rm $(docker ps -aq) # remove stopped containers

docker exec -it sqlserver /opt/mssql-tools/bin/sqlcmd -S localhost -U sa -P 'ABCabc123' # connect to sql server with interative mode

docker run --help

# create container

docker run -dP --name phpserver webdevops/php-nginx # run nginx php server container
docker exec -it phpserver /bin/bash # "log into" the container
vi /app/index.php # create a php file
curl https://codeload.github.com/simplepie/simplepie/zip/1.4.3 > simplepie1.4.3.zip # download simplepie
unzip simplepie1.4.3.zip
mkdir /app/php
mkdir /app/cache
mkdir /app/php/library
cp -r s*/library/* /app/php/library/.
cp -r s*/autoloader.php /app/php/.
chmod 777 /app/cache
vi /app/rss.php
docker commit -m "added res" -a "Liang Peng" phpserver itoupeter/rss-php-nginx:v1
docker push itoupeter/rss-php-nginx:v1

docker cp sad_lamport:/opt/ /etc/nginx/vhost.conf . # copy vhost.conf to local
docker build -t itoupeter/rss-php-nginx:v2 .
docker run -dP itoupeter/rss-php-nginx:v2

# run Ubuntu

docker run -it --name ubuntu --rm ubuntu
apt-get update
apt-get install build-essential # [-y] yes to all
apt-get install cmake

# basic cmake

cmake_minimum_required (VERSION 2.6)
project (Demo)
# The version number
set (Demo_VERSION_MAJOR 1)
set (Demo_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
    "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
    "${PROJECT_BINARY_DIR}/TutorialConfig.h"
)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

# add the executable
add_executable(Demo demo.cpp)

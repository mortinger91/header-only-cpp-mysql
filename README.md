# easy-cpp-mysql
Very easy HEADER-ONLY C++ Mysql Wrapper

Only .h file, just paste it into your project

Following, a few more informations:
* build instructions
* how to find and install dependencies
* example function
* example cpp file

The official mysql C library is required and is the only dependency

on Debian-like distributions issue the command "sudo apt install libmysqlclient-dev"

try with "sudo apt install default-libmysqlclient-dev" as an alternative.


Look for an equivalent one if you are on a different OS or Linux distribution

using GCC build with lmysqlclient flag (tested on Debian buster/sid & GCC 8.2.0-13)

example: "g++ program main.o *...* -lmysqlclient".


If you cannot locate the package you are probably missing the mysql repositories

go to "https://repo.mysql.com/" and download the file

"mysql-apt-config_*LATEST_VERSION_NUMBER*_all.deb".


You can download it using "curl *DOWNLOAD LINK* --output pkg.deb" or via browser

install it using "dpkg -i pkg.deb" and choose your system version or the latest one

after having added mysql repos you should be able to "sudo apt install libmysqlclient-dev"








**EXAMPLE**

A very simple example.cpp file, that's everything you need to test the functions

compile it with "g++ example example.cpp -lmysqlclient"

example.cpp:

	#include "mysql_wrapper.h"
	example("my_hostname", "my_user", "my_password", 
		"SELECT * FROM myschema.mydatabase", 
		"INSERT INTO myschema.mydatabase (col1,col2,col3) VALUES (1,2,3)");

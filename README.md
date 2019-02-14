# header-only-cpp-mysql
HEADER-ONLY easy C++ Mysql Wrapper

Only .h file, just paste it into your project

Following, a few more informations:
* build instructions
* how to find and install dependencies
* example function
* example cpp file

The official mysql C library is required and is the only dependency.

On Debian-like distributions issue the command "*sudo apt install libmysqlclient-dev*".

Try with "*sudo apt install default-libmysqlclient-dev*" as an alternative.

Look for an equivalent one if you are on a different OS or Linux distribution.

Using GCC build with **lmysqlclient** flag (tested on Debian buster/sid & GCC 8.2.0-13).

Example: "*g++ program main.o ... -lmysqlclient*".

If you cannot locate the package you are probably missing the mysql repositories.

Go to "*https://repo.mysql.com/*" and download the file "*mysql-apt-config_LATEST_VERSION_NUMBER_all.deb*".

You can download it using "*curl DOWNLOAD LINK --output pkg.deb*" or via browser.

Install it using "*sudo dpkg -i pkg.deb*" and choose your system version or the latest one.

After having added mysql repos you should be able to "*sudo apt install libmysqlclient-dev*".

**EXAMPLE:**

A very simple example.cpp file, that's everything you need to test the functions.

Compile it with "*g++ example example.cpp -lmysqlclient*"
Execute it with "*./example*"

*example.cpp:*

	#include "mysql_wrapper.h"
	example("my_hostname", "my_user", "my_password", 
		"SELECT * FROM myschema.mydatabase", 
		"INSERT INTO myschema.mydatabase (col1,col2,col3) VALUES (1,2,3)");
		
	int main(int argc, char *argv[])
	{
		example("my_hostname", "my_user", "my_password", 
		"SELECT * FROM myschema.mydatabase", 
		"INSERT INTO myschema.mydatabase (col1,col2,col3) VALUES (1,2,3)");
		return 0;
	}

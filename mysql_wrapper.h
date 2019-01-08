#ifndef MYSQL_H
#define MYSQL_H

#include <string>
#include <stdio.h>
#include <iostream>
#include <mysql/mysql.h>

// pointer to connection handler
// single handler managed by the library, create more or make "mysql_connect" return MYSQL*
// instead of boolean if you need multiple connections at one time
MYSQL *conn;

// connect to the endpoint
bool mysql_connect(const char *host_name, const char *user_name, const char *password)
{
    conn = mysql_init (NULL);     // allocate, initialize connection handler
    if (conn == NULL)
    {
        fprintf (stderr, "mysql_init() failed\n");
        return false;
    }
    // schema's name, connection port, unix_socket and flags are hard-coded for simplicity
    // modify these values or make them variables if you need more control
    // you can always specify the schema's name in the queries so that's not necessary
    if (mysql_real_connect (conn, host_name, user_name, password, 
        NULL, 3306, NULL, 0) == NULL)
    {
        fprintf (stderr, "mysql_real_connect() failed:\nError %u (%s)\n", 
                mysql_errno (conn), mysql_error (conn));
        return false;
    }
    return true;     // connection is established
}

// close connection to the server
void mysql_disconnect()
{
	mysql_close (conn);
}

// print in the stdout the result of a SELECT query and the number
// of rows returned, 0 if none
// modify the code inside the while for custom behaviour
bool mysql_print_select(std::string selectQuery_string)
{
	const char* selectQuery = &selectQuery_string[0];
	if (mysql_query (conn, selectQuery) != 0)
	{
		std::cout << "SELECT query failed" << std::endl;
		return false;
	}

	// generate the result set
	MYSQL_RES *res_set;
	res_set = mysql_store_result (conn);      
	if (res_set == NULL)
	{
		std::cout << "mysql_store_result() failed" << std::endl;
		return false;
	}

	// processing for each row
	MYSQL_ROW row;
	while ((row = mysql_fetch_row (res_set)) != NULL)
	{
		for (unsigned int i = 0; i < mysql_num_fields (res_set); i++)
		{
			if (i > 0)
			fputc ('\t', stdout);
			printf ("%s", row[i] != NULL ? row[i] : "NULL");
		}
		fputc ('\n', stdout);
	}

	// error checking
	if (mysql_errno (conn) != 0)
	{
		std::cout << "mysql_fetch_row() failed" << std::endl;
	}
	else
	{
		std::cout << (unsigned long) mysql_num_rows (res_set) 
			<< " rows returned" << std::endl;
	}

	// freeing the memory allocated for the result set
	mysql_free_result (res_set);

	return true;
}

// function for a INSERT query
bool mysql_insert(std::string insertQuery_string)
{
	const char* insertQuery = &insertQuery_string[0];
	if (mysql_query (conn, insertQuery) != 0)
	{
      std::cout << "INSERT statement failed" << std::endl;
      return false;
	}
	std::cout << "INSERT statement succeeded: " << (unsigned long) mysql_affected_rows (conn) 
		<< " rows affected" << std::endl;
	return true;
}

// example function which connects and perform a select and an insert query
void example(const char *host_name, const char *user_name, const char *password, std::string selectQuery, std::string insertQuery)
{
	if (!mysql_connect(host_name, user_name, password))
	{
		std::cout << "error on connect" << std::endl;
		return;
	}
	if (!mysql_print_select(selectQuery))
	{
		std::cout << "error on select" << std::endl;
		return;
	}
	if (!mysql_insert(insertQuery))
	{
		std::cout << "error on insert" << std::endl;
		return;
	}
	std::cout << "all operations completed" << std::endl;
	return;
}

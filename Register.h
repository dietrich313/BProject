#pragma once
#include "stdafx.h"
#include "jdbc/mysql_connection.h"
#include "jdbc/mysql_driver.h"
#include "jdbc/cppconn/statement.h"
#include "jdbc/cppconn/sqlstring.h"
#include "jdbc/cppconn/resultset.h"
#ifndef Register_H
#define Register_H


#include <string>
class User {

	std::string username;
	std::string password;
	std::string email;
	std::string fname;
	std::string lname;
public:
	User();
	User(std::string username,
		std::string password,
		std::string email,
		std::string fname,
		std::string lname);
	bool Register(std::string username1,
		std::string password1,
		std::string email1,
		std::string fname1,
		std::string lname1,
		HWND hDlg);
	bool Login(std::string username1, std::string password1,HWND hDlg);
};
#endif // !Register
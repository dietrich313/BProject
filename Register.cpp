#include "stdafx.h"
#include "jdbc/mysql_connection.h"
#include "jdbc/mysql_driver.h"
#include "jdbc/cppconn/statement.h"
#include "jdbc/cppconn/sqlstring.h"
#include "jdbc/cppconn/resultset.h"
#include "jdbc/mysql_error.h"
#include "Register.h"
#include <string>
#include <sstream>



	User::User() {};
	User::User(std::string username,
		std::string password,
		std::string email,
		std::string fname,
		std::string lname) : username(username),
		password(password), email(email),
		fname(fname), lname(lname) {};

	// Register Function 
	bool User::Register(std::string username1,
		std::string password1,
		std::string email1,
		std::string fname1,
		std::string lname1, 
		HWND hDlg)
	{ try {
		sql::mysql::MySQL_Driver *driver;
		sql::Connection *con;
		sql::Statement *stmt;
		sql::ResultSet *res;
		driver = sql::mysql::get_mysql_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "");
		con->setSchema("test");
		stmt = con->createStatement();
		//select all where username or email matches
		std::stringstream query;
		query << "SELECT * FROM user where username=\'" << username1.c_str() << "\'" << "\n" << "OR email=\'" << email1.c_str() << "\'";
		std::string ssa = query.str();
		res = stmt->executeQuery(sql::SQLString(ssa.c_str()));
		
		if (!res->next())
		{
			delete stmt;
			stmt = con->createStatement();
			std::stringstream query2;
			query2 << "INSERT INTO user (Username, Password,email,FirstName, LastName) VALUES ('";
			query2 << username1.c_str() << "'" << "," << "'"<< password1.c_str() << "'" << "," << "'";
			query2 << email1.c_str() << "'" << "," << "'"<< fname1.c_str() << "'" << "," << "'";
			query2 << lname1.c_str() << "'" << ");";
			ssa = query2.str();
			stmt->execute(sql::SQLString(ssa.c_str()));
				
				
			delete res;
			delete stmt;
			delete con;
			std::stringstream msg;
			msg << "User Created " << username1.c_str() << " Created";
			MessageBox(hDlg,
				LPCSTR(msg.str().c_str()),
				LPCSTR("Success"),
				MB_OK);
			return true;

		}

		else
		{
			delete stmt;
			stmt = con->createStatement();
			delete res;
			std::stringstream query2;
			query2 << "SELECT email FROM user where email='" << email1.c_str() << "'";
			std::stringstream msg;
			res = stmt->executeQuery(sql::SQLString(query2.str().c_str()));
			 if (res->next())
			{
				msg << "Email " << email1.c_str() << " Already Registered";
				MessageBox(hDlg,
					LPCSTR(msg.str().c_str()),
					NULL,
					MB_OK);
			}

			else {
				msg << "Username " << username1.c_str() << " Already In Use";
				MessageBox(hDlg,
					LPCSTR(msg.str().c_str()),
					NULL,
					MB_OK);
			}
			}

			delete res;
			delete stmt;
			delete con;
			return false;

		

		}

	catch (sql::SQLException &e)
	{
		std::stringstream s;
		s << "# ERR: SQLException in " << __FILE__;
		s << "(" << __FUNCTION__ << ") on line "<< __LINE__ << std::endl;
		s << "# ERR: " << e.what();
		s << " (MySQL error code: " << e.getErrorCode();
		s << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		std::string f = s.str();
		MessageBox(hDlg,
			LPCSTR(f.c_str()),
			NULL,
			MB_OK);
	}
	}


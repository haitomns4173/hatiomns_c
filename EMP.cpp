// Note in the search function we can make the program more effective by using the SQL query part as another function;

#include <iostream>
#include <winsock.h>
#include <mysql.h>
#include <conio.h>
#include <direct.h>
#include <windows.h>
#include <sstream>

using namespace std;

// Deceleration of Global Variables
MYSQL* connection;
short int login_fail = 1;
int menu_select;
char retry_key;

// Use to set the Pointer
void setPointer(short int xpnt, short int ypnt)
{
	COORD position = { xpnt, ypnt };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

// Use to print TopPart
void top_printing()
{
	system("CLS");
	setPointer(60, 12);
	cout << "EMPLOYEE MANAGEMENT SYSTEM" << endl;
}

// Use to open the program in FullScreen
void fullscreen()
{
	keybd_event(VK_MENU, 0x38, 0, 0); //Press down Alt
	keybd_event(VK_RETURN, 0x1c, 0, 0); //Press down Enter

	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0); //Release Alternate
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);//Release Enter
}

// Class for handling the Database
class Mysql
{
public:

    MYSQL_ROW row;
    MYSQL_RES* res;
    int number_of_rows=0;

    // Making the connection
    int mysql_connection()
    {
        connection = mysql_init(0);
        connection = mysql_real_connect(connection, "localhost", "root", "", "cpp_test", 3306 , NULL, 0);
        if (connection)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }

    }

    // Query Executor for Insertion
    int query_executor(const char* final_query)
    {
        int query_state = 0;
        query_state = mysql_query(connection, final_query);

        if(query_state == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    int query_select(const char* final_query)
    {
        if(connection)
        {
            int qstate = mysql_query(connection, final_query);

            if(!qstate)
            {
                res = mysql_store_result(connection);
                row = mysql_fetch_row(res);
                number_of_rows = mysql_num_rows(res);
            }
        }
        return number_of_rows;
    }
};

class Admin
{
    Mysql adminMain;

public:
    void admin_panel()
    {
	re_try_admin:

		top_printing();
		setPointer(60, 17);
		cout << "Admin Panel";
		setPointer(60, 19);
		cout << "1. Search Employee";
		setPointer(60, 21);
		cout << "2. Register Employee";
		setPointer(60, 23);
		cout << "3. Update Employee";
		setPointer(60, 25);
		cout << "4. Delete Employee";
		setPointer(60, 27);
		cout << "5. Employee Salary";
		setPointer(60, 29);
		cout << "6. View Salary";
		setPointer(60, 31);
		cout << "7. Work Assignment";
		setPointer(60, 33);
		cout << "8. Advance Salary";
        setPointer(60, 35);
		cout << "9. Username/Password Change";
        setPointer(60, 37);
		cout << "10. Notice";
		setPointer(60, 39);
		cout << "Press the number .... ";
		cin >> menu_select;
		fflush(stdin);
		switch (menu_select)
		{
		case 1:
		    employee_searching();
			break;
		case 2:
		    employee_registration();
			break;
		case 3:
		    employee_update();
			break;
		case 4:
		    employee_delete();
			break;
		case 5:
		    employee_salary();
			break;
		case 6:
		    view_salary();
			break;
        case 7:
            work_assignment();
			break;
        case 8:
            advance_salary();
			break;
        case 9:
            username_password_change();
			break;
        case 10:
            notice();
			break;
		default:
			setPointer(60, 42);
			cout << "Wrong Input!";
			setPointer(60, 44);
			cout << "Hit Enter to re-enter and Esc to exit ....";
			retry_key = _getch();

			if (retry_key == 27)
			{
				exit(0);
			}
			else
			{
				goto  re_try_admin;
			}
		}
    }

    void employee_searching()
    {
        int search_id = 0, search_post = 0, rows_in_employee = 0, table_y = 22;
        string search_name;

        top_printing();
		setPointer(60, 17);
		cout << "Search Method";
		setPointer(60, 19);
		cout << "1. By Employee ID";
		setPointer(60, 21);
		cout << "2. By Name";
		setPointer(60, 23);
		cout << "3. By Post";
		setPointer(60, 26);
        cout << "Press the number .... ";
		cin >> menu_select;
		fflush(stdin);
		if(menu_select == 1)
        {
            setPointer(60, 29);
            cout << "Employee ID : ";
            cin >> search_id;


            stringstream query_holder;
            query_holder << "select * from employee where id = "<<search_id<<"";
            string temp_query = query_holder.str();
            const char* final_query = temp_query.c_str();

            rows_in_employee = adminMain.query_select(final_query);

            if(rows_in_employee==0)
            {
                setPointer(60, 32);
                cout << "No Record Found";
            }
            else
            {
                top_printing();
                setPointer(60, 17);
                cout << "Query Result";
                setPointer(60, 20);
                cout << "ID   |Name\t\t|Age\t|Post Code\t|Phone";
                setPointer(60, 21);
                cout << "--------------------------------------------------";
                while(adminMain.row = mysql_fetch_row(adminMain.res))
                {
                    setPointer(60,table_y++);
                    cout << adminMain.row[0] << "    |" << adminMain.row[1] << "\t|" << adminMain.row[2] << "\t|" << adminMain.row[3] << "\t\t|" << adminMain.row[4] << "\n";
                }
            }
        }
        else if (menu_select == 2)
        {
            setPointer(60, 29);
            cout << "Employee Name : ";
            cin >> search_name;


            stringstream query_holder;
            query_holder << "select * from employee where name = '"<<search_name<<"'";
            string temp_query = query_holder.str();
            const char* final_query = temp_query.c_str();

            rows_in_employee = adminMain.query_select(final_query);

            if(rows_in_employee==0)
            {
                setPointer(60, 32);
                cout << "No Record Found";
            }
            else
            {
                top_printing();
                setPointer(60, 17);
                cout << "Query Result";
                setPointer(60, 20);
                cout << "ID   |Name\t\t|Age\t|Post Code\t|Phone";
                setPointer(60, 21);
                cout << "--------------------------------------------------";
                while(adminMain.row = mysql_fetch_row(adminMain.res))
                {
                    setPointer(60,table_y++);
                    cout << adminMain.row[0] << "    |" << adminMain.row[1] << "\t|" << adminMain.row[2] << "\t|" << adminMain.row[3] << "\t\t|" << adminMain.row[4] << "\n";
                }
            }
        }
        else
        {
            setPointer(60, 29);
            cout << "Employee Post : ";
            cin >> search_post;


            stringstream query_holder;
            query_holder << "select * from employee where post_code = "<<search_post<<"";
            string temp_query = query_holder.str();
            const char* final_query = temp_query.c_str();

            rows_in_employee = adminMain.query_select(final_query);

            if(rows_in_employee==0)
            {
                setPointer(60, 32);
                cout << "No Record Found";
            }
            else
            {
                top_printing();
                setPointer(60, 17);
                cout << "Query Result";
                setPointer(60, 20);
                cout << "ID   |Name\t\t|Age\t|Post Code\t|Phone";
                setPointer(60, 21);
                cout << "--------------------------------------------------";
                while(adminMain.row = mysql_fetch_row(adminMain.res))
                {
                    setPointer(60,table_y++);
                    cout << adminMain.row[0] << "    |" << adminMain.row[1] << "\t|" << adminMain.row[2] << "\t|" << adminMain.row[3] << "\t\t|" << adminMain.row[4] << "\n";
                }
            }
        }
    }

    void employee_registration()
    {
    retry_registeration:
        string emp_name, phone, username_in, password_in;
        int age = 0, post_code = 0, rows_in_userpass = 0;

        top_printing();
		setPointer(60, 17);
		cout << "Registration";
		setPointer(60, 18);
		cout << "Fill in the Details :";

		setPointer(60, 22);
		cout << "Employee Name :";
		setPointer(60, 24);
		cout << "Age           :";
		setPointer(60, 26);
		cout << "Post          :";
		setPointer(60, 28);
		cout << "Phone         :";

		setPointer(76, 22);
		fflush(stdin);
		getline(cin, emp_name);

		setPointer(76, 24);
		fflush(stdin);
		cin >> age;
		if(age<18 || age >88)
        {
            setPointer(60, 31);
            cout << "Wrong AGE!";
			setPointer(60, 44);
			cout << "Hit Enter to re-enter and Esc to exit ....";
			retry_key = _getch();

			if (retry_key == 27)
			{
				exit(0);
			}
			else
			{
				goto  retry_registeration;
			};
        }
		setPointer(76, 26);
		fflush(stdin);
		cin >> post_code;
		if(post_code != 1 && post_code != 2)
        {
            setPointer(60, 31);
            cout << "Wrong Input!";
			setPointer(60, 44);
			cout << "Hit Enter to re-enter and Esc to exit ....";
			retry_key = _getch();

			if (retry_key == 27)
			{
				exit(0);
			}
			else
			{
				goto  retry_registeration;
			}
        }
		setPointer(76, 28);
		fflush(stdin);
		getline(cin,phone);
		if(phone.size()<10)
        {
            setPointer(60, 31);
            cout << "Wrong Phone!";
			setPointer(60, 44);
			cout << "Hit Enter to re-enter and Esc to exit ....";
			retry_key = _getch();

			if (retry_key == 27)
			{
				exit(0);
			}
			else
			{
				goto  retry_registeration;
			}
        }
retry_credentials:
		setPointer(60, 31);
		cout << "Login Credentials :";

		setPointer(60, 33);
		cout << "USERNAME      : ";
		setPointer(60, 35);
		cout << "PASSWORD      : ";

		setPointer(76, 33);
        cin >> username_in;

        stringstream query_holder;
        query_holder << "select * from userpass where username = '"<<username_in<<"'";
        string temp_query = query_holder.str();
        const char* final_query = temp_query.c_str();

        rows_in_userpass = adminMain.query_select(final_query);

        if(rows_in_userpass!=0)
        {
            setPointer(60, 37);
            cout << "Username is Already Taken! Retry";
            _getch();
            setPointer(86, 33);
            cout <<"\b\b\b\b\b\b\b\b\b\b          ";
            setPointer(92, 37);
            cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b                                ";
            goto retry_credentials;
        }

        setPointer(76, 35);
        cin >> password_in;

        stringstream query_holder2;
        query_holder2 << "INSERT INTO `employee`(`id`, `name`, `age`, `post_code`, `phone`) VALUES (NULL,'"<<emp_name<<"', '"<<age<<"', '"<<post_code<<"', '"<<phone<<"')";
        string temp_query2 = query_holder2.str();
        const char* final_query2 = temp_query2.c_str();

        adminMain.query_executor(final_query2);

        stringstream query_holder3;
        query_holder3 << "INSERT INTO `userpass` (`id`, `username`, `password`, `post_code`) VALUES (NULL,'"<<username_in<<"', '"<<password_in<<"','"<<post_code<<"')";
        string temp_query3 = query_holder3.str();
        const char* final_query3 = temp_query3.c_str();

        int insert_result;
        insert_result = adminMain.query_executor(final_query3);
        if(insert_result  == 1)
        {
            setPointer(60, 38);
            cout << "Recorded!!";
            setPointer(60, 39);
            cout << "Hit Enter to continue....";
            _getch();

            stringstream query_holder4;
            query_holder4 << "SELECT * FROM `employee` WHERE `name` LIKE '"<<emp_name<<"'";
            string temp_query4 = query_holder4.str();
            const char* final_query4 = temp_query4.c_str();

            adminMain.query_select(final_query4);

            top_printing();
            setPointer(60, 17);
            cout << "Registration";
            setPointer(60, 19);
            cout << "Employee Details Successfully Inserted.";
            setPointer(60, 21);
            cout << "Employee ID : " << adminMain.row[0];
            setPointer(60, 24);
            cout << "Hit Enter to continue....";
            _getch();
        }
        else
        {
            setPointer(60, 37);
            cout << "Insert Failed!";
            _getch();
        }
    }

    void employee_update()
    {
        string emp_name, phone;
        int employee_id = 0, rows_in_employee, age = 0, post_code = 0, update_result = 0;

    retry_update:

        top_printing();
		setPointer(60, 17);
		cout << "Employee Update";
		setPointer(60, 20);
		cout << "Employee ID :";
		setPointer(74, 20);
		cin >> employee_id;

		stringstream query_holder;
        query_holder << "select * from employee where id = "<<employee_id<<"";
        string temp_query = query_holder.str();
        const char* final_query = temp_query.c_str();

        rows_in_employee = adminMain.query_select(final_query);

        if(rows_in_employee==0)
        {
            setPointer(60, 32);
            cout << "No Record Found";
            setPointer(60, 33);
            cout << "Hit Enter to re-enter and Esc to exit ....";
			retry_key = _getch();

			if (retry_key == 27)
			{
				exit(0);
			}
			else
			{
				goto  retry_update;
			}
        }
        else
        {
            setPointer(60, 32);
            cout << "Record Found";
            setPointer(60, 33);
            cout << "Hit Enter to continue....";
            _getch();

            top_printing();
            setPointer(60, 17);
            cout << "Registration";
            setPointer(60, 18);
            cout << "Fill in the Details :";

            setPointer(60, 22);
            cout << "Employee Name :";
            setPointer(60, 24);
            cout << "Age           :";
            setPointer(60, 26);
            cout << "Post          :";
            setPointer(60, 28);
            cout << "Phone         :";

            setPointer(76, 22);
            fflush(stdin);
            getline(cin, emp_name);

            setPointer(76, 24);
            fflush(stdin);
            cin >> age;
            if(age<18 || age >88)
            {
                setPointer(60, 31);
                cout << "Wrong AGE!";
                setPointer(60, 44);
                cout << "Hit Enter to re-enter and Esc to exit ....";
                retry_key = _getch();

                if (retry_key == 27)
                {
                    exit(0);
                }
                else
                {
                    goto  retry_update;
                };
            }
            setPointer(76, 26);
            fflush(stdin);
            cin >> post_code;
            if(post_code != 1 && post_code != 2)
            {
                setPointer(60, 31);
                cout << "Wrong Input!";
                setPointer(60, 44);
                cout << "Hit Enter to re-enter and Esc to exit ....";
                retry_key = _getch();

                if (retry_key == 27)
                {
                    exit(0);
                }
                else
                {
                    goto  retry_update;
                }
            }
            setPointer(76, 28);
            fflush(stdin);
            getline(cin,phone);
            if(phone.size()<10)
            {
                setPointer(60, 31);
                cout << "Wrong Phone!";
                setPointer(60, 44);
                cout << "Hit Enter to re-enter and Esc to exit ....";
                retry_key = _getch();

                if (retry_key == 27)
                {
                    exit(0);
                }
                else
                {
                    goto  retry_update;
                }
            }

            stringstream query_holder2;
            query_holder2 << "UPDATE `employee` SET `name`='"<<emp_name<<"',`age`='"<<age<<"',`post_code`='"<<post_code<<"',`phone`='"<<phone<<"' WHERE id = "<<employee_id<<"";
            string temp_query2 = query_holder2.str();
            const char* final_query2 = temp_query2.c_str();

            update_result = adminMain.query_executor(final_query2);

            if(update_result == 1)
            {
                setPointer(60, 38);
                cout << "Recorded Updated!!";
                setPointer(60, 39);
                cout << "Hit Enter to continue....";
                _getch();
            }
            else
            {
                setPointer(60, 37);
                cout << "Update Failed!";
                setPointer(60, 44);
                cout << "Hit Enter to re-enter and Esc to exit ....";
                retry_key = _getch();

                if (retry_key == 27)
                {
                    exit(0);
                }
                else
                {
                    goto retry_update;
                }
            }
        }
    }

    void employee_delete()
    {
        int employee_id = 0, delete_emp = 0, delete_emp2 = 0;
        top_printing();

		setPointer(60, 17);
		cout << "Employee Delete";
		setPointer(60, 20);
		cout << "Employee ID :";
		setPointer(74, 20);
		cin >> employee_id;

		stringstream query_holder;
        query_holder << "DELETE FROM `employee` WHERE id = "<<employee_id<<"";
        string temp_query = query_holder.str();
        const char* final_query = temp_query.c_str();

        delete_emp = adminMain.query_executor(final_query);

        stringstream query_holder2;
        query_holder2 << "DELETE FROM `userpass` WHERE id = "<<employee_id<<"";
        string temp_query2 = query_holder2.str();
        const char* final_query2 = temp_query2.c_str();

        delete_emp2 = adminMain.query_executor(final_query2);

        if(delete_emp == 1 && delete_emp2 == 1)
        {
            setPointer(60, 23);
            cout << "Deleted!!";
        }
        else
        {
            setPointer(60, 23);
            cout << "Deletation Failed!!";
        }
    }

    void work_assignment()
    {
        string work, employee_name;
        int employee_name_search = 0, work_assign_result = 0;

    retry_work_assignment:
        top_printing();

		setPointer(60, 17);
		cout << "Work Assignment";
		setPointer(60, 18);
		cout << "Fill in the Details :";

		setPointer(60, 22);
		cout << "Work Name     :";
		setPointer(60, 24);
		cout << "Employee Name :";
		setPointer(76, 22);
		fflush(stdin);
		getline(cin, work);
		setPointer(76, 24);
		fflush(stdin);
		getline(cin, employee_name);

		stringstream query_holder;
        query_holder << "SELECT * FROM `employee` WHERE `name` LIKE '"<<employee_name<<"'";
        string temp_query = query_holder.str();
        const char* final_query = temp_query.c_str();

        employee_name_search = adminMain.query_select(final_query);

        if(employee_name_search == 0)
        {
            setPointer(60, 32);
            cout << "There is no Employee named " << employee_name;
            setPointer(60, 44);
			cout << "Hit Enter to re-enter and Esc to exit ....";
			retry_key = _getch();

			if (retry_key == 27)
			{
				exit(0);
			}
			else
			{
				goto  retry_work_assignment;
			}
        }
        else
        {
            stringstream query_holder2;
            query_holder2 << "INSERT INTO `work`(`id`, `work_name`, `work_by`, `work_to`) VALUES ('NULL','"<<work<<"','Admin','"<<employee_name<<"')";
            string temp_query2 = query_holder2.str();
            const char* final_query2 = temp_query2.c_str();

            work_assign_result = adminMain.query_executor(final_query2);

            if(work_assign_result == 1)
            {
                setPointer(60, 32);
                cout << "Work Assisgned!!";
            }
            else
            {
                setPointer(60, 32);
                cout << "Work Not Assisgned!!";
                setPointer(60, 44);
                cout << "Hit Enter to re-enter and Esc to exit ....";
                retry_key = _getch();

                if (retry_key == 27)
                {
                    exit(0);
                }
                else
                {
                    goto  retry_work_assignment;
                }
            }
        }
    }

    void advance_salary()
    {
        float advance_salary_amount;
        string employee_name, temp_employee_id;
        int employee_name_search = 0, advance_salary_result = 0;

    retry_advance_salary:
        top_printing();

		setPointer(60, 17);
		cout << "Advance Salary";
		setPointer(60, 18);
		cout << "Fill in the Details :";

		setPointer(60, 22);
		cout << "Employee Name  :";
		setPointer(60, 24);
		cout << "Total Amount   :";
		setPointer(77, 22);
		fflush(stdin);
		getline(cin, employee_name);
		setPointer(77, 24);
		fflush(stdin);
		cin >> advance_salary_amount;

		stringstream query_holder;
        query_holder << "SELECT * FROM `employee` WHERE `name` LIKE '"<<employee_name<<"'";
        string temp_query = query_holder.str();
        const char* final_query = temp_query.c_str();

        employee_name_search = adminMain.query_select(final_query);
        temp_employee_id = adminMain.row[0];

        if(employee_name_search == 0)
        {
            setPointer(60, 32);
            cout << "There is no Employee named " << employee_name;
            setPointer(60, 44);
			cout << "Hit Enter to re-enter and Esc to exit ....";
			retry_key = _getch();

			if (retry_key == 27)
			{
				exit(0);
			}
			else
			{
				goto  retry_advance_salary;
			}
        }
        else
        {
            stringstream query_holder2;
            query_holder2 << "INSERT INTO `advance_salary`(`id`, `amount`, `employee_id`) VALUES ('NULL','"<<advance_salary_amount<<"','"<<temp_employee_id<<"')";
            string temp_query2 = query_holder2.str();
            const char* final_query2 = temp_query2.c_str();

            advance_salary_result = adminMain.query_executor(final_query2);

            if(advance_salary_result == 1)
            {
                setPointer(60, 32);
                cout << "Advance Salary Recorded!!";
            }
            else
            {
                setPointer(60, 32);
                cout << "Advance Salary NOT Recorded!!";
                setPointer(60, 44);
                cout << "Hit Enter to re-enter and Esc to exit ....";
                retry_key = _getch();

                if (retry_key == 27)
                {
                    exit(0);
                }
                else
                {
                    goto retry_advance_salary;
                }
            }
        }
    }

    void notice()
    {
        string notice_title, notice_body, notice_by;
        int notice_result = 0;
    retry_notice:
        top_printing();

		setPointer(60, 17);
		cout << "Notice";
		setPointer(60, 18);
		cout << "Fill in the Details :";

		setPointer(60, 22);
		cout << "Notice Title  :";
		setPointer(60, 24);
		cout << "Notice Body   :";
		setPointer(60, 26);
		cout << "Notice BY     :";
		setPointer(76, 22);
		fflush(stdin);
		getline(cin, notice_title);
		setPointer(76, 24);
		fflush(stdin);
		getline(cin, notice_body);
		setPointer(76, 26);
		fflush(stdin);
		getline(cin, notice_by);

		stringstream query_holder;
        query_holder << "INSERT INTO `notice`(`id`, `notice_title`, `notice_body`, `notice_by`) VALUES ('NULL','"<<notice_title<<"','"<<notice_body<<"','"<<notice_by<<"')";
        string temp_query = query_holder.str();
        const char* final_query = temp_query.c_str();

        notice_result = adminMain.query_executor(final_query);

        if(notice_result == 1)
        {
            setPointer(60, 32);
            cout << "Notice Posted!!";
        }
        else
        {
            setPointer(60, 32);
            cout << "Notice Post Failed!!";
            setPointer(60, 44);
            cout << "Hit Enter to re-enter and Esc to exit ....";
            retry_key = _getch();

            if (retry_key == 27)
            {
                exit(0);
            }
            else
            {
                goto  retry_notice;
            }
        }
    }

    void username_password_change()
    {
        int employee_id = 0, rows_in_employee = 0, update_result = 0;
        string username, password;

     retry_update:
        top_printing();
		setPointer(60, 17);
		cout << "Username/Password Update";
		setPointer(60, 20);
		cout << "Employee ID :";
		setPointer(74, 20);
		cin >> employee_id;

		stringstream query_holder;
        query_holder << "select * from employee where id = "<<employee_id<<"";
        string temp_query = query_holder.str();
        const char* final_query = temp_query.c_str();

        rows_in_employee = adminMain.query_select(final_query);

        if(rows_in_employee==0)
        {
            setPointer(60, 32);
            cout << "No Record Found";
            setPointer(60, 33);
            cout << "Hit Enter to re-enter and Esc to exit ....";
			retry_key = _getch();

			if (retry_key == 27)
			{
				exit(0);
			}
			else
			{
				goto  retry_update;
			}
        }
        else
        {
            setPointer(60, 32);
            cout << "Record Found";
            setPointer(60, 33);
            cout << "Hit Enter to continue....";
            _getch();

            top_printing();
            setPointer(60, 17);
            cout << "LOGIN";
            setPointer(60, 20);
            cout << "Username : " << endl;
            setPointer(60, 22);
            cout << "Password : ";
            setPointer(71, 20);
            cin >> username;
            setPointer(71, 22);
            cin >> password;

            stringstream query_holder2;
            query_holder2 << "UPDATE `userpass` SET `username`='"<<username<<"',`password`='"<<password<<"' WHERE id = "<<employee_id<<"";
            string temp_query2 = query_holder2.str();
            const char* final_query2 = temp_query2.c_str();

            update_result = adminMain.query_executor(final_query2);

            if(update_result == 1)
            {
                setPointer(60, 38);
                cout << "Recorded Updated!!";
                setPointer(60, 39);
                cout << "Hit Enter to continue....";
                _getch();
            }
            else
            {
                setPointer(60, 37);
                cout << "Update Failed!";
                retry_key = _getch();

                if (retry_key == 27)
                {
                    exit(0);
                }
                else
                {
                    goto  retry_update;
                }
            }
        }
    }

    void employee_salary()
    {
        _getch();
    }

    void view_salary()
    {
        _getch();
    }

    void view_work()
    {
        int rows_in_view_work  = 0, table_y = 21;

    retry_view_work:
        top_printing();
		setPointer(60, 17);
		cout << "View Work";

		stringstream query_holder;
        query_holder << "SELECT * FROM `advance_salary`";
        string temp_query = query_holder.str();
        const char* final_query = temp_query.c_str();

        rows_in_view_work = adminMain.query_select(final_query);

        if(rows_in_view_work == 0)
        {
            setPointer(60, 32);
            cout << "No Record Found";
            setPointer(60, 33);
            cout << "Hit Enter to re-enter and Esc to exit ....";
			retry_key = _getch();

			if (retry_key == 27)
			{
				exit(0);
			}
			else
			{
				goto  retry_view_work;
			}
        }
        else
        {
                top_printing();
                setPointer(60, 17);
                cout << "Query Result";
                setPointer(60, 20);
                cout << "ID   |Name\t\t|Age\t|Post Code\t|Phone";
                setPointer(60, 21);
                cout << "--------------------------------------------------";
                while(adminMain.row = mysql_fetch_row(adminMain.res))
                {
                    setPointer(60,table_y++);
                    cout << adminMain.row[0] << "    |" << adminMain.row[1] << "\t|" << adminMain.row[2] << "\t|" << adminMain.row[3] << "\t\t|" << adminMain.row[4] << "\n";
                }
        }
    }
};

class Manager: public Admin
{
public:
    void manager_panel()
    {
	re_try_manager:

		top_printing();
		setPointer(60, 17);
		cout << "Manager Panel";
		setPointer(60, 19);
		cout << "1. Search Employee";
		setPointer(60, 21);
		cout << "2. Register Employee";
		setPointer(60, 23);
		cout << "3. Update Employee";
		setPointer(60, 25);
		cout << "4. Delete Employee";
		setPointer(60, 27);
		cout << "5. Employee Salary";
		setPointer(60, 29);
		cout << "6. View Salary";
		setPointer(60, 31);
		cout << "7. Work Assignment";
		setPointer(60, 33);
		cout << "8. View Advance Salary";
        setPointer(60, 35);
		cout << "9. Notice";
		setPointer(60, 39);
		cout << "Press the number .... ";
		cin >> menu_select;
		fflush(stdin);
		switch (menu_select)
		{
		case 1:
		    employee_searching();
			break;
		case 2:
		    employee_registration();
			break;
		case 3:
		    employee_update();
			break;
		case 4:
		    employee_delete();
			break;
		case 5:
		    employee_salary();
			break;
		case 6:
		    view_salary();
			break;
        case 7:
            work_assignment();
			break;
        case 8:
			break;
        case 9:
            notice();
			break;
		default:
			setPointer(60, 42);
			cout << "Wrong Input!";
			setPointer(60, 44);
			cout << "Hit Enter to re-enter and Esc to exit ....";
			retry_key = _getch();

			if (retry_key == 27)
			{
				exit(0);
			}
			else
			{
				goto  re_try_manager;
			}
		}
    }
};

class Employee: public Admin
{
public:
    void employee_panel()
    {
	re_try_manager:

		top_printing();
		setPointer(60, 17);
		cout << "Employee Panel";
		setPointer(60, 19);
		cout << "1. Update Employee";
		setPointer(60, 21);
		cout << "2. View Salary";
		setPointer(60, 23);
		cout << "3. View Work";
		setPointer(60, 25);
		cout << "4. Advance Salary";
		setPointer(60, 27);
		cout << "5. Notice";
		setPointer(60, 39);
		cout << "Press the number .... ";
		cin >> menu_select;
		fflush(stdin);
		switch (menu_select)
		{
		case 1:
		    employee_update();
			break;
		case 2:
		    view_salary();
			break;
		case 3:
		    view_work();
			break;
		case 4:
		    advance_salary();
			break;
		case 5:
			break;
		default:
			setPointer(60, 42);
			cout << "Wrong Input!";
			setPointer(60, 44);
			cout << "Hit Enter to re-enter and Esc to exit ....";
			retry_key = _getch();

			if (retry_key == 27)
			{
				exit(0);
			}
			else
			{
				goto  re_try_manager;
			}
		}
    }
};

class Login
{
	char username[20], password[10];
	char admin_username[20] = "admin";
	char admin_password[10] = "123";

	Mysql loginValidate;

public:
	void login_input()
	{
	re_try_login:

        int login_check;

		top_printing();

		setPointer(60, 17);
		cout << "LOGIN";
		setPointer(60, 20);
		cout << "Username : " << endl;
		setPointer(60, 22);
		cout << "Password : ";
		setPointer(71, 20);
		cin >> username;
		setPointer(71, 22);
		cin >> password;

        stringstream query_holder;
        query_holder << "SELECT * FROM `userpass` WHERE `username` = '"<< username <<"' AND `password` = '"<< password <<"'";
        string temp_query = query_holder.str();
        const char* final_query = temp_query.c_str();

        login_check = loginValidate.query_select(final_query);

		// Check if the user is valid or not
		if (strcmp(admin_username, username) == 0 && strcmp(admin_password, password) == 0)
		{
			setPointer(60, 25);
			cout << "Success!";
			setPointer(60, 28);
			cout << "Proceeding to the panel ......";
			Sleep(1500);
			Admin adminMain;
			adminMain.admin_panel();
		}
		else if (login_check == 1)
		{
			setPointer(60, 25);
			cout << "Success!";
			setPointer(60, 28);
			cout << "Proceeding to the panel ......";
			Sleep(1500);

			if(strcmp("1", loginValidate.row[3]) == 0)
            {
                Manager managerMain;
                managerMain.manager_panel();
            }
            else
            {
                Employee employeeMain;
                employeeMain.employee_panel();
            }
		}
		else
		{
			setPointer(60, 25);
			cout << "Fail!";
			if (login_fail <= 10)
			{
				setPointer(60, 28);
				cout << "Hit Esc to exit and Enter to retry ....";
				retry_key = _getch();
				if (retry_key == 27)
				{
					exit(0);
				}
				else
				{
					login_fail++;
					goto re_try_login;
				}
			}
			else
			{
				setPointer(60, 28);
				cout << "You are not a valid user !!!";
				system("PAUSE");
				exit(0);
			}
		}
	}
};

int main()
{
    Mysql connect;

    fullscreen();
    system("COLOR 47");
    top_printing();

    setPointer(60, 20);
	cout << "WELCOME TO THE PROGRAM";
	setPointer(60, 21);
	cout << "Coded by : ......";

	// Checks if the connection between the database and the program
    if(connect.mysql_connection())
    {
        setPointer(60, 30);
        cout << "Connected to Database!!";
        Sleep(2000);
    }
    else
    {
        setPointer(60, 30);
        cout << "Not Connected to Database!!";
        setPointer(60, 31);
        cout << "Exiting..";
        Sleep(6000);
        exit(0);
    }

    // Now the login page is executed
    Login mainLogin;
    mainLogin.login_input();

    mysql_close(connection);
    return 0;
}

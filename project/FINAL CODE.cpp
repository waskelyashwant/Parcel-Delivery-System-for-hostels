#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
#include<stdio.h>
#include<time.h>
using namespace std;
class parcel;
map < string, pair<string,string>> map_ID_OTP_Email_id; //used for storing parcel-id, OTP, email-id
map < string, parcel > map_ID_parcel;   // used for storing parcel-id with object of class parcel
/* Address class for address of parcel
Contains Data Member: Hostel and Room No.*/
class Address 
{
  string Hostel;
  int Room_no;
  public:

  string getHostel ()
  {
    return Hostel;
  }
  int getRoom_no ()
  {
    return Room_no;
  }


  Address ()
  {
  }

  Address (string hostel, int room)
  {
    Hostel = hostel;
    Room_no = room;
  }
  void ChangeAddress (string hostel, int room) 
  {
    Hostel = hostel;
    Room_no = room;
  }
};
/* Parcel Class for parcel details
Data Members: Parcel ID, OTP key, Object of Address class*/
class parcel
{

private:
  string Parcel_Id;
  string Parcel_Authentication;
  Address Address_of_Delivery;

public:
  parcel ()
  {
  }
  parcel (string id, int room, string hostel)
  {
    Parcel_Id = id;
    Address_of_Delivery = Address (hostel, room);
    generate_authentication_key ();

  }

  void generate_authentication_key ()
  {
    srand (time (0));
    int x = rand () % 9000 + 1000;
    Parcel_Authentication = to_string (x);

  }

  void collect_parcel ()
  {

  }

  bool send_notification ()
  {
    string email_id;
    fstream f;
    if (Address_of_Delivery.getHostel () == "G6")
      {
	int flag = 0;
	string word, filename;
	filename = "G6.txt";
	f.open (filename.c_str ());
	while (f >> word)
	  {
	    //stringstream ss;
	    //ss<<Address_of_Delivery.Room_no;
	    // string rno = ss.rno();
	    string str = to_string (Address_of_Delivery.getRoom_no() );
	    if (word == str)
	      {
		f >> word;
		email_id = word;
	      }
	  }

      }
    else if (Address_of_Delivery.getHostel () == "G5")
      {
	int flag = 0;
	string word, filename;
	filename = "G5.txt";
	f.open (filename.c_str ());
	while (f >> word)
	  {
	    string str = to_string (Address_of_Delivery.getRoom_no ());
	    if (word == str)
	      {
		f >> word;
		email_id = word;
	      }
	  }

      }
      else 
      { cout<<"Hostel is Not in Database\n\n";
      			return false;
      }

    if (email_id.size () == 0)
      {
	cout << "\t\nEmail Id has not been found in Database.\n";
	return false;
      }
    else
      {

	fstream fio;
	fio.open ("message.txt", ios::out);
	string message = "There is a parcel for you with Parcel Id " + Parcel_Id + ". Use " + Parcel_Authentication + " as OTP during checkout. \n This is automatically genrated e-mail, Don't reply to it.";	
	// \n\t\t This Mail has been successfully Sent to " + email_id + ".\n";
	fio << "From:" << "IITJ Courier Management System" <<
	  "<iitjcouriermanagement@gmail.com>" << endl << "To:" <<
	  "'Dear Customer' <" << email_id << ">" << endl <<
	  "Subject: Parcel CheckIn\n" << message << endl;
	fio.close ();
	string str =
	  "curl -s --url 'smtps://smtp.gmail.com:465' --ssl-reqd   --mail-from 'iitjcouriermanagementsystem@gmail.com' --mail-rcpt '"
	  + email_id +
	  "'   --upload-file message.txt --user 'iitjcouriermanagementsystem@gmail.com:vvy616263' --insecure";
	
	const char *command = str.c_str ();
	system (command);
	map_ID_OTP_Email_id[Parcel_Id]=make_pair(get_auth_id(),email_id); 
	
	 //{ get_auth_id(),email_id}
 //   map_ID_OTP_Email_id[Parcel_Id].insert(make_pair(get_auth_id(),email_id));
//m.insert(make_pair("Noob", map<int, int>())); 
 //   m["Noob"].insert(make_pair(0, 5)); 
	//cout<<message<<endl; 
	return true;
      }

  }
  void add_parcel_to_map ()
  {

  }
  string get_auth_id ()
  {
    return Parcel_Authentication;
  }

  void getaddress ()
  {
      cout << "Hostel-: " << Address_of_Delivery.
      getHostel () << " Room-no--: " << Address_of_Delivery.
      getRoom_no () << endl;
  }

};
/* Class Delivery Man for delivery man details
Data Member: Delivery man's Company and his delivery ID*/
class Delivery_Man
{
private:
  string Company_Name;
  string delivery_id;
public:
    Delivery_Man()
    {
        
    }
  Delivery_Man (string Com_name, string del_id)
  {
    Company_Name = Com_name;
    delivery_id = del_id;
  }
  string getid ()
  {
    return delivery_id;
  }
  string getname ()
  {
    return Company_Name;
  }
  bool verify_id ()
  {				
    fstream f;
    int flag = 0;
    string word, filename;
    filename = "dman.txt";
    f.open (filename.c_str ());
    while (f >> word)
      {
	if (Company_Name == word)
	  {
	    f >> word;
	    if (delivery_id == word)
	      {
		flag = 1;
		return true;

	      }
	  }
      }
    if (flag == 0)
      {
	return false;
      }

  }

};
/*Function for 1 option of menu driven program  */
void
function_of_case1 ()
{
  string com, id;
  int i = 3;

  cout << "Enter the Courier Company Name\n";
  cin >> com;
  while (i--)
    {
      cout << "Enter Delivery Man Id\n";
      cin >> id;
      Delivery_Man Del_Man (com, id);
      if (Del_Man.verify_id () == true)
	{
	  int room;
	  string hostel, id;
	  int x = 1;
	  do
	    {
	      cout << "Enter Parcel ID :-\n";
	      cin >> id;
	      cout << "Enter Hostel :-\n";
	      cin >> hostel;
	      cout << "Enter Room No :-\n";
	      cin >> room;
	      if (hostel == "G6" || hostel == "G5")
		{
		  x = 0;
		}
	      else
		{
		  x = 1;
		  cout << "\n Wrong Hostel No., Please Try AGAIN \n";

		}
	      //x=0;
	    }
	  while (x == 1);
	  parcel input_parcel (id, room, hostel);

	  if (input_parcel.send_notification ())
	    {
	      map_ID_parcel[id] = input_parcel;
	      string otp = input_parcel.get_auth_id ();
	      //map_ID_OTP[id]=otp;
	      
	      cout <<
		"\t\t \n-----------Parcel is Successfully collected----------\n"
		<< endl;
	    }
	  else
	    cout << "\tParcel had not been Collected.\n";

	  break;
	}
      else
	{
	  cout << "Wrong Id\n";

	}

    }

}

/*Function for 2 option of menu driven program  */

void
function_of_case2 ()
{
  if (map_ID_OTP_Email_id.size () == 0)
    {
      cout << "No Parcels are available to be collected.\n";
      return;
    }
  cout << "ENTER PARCEL ID\n";
  string temp;
  cin >> temp;
  auto itr = map_ID_OTP_Email_id.find (temp);
  if (itr != map_ID_OTP_Email_id.end ())
    {
      int tryit = 3;
      while (tryit > 0)
	{
	  string totp;
	  cout << "ENTER OTP\n";
	  cin >> totp;
	  if (itr->second.first == totp)
	    {
	      cout << "\t\tYou have been successfully verified\n"
		<< "\t\tYou can now collect your parcel\n";
	    
	     
	      
	    fstream fio;
	fio.open ("message.txt", ios::out);
	string message = "Your Parcel with Id " + itr->first + " , has been successfully Checkout. \n This is automatically genrated e-mail, Don't reply to it. "; 
	
	
	fio << "From:" << "IITJ Courier Management System" <<
	  "<iitjcouriermanagement@gmail.com>" << endl << "To:" <<
	  "'Dear Customer' <" << itr->second.second << ">" << endl <<
	  "Subject: Parcel CheckOut\n" << message << endl;
	fio.close ();
	string str =
	  "curl -s --url 'smtps://smtp.gmail.com:465' --ssl-reqd   --mail-from 'iitjcouriermanagementsystem@gmail.com' --mail-rcpt '"
	  + itr->second.second +
	  "'   --upload-file message.txt --user 'iitjcouriermanagementsystem@gmail.com:vvy616263' --insecure";
	
	const char *command = str.c_str ();
	system (command);
	      
	      
	      
	  /***********************************  Work is still Pending  *********************************************/   
	      map_ID_OTP_Email_id.erase (temp);
	      map_ID_parcel.erase (temp);
	      cout << "\t\tPARCEL with ID " << temp <<
		" is deleted from Database\n" << endl;
		break;
	    }
	  else
	    {


	      cout << "Wrong OTP .Try Again...";
	      tryit--;
	      cout << tryit << " Chance left.\n";


	    }
	}
    }
  else
    {
      cout << "Parcel ID not found \n";
      cout << "\tReturning to MAIN MENU...\n";
      //delay(3000);

    }

}

/*Function for 3 option of menu driven program  */

void
function_of_case3 ()
{
  //cout<<" ----PARCEL ID----\n";
  cout<<"\nEnter Password: \t";
  string secure_key;
  //SetStdinEcho(false);
  cin>>secure_key;
  //SetStdinEcho(true);
  if(secure_key=="vvy616263")
  {
      cout<<"\nVerified\n";
  if (map_ID_parcel.size () == 0)
    {
      cout << "All parcels are delivered :) \n\n";
    }
  else
    {
      int i = 1;
      for (auto it = map_ID_parcel.begin (); it != map_ID_parcel.end ();it++, i++)
	{
	  cout << " " << i << "--: ID - " << it->first << "  ";
	  it->second.getaddress ();
	}
	cout<<endl;
    }
  }
  else
  {
      cout<<"\n Wrong Password \n";
      return ;
  }
}

int
main ()
{
  int c;
			/* Menu Driven Program */
  cout << "\t\t\tWelcome to IITJ Courier Management System\n";
  while (1)
    {	
      cout << "\t\t1--: Deliver a Parcel(for Delivery boy)\n"
	<< "\t\t2--: Collect a Parcel(for students)\n"
	<< "\t\t3--: Show undelivered Parcels(for admin only->password required)\n"
	<< "\t\t4--: Exit the program\n";
      cin >> c;
      switch (c)
	{
	case 1:
	  function_of_case1();

	  break;
	case 2:
	  function_of_case2();

	  break;
	case 3:
	  function_of_case3();

	  break;
	case 4:
	  {
	    cout << "\n\t\t\tThank you for using.\n\n";
	    exit (1);
	  }
	  break;
	default:
	  {
	    cout << "\nWrong Input\n";
	    break;

	  }
	  break;
	}


    }
  return 0;
}

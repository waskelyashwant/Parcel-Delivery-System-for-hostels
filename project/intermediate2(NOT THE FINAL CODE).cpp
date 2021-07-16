#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
#include<stdio.h>
#include<time.h>
using namespace std;
class parcel;
map < string, string > map_ID_OTP;
map < string, parcel > map_ID_parcel;
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
	    string str = to_string (Address_of_Delivery.getRoom_no ());
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

    if (email_id.size () == 0)
      {
	cout << "\t\nEmail Id has not found in Database.\n";
	return false;
      }
    else
      {

	fstream fio;
	fio.open ("message.txt", ios::out);
	string message = "There is Parcel for you with Id " + Parcel_Id + ". Use " + Parcel_Authentication + " as OTP during Checkout.";	
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
    cout << "Hostel-" << Address_of_Delivery.
      getHostel () << " Room-no--: " << Address_of_Delivery.
      getRoom_no () << endl;
  }

};

class Delivery_Man
{
private:
  string Company_Name;
  string delivery_id;
public:
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
  {				// file stream
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
	      cout << "Enter Hostel :-(e.g:-G5,G6)\n";
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
	      map_ID_OTP.insert (
				  {
				  id, otp}
	      );
	      cout <<
		"\t\t \n-----------Parcel is Successfully Received ----------\n"
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

void
function_of_case2 ()
{
  if (map_ID_OTP.size () == 0)
    {
      cout << "No Parcel to Collect.\n";
      return;
    }


  cout << "ENTER PARCEL ID\n";
  string temp;
  cin >> temp;
  auto itr = map_ID_OTP.find (temp);
  if (itr != map_ID_OTP.end ())
    {
      int tryit = 3;
      while (tryit > 0)
	{
	  string totp;
	  cout << "ENTER OTP\n";
	  cin >> totp;
	  if (itr->second == totp)
	    {
	      cout << "\t\tYou have been successfully verified\n"
		<< "\t\tYou can now collect your parcel\n";
	      // delay(3000);
	      map_ID_OTP.erase (temp);
	      map_ID_parcel.erase (temp);
	      cout << "\t\tPARCEL with ID " << temp <<
		" is deleted from Database" << endl;
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

void
function_of_case3 ()
{
  //cout<<" ----PARCEL ID----\n";
  if (map_ID_parcel.size () == 0)
    {
      cout << "There is no Collected Parcels. \n";
    }
  else
    {
      int i = 1;
      for (auto it = map_ID_parcel.begin (); it != map_ID_parcel.end ();
	   it++, i++)
	{
	  cout << " " << i << "--: ID - " << it->first << "  ";
	  it->second.getaddress ();

	}
    }
}

int
main ()
{
  int c;

  cout << "\t\t\tWelcome to IITJ Courier Management System\n";
  while (1)
    {
      cout << "\t\t1--: Deliver a Parcel(for Delivery_boy)\n"
	<< "\t\t2--: Wants to collect the Parcel\n"
	<< "\t\t3--: Show the undelivered Parcels\n"
	<< "\t\t4--: EXit the program\n";
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
	    cout << "\n\t\t\tThanking for Using\n\n";
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


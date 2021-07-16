#include<iostream>
#include<bits/stdc++.h>
//#include<map>
#include<stdio.h>
#include<time.h> 
#include<errno.h>
using namespace std;

int sendmail(const char *to, const char *from, const char *subject, const char *message)
{
    int retval = -1;
    FILE *mailpipe = popen("/usr/lib/sendmail -t", "w");
    if (mailpipe != NULL) {
        fprintf(mailpipe, "To: %s\n", to);
        fprintf(mailpipe, "From: %s\n", from);
        fprintf(mailpipe, "Subject: %s\n\n", subject);
        fwrite(message, 1, strlen(message), mailpipe);
        fwrite(".\n", 1, 2, mailpipe);
        pclose(mailpipe);
        retval = 0;
     }
     else {
         perror("Failed to invoke sendmail");
     }
     return retval;
}



class parcel;
map<string,string> map_ID_OTP;
map<string,parcel> map_ID_parcel;
class Address{
    public:
    
    string Hostel;
    int  Room_no;
    
    
        Address()
        {}
    
    Address(string hostel, int room)
    {   Hostel=hostel;
        Room_no=room;
    }
    void ChangeAddress(string hostel,int room)
    {   
        Hostel=hostel;
        Room_no=room;
    }
};
class parcel{
    
    private:
        string Parcel_Id;
        string Parcel_Authentication;
        Address Address_of_Delivery;
    
    public:
    parcel()
    {}
    parcel(string id, int  room,string hostel) 
    {   Parcel_Id= id;
        Address_of_Delivery=Address(hostel,room);
        generate_authentication_key();
        send_notification();
    }
    
    void generate_authentication_key()
        {   
        	srand(time(0));
        int x=rand()%9000 +1000;
            Parcel_Authentication=to_string(x) ;
           
        }
        
    void collect_parcel()
        {
            
        }
        
         void send_notification()
        {
            string email_id;
			fstream f;
			if(Address_of_Delivery.Hostel=="G6")
			{
			   int flag=0;
 				string word, filename;
				filename = "G6.txt";
				f.open(filename.c_str());
				while(f>>word)
				{
				   //stringstream ss;
				   //ss<<Address_of_Delivery.Room_no;
				  // string rno = ss.rno();
				  string str=to_string(Address_of_Delivery.Room_no);
				   if(word==str)
				   {
				       f>>word;
				       email_id=word;
				   }
				}

			}
			else if(Address_of_Delivery.Hostel=="G5")
			{
			   int flag=0;
 				string word, filename;
				filename = "G5.txt";
				f.open(filename.c_str());
				while(f>>word)
				{		string str=to_string(Address_of_Delivery.Room_no);
				   if(word==str)
				   {
				       f>>word;
				       email_id=word;
				   }
				}

			}
			
		string message = "There is Parcel for you with Id " +  Parcel_Id +".\n Use " + Parcel_Authentication + "as OTP.";
		cout<<message<<endl; 
        
        }
      void add_parcel_to_map()
      {
          
      }
      string get_auth_id()
      {
          return Parcel_Authentication;
      }
        
       void getaddress()
       {	cout<<Address_of_Delivery.Hostel<<" "<<Address_of_Delivery.Room_no<<endl;
       }
    
};

class Delivery_Man
{   private:
        string Company_Name; 
        string delivery_id;
    public:
        Delivery_Man(string Com_name, string del_id)
        {   Company_Name=Com_name;
            delivery_id=del_id;
        }
        string getid()
        {
            return delivery_id;
        }
        string getname()
        {
            return Company_Name;
        }
        bool verify_id()
            {       // file stream
				fstream f;
				int flag=0;
 				string word, filename;
				filename = "dman.txt";
				f.open(filename.c_str());
				while( f >> word )
				{
					if(Company_Name==word)
						{
							f>>word;
							if(delivery_id==word)
								{
									flag=1;
									return true;
									
								}
						}
				}
				if(flag==0)
				{
					return false;
				}
			               
            }
        
};
void function_of_case1()
{   string com,id;
    int i=3;
    
        cout<<"Enter the Courier Company Name\n";
    cin>>com;
    while(i--)
   { cout<<"Enter Delivery Man Id\n";
    cin>>id;
    Delivery_Man Del_Man(com,id);
    if(Del_Man.verify_id()==true)
    {   int room;
        string hostel,id;
        cout<<"Enter Parcel ID :-\n";
        cin>>id;
        cout<<"Enter Hostel :-\n";
        cin>>hostel;
        cout<<"Enter Room No :-\n";
        cin>>room;
        parcel input_parcel(id,room,hostel);
        
        map_ID_parcel[id]=input_parcel;
        string otp=input_parcel.get_auth_id();
        //map_ID_OTP[id]=otp;
	map_ID_OTP.insert({id,otp});
	cout<<"\t\t -----------Parcel is Successfully collected----------"<<endl;
        
        break;
    }
    else
    {
        cout<<"Wrong Id";
        
    }
    
    }
    
}
void function_of_case2()
{
    cout<<"ENTER PARCEL ID\n";
string temp;
cin>>temp;
auto itr = map_ID_OTP.find(temp);
if(itr!=map_ID_OTP.end())
{
    string totp;
    cout<<"ENTER OTP\n";
    cin>>totp;
    if(itr->second==totp)
    {
        cout<<"You have been successfully verified\n"
            <<"You can now collect your parcel\n";
       // delay(3000);
        map_ID_OTP.erase(temp);
        map_ID_parcel.erase(temp);
        cout<<"PARCEL with ID "<<temp<<" is deleted from Database";
    }
    else
    {
        int tryit=3;
        if(tryit>0)
        {
        cout<<"Wrong OTP\n";
        tryit--;
        cout<<tryit<<" chances left";
        }
        
    }
}
else
{
    cout<<"Parcel ID not found \n";
    cout<<"Returning to MAIN MENU...\n";
    //delay(3000);
    
}

}
void function_of_case3()
{
    cout<<" ----PARCEL ID----\n";
    int i=1;
    for(auto it = map_ID_parcel.begin();it!=map_ID_parcel.end();it++,i++)
    {  cout<<" "<<i<<":-"<<it->first;
    		it->second.getaddress();
            
    }
}

int main()
{       int c;
    while(1)
    {   cout<<"1--: Enter the Package\n"
            <<"2--: Get the Package\n"
            <<"3--: Show the undelivered Packages\n"
            <<"4--: EXit the program\n";
           cin>>c;
        switch(c)
        {   case 1:    function_of_case1();
                        
                break;
             case 2:    function_of_case2();
                        
                break; 
             case 3:    function_of_case3();
                    
                break; 
             case 4:        exit(1);
                         break;
             default: {
                 cout<< "\nWrong Input";
                 break;
                 
                      }             break;
        }
        
        
    }
    return 0;
}

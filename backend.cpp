#include <string>
#include <vector>
#include <fstream>
#include <ctype.h>
#include <iostream>

using namespace std;

class train_business;
class station;
class users
{
    string name;
    bool admin;
    string password;

public:
    string get_name();
    bool if_admin();
    void set_data(string, string);
    void change_password();
    users();
    users(string, string, bool);
};
class tracks
{
protected:
    float length;
    string start;
    string end;

public:
    void set_data(int,int,string);
    vector<string> get_data();
    void remove_track(int);
    void virtual remove_station(string)=0;
    vector<station> all_tracks();
    tracks();
    tracks(string,string,string);
};
class station:public tracks
{
protected:
    string name;
public:
    void remove_station(string)override;
    void set_data(string);
    vector<string> all_stations();
    station();
    station(string,string,string);
};
class trains
{
protected:
    string ID;
    string name;

public:
    void set_data(int ,string);
    vector<string> get_data();
    void remove_train(int);
    vector<train_business> all_trains();
    string get_name();
    string get_id();
    int virtual get_price()=0;
    trains(string, string);
    trains();
};
class train_business:public trains{
int static price;    
public:
int get_price()override;
void set_price(int);
string type();
train_business();
train_business(string);
train_business(string,string);
};
class train_economy:public trains{  
    int static price;  
public:    
void set_price(int a){    ofstream file("economy.txt");
    string line;
    file<<a;}
int get_price()override;
string type();
train_economy();
train_economy(string);
};
class train_executive:public trains{
    int static price;
public:    
int get_price()override;
void set_price(int a){    ofstream file("executive.txt");string line;file<<a;}
string type();
train_executive();
train_executive(string);
};
class train_stop
{
protected:
    string arrival;
    string departure;
    string station_name;

public:
    void set_data(string,int,string,string);
    train_stop(string,string,string);
    train_stop();
    vector <string> get_data();
};
class train_schedule : public train_stop
{
protected:
    int no_of_stations;
    vector<train_stop> stops;

public:
    void add_stop(string,int,string,string);
    void remove_stop(string,int);
    vector<train_stop> get_schedule(string);
    void set_no_of_stations();
};
class passanger_booking
{
protected:
    string train_name, from, to, date, name_passanger;
    int seat;

public:
    void set_data(string,string,int,int,int);
    vector <vector<string>> get_data(string);
    void cancel_booking(vector<string>);
    vector <train_business> get_train(int,int);
    vector <vector<string>> all_bookings();
};
//*******







int train_business::get_price(){
    ifstream file("business.txt");
    string line;
    (getline(file,line));
    int Price=stoi(line);
    return Price;
}
train_business::train_business(){}
train_business::train_business(string a):trains(a,"Business"){}
int train_business::price=1000;
void train_business::set_price(int a){
    ofstream file("business.txt");
    string line;
    file<<a;
}
string train_business::type(){
    return ID;
}
train_business::train_business(string a,string b):trains(a,b){}
int train_economy::get_price(){
    ifstream file("economy.txt");
    string line;
    (getline(file,line));
    int Price=stoi(line);
    return Price;
}
train_economy::train_economy(){}
train_economy::train_economy(string a):trains(a,"Economy"){}
int train_economy::price=500;
string train_economy::type(){
    return ID;
}
int train_executive::get_price(){
    ifstream file("executive.txt");
    string line;
    (getline(file,line));
    int Price=stoi(line);
    return Price;}
train_executive::train_executive(){}
train_executive::train_executive(string a):trains(a,"Executive"){}
string train_executive::type(){
    return ID;
}
/* Function to check if name entered for a user is valid to be used as name.s
string name as input,double for overloading
return true if name valid
*/ 
bool correct_name(string name, double a)
{
    bool contains_special_chars_or_numbers;
    // Check if the name contains special characters or numbers
    contains_special_chars_or_numbers = false;
    for (char c : name)
    {
        if (!isalpha(c) && !isspace(c))
        {
            contains_special_chars_or_numbers = true;
            break;
        }
    }

    if (contains_special_chars_or_numbers)
    {
        return 0;
    }
    return 1;
}
// To check if name for station or train is valid. 
//name as input int for overloading return true for correct name
bool correct_name(string name, int i)
{
    bool contains_special_chars;
    // Check if the name contains special characters or numbers
    contains_special_chars = false;
    for (char c : name)
    {
        if (!isalpha(c) && !isspace(c) && !isdigit(c) && !(c == '-'))
        {
            contains_special_chars = true;
            break;
        }
    }

    if (contains_special_chars)
    {
        return 0;
    }
    return 1;
}
string users::get_name()
{
    return name;
}
bool users::if_admin()
{
    return admin;
}
void users::set_data(string a, string b)
{
    ofstream user("user.txt", ios::app);
    this->name = a;
    password = b;
    admin = false;
    user << name << '\n'
         << password << '\n'
         << "false\n";
    user.close();
}
void users::change_password()
{
    string a;
    cout << "\nEnter Previous Password : ";
    fflush(stdin);
    getline(cin, a);
    if (a == password)
    {
        cout << "\nEnter New Password : ";
        getline(cin, password);
        cout << "\nPassword Changed";
        return;
    }
    else
    {
        cout << "\nIncorrect Password : Password not Changed ";
    }
}
users::users()
{
}
users::users(string a, string b, bool c) : name(a), password(b), admin(c)
{
}
//**************
void station::set_data(string a)
{
    ofstream stations("station.txt", ios::app);
    fflush(stdin);
    name = a;
    stations << name << '\n';
    stations.close();
}
void station::remove_station(string station_remove)
{
    vector <string> stations = this->all_stations();
    ofstream file("station.txt",ios::trunc);
    for(int i = 0;i < stations.size();i++)
        if(stations[i] != station_remove)
            file << stations[i] << endl;
    file.close();
    station a;int k;
    vector<string>data;
    
    vector<station>all_tracks=a.all_tracks();
        for(int i=0;i<all_tracks.size();){
            data.clear();
            data=all_tracks[i].get_data();
            if(data[0]==station_remove||data[1]==station_remove){
            a.remove_track(i);all_tracks.clear();all_tracks=a.all_tracks();
            }
            else i++;
        }
    data.clear();
    train_schedule b;train_business c;
    vector<train_business>all_trains=c.all_trains();
    vector<train_stop>stops;
    for(int i=0;i<all_trains.size();i++){
        stops.clear();
        stops=b.get_schedule(all_trains[i].get_name());
        for(int j=0;j<stops.size();j++){
            data.clear();
            data=stops[j].get_data();
            if(data[0]==station_remove){
                b.remove_stop(all_trains[i].get_name(),j+1);i--;break;
            }
        }
    }

}
vector<string> station::all_stations()
{
    vector <string> all_station;
    string line;
    int i = 0;
    ifstream station("station.txt");
    if (station.fail())
    {
        cout << "\nNo existing Stations";
        return all_station;
    }
    while (getline(station, line))
    {
        if(!line.empty())
            all_station.push_back(line);
    }
    station.close();
    return all_station;
}
station::station(){}
station::station(string a,string b,string c):tracks(a,b,c){}
//**************
void tracks::set_data(int starting,int ending,string Length)
{
    station *ptr=new station;
    vector<string>all_station=ptr->all_stations();
    ofstream file("tracks.txt",ios::app);
    station z;
    vector<station>all_tracks=z.all_tracks();
    for(int i=0;i<all_tracks.size();i++){
        if((all_tracks[i].get_data()[0]==all_station[starting-1])&&all_tracks[i].get_data()[1]==all_station[ending-1]){
            return;
        }
        if((all_tracks[i].get_data()[1]==all_station[starting-1])&&all_tracks[i].get_data()[0]==all_station[ending-1]){
            return;
        }
    }
    for(int i=0;i<all_station.size();i++){
        if(i==starting-1){
            file<<all_station[i]<<'\n';
        }
        if(i==ending-1){
            file<<all_station[i]<<'\n';
        }
    }
    cout << length;
    file<<Length<<'\n';file.close();
}
void tracks::remove_track(int track_num)
{
    vector<station>all_track=this->all_tracks();
    ofstream file("tracks.txt",ios::trunc);
    for(int i = 0;i < all_track.size();i++){
        if(i == track_num)
            continue;
        file << all_track[i].get_data()[0] << endl;
        file << all_track[i].get_data()[1] << endl;
        file << all_track[i].get_data()[2] << endl;
    }
    file.close();
}
vector <station> tracks::all_tracks()
{
    vector<station> all_track;
    string line3,line1,line2;
    ifstream track("tracks.txt",ios::in);
    if(track.fail()){
        cout<<"\nNo Existing Track ";
        return all_track;
    }
    while(getline(track,line1)){
        getline(track,line2);getline(track,line3);
        all_track.push_back(*(new station (line1,line2,line3)) );
    }
    track.close();
    return all_track;
}
vector<string> tracks::get_data(){
    vector <string> data;
    data.push_back(start);
    data.push_back(end);
    data.push_back(to_string(length));
    return data;
    }
tracks::tracks(){}
tracks::tracks(string a,string b,string c):start(a),end(b),length(stod(c)){}
//***************
void trains::set_data(int id,string name)
{
    string line;
    if(id==1){line="Business";}
    if(id==2){line="Executive";}
    if(id==3){line="Economy";}
    ofstream trains("trains.txt", ios::app);
    trains << line << '\n'
           << name << '\n';
    trains.close();
}
void trains::remove_train(int i)
{
    vector<string>data;
    vector<train_business>all_train=this->all_trains();
    int j=0;
    ofstream file("trains.txt",ios::trunc);
    for(int j=0;j<all_train.size();j++){
        if(j!=i-1){//considering train number start from 1 given in input
            data=all_train[j].get_data();
            file<<data[0]<<endl<<data[1]<<endl;
            data.clear();
        }
    }
    file.close();
    string d=all_train[i-1].get_name()+".txt";
    remove(d.c_str());
}
vector<train_business> trains::all_trains()
{
    vector<train_business>all_train;
    string line1,line2;
    ifstream train("trains.txt");
    while (getline(train, line1))
    {
        getline(train, line2);
        all_train.push_back(*(new train_business(line1,line2)));
    }
    train.close();
    return all_train;
}
trains::trains(string a, string b) : name(a), ID(b) {}
trains::trains() {}
string trains::get_name()
{
    return ID;
}
vector<string> trains::get_data(){
    vector <string> data;
    data.push_back(name);
    data.push_back(ID);
    return data;}
string trains::get_id(){
    return name;
}    
//****************
void train_stop::set_data(string file_name,int station_no,string arrival_time,string departure_time)
{
    ofstream file(file_name,ios::app);
    station *a = new station;
    vector <string>all_station=a->all_stations();
    station_name=all_station[station_no-1];
    arrival=arrival_time;
    departure=departure_time;
    file << station_name << '\n'
         << arrival_time << '\n'
         << departure_time << '\n';
    file.close();
}
vector <string> train_stop::get_data()
{
    vector <string> tmp;
    tmp.push_back(station_name);
    tmp.push_back(arrival);
    tmp.push_back(departure);
    return tmp;
}
train_stop::train_stop(string station,string arrival_time,string departure_time):station_name(station),arrival(arrival_time){
    departure=departure_time;
}
train_stop::train_stop(){};
//***************
void train_schedule::add_stop(string file,int station_no,string arrival_time,string departure_time)
{
    train_stop a;
    a.set_data(file,station_no,arrival_time,departure_time);
    stops.push_back(a);
    no_of_stations++;
}
void train_schedule::set_no_of_stations()
{
    no_of_stations = 0;
}
void train_schedule::remove_stop(string a,int stop_no )
{
    int i;
    vector<train_stop>stops=this->get_schedule(a);
    string line;
    ofstream file(a,ios::trunc);
    for(int i=0;i<stops.size();i++){
        if(i!=stop_no-1){
            file<<stops[i].get_data()[0]<<endl;
            file<<stops[i].get_data()[1]<<endl;
            file<<stops[i].get_data()[2]<<endl;
        }
    }
    no_of_stations--;
   file.close();
}
vector<train_stop> train_schedule::get_schedule(string a)
{
    ifstream file(a);
    string line1,line2,line3;
    vector<train_stop>stops;
    while (getline(file, line1))
    {
        getline(file, line2);
        getline(file, line3);
        stops.push_back(*(new train_stop(line1,line2,line3)));
    }
    file.close();
    return stops;
}
//****************
void passanger_booking::set_data(string name,string train,int starting,int ending,int seat_no)
{
    ofstream file("booking.txt",ios::app);
    station b;
    vector<string>a=b.all_stations();
    train_business z;string type;
    vector<train_business>all=z.all_trains();
    for(int i=0;i<all.size();i++){
        if(train==all[i].get_name()){
            type=all[i].get_id();cout<<all[i].get_name();break;
        }
    }
    file<<name<<'\n'<<a[starting-1]<<'\n'<<a[ending-1]<<'\n'<<train<<'\n'<<seat_no<<'\n'<<type<<'\n';
    file.close();
}
vector<vector<string>> passanger_booking::get_data(string name)
{
    ifstream booking("booking.txt");
    string line1,line2,line3,line4,line5,line6;
    vector<vector<string>> booking_data;
    vector <string> tmp;
    while(getline(booking,line1)){
        getline(booking,line2);getline(booking,line3);
        getline(booking,line4);getline(booking,line5);getline(booking,line6);
        if(line1==name){
            tmp.push_back(line1);tmp.push_back(line2);
            tmp.push_back(line3);tmp.push_back(line4);
            tmp.push_back(line5);tmp.push_back(line6);
            booking_data.push_back(tmp);
            tmp.clear();
        }
    }
    return booking_data;
}
void passanger_booking::cancel_booking(vector <string> a)
{
    int i = 0;
    vector <vector<string>> all_tickets = all_bookings();
    ofstream file("booking.txt",ios::trunc);
    while(i != all_tickets.size())
    {
        if((a[1] == all_tickets[i][1]) && (a[2] == all_tickets[i][2]) && (a[3] == all_tickets[i][3]) && (a[4] == all_tickets[i][4]))
        {
            i++;
            continue;
        }
        else
        for(int j = 0;j < 6;j++)
            file << all_tickets[i][j] << endl;
        i++;
    }
}//***************

vector<train_business> passanger_booking::get_train(int starting_station,int ending_station){
    train_business a;station b;
    bool starting=0,ending=0;
    string name;
    vector<train_business>available_trains;if(starting_station==ending_station){return available_trains;}
    vector<train_business>all_trains=a.all_trains();
    vector<string>all_stations=b.all_stations();
    for(int i=0;i<all_trains.size();i++){
        ifstream file(all_trains[i].get_name());
        while(getline(file,name)){
            if(name==all_stations[starting_station-1]){starting=true;}
            if(name==all_stations[ending_station-1]){ending=true;}
            getline(file,name);getline(file,name);
        }
        file.close();
        if(starting&&ending){
            available_trains.push_back(all_trains[i]);
        }
        starting=false;ending=false;
    }
    return available_trains;
}

vector <vector<string>> passanger_booking:: all_bookings(){
    vector <vector<string>> bookings;
    vector <string> tmp;
    string line,line1,line2,line3,line4,line5;
    ifstream file("booking.txt");
    while(getline(file,line))
    {
        getline(file,line1);getline(file,line2);getline(file,line3);getline(file,line4);getline(file,line5);
        tmp.push_back(line);tmp.push_back(line1),tmp.push_back(line2);tmp.push_back(line3),tmp.push_back(line4);
        tmp.push_back(line5);
        bookings.push_back(tmp);
        tmp.clear();
    }
    return bookings;
}

users *login_page(string name, string password)
{
    string file_name, file_password, admin;
    bool b = 0;
    ifstream user("user.txt");
    while (getline(user, file_name))
    {
        getline(user, file_password);
        if (file_name == name && file_password == password)
        {
            getline(user, admin);
            if (admin == "true")
            {
                b = true;
                user.close();
            }
            users *a = new users(name, password, b);
            user.close();
            return a;
        }
        getline(user, admin);
    }
    user.close();
    return nullptr;
}
users *new_user(string name, string password)
{
    users *p = new users(name, password, false);
    p->set_data(name, password);
    return p;
}
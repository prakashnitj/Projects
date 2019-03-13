#include<bits/stdc++.h>
using namespace std;
#define lat1d 12.9611159
#define lon1d 77.6362214
#define PI 3.14159265358979323846
#define EARTH_RADIUS 6371.0
ifstream ifile("cab.json");
ofstream ofile("answer.json");
double deg_to_rad(double deg)
{
    return (deg*PI/180);
}
double distanc(double lat2d,double lon2d)
{
    double lat1,lon1,lat2,lon2,delta_lon,central_ang;
    lat1=deg_to_rad(lat1d);
    lon1=deg_to_rad(lon1d);
    lat2=deg_to_rad(lat2d);
    lon2=deg_to_rad(lon2d);
    delta_lon=lon2-lon1;
    central_ang = acos( sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(delta_lon));

    return (EARTH_RADIUS * central_ang);
}
struct json
{
/* i and j are used to access various
    elements of the char arrays. x is used
    to measure the size of the element of
    latitude_as_string array. y is used to
    measure the size of the element of
    longitude_as_string array. m is used
    to measure the size of the element
    of id_as_string array. n is used to
    measure the size of the element of
    name array. f keeps count of " " "
    symbol. fi keeps count of " : " symbol.
    */
    long long int length, i=0, j, x, y, m,n, f, fi, id[100000];
    char latitude_as_string[1000],longitude_as_string[1000],id_as_string[1000], name[1000];
    double lat2d, lon2d;

    // To get each line of customers.json
    // file as string.
    string line;

    void distance_calculator()
    {
        if(distanc(lat2d,lon2d)<=50.0000){
            id[i]=atoll(id_as_string);
            i++;
            ofile<< "{\"user_id\": " << id[i - 1] << ", \"name\": " << name << "}" << endl;
        }
    }
    void json_parser()
    {
        if(ifile.is_open()){
            while(getline(ifile,line)){
                f=0;x=0;y=0;fi=0;m=0;n=0;
                length=line.size();
                for(j=0;j<length;j++){
                    if(line[j]=='"'){f++;}
                    else if(line[j]==':'){fi++;}

                    if(f==3){
                        j++;
                        while(line[j]!='"'){
                            latitude_as_string[x]=line[j];
                            x++;
                            j++;
                        }
                        j--;
                        latitude_as_string[x]='\0';
                    }
                    else if(f==13){
                        j++;
                        while(line[j]!='"'){
                            longitude_as_string[y]=line[j];
                            y++;
                            j++;
                        }
                        j--;
                        longitude_as_string[y]='\0';
                    }
                    if(fi==2){
                        j+=2;
                        while(line[j]!=','){
                            id_as_string[m]=line[j];
                            m++;
                            j++;
                        }
                        j--;
                        id_as_string[m]='\0';
                        fi++;
                    }
                    else if(fi==4){
                        j+=2;
                        while(line[j]!=','){
                            name[n]=line[j];
                            n++;
                            j++;
                        }
                        j--;
                        name[n]='\0';
                        f+=2;
                        fi++;
                    }
                }
                lat2d=atof(latitude_as_string);
                lon2d=atof(longitude_as_string);
                distance_calculator();
            }
        }
        ifile.close();
        ofile.close();
    }
};
int main()
{
    json obj;
    obj.json_parser();
    return 0;
}

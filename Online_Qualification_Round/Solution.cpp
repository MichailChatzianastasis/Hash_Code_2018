#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
int turn=0;
using namespace std;


class point {
public:
    int x;
    int y;
    point(int a=0,int b=0) {
        x=a;
        y=b;
}


};
int my_distance(point grid1,point grid2)
{
    return abs(grid1.x-grid2.x)+abs(grid1.y-grid2.y);
}

class car{
    public:
    int cant_get_ever;
     int m;
     std::vector<int> r;
     int isav;
     point grid;
     car(){
     m=0;
     grid.x=0;
     isav=0;
     grid.y=0;
     cant_get_ever=0;}

     void update(int dia, int a[])
     {   point grid_start(a[0],a[1]);
         point grid_finish(a[2],a[3]);
         int d3=a[4]-turn-my_distance(grid,grid_start);
         if(d3<0)
            d3=0;
         isav=my_distance(grid,grid_start)+d3+my_distance(grid_start,grid_finish);
        grid=grid_finish;
        r.push_back(dia);
        m++;
     }

};

int isvalid_car_to_ride(int turn, car u, int a[],int i)
{
    point grid_start(a[0],a[1]);
    point grid_finish(a[2],a[3]);
    int d1,d2;
    d1=my_distance(u.grid,grid_start);
    d2=my_distance(grid_start,grid_finish);
    int isvalid=0;
    if((turn+d1+d2<=a[5]) && (a[5]-a[4])>=d2)
        isvalid=1;
    return isvalid;

}

int main() {
    int am,dia;
ifstream myReadFile;
myReadFile.open("e_high_bonus.in");
int r,c,f,n,b,t,i,j;
myReadFile>> r>>c>>f>>n>>b>>t;
int a[10000][6];
for(i=0;i<n;i++)
    for(j=0;j<6;j++)
    myReadFile>>a[i][j];
int inside;
int rides[81];
myReadFile.close();
car vehicle[f];
for(i=0;i<n;i++)
    rides[i]=0;

while(turn<t)
{

for(am=0;am<f;am++) {
    inside=0;
    if(vehicle[am].isav<=turn && vehicle[am].cant_get_ever==0)
       {
           for(dia=0;dia<n;dia++)
               if(rides[dia]==0 && isvalid_car_to_ride(turn,vehicle[am],a[dia],dia)==1)
               {    inside=1;
                    vehicle[am].update(dia,a[dia]);
                    rides[dia]=1;
                    break;
                }
        if(inside==0) vehicle[am].cant_get_ever=1;
       }
    }
turn=turn+10000;
}
ofstream myfile ("solution5.txt");
if (myfile.is_open())
  {
      for(i=0;i<f;i++)
      {
        myfile << vehicle[i].m <<" ";
        for(j=0;j<vehicle[i].m;j++)
            myfile<< vehicle[i].r[j] <<" " ;
        myfile << "\n";
      }
  }
myfile.close();
return 0;
}

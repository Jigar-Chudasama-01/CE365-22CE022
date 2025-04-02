#include<bits/stdc++.h>
using namespace std;
void leftside()
{
    cout<<"Enter Non terminal for LEFT hand side: ";
}
void rightside(){
    cout<<"Enter Non terminal or terminal for right hand side: ";
}
void rightside2()
{
    cout<<"Enter Non terminal or terminal for right hand side2: ";
}
void input3times(vector<char>&v){
    for(int i=0;i<3;i++){
        char x;
        cin>>x;
        v.push_back(x);
    }
}
void input1time(vector<char>&v){
    char x;
    cin>>x;
    v.push_back(x);
}
int main()
{
    vector<char>v10,v11,v20,v21,v30,v31,v40,v41,v50;
    char a,b,c,d,e;

    leftside();
    cin>>a;
    rightside();
    input3times(v10);
    rightside2();
    input1time(v11);

    leftside();
    cin>>b;
    rightside();
    input1time(v20);
    rightside2();
    input1time(v21);

    leftside();
    cin>>c;
    rightside();
    input1time(v30);
    rightside2();
    input1time(v31);

    leftside();
    cin>>d;
    rightside();
    input3times(v40);
    rightside2();
    input1time(v41);

    leftside();
    cin>>d;
    rightside();
    input1time(v50);
    input1time(v50);
    // cout<<"temp";
    cout<<"FIRST("<<a<<") = "<<"{ "<<v20[0]<<" , "<<v30[0]<<" , "<<v40[0]<<" , "<<v41[0]<<" }"<<endl;
    // cout<<"temp2";
    cout<<"FIRST("<<b<<") = "<<"{ "<<v20[0]<<" , "<<v21[0]<<" }"<<endl;;
    cout<<"FIRST("<<c<<") = "<<"{ "<<v30[0]<<" , "<<v31[0]<<" }"<<endl;;
    cout<<"FIRST("<<d<<") = "<<"{ "<<v40[0]<<" , "<<v41[0]<<" }"<<endl;;
    cout<<"FIRST("<<e<<") = "<<"{ "<<v20[0]<<" , "<<v40[0]<<" }"<<endl;

    cout<<"FOLLOW("<<a<<") = "<<"{ "<<v40[2]<<" , "<<"$"<<" }"<<endl;
    cout<<"FOLLOW("<<b<<") = "<<"{ "<<v30[0]<<" , "<<v40[0]<<" , "<<v40[2]<<" , $" <<" }"<<endl;
    cout<<"FOLLOW("<<c<<") = "<<"{ "<<v41[0]<<" , "<<v40[2]<<" , $" <<" }"<<endl;
    cout<<"FOLLOW("<<d<<") = "<<v40[2]<<" , $" <<" }"<<endl;
    cout<<"FOLLOW("<<e<<") = "<<v40[2]<<" , $" <<" }"<<endl;

}

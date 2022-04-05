#include<iostream>
#include<bits/stdc++.h>
using namespace std;


vector<vector<int>* > direc;
vector<vector<int> *> s;
int gdi;  //currently not doing anything with gdi
int gd;
int bus;
void stat(){
    cout<<gd<<endl;
    cout<<s.size()<<endl;
    for(auto it=s.begin();it!=s.end();it++){
        cout<<(*(*it))[0]<<" ";
        cout<<(*(*it))[1]<<endl;
    }
}
void ser(int val){

    int div = (int)pow(2,gd);
    int num=(*direc[val%div])[1]; //no order in buckets as of now
    for(int i=2;i<num+2;i++){
        if((*direc[val%div])[i]==val){
            cout<<"found here at "<<val%div<<" "<<i-2<<endl;
        }
    }
}
void del(int val){

    int div = (int)pow(2,gd);
    int num=(*direc[val%div])[1];
    for(int i=2;i<num+2;i++){
        if((*direc[val%div])[i]==val){
            (*direc[val%div]).erase((*direc[val%div]).begin()+i);
            (*direc[val%div]).push_back(0);
            (*direc[val%div])[1] = num-1;
            cout<<"del "<<(*direc[val%div])[1]<<" "<<(*direc[val%div])[0]<<endl;
            return;
        }
    }

}
void in(int val){
    //case1
    int div = (int)pow(2,gd);
    int num=(*direc[val%div])[1];
    if(num<bus){
        (*direc[val%div])[num+2] = val;
        (*direc[val%div])[1] = num+1;
        cout<<"i am at "<<val%div<<" "<<num<<endl;
    }
    else if(num==bus){
        int locd = (*direc[val%div])[0];
        if(locd<gd){
            vector<int> * p = new vector<int>(bus+2);
            s.push_back(p);
            (*p)[0]=locd+1; //locdepth
            (*p)[1]=0;  //no.ofentries
            (*direc[val%div])[0]=locd+1;
            (*direc[val%div])[1] = 0;
            //direc[val%div]=p;
            num=(*direc[val%div])[1];
            int divloc = (int)pow(2,locd+1);
            int divlocold = (int)pow(2,locd);
            for(int i=2;i<bus+2;i++){
                if(((*direc[val%div])[i])%divloc==((*direc[val%div])[i])%divlocold){
                    int n0=(*direc[val%div])[1];
                    (*direc[val%div])[n0+2] = (*direc[val%div])[i];
                    (*direc[val%div])[1]=n0+1;
                }
                else{
                    int n0=(*p)[1];
                    (*p)[n0+2]=(*direc[val%div])[i];
                    (*p)[1]=n0+1;
                }
            }
            direc[(val%divlocold )+divlocold]=p;
            if((*direc[val%div])[1]==bus){
                in(val);
            }
            else{
                num =(*direc[val%div])[1];
                (*direc[val%div])[num+2] = val;
                (*direc[val%div])[1] = num+1;
                cout<<"i am at "<<val%div<<" "<<num<<endl;
            //(*direc[val%div])[0] = locd+1;
            }
            for(int i=0;i<div;i++){
                if(i%divloc==(val%divlocold )+divlocold){
                    direc[i] = p;
                }
            }



        }
        else if(locd ==gd){
                for(int i=0;i<(int)pow(2,gd);i++){
                    direc.push_back(direc[i]);
                }
                gd++;
                in(val);
        }

    }
}
void initial(int gdi,int bus){
    //currently not doing anything with gdi..just starting from start
    vector<int> * p =new vector<int>(bus+2);
    (*p)[0]=1; //locdepth
    (*p)[1]=0;  //no.ofentries
    s.push_back(p);
    vector<int> * q =new vector<int>(bus+2);
    (*q)[0]=1;
    (*q)[1]=0;
    s.push_back(q);
    for(int i=0;i<(int)pow(2,gdi);i++){
        if(i%2==0){
            direc.push_back(p);
        }
        else{
            direc.push_back(q);
        }


    }

}

int main(){
    cin>>gdi;
    cin>>bus;
    //vector<vector<int> *> direc((int)pow(2,gd));
    gd=1;
    initial(gd,bus);


    int opcode;
    cin>>opcode;
    while(opcode!=6){
        if(opcode == 2){
            int val;
            cin>>val;
            in(val);
        }
        else if(opcode ==3){
            int val;
            cin>>val;
            ser(val);
        }
        else if(opcode ==4){
            int val;
            cin>>val;
            del(val);
        }
        else if(opcode ==5){
            stat();
        }
        cin>>opcode;

    }




}

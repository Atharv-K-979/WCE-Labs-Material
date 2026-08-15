#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct Item{
    string name;
    double qty;
    double value;
    bool indivisible;
};
bool cmpRatio(Item a,Item b){
    return (a.value/a.qty)>(b.value/b.qty);
}
double knapsack(vector<Item>items,double capacity){
    sort(items.begin(),items.end(),cmpRatio);
    double total=0,remaining=capacity;
    for(auto item:items){
        if(remaining<=0)
            break;
        if(item.qty<=remaining){
            total+=item.value;
            remaining-=item.qty;
        }
        else if(!item.indivisible){
            double fraction=remaining/item.qty;
            total+=item.value*fraction;
            remaining=0;
        }
    }
    return total;
}
int main(){
    vector<Item>test1={
        {"crudeoil",300,900,false},
        {"coal",250,700,false},
        {"machinery",150,650,true},
        {"grain",200,500,false},
        {"steel",180,620,true},
        {"chemicals",100,450,false},
        {"vehicles",120,800,true},
        {"textiles",90,300,false},
        {"electronics",60,700,true},
        {"fertilizer",140,400,false}
    };
    vector<Item>test2={{"a",20,100,false},{"b",30,90,false}};
    vector<Item>test3={{"x",15,150,true}};
    vector<Item>test4={{"p",10,100,true},{"q",20,150,false}};
    vector<Item>test5={{"z",5,50,false}};
    cout<<"test case 1: total value loaded is "<<knapsack(test1,1000)<<endl;
    cout<<"test case 2: total value loaded is "<<knapsack(test2,50)<<endl;
    cout<<"test case 3: total value loaded is "<<knapsack(test3,10)<<endl;
    cout<<"test case 4: total value loaded is "<<knapsack(test4,25)<<endl;
    cout<<"test case 5: total value loaded is "<<knapsack(test5,0)<<endl;
    return 0;
}

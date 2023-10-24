#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include <map>
using namespace std;

class cache 
{
    public:
        int capacity;
        map<int,int> cachemap;
        list<int> cacheList;
        list<int>::iterator tail ;
        list<int>::iterator head ;
    public:
        cache() : tail(cacheList.end()), head(cacheList.begin()) {}

        virtual int get(int key)=0;
        virtual void set(int value, int key)=0;
        virtual void setCp(int value)=0;
    
    
    
};
class LRUCache : public cache
{
    public:
    void setCp(int value) override
    {
        capacity = value;
        
    };
    
    void set(int value,int key) override
    {
        list<int>::iterator itr = std::find(cacheList.begin(),cacheList.end(),key);
        if (itr == cacheList.end()) 
        {
            if (cacheList.size() < capacity) {
                cacheList.push_front(key);
                cachemap.insert(make_pair(key,value));
            }
            else
            {
                cacheList.pop_back();
                cacheList.push_front(key);
                cachemap.insert(make_pair(key,value));
            }
        }
        else
        {
            cacheList.remove(key);
            cacheList.push_front(key);
            cachemap[key] = value;
        }
    };
    
    int get(int key) override{
     list<int>::iterator itr = std::find(cacheList.begin(), cacheList.end(), key);
        if (itr != cacheList.end()) 
        {
            return cachemap[key];
        }
        else
        {
            return -1;
        }
    };
};

int main() {

    //enter query number you want to do and capacity of cache with space 
    int numofquerys;
    int capacity;
    
    cin>>numofquerys;
    cin>>capacity;
    
    LRUCache* myCache = new LRUCache();
    if (capacity <= 0) {
        cout<<"capacity can't be 0";
        delete myCache;
        return 0;
    }
    myCache->setCp(capacity);
    
    //enter querys in each line "get n"(return the value of key n) or "set n m" (sets the value of n to m and insert if doesn't exist else makes it last used )
    for ( int i =0; i < numofquerys; i++) 
    {
        string funcName;
        cin>> funcName;
        
        if (funcName == "get" )
        {
            int firstParam;
            cin >> firstParam;
            cout << myCache->get(firstParam) <<"\n";
        }
        else if(funcName == "set")
        {
            int firstParam;
            int secondParam;
            
            cin >> firstParam >> secondParam;
            myCache->set(secondParam, firstParam);
            
        }
        
        
        
    }
    
    delete myCache;
    return 0;
}




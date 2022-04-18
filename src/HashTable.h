#include <iostream>
#include <list>
#include <vector>

using namespace std;
/*struct Actor{
  int key;
  string name;
};*/

class HashTable{
    private:
    
        struct Actor{
            int key;
            string name;
            string movieList;
        };
        
        list<Actor*> *table;
        int total;
        
        const int actorTotal = 11456063;
  
        double loadFactor = 0.8;
        
        int getHash(int key){
            return key % total;
        }
        
    public:
        /*HashTable(){
            total = actorTotal / loadFactor;
            table = new list<Actor*>[total];
        }*/
        
        HashTable(int n){
            total = n;
            table = new list<Actor*>[total];
        }
        
        /*HashTable(){
            total = actorTotal / loadFactor;
            table = new list<Actor*>[total];
        }*/
        
        /*double getLoadFactor(){
            double loadFactor;
            double count;
            
            loadFactor = count / total;
            return loadFactor;
        }*/
        
        void insert(int Key, string Name, string mList){
            Actor* actor = new Actor();
            actor->key = Key;
            actor->name = Name;
            actor->movieList = mList;
            //cout << actor->key << " " << actor->name << " " << getHash(Key) << endl;
            table[getHash(Key)].push_back(actor);
        }
        
        void removeA(int Key, string Name){
            int x = getHash(Key);
            
            list<Actor*>::iterator it;
            for(it = table[x].begin(); it != table[x].end(); ++it){
                Actor* temp = *it;
                if(temp->name == Name){
                    //cout << temp->name << " ";
                    break;
                }
            }
            
            if(it != table[x].end()){
                table[x].erase(it);
            }
        }
        
        bool findA(int Key, string Name){
            int x = getHash(Key);
            
            list<Actor*>::iterator it;
            for(it = table[x].begin(); it != table[x].end(); ++it){
                Actor* temp = *it;
                if(temp->name == Name){
                    //cout << temp->name << " ";
                    break;
                }
            }
            
            if(it != table[x].end()){
                return true;
            }
            
            return false;
        }
        
        void printAll(){
            list<Actor*>::iterator it;
            for(int i = 0; i < total; i++){
                cout << "Index " << i << ": ";
                
                for(it = table[i].begin(); it != table[i].end(); ++it){
                    Actor* temp = *it;
                    cout << temp->name << "  ";
                }
                cout << endl;
            }
        }
};

/*int main(){
    HashTable ht(2);
    //HashTable ht();
    
    ht.insert(1, "Harry Potter" , "Sorcerers Stone");
    ht.insert(1, "Larry King", "Late Night");
    ht.insert(0, "Larry Lobster", "SpongeBob");
    
    ht.printAll();
    //cout << endl << ht.getLoadFactor() << endl;
    cout << ht.findA(1, "Larry King") << endl;
    
    ht.removeA(1, "Larry King");
    
    ht.printAll();
    
    cout << ht.findA(1, "Harry Potter") << endl;
    cout << ht.findA(1, "Larry King");
    
    //ht.printAll();
    //cout << endl << ht.getLoadFactor() << endl;
    
    return 0;    
}*/
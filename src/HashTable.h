#pragma once

#include <iostream>
#include <list>
#include <vector>

using namespace std;

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

        double threshold = 0.8;

        double loadFactor;

        //gets the hash of a key by dividing a unique key by the total number of buckets in the table
        int getHash(int key){
            return key % total;
        }

    public:
        //base constructor of HashTable, used for known amount of items
        HashTable(){
            //setting the total number of buckets within the table to be just under the threshold required for a resize
            total = (actorTotal / threshold) + 1;
            table = new list<Actor*>[total];
        }

        //constructor used when creating a table that needs to be modular
        HashTable(int n){
            //total number of buckets is set to a desired initial number
            total = n;
            table = new list<Actor*>[total];
        }

        //returns the number of buckets in the table
        int getTotal(){
            return total;
        }

        //function used to calculate the load size of the table
        double getLoadFactor(){
            double count = 0;

            list<Actor*>::iterator it;
            for(int x = 0; x < total; x++) {
                //x is the index (hash) of the bucket
                // load factor determined by filled buckets
                if (table[x].size() > 0) { count++; }

                // load factor determined by items in the HashTable
                // for(it = table[x].begin(); it != table[x].end(); ++it){
                //     Actor* temp = *it;
                //     //check to see if the bucket is filled or empty by seeing if there is an actor object in the bucket or if it is NULL
                //     if(temp != NULL){
                //         count++;
                //     }
                // }

            }
            //load factor is calculated by dividing the total number of buckets filled by the total number of buckets
            loadFactor = count / total;
            return loadFactor;
        }

        void resize() {
          int oldTotal = total;
          total *= 2;

          list<Actor *> *newTable;
          newTable = new list<Actor *>[total];

          // list<Actor *>::iterator it;
          for (int x = 0; x < oldTotal; x++) {
            // iterator causes a segfault
            // for (it = table[x].begin(); it != table[x].end(); ++it) {
            if (table[x].size() == 0) { continue; } // don't attempt to move empty cells
            for (auto actor : table[x]) {
              Actor *temp = actor;
              int index = getHash(temp->key);
              newTable[index].push_back(temp);
            }
          }
          delete[] table;
          table = newTable;
        }

        // function used to insert an actor into the table
        void insert(int Key, string Name, string mList){
            Actor* actor = new Actor();
            actor->key = Key;
            actor->name = Name;
            actor->movieList = mList;
            //we push back the actor to the key index we get when we call the hash function of their key
            table[getHash(Key)].push_back(actor);

            if (getLoadFactor() > threshold) { resize(); }
        }

        //removes an actor from the table
        void removeA(int Key, string Name){
            int x = getHash(Key);

            list<Actor*>::iterator it;
            //we check the list at the hashed index for the desired name of the actor using an iterator
            for(it = table[x].begin(); it != table[x].end(); ++it){
                Actor* temp = *it;
                //checks to see if the actors name the iterator is currently pointing to matches the desired name
                if(temp->name == Name){
                    //if it matches the for loop breaks,
                    break;
                }
            }

            //if the loop breaks, the iterator will equal the desired actor, and as long as we are not at the end of the list at the hashed index, we delete that actor
            if(it != table[x].end()){
                table[x].erase(it);
            }
        }

        //function used to find an actor based on their unique key and name
        bool findA(int Key, string Name){
            //much of this structure is very similar to the remove function
            int x = getHash(Key);

            list<Actor*>::iterator it;
            for(it = table[x].begin(); it != table[x].end(); ++it){
                //checks to see if the name attatched to the temp actor is the name we are looking for
                Actor* temp = *it;
                if(temp->name == Name){
                    break;
                }
            }

            //if the temp actors name matches, we return true
            if(it != table[x].end()){
                return true;
            }

            //if the loop is never broken, we did not find the actor, so we return false
            return false;
        }

        //function used to find an actor using only their unique id
        bool findKey(int Key){
            //this function is the same as the function above
            int x = getHash(Key);

            list<Actor*>::iterator it;
            for(it = table[x].begin(); it != table[x].end(); ++it){
                Actor* temp = *it;
                //instead of checking for actor names we are now comparing actor keys
                if(temp->key == Key){
                    break;
                }
            }

            if(it != table[x].end()){
                return true;
            }

            return false;
        }

        //function used to print the contents of the table
        void printAll(){
            for(int i = 0; i < total; i++){
                cout << "Index " << i << ": ";

                for (auto actor : table[i]) {
                    Actor* temp = actor;
                    cout << temp->name << "  ";
                }
                cout << endl;
            }
        }
};

/*int main(){
    //HashTable ht;
    HashTable ht(3);
    
    ht.insert(1, "Harry Potter" , "Sorcerers Stone");
    ht.insert(1, "Larry King", "Late Night");
    ht.insert(0, "Larry Lobster", "SpongeBob");
    
    //ht.printAll();
    //cout << endl << ht.getLoadFactor() << endl;
    //cout << ht.findA(1, "Larry King") << endl;
    
    //ht.removeA(1, "Larry King");
    cout << ht.findA(0);
    
    //ht.printAll();
    
    //cout << ht.findA(1, "Harry Potter") << endl;
    //cout << ht.findA(1, "Larry King") << endl;
    
    //cout << ht.getTotal() << endl;
    //cout << ht.getLoadFactor() << endl;
    /*ht.resize();
    cout << ht.getTotal() << endl;*/
    //ht.printAll();
    //cout << endl << ht.getLoadFactor() << endl;
    //int total = ht.actorTotal / ht2.loadFactor;
    //cout << total;
    
    /*HashTable ht(total);
    ht.insert(1, "Harry Potter" , "Sorcerers Stone");
    ht.insert(1, "Larry King", "Late Night");
    ht.insert(0, "Larry Lobster", "SpongeBob");
    ht.printAll();
    return 0;    
}*/

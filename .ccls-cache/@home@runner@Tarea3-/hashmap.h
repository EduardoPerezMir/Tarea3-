//
//  HashMap.h
//  TablaHashLab
//
//  Created by Matias Barrientos on 11-08-18.
//  Copyright © 2018 Matias Barrientos. All rights reserved.
//

#ifndef HashMap_h
#define HashMap_h


typedef struct HashMap HashMap;

typedef struct Pair {
     int key;
     void * value;
} Pair;

HashMap * createMap(long capacity);
void insertMap(HashMap * table, int key, void * value);
void eraseMap(HashMap * table, int key);
Pair * searchMap(HashMap * table, int key);
Pair * firstMap(HashMap * table);
Pair * nextMap(HashMap * table);
void enlarge(HashMap * map);

#endif /* HashMap_h */

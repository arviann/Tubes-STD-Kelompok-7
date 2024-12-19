#ifndef TUBES_H_INCLUDED
#define TUBES_H_INCLUDED

#include <iostream>
#include <string>

#define info(P) (P->info)
#define next(P) (P->next)
#define prev(P) (P->prev)
#define child(P) (P->child)
#define first(L) (L.first)
#define last(L) (L.last)

using namespace std;

// Struktur data Parent (E-commerce)
struct ECommerce {
    string name;
    int totalTransaction; // Total transaksi untuk parent
};

// Struktur data Child (Product)
struct Product {
    string productName;
    int price;
};

// Pointer untuk Parent dan Child
typedef struct elmECommerce *adrParent;
typedef struct elmProduct *adrChild;

// elm Parent (Double Linked List)
struct elmECommerce {
    ECommerce info;
    adrParent prev;
    adrParent next;
    adrChild child;
};

// elm Child (Single Linked List)
struct elmProduct {
    Product info;
    adrChild next;
};

// List Parent
struct ParentList {
    adrParent first;
    adrParent last;
};

// List Child
struct ChildList {
    adrChild first;
};

void createParentList(ParentList &L);
void createChildList(ChildList &L);
adrParent createelmECommerce(ECommerce info);
adrChild createelmProduct(Product info);

void insertParentLast(ParentList &L, adrParent P);
void insertChild(adrParent parent, adrChild child);
void showAllParents(ParentList &L);
void showAllData(ParentList &L);
void showAllChild(adrParent P);

adrParent searchParent(ParentList &L, string name);
adrChild searchChild(adrParent parent, string productName);

void deleteFirstParent(ParentList &L, adrParent &P);
void deleteLastParent(ParentList &L, adrParent &P);
void deleteAfterParent(ParentList &L, adrParent &P);
void deleteChild(adrParent parent, adrChild &C);

int calculateTotalTransaction(adrParent parent);
void updateParent(ParentList &L, string oldName, string newName);
void updateChild(adrParent parent, string oldProductName, string newProductName, int newPrice);
adrChild searchChildOnParent(adrParent parent, string productName);

void testNew(ParentList &L, ECommerce info, Product infoC);

#endif // TUBES_H_INCLUDED

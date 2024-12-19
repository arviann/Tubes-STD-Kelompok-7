#include "tubes.h"

// Inisialisasi Parent List
void createParentList(ParentList &L) {
    first(L) = NULL;
    last(L) = NULL;
}

void createChildList(ChildList &L) {
    first(L) = NULL;
}

// Membuat elm Parent
adrParent createelmECommerce(ECommerce info) {
    adrParent P = new elmECommerce;
    info(P) = info;
    prev(P) = NULL;
    next(P) = NULL;
    child(P) = NULL;
    return P;
}

// Membuat elm Child
adrChild createelmProduct(Product info) {
    adrChild C = new elmProduct;
    info(C) = info;
    next(C) = NULL;
    return C;
}

// Menambahkan Parent di akhir list
void insertParentLast(ParentList &L, adrParent P) {
    adrParent temp = first(L);
    while (temp != NULL) {
        if (info(temp).name == info(P).name) {
            cout << "E-Commerce dengan nama '" << info(P).name << "' sudah ada." << endl;
            delete P;
            return;
        }
        temp = next(temp);
    }
    if (first(L) == NULL) {
        first(L) = P;
        last(L) = P;
    } else {
        next(last(L)) = P;
        prev(P) = last(L);
        last(L) = P;
    }
}

// Menambahkan Child ke Parent tertentu
void insertChild(adrParent parent, adrChild child) {
    adrChild temp = child(parent);
    while (temp != NULL) {
        if (info(temp).productName == info(child).productName) {
            cout << "Produk dengan nama '" << info(child).productName << "' sudah ada." << endl;
            delete child;
            return;
        }
        temp = next(temp);
    }
    if (child(parent) == NULL) {
        child(parent) = child;
    } else {
        temp = child(parent);
        while (next(temp) != NULL) {
            temp = next(temp);
        }
        next(temp) = child;
    }
}

// Menampilkan semua Parent
void showAllParents(ParentList &L) {
    adrParent P = first(L);
    cout << "====== Daftar E-Commerce ======" << endl;
    if (first(L) == NULL){
        cout << "Data E-commerce kosong" << endl;
    } else {
        while (P != NULL) {
        cout << "E-Commerce: " << info(P).name
             << ", Total Transactions: " << calculateTotalTransaction(P) << endl;
        P = next(P);
        }
    }
}

// Menampilkan semua data (Parent dan Child)
void showAllData(ParentList &L) {
    adrParent P = first(L);
    cout << "-----------------------------------------" << endl;
    cout << "====== Daftar E-Commerce dan Produk ======" << endl;
    if (first(L) == NULL){
        cout << "Data E-commerce kosong" << endl;
    } else {
        while (P != NULL) {

        cout << "E-Commerce: " << info(P).name
             << ", Total Transaksi: Rp" << calculateTotalTransaction(P) << endl;
        adrChild Q = child(P);
        while (Q != NULL) {
            cout << "  Produk: " << info(Q).productName
                 << ", Harga: Rp" << info(Q).price << endl;
            Q = next(Q);
        }
        P = next(P);
        }
    }
    cout << "-----------------------------------------" << endl;
}

void showAllChild(adrParent P) {
    if (P == NULL){
        cout << "Data E-commerce kosong" << endl;
    } else {
        adrChild Q = child(P);
        while (Q != NULL) {
            cout << "  Produk: " << info(Q).productName
                 << ", Harga: Rp" << info(Q).price << endl;
            Q = next(Q);
        }
        P = next(P);
    }
    cout << "-----------------------------------------" << endl;
}

// Mencari Parent berdasarkan nama
adrParent searchParent(ParentList &L, string name) {
    adrParent P = first(L);
    while (P != NULL) {
        if (info(P).name == name) {
            return P;
        }
        P = next(P);
    }
    return NULL;
}

// Mencari Child berdasarkan nama produk
adrChild searchChild(adrParent parent, string productName) {
    adrChild C = child(parent);
    while (C != NULL) {
        if (info(C).productName == productName) {
            return C;
        }
        C = next(C);
    }
    return NULL;
}

// Menghapus Parent pertama
void deleteFirstParent(ParentList &L, adrParent &P) {
    if (first(L) != NULL) {
        P = first(L);
        if (first(L) == last(L)) {
            first(L) = NULL;
            last(L) = NULL;
        } else {
            first(L) = next(P);
            prev(first(L)) = NULL;
        }
        next(P) = NULL;
        delete P;
    }
}

// Menghapus Parent terakhir
void deleteLastParent(ParentList &L, adrParent &P) {
    if (first(L) != NULL) {
        P = last(L);
        if (first(L) == last(L)) {
            first(L) = NULL;
            last(L) = NULL;
        } else {
            last(L) = prev(P);
            next(last(L)) = NULL;
        }
        prev(P) = NULL;
        delete P;
    }
}

// Menghapus Parent setelah parent tertentu
void deleteAfterParent(ParentList &L, adrParent &P) {
    if (first(L) != NULL){
        next(prev(P)) = next(P);
        prev(next(P)) = prev(P);
        prev(P) = NULL;
        next(P) = NULL;
        delete P;
    }
}

// Menghapus Child dari Parent
void deleteChild(adrParent parent, adrChild &C) {
    if (child(parent) != NULL) {
        if (child(parent) == C) {
            child(parent) = next(C);
        } else {
            adrChild temp = child(parent);
            while (next(temp) != C) {
                temp = next(temp);
            }
            next(temp) = next(C);
        }
        delete C;
    }
}

// Menghitung total transaksi untuk Parent tertentu
int calculateTotalTransaction(adrParent parent) {
    int total = 0;
    adrChild C = child(parent);
    while (C != NULL) {
        total += info(C).price;
        C = next(C);
    }
    info(parent).totalTransaction = total;
    return total;
}

// Mengupdate nama parent
void updateParent(ParentList &L, string oldName, string newName) {
    adrParent P = searchParent(L, oldName);
    if (P != NULL) {
        info(P).name = newName;
        cout << "E-Commerce " << oldName << " berhasil diubah menjadi " << newName << endl;
    } else {
        cout << "E-Commerce " << oldName << " tidak ditemukan." << endl;
    }
}

// Mengupdate data child
void updateChild(adrParent parent, string oldProductName, string newProductName, int newPrice) {
    adrChild C = searchChild(parent, oldProductName);
    if (C != NULL) {
        info(C).productName = newProductName;
        info(C).price = newPrice;
        cout << "Produk " << oldProductName << " berhasil diupdate." << endl;
    } else {
        cout << "Produk " << oldProductName << " tidak ditemukan." << endl;
    }
}



adrChild searchChildOnParent(adrParent parent, string productName) {
    if (parent == NULL) {
        cout << "E-Commerce tidak ditemukan!" << endl;
        return NULL;
    }

    adrChild C = searchChild(parent, productName);
    if (C != NULL) {
        cout << "Produk ditemukan: " << endl;
        cout << "Nama Produk: " << info(C).productName << ", Harga: Rp" << info(C).price << endl;
        return C;
    } else {
        cout << "Produk " << productName << " tidak ditemukan di E-Commerce ini." << endl;
        return NULL;
    }
}

void testNew(ParentList &L, ECommerce info, Product infoC){
    adrParent x;

    info.name = "Tokopedia";
    info.totalTransaction = 0;
    x = createelmECommerce(info);
    insertParentLast(L, x);

    info.name = "Shopee";
    info.totalTransaction = 0;
    x = createelmECommerce(info);
    insertParentLast(L, x);

    info.name = "Lazada";
    info.totalTransaction = 0;
    x = createelmECommerce(info);
    insertParentLast(L, x);

    adrChild c;
    adrParent p;

    infoC.productName = "TV";
    infoC.price = 10000000;
    c = createelmProduct(infoC);
    p = searchParent(L,"Tokopedia");
    info.totalTransaction++;
    insertChild(p, c);

    infoC.productName = "HP";
    infoC.price = 7000000;
    c = createelmProduct(infoC);
    p = searchParent(L,"Tokopedia");
    info.totalTransaction++;
    insertChild(p, c);

    infoC.productName = "Labubu";
    infoC.price = 350000;
    c = createelmProduct(infoC);
    p = searchParent(L,"Tokopedia");
    insertChild(p, c);

    infoC.productName = "Jam";
    infoC.price = 4000000;
    c = createelmProduct(infoC);
    p = searchParent(L,"Shopee");
    insertChild(p, c);

    infoC.productName = "Parfum";
    infoC.price = 500000;
    c = createelmProduct(infoC);
    p = searchParent(L,"Shopee");
    insertChild(p, c);

    infoC.productName = "Tas";
    infoC.price = 250000;
    c = createelmProduct(infoC);
    p = searchParent(L,"Shopee");
    insertChild(p, c);

    infoC.productName = "Cermin";
    infoC.price = 270000;
    c = createelmProduct(infoC);
    p = searchParent(L,"Lazada");
    insertChild(p, c);

    infoC.productName = "Helm";
    infoC.price = 380000;
    c = createelmProduct(infoC);
    p = searchParent(L,"Lazada");
    insertChild(p, c);

    infoC.productName = "Basreng";
    infoC.price = 20000;
    c = createelmProduct(infoC);
    p = searchParent(L,"Lazada");
    insertChild(p, c);

    showAllData(L);
}

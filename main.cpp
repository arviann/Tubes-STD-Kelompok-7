#include "tubes.h"

void showMenu() {
    cout << "============ MENU E-COMMERCE ============" << endl;
    cout << "1. Tambah E-Commerce (Parent)" << endl;
    cout << "2. Tambah Produk (Child)" << endl;
    cout << "3. Tampilkan Semua Data" << endl;
    cout << "4. Hapus E-Commerce (Parent)" << endl;
    cout << "5. Hapus Produk (Child)" << endl;
    cout << "6. Cari E-Commerce" << endl;
    cout << "7. Cari Produk pada E-Commerce" << endl;
    cout << "8. Update E-Commerce" << endl;
    cout << "9. Update Produk" << endl;
    cout << "10. Hitung Total Transaksi E-Commerce" << endl;
    cout << "11. View Test Data" << endl;
    cout << "0. Keluar" << endl;
    cout << "Pilih menu: ";
}

int main() {
    ParentList listECommerce;
    createParentList(listECommerce);

    ECommerce info;
    Product infoC;

    int pilihan;
    do {
        showMenu();
        cin >> pilihan;
        cin.ignore(); // Membersihkan input buffer

        switch (pilihan) {
        case 1: { // Tambah E-Commerce (Parent)
        ECommerce dataECommerce;
        cout << "Masukkan Nama E-Commerce: ";
        getline(cin, dataECommerce.name);
        dataECommerce.totalTransaction = 0;

        adrParent newECommerce = createelmECommerce(dataECommerce);
        insertParentLast(listECommerce, newECommerce); // Sudah menangani duplikasi
        cout << "-----------------------------------------" << endl;
        break;
        }
        case 2: { // Tambah Produk (Child)
        string eCommerceName;
        cout << "Masukkan Nama E-Commerce: ";
        getline(cin, eCommerceName);
        adrParent parent = searchParent(listECommerce, eCommerceName);
        if (parent != NULL) {
            Product dataProduct;
            cout << "Masukkan Nama Produk: ";
            getline(cin, dataProduct.productName);
            cout << "Masukkan Harga Produk: ";
            cin >> dataProduct.price;

            adrChild newProduct = createelmProduct(dataProduct);
            insertChild(parent, newProduct); // Sudah menangani duplikasi
        } else {
            cout << "E-Commerce tidak ditemukan!" << endl;
        }
        cout << "-----------------------------------------" << endl;
        break;
        }
        case 3: { // Tampilkan Semua Data
            showAllData(listECommerce);
            break;
        }
        case 4: { // Hapus E-Commerce (Parent)
            string eCommerceName;
            cout << "Masukkan Nama E-Commerce yang ingin dihapus: ";
            getline(cin, eCommerceName);

            adrParent parent = searchParent(listECommerce, eCommerceName);
            if (parent != NULL) {
                if (parent == first(listECommerce)){
                    deleteFirstParent(listECommerce, parent);
                } else if (parent == last(listECommerce)){
                    deleteLastParent(listECommerce, parent);
                } else {
                    deleteAfterParent(listECommerce, parent);
                }
                cout << "E-Commerce berhasil dihapus!" << endl;
            } else {
                cout << "E-Commerce tidak ditemukan!" << endl;
            }
            cout << "-----------------------------------------" << endl;
            break;
        }
        case 5: { // Hapus Produk (Child)
            string eCommerceName, productName;
            cout << "Masukkan Nama E-Commerce: ";
            getline(cin, eCommerceName);

            adrParent parent = searchParent(listECommerce, eCommerceName);
            if (parent != NULL) {
                cout << "Masukkan Nama Produk yang ingin dihapus: ";
                getline(cin, productName);

                adrChild product = searchChild(parent, productName);
                if (product != NULL) {
                    deleteChild(parent, product);
                    cout << "Produk berhasil dihapus!" << endl;
                } else {
                    cout << "Produk tidak ditemukan!" << endl;
                }
            } else {
                cout << "E-Commerce tidak ditemukan!" << endl;
            }
            break;
        }
        case 6: { // Cari E-Commerce
            string eCommerceName;
            cout << "Masukkan Nama E-Commerce yang ingin dicari: ";
            getline(cin, eCommerceName);

            adrParent parent = searchParent(listECommerce, eCommerceName);
            if (parent != NULL) {
                cout << "E-Commerce ditemukan!" << endl;
                cout << "Nama: " << info(parent).name
                     << ", Total Transaksi: " << info(parent).totalTransaction << endl;
                showAllChild(parent);
            } else {
                cout << "E-Commerce tidak ditemukan!" << endl;
            }
            break;
        }
        case 10: { // Hitung Total Transaksi E-Commerce
            string eCommerceName;
            cout << "Masukkan Nama E-Commerce: ";
            getline(cin, eCommerceName);

            adrParent parent = searchParent(listECommerce, eCommerceName);
            if (parent != NULL) {
                int total = calculateTotalTransaction(parent);
                cout << "Total Transaksi untuk " << info(parent).name
                     << ": Rp" << total << endl;
            } else {
                cout << "E-Commerce tidak ditemukan!" << endl;
            }
            break;
        }
        case 0:
            cout << "Terima kasih telah menggunakan sistem E-Commerce." << endl;
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            break;


        cout << endl;
        case 7: { // Cari Produk pada E-Commerce
            string eCommerceName, productName;
            cout << "Masukkan Nama E-Commerce: ";
            getline(cin, eCommerceName);
            adrParent parent = searchParent(listECommerce, eCommerceName);

            cout << "Masukkan Nama Produk yang ingin dicari: ";
            getline(cin, productName);
            searchChildOnParent(parent, productName);
            break;
        }
        case 8: { // Update E-Commerce
            string oldName, newName;
            cout << "Masukkan Nama E-Commerce yang ingin diupdate: ";
            getline(cin, oldName);
            cout << "Masukkan Nama Baru: ";
            getline(cin, newName);
            updateParent(listECommerce, oldName, newName);
            break;
        }
        case 9: { // Update Produk
            string eCommerceName, oldProductName, newProductName;
            int newPrice;

            cout << "Masukkan Nama E-Commerce: ";
            getline(cin, eCommerceName);
            adrParent parent = searchParent(listECommerce, eCommerceName);

            if (parent != NULL) {
                cout << "Masukkan Nama Produk yang ingin diupdate: ";
                getline(cin, oldProductName);
                cout << "Masukkan Nama Produk Baru: ";
                getline(cin, newProductName);
                cout << "Masukkan Harga Baru: ";
                cin >> newPrice;
                cin.ignore();
                updateChild(parent, oldProductName, newProductName, newPrice);
            } else {
                cout << "E-Commerce tidak ditemukan!" << endl;
            }
            break;
        }
        case 11:{
            testNew(listECommerce , info, infoC);
            break;
        }
        case 12:{
            showAllParents(listECommerce);
            break;
        }
        }
    }
    while (pilihan != 0);
    return 0;
}

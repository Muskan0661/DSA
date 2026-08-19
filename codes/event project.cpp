
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

#define MAX_EVENTS 100
#define HASH_SIZE  101

// ================================================================
//  USER
// ================================================================
class User {
public:
    char  name[100];
    char  address[100];
    char  phone[20];
    char  date[20];
    float payment_advance;
    int   booking_id;

    User() {
        booking_id      = -1;
        payment_advance = 0;
        strcpy(name,    "");
        strcpy(address, "");
        strcpy(phone,   "");
        strcpy(date,    "");
    }
};

// ================================================================
//  EVENT
// ================================================================
class Event {
public:
    int    EventNumber;
    int    gs;
    int    time;
    string ven;
    int    info;
    User   usr;

    Event() : EventNumber(-1), gs(0), time(0), info(0) {}
};

// ================================================================
//  [1] HASH TABLE  (Linear Probing)
// ================================================================
struct HashNode {
    int  key;
    int  arrIdx;
    bool occupied;
    HashNode() : key(-1), arrIdx(-1), occupied(false) {}
};

class HashTable {
    HashNode table[HASH_SIZE];

    int hashFunc(int k) { return k % HASH_SIZE; }

public:
    void insert(int eventNum, int idx) {
        int h = hashFunc(eventNum), i = 0;
        while (table[(h + i) % HASH_SIZE].occupied) i++;
        int pos = (h + i) % HASH_SIZE;
        table[pos].key      = eventNum;
        table[pos].arrIdx   = idx;
        table[pos].occupied = true;
    }

    int search(int eventNum) {
        int h = hashFunc(eventNum);
        for (int i = 0; i < HASH_SIZE; i++) {
            int pos = (h + i) % HASH_SIZE;
            if (!table[pos].occupied)       return -1;
            if (table[pos].key == eventNum) return table[pos].arrIdx;
        }
        return -1;
    }

    void remove(int eventNum) {
        int h = hashFunc(eventNum);
        for (int i = 0; i < HASH_SIZE; i++) {
            int pos = (h + i) % HASH_SIZE;
            if (table[pos].key == eventNum) {
                table[pos].occupied = false;
                return;
            }
        }
    }

    void rebuild(Event* Events, int cnt) {
        for (int i = 0; i < HASH_SIZE; i++) table[i] = HashNode();
        for (int i = 0; i < cnt; i++)
            if (Events[i].EventNumber != -1)
                insert(Events[i].EventNumber, i);
    }

    void display() {
        cout << "\n-------- Hash Table (Linear Probing) --------\n";
        cout << left << setw(8)  << "Slot"
             << setw(14) << "EventNumber"
             << "ArrayIndex\n";
        cout << string(36, '-') << "\n";
        for (int i = 0; i < HASH_SIZE; i++)
            if (table[i].occupied)
                cout << setw(8)  << i
                     << setw(14) << table[i].key
                     << table[i].arrIdx << "\n";
    }
};

// ================================================================
//  [2] AVL TREE
// ================================================================
struct AVLNode {
    int      eventNumber, height;
    AVLNode *left, *right;
    AVLNode(int en) : eventNumber(en), height(1), left(NULL), right(NULL) {}
};

class AVLTree {
    AVLNode* root;

    int ht(AVLNode* n)  { return n ? n->height : 0; }
    int bal(AVLNode* n) { return n ? ht(n->left) - ht(n->right) : 0; }

    void updateH(AVLNode* n) {
        if (n) n->height = 1 + max(ht(n->left), ht(n->right));
    }

    AVLNode* rRotate(AVLNode* y) {
        AVLNode* x  = y->left;
        AVLNode* T2 = x->right;
        x->right = y; y->left = T2;
        updateH(y); updateH(x);
        return x;
    }

    AVLNode* lRotate(AVLNode* x) {
        AVLNode* y  = x->right;
        AVLNode* T2 = y->left;
        y->left = x; x->right = T2;
        updateH(x); updateH(y);
        return y;
    }

    AVLNode* balance(AVLNode* n, int key) {
        updateH(n);
        int b = bal(n);
        if (b > 1  && key < n->left->eventNumber)  return rRotate(n);
        if (b < -1 && key > n->right->eventNumber) return lRotate(n);
        if (b > 1  && key > n->left->eventNumber)  { n->left  = lRotate(n->left);  return rRotate(n); }
        if (b < -1 && key < n->right->eventNumber) { n->right = rRotate(n->right); return lRotate(n); }
        return n;
    }

    AVLNode* insert(AVLNode* node, int key) {
        if (!node) return new AVLNode(key);
        if      (key < node->eventNumber) node->left  = insert(node->left,  key);
        else if (key > node->eventNumber) node->right = insert(node->right, key);
        else return node;
        return balance(node, key);
    }

    AVLNode* minNode(AVLNode* n) { while (n->left) n = n->left; return n; }

    AVLNode* remove(AVLNode* node, int key) {
        if (!node) return node;
        if      (key < node->eventNumber) node->left  = remove(node->left,  key);
        else if (key > node->eventNumber) node->right = remove(node->right, key);
        else {
            if (!node->left || !node->right) {
                AVLNode* tmp = node->left ? node->left : node->right;
                if (!tmp) { delete node; return NULL; }
                *node = *tmp; delete tmp;
            } else {
                AVLNode* s = minNode(node->right);
                node->eventNumber = s->eventNumber;
                node->right = remove(node->right, s->eventNumber);
            }
        }
        updateH(node);
        int b = bal(node);
        if (b > 1  && bal(node->left)  >= 0) return rRotate(node);
        if (b > 1  && bal(node->left)  <  0) { node->left  = lRotate(node->left);  return rRotate(node); }
        if (b < -1 && bal(node->right) <= 0) return lRotate(node);
        if (b < -1 && bal(node->right) >  0) { node->right = rRotate(node->right); return lRotate(node); }
        return node;
    }

    bool search(AVLNode* n, int key) {
        if (!n) return false;
        if (n->eventNumber == key) return true;
        return key < n->eventNumber ? search(n->left, key) : search(n->right, key);
    }

    void inorder(AVLNode* n) {
        if (!n) return;
        inorder(n->left);
        cout << n->eventNumber << " ";
        inorder(n->right);
    }

    void printTree(AVLNode* n, string prefix, bool isLeft) {
        if (!n) return;
        cout << prefix << (isLeft ? "|-- " : "\\-- ")
             << n->eventNumber << " (h=" << n->height << ")\n";
        printTree(n->left,  prefix + (isLeft ? "|   " : "    "), true);
        printTree(n->right, prefix + (isLeft ? "|   " : "    "), false);
    }

public:
    AVLTree() : root(NULL) {}
    void insert(int k) { root = insert(root, k); }
    void remove(int k) { root = remove(root, k); }
    bool search(int k) { return search(root, k); }

    void display() {
        cout << "\n-------- AVL Tree --------\n";
        if (!root) { cout << "(empty)\n"; return; }
        printTree(root, "", false);
        cout << "Inorder: "; inorder(root); cout << "\n";
    }
};

// ================================================================
//  [3] BST  - Search users by Booking ID
// ================================================================
struct BSTNode {
    int   bookingId, eventNumber;
    char  userName[100];
    BSTNode *left, *right;

    BSTNode(int id, char* nm, int en)
        : bookingId(id), eventNumber(en), left(NULL), right(NULL)
    { strcpy(userName, nm); }
};

class BST {
    BSTNode* root;

    BSTNode* insert(BSTNode* n, int id, char* nm, int en) {
        if (!n) return new BSTNode(id, nm, en);
        if      (id < n->bookingId) n->left  = insert(n->left,  id, nm, en);
        else if (id > n->bookingId) n->right = insert(n->right, id, nm, en);
        return n;
    }

    BSTNode* searchNode(BSTNode* n, int id) {
        if (!n || n->bookingId == id) return n;
        return id < n->bookingId ? searchNode(n->left, id) : searchNode(n->right, id);
    }

    BSTNode* minNode(BSTNode* n) { while (n->left) n = n->left; return n; }

    BSTNode* remove(BSTNode* n, int id) {
        if (!n) return n;
        if      (id < n->bookingId) n->left  = remove(n->left,  id);
        else if (id > n->bookingId) n->right = remove(n->right, id);
        else {
            if (!n->left)  { BSTNode* t = n->right; delete n; return t; }
            if (!n->right) { BSTNode* t = n->left;  delete n; return t; }
            BSTNode* s = minNode(n->right);
            n->bookingId   = s->bookingId;
            n->eventNumber = s->eventNumber;
            strcpy(n->userName, s->userName);
            n->right = remove(n->right, s->bookingId);
        }
        return n;
    }

public:
    BST() : root(NULL) {}

    void insert(int id, char* nm, int en) { root = insert(root, id, nm, en); }
    void remove(int id)                   { root = remove(root, id); }

    void search(int id) {
        BSTNode* res = searchNode(root, id);
        if (res) {
            cout << "\n[BST] Booking Found!\n";
            cout << "  Booking ID : " << res->bookingId   << "\n";
            cout << "  User Name  : " << res->userName    << "\n";
            cout << "  Event#     : " << res->eventNumber << "\n";
        } else {
            cout << "\n[BST] Booking ID " << id << " not found.\n";
        }
    }
};

// ================================================================
//  [4] MIN-HEAP  (Custom, not STL)
// ================================================================
class MinHeap {
    vector<Event> H;

    void heapifyUp(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (H[p].time > H[i].time) { swap(H[p], H[i]); i = p; }
            else break;
        }
    }

    void heapifyDown(int i) {
        int n = (int)H.size();
        while (true) {
            int s = i, l = 2*i+1, r = 2*i+2;
            if (l < n && H[l].time < H[s].time) s = l;
            if (r < n && H[r].time < H[s].time) s = r;
            if (s != i) { swap(H[i], H[s]); i = s; }
            else break;
        }
    }

public:
    void  push(Event e) { H.push_back(e); heapifyUp((int)H.size()-1); }
    Event top()         { return H[0]; }
    void  pop()         { H[0] = H.back(); H.pop_back(); heapifyDown(0); }
    bool  empty()       { return H.empty(); }
    int   size()        { return (int)H.size(); }

    
    void update(int eventNumber, int newGs, int newTime, string newVen) {
        for (int i = 0; i < (int)H.size(); i++) {
            if (H[i].EventNumber == eventNumber) {
                H[i].gs   = newGs;
                H[i].time = newTime;
                H[i].ven  = newVen;
                break;
            }
        }
        vector<Event> tmp = H;
        H.clear();
        for (int i = 0; i < (int)tmp.size(); i++) push(tmp[i]);
    }

    
    void removeEvent(int eventNumber) {
        int idx = -1;
        for (int i = 0; i < (int)H.size(); i++)
            if (H[i].EventNumber == eventNumber) { idx = i; break; }
        if (idx == -1) return;
        H[idx] = H.back();
        H.pop_back();
        if (idx < (int)H.size()) heapifyDown(idx);
    }

    void display() {
        cout << "\n-------- Min-Heap (Scheduled Events) --------\n";
        if (H.empty()) { cout << "(empty)\n"; return; }
        cout << left << setw(10) << "Event#"
             << setw(12) << "Duration"
             << setw(20) << "Venue"
             << "Status\n";
        cout << string(55, '-') << "\n";
        for (int i = 0; i < (int)H.size(); i++)
            cout << setw(10) << H[i].EventNumber
                 << setw(12) << (to_string(H[i].time) + " min")
                 << setw(20) << H[i].ven
                 << (H[i].info ? "BOOKED" : "AVAILABLE") << "\n";
    }
};

// ================================================================
//  [Feature F] STAFF MEMBER
// ================================================================
struct StaffMember {
    int  id;
    char name[100];
    char role[50];
    bool available;
    int  assignedEvent;

    StaffMember() : id(-1), available(true), assignedEvent(-1) {
        strcpy(name, ""); strcpy(role, "");
    }
};

StaffMember staffList[50];
int staffCnt = 0;

// ================================================================
//  [7] QUICKSORT  - Sort by Guest Count
// ================================================================
Event Events[MAX_EVENTS];
int   cnt = 0;

int qsPartition(Event arr[], int low, int high) {
    int pivot = arr[high].gs, i = low - 1;
    for (int j = low; j < high; j++)
        if (arr[j].gs <= pivot) swap(arr[++i], arr[j]);
    swap(arr[i+1], arr[high]);
    return i + 1;
}

void quickSort(Event arr[], int low, int high) {
    if (low < high) {
        int pi = qsPartition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ================================================================
//  [8] MERGE SORT  - Sort by Duration
// ================================================================
void msmerge(Event arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    vector<Event> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i].time <= R[j].time) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(Event arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        msmerge(arr, l, m, r);
    }
}

// ================================================================
//  [9] BINARY SEARCH  - Search by EventNumber
// ================================================================
bool cmpEventNum(Event a, Event b) { return a.EventNumber < b.EventNumber; }

void sortByEventNum(Event arr[], int n) {
    sort(arr, arr + n, cmpEventNum);
}

int binarySearch(Event arr[], int n, int target) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if      (arr[m].EventNumber == target) return m;
        else if (arr[m].EventNumber <  target) l = m + 1;
        else                                   r = m - 1;
    }
    return -1;
}

// ================================================================
//  GLOBAL DSA STRUCTURES
// ================================================================
HashTable              hashTable;
AVLTree                avlTree;
BST                    userBST;
MinHeap                minHeap;
queue<User>            registrationQueue;
stack<Event>           history;
queue< pair<int,User> > waitlistQueue;

// ================================================================
//  [Feature D] VENUE CONFLICT CHECK
// ================================================================
bool venueConflict(const string& venue, const string& date, int skipEventNum) {
    for (int i = 0; i < cnt; i++) {
        if (Events[i].info == 1 &&
            Events[i].EventNumber != skipEventNum &&
            Events[i].ven == venue &&
            string(Events[i].usr.date) == date)
            return true;
    }
    return false;
}

// ================================================================
//  EVENT MANAGER
// ================================================================
class EventManager {

    void printEvent(const Event& e) {
        cout << "\n+-------------------------------------------+\n";
        cout << "  Event#   : " << e.EventNumber << "\n";
        cout << "  Venue    : " << e.ven          << "\n";
        cout << "  Guests   : " << e.gs           << "\n";
        cout << "  Duration : " << e.time         << " min\n";
        cout << "  Status   : " << (e.info ? "BOOKED" : "AVAILABLE") << "\n";
        if (e.info) {
            cout << "  User     : " << e.usr.name       << "\n";
            cout << "  Date     : " << e.usr.date       << "\n";
            cout << "  Booking# : " << e.usr.booking_id << "\n";
            cout << "  Advance  : Rs." << fixed << setprecision(2)
                 << e.usr.payment_advance << "\n";
        }
        cout << "+-------------------------------------------+\n";
    }

public:

    // ---------------------------------------------------------------
    //  ADD EVENT
    // ---------------------------------------------------------------
    void addEvent() {
        if (cnt >= MAX_EVENTS) { cout << "Event limit reached!\n"; return; }

        Event e;
        cout << "\nEnter Event Number : "; cin >> e.EventNumber;

        if (avlTree.search(e.EventNumber)) {
            cout << "Event#" << e.EventNumber << " already exists!\n";
            return;
        }

        cout << "Total Guests       : "; cin >> e.gs;
        cout << "Duration (minutes) : "; cin >> e.time;
        cout << "Venue Name         : "; cin >> e.ven;
        e.info = 0;

        Events[cnt] = e;
        hashTable.insert(e.EventNumber, cnt);
        avlTree.insert(e.EventNumber);
        minHeap.push(e);
        cnt++;

        cout << "\nEvent added! (Inserted into HashTable + AVL Tree + MinHeap)\n";
    }

    // ---------------------------------------------------------------
    //  BOOK EVENT
    // ---------------------------------------------------------------
    void bookEvent() {
        int ev;
        cout << "\nEnter Event Number: "; cin >> ev;

        int idx = hashTable.search(ev);
        if (idx == -1)             { cout << "Event not found!\n";     return; }
        if (Events[idx].info == 1) { cout << "Event already booked!\n"; return; }

        history.push(Events[idx]);

        char dateInput[20];
        cout << "\n--- Enter Booking Details ---\n";
        cout << "Booking ID       : "; cin >> Events[idx].usr.booking_id;
        cout << "Name             : "; cin >> Events[idx].usr.name;
        cout << "City             : "; cin >> Events[idx].usr.address;
        cout << "Phone            : "; cin >> Events[idx].usr.phone;
        cout << "Date (DD/MM/YYYY): "; cin >> dateInput;
        strcpy(Events[idx].usr.date, dateInput);
        cout << "Advance Payment  : "; cin >> Events[idx].usr.payment_advance;

        // [Feature D] Venue conflict check
        if (venueConflict(Events[idx].ven, string(Events[idx].usr.date), ev)) {
            cout << "\n[CONFLICT] Venue '" << Events[idx].ven
                 << "' is already booked on " << Events[idx].usr.date << "!\n";
            cout << "Booking cancelled to avoid conflict.\n";
            Events[idx] = history.top(); history.pop();
            return;
        }

        Events[idx].info = 1;
        userBST.insert(Events[idx].usr.booking_id, Events[idx].usr.name, ev);
        registrationQueue.push(Events[idx].usr);

        cout << "\nBooked successfully! (Added to BST + Registration Queue)\n";
    }

    // ---------------------------------------------------------------
    //  CHECKOUT & BILL
    // ---------------------------------------------------------------
    void checkOut() {
        int ev;
        cout << "\nEnter Event Number: "; cin >> ev;

        int idx = hashTable.search(ev);
        if (idx == -1 || Events[idx].info == 0) {
            cout << "Event not found or not booked!\n"; return;
        }

        int guests, duration;
        cout << "Actual Guests   : "; cin >> guests;
        cout << "Duration (mins) : "; cin >> duration;

        int    tables    = (int)ceil(guests / 6.0);
        int    staffNum  = (int)ceil(guests / 10.0);
        double food      = guests * 150.0;
        double staffCost = staffNum * (duration / 60.0) * 30.0;
        double venue     = 1500.0;
        double decor     = 1000.0;
        double total     = food + staffCost + venue + decor;
        double advance   = Events[idx].usr.payment_advance;
        double remaining = total - advance;

        cout << "\n============== FINAL BILL ==============\n";
        cout << "  Event#       : " << ev                   << "\n";
        cout << "  Guest Name   : " << Events[idx].usr.name << "\n";
        cout << "  Tables       : " << tables               << "\n";
        cout << "  Staff Needed : " << staffNum             << "\n";
        cout << "  Food         : Rs." << fixed << setprecision(2) << food      << "\n";
        cout << "  Staff Cost   : Rs." << staffCost                             << "\n";
        cout << "  Venue        : Rs." << venue                                 << "\n";
        cout << "  Decoration   : Rs." << decor                                 << "\n";
        cout << "  ----------------------------------------\n";
        cout << "  TOTAL        : Rs." << total                                 << "\n";
        cout << "  Advance Paid : Rs." << advance                               << "\n";
        cout << "  REMAINING    : Rs." << remaining                             << "\n";
        cout << "========================================\n";

        // Release staff
        for (int i = 0; i < staffCnt; i++)
            if (!staffList[i].available && staffList[i].assignedEvent == ev) {
                staffList[i].available     = true;
                staffList[i].assignedEvent = -1;
            }

        userBST.remove(Events[idx].usr.booking_id);
        avlTree.remove(ev);
        hashTable.remove(ev);
        Events[idx].info = 0;
        cout << "Checkout complete. Event slot freed.\n";
    }

    // ---------------------------------------------------------------
    //  [Feature A] EDIT EVENT
    // ---------------------------------------------------------------
    void editEvent() {
        int ev;
        cout << "\nEnter Event Number to edit: "; cin >> ev;

        int idx = hashTable.search(ev);
        if (idx == -1) { cout << "Event not found!\n"; return; }

        cout << "\nCurrent details:";
        printEvent(Events[idx]);

        cout << "\nWhat do you want to edit?\n";
        cout << "  1. Venue\n";
        cout << "  2. Guests\n";
        cout << "  3. Duration\n";
        cout << "  4. All three\n";
        cout << "Choice: ";
        int ch; cin >> ch;

        string newVen  = Events[idx].ven;
        int    newGs   = Events[idx].gs;
        int    newTime = Events[idx].time;

        if (ch == 1 || ch == 4) { cout << "New Venue    : "; cin >> newVen;  }
        if (ch == 2 || ch == 4) { cout << "New Guests   : "; cin >> newGs;   }
        if (ch == 3 || ch == 4) { cout << "New Duration : "; cin >> newTime; }

        Events[idx].ven  = newVen;
        Events[idx].gs   = newGs;
        Events[idx].time = newTime;

        minHeap.update(ev, newGs, newTime, newVen);

        cout << "\nEvent#" << ev << " updated successfully.\n";
        cout << "(MinHeap re-heapified since duration changed)\n";
    }

   
    void cancelBooking() {
        int ev;
        cout << "\nEnter Event Number to cancel: "; cin >> ev;

        int idx = hashTable.search(ev);
        if (idx == -1 || Events[idx].info == 0) {
            cout << "Event not found or not booked!\n"; return;
        }

        cout << "\nDays until event (enter number): ";
        int daysLeft; cin >> daysLeft;

        double advance = Events[idx].usr.payment_advance;
        double penalty = 0.0;
        string tier;

        if      (daysLeft > 30)  { penalty = advance * 0.10; tier = ">30 days  (10% penalty)"; }
        else if (daysLeft >= 15) { penalty = advance * 0.30; tier = "15-30 days (30% penalty)"; }
        else if (daysLeft >= 7)  { penalty = advance * 0.50; tier = "7-14 days  (50% penalty)"; }
        else                     { penalty = advance * 1.00; tier = "<7 days   (100% forfeited)"; }

        double refund = advance - penalty;

        cout << "\n============= CANCELLATION BILL =============\n";
        cout << "  Event#       : " << ev                   << "\n";
        cout << "  Customer     : " << Events[idx].usr.name << "\n";
        cout << "  Advance Paid : Rs." << fixed << setprecision(2) << advance << "\n";
        cout << "  Tier         : " << tier                 << "\n";
        cout << "  Penalty      : Rs." << penalty           << "\n";
        cout << "  REFUND       : Rs." << refund            << "\n";
        cout << "=============================================\n";

        userBST.remove(Events[idx].usr.booking_id);
        Events[idx].info = 0;

        // Release staff
        for (int i = 0; i < staffCnt; i++)
            if (!staffList[i].available && staffList[i].assignedEvent == ev) {
                staffList[i].available     = true;
                staffList[i].assignedEvent = -1;
            }

        cout << "\nBooking cancelled.\n";

        // [Feature C] Auto-book from Waitlist
        bool autoBooked = false;
        while (!waitlistQueue.empty()) {
            pair<int,User> front = waitlistQueue.front();
            waitlistQueue.pop();

            if (front.first == ev) {
                User wu = front.second;

                if (venueConflict(Events[idx].ven, string(wu.date), ev)) {
                    cout << "[Waitlist] Venue conflict for " << wu.name << " - skipping.\n";
                    continue;
                }

                Events[idx].usr  = wu;
                Events[idx].info = 1;
                userBST.insert(wu.booking_id, wu.name, ev);
                registrationQueue.push(wu);

                cout << "\n[Waitlist] Auto-booked: " << wu.name
                     << " (Booking ID: " << wu.booking_id << ")"
                     << " moved from waitlist to Event#" << ev << ".\n";
                autoBooked = true;
                break;
            } else {
                waitlistQueue.push(front);
                break;
            }
        }

        if (!autoBooked)
            cout << "[Waitlist] No one in waitlist for Event#" << ev << ".\n";
    }

    // ---------------------------------------------------------------
    //  [Feature C] JOIN WAITLIST
    // ---------------------------------------------------------------
    void joinWaitlist() {
        int ev;
        cout << "\nEnter Event Number to join waitlist: "; cin >> ev;

        int idx = hashTable.search(ev);
        if (idx == -1) { cout << "Event not found!\n"; return; }
        if (Events[idx].info == 0) {
            cout << "Event is available - just book it directly!\n"; return;
        }

        User wu;
        cout << "\n--- Waitlist Registration ---\n";
        cout << "Booking ID       : "; cin >> wu.booking_id;
        cout << "Name             : "; cin >> wu.name;
        cout << "City             : "; cin >> wu.address;
        cout << "Phone            : "; cin >> wu.phone;
        cout << "Date (DD/MM/YYYY): "; cin >> wu.date;
        cout << "Advance Payment  : "; cin >> wu.payment_advance;

        waitlistQueue.push(make_pair(ev, wu));

        // Count position in waitlist
        int pos = 0;
        queue< pair<int,User> > tmp = waitlistQueue;
        while (!tmp.empty()) {
            if (tmp.front().first == ev) pos++;
            tmp.pop();
        }

        cout << "\n" << wu.name << " added to waitlist for Event#"
             << ev << ". Position: " << pos << "\n";
    }

    // ---------------------------------------------------------------
    //  [Feature D] CHECK VENUE CONFLICT (standalone)
    // ---------------------------------------------------------------
    void checkVenueConflict() {
        string venue, date;
        cout << "\nEnter Venue Name       : "; cin >> venue;
        cout << "Enter Date (DD/MM/YYYY): "; cin >> date;

        bool conflict = false;
        cout << "\n--- Venue Conflict Report for '" << venue << "' on " << date << " ---\n";
        for (int i = 0; i < cnt; i++) {
            if (Events[i].info == 1 &&
                Events[i].ven == venue &&
                string(Events[i].usr.date) == date) {
                cout << "  CONFLICT: Event#" << Events[i].EventNumber
                     << " already booked here on this date.\n";
                cout << "  Booked by: " << Events[i].usr.name
                     << " (Booking ID: " << Events[i].usr.booking_id << ")\n";
                conflict = true;
            }
        }
        if (!conflict)
            cout << "  No conflicts. Venue is free on " << date << ".\n";
    }

    // ---------------------------------------------------------------
    //  [Feature E] VIEW ALL BOOKINGS
    // ---------------------------------------------------------------
    void viewAllBookings() {
        cout << "\n==================== ALL BOOKINGS ====================\n";
        cout << left
             << setw(8)  << "Event#"
             << setw(20) << "Customer"
             << setw(18) << "Venue"
             << setw(12) << "Date"
             << setw(10) << "Guests"
             << setw(12) << "Booking ID"
             << "Advance (Rs.)\n";
        cout << string(90, '-') << "\n";

        int count = 0;
        for (int i = 0; i < cnt; i++) {
            if (Events[i].info == 1) {
                cout << left
                     << setw(8)  << Events[i].EventNumber
                     << setw(20) << Events[i].usr.name
                     << setw(18) << Events[i].ven
                     << setw(12) << Events[i].usr.date
                     << setw(10) << Events[i].gs
                     << setw(12) << Events[i].usr.booking_id
                     << fixed << setprecision(2)
                     << Events[i].usr.payment_advance << "\n";
                count++;
            }
        }

        if (count == 0) cout << "  No bookings found.\n";
        cout << string(90, '-') << "\n";
        cout << "Total booked events: " << count << "\n";
        cout << "======================================================\n";
    }

    // ---------------------------------------------------------------
    //  [Feature F] STAFF MANAGEMENT
    // ---------------------------------------------------------------
    void staffMenu() {
        int ch;
        do {
            cout << "\n===== STAFF MANAGEMENT =====\n";
            cout << "  1. Add Staff Member\n";
            cout << "  2. Assign Staff to Event\n";
            cout << "  3. Unassign Staff from Event\n";
            cout << "  4. View All Staff\n";
            cout << "  5. View Available Staff\n";
            cout << "  6. View Staff for a Specific Event\n";
            cout << "  7. Remove Staff Member\n";
            cout << "  0. Back to Main Menu\n";
            cout << "============================\n";
            cout << "Choice: "; cin >> ch;

            if (ch == 1) {
                if (staffCnt >= 50) { cout << "Staff list full!\n"; continue; }
                StaffMember s;
                cout << "Staff ID   : "; cin >> s.id;

                bool dup = false;
                for (int i = 0; i < staffCnt; i++)
                    if (staffList[i].id == s.id) { dup = true; break; }
                if (dup) { cout << "Staff ID already exists!\n"; continue; }

                cout << "Name       : "; cin >> s.name;
                cout << "Role (Catering/AV/Security/Decor): "; cin >> s.role;
                s.available     = true;
                s.assignedEvent = -1;
                staffList[staffCnt++] = s;
                cout << "Staff member " << s.name << " added.\n";

            } else if (ch == 2) {
                int sid, ev;
                cout << "Staff ID : "; cin >> sid;
                cout << "Event#   : "; cin >> ev;

                int idx = hashTable.search(ev);
                if (idx == -1) { cout << "Event not found!\n"; continue; }

                bool found = false;
                for (int i = 0; i < staffCnt; i++) {
                    if (staffList[i].id == sid) {
                        if (!staffList[i].available) {
                            cout << staffList[i].name
                                 << " already assigned to Event#"
                                 << staffList[i].assignedEvent << "!\n";
                        } else {
                            staffList[i].available     = false;
                            staffList[i].assignedEvent = ev;
                            cout << staffList[i].name
                                 << " assigned to Event#" << ev << ".\n";
                        }
                        found = true; break;
                    }
                }
                if (!found) cout << "Staff ID " << sid << " not found.\n";

            } else if (ch == 3) {
                int sid;
                cout << "Staff ID : "; cin >> sid;
                bool found = false;
                for (int i = 0; i < staffCnt; i++) {
                    if (staffList[i].id == sid) {
                        staffList[i].available     = true;
                        staffList[i].assignedEvent = -1;
                        cout << staffList[i].name << " is now available.\n";
                        found = true; break;
                    }
                }
                if (!found) cout << "Staff ID " << sid << " not found.\n";

            } else if (ch == 4) {
                cout << "\n-------- All Staff --------\n";
                cout << left << setw(8)  << "ID"
                             << setw(22) << "Name"
                             << setw(15) << "Role"
                             << "Status\n";
                cout << string(65, '-') << "\n";
                if (staffCnt == 0) { cout << "(no staff registered)\n"; continue; }
                for (int i = 0; i < staffCnt; i++) {
                    cout << setw(8)  << staffList[i].id
                         << setw(22) << staffList[i].name
                         << setw(15) << staffList[i].role;
                    if (staffList[i].available)
                        cout << "AVAILABLE\n";
                    else
                        cout << "ASSIGNED -> Event#" << staffList[i].assignedEvent << "\n";
                }

            } else if (ch == 5) {
                cout << "\n--- Available Staff ---\n";
                cout << left << setw(8) << "ID" << setw(22) << "Name" << "Role\n";
                cout << string(45, '-') << "\n";
                bool any = false;
                for (int i = 0; i < staffCnt; i++) {
                    if (staffList[i].available) {
                        cout << setw(8)  << staffList[i].id
                             << setw(22) << staffList[i].name
                             << staffList[i].role << "\n";
                        any = true;
                    }
                }
                if (!any) cout << "No staff currently available.\n";

            } else if (ch == 6) {
                int ev;
                cout << "Event# : "; cin >> ev;
                cout << "\n--- Staff for Event#" << ev << " ---\n";
                bool any = false;
                for (int i = 0; i < staffCnt; i++) {
                    if (!staffList[i].available && staffList[i].assignedEvent == ev) {
                        cout << "  [ID:" << staffList[i].id << "] "
                             << staffList[i].name
                             << " (" << staffList[i].role << ")\n";
                        any = true;
                    }
                }
                if (!any) cout << "No staff assigned to this event.\n";

            } else if (ch == 7) {
                int sid;
                cout << "Staff ID to remove: "; cin >> sid;
                bool found = false;
                for (int i = 0; i < staffCnt; i++) {
                    if (staffList[i].id == sid) {
                        if (!staffList[i].available)
                            cout << "Warning: assigned to Event#"
                                 << staffList[i].assignedEvent << ". Removing anyway.\n";
                        for (int j = i; j < staffCnt - 1; j++)
                            staffList[j] = staffList[j+1];
                        staffCnt--;
                        cout << "Staff member removed.\n";
                        found = true; break;
                    }
                }
                if (!found) cout << "Staff ID " << sid << " not found.\n";
            }

        } while (ch != 0);
    }

    // ---------------------------------------------------------------
    //  AVAILABLE EVENTS
    // ---------------------------------------------------------------
    void showAvailable() {
        cout << "\n--- Available Events ---\n";
        bool found = false;
        for (int i = 0; i < cnt; i++)
            if (Events[i].info == 0) { printEvent(Events[i]); found = true; }
        if (!found) cout << "All events are currently booked.\n";
    }

    // ---------------------------------------------------------------
    //  SEARCH BY NAME
    // ---------------------------------------------------------------
    void searchByName() {
        char uname[100];
        cout << "Enter Name: "; cin >> uname;
        bool found = false;
        for (int i = 0; i < cnt; i++)
            if (Events[i].info == 1 && strcmp(Events[i].usr.name, uname) == 0) {
                printEvent(Events[i]); found = true;
            }
        if (!found) cout << "No booking found for: " << uname << "\n";
    }

    // ---------------------------------------------------------------
    //  SEARCH BY BOOKING ID  [BST]
    // ---------------------------------------------------------------
    void searchByBookingID() {
        int id;
        cout << "Enter Booking ID: "; cin >> id;
        cout << "[BST O(log n) Search]\n";
        userBST.search(id);
    }

    // ---------------------------------------------------------------
    //  UNDO  [Stack]
    // ---------------------------------------------------------------
    void undoBooking() {
        if (history.empty()) { cout << "Nothing to undo!\n"; return; }
        Event last = history.top(); history.pop();
        for (int i = 0; i < cnt; i++) {
            if (Events[i].EventNumber == last.EventNumber) {
                if (Events[i].info == 1)
                    userBST.remove(Events[i].usr.booking_id);
                Events[i] = last;
                cout << "Undo successful! Event#" << last.EventNumber << " restored.\n";
                return;
            }
        }
    }

    // ---------------------------------------------------------------
    //  REGISTRATION QUEUE  [Queue]
    // ---------------------------------------------------------------
    void showQueue() {
        queue<User> tmp = registrationQueue;
        cout << "\n--- Registration Queue (FIFO) ---\n";
        if (tmp.empty()) { cout << "Queue is empty.\n"; return; }
        int pos = 1;
        while (!tmp.empty()) {
            cout << pos++ << ". " << tmp.front().name
                 << "  |  Booking ID: " << tmp.front().booking_id << "\n";
            tmp.pop();
        }
    }

    // ---------------------------------------------------------------
    //  SHOW WAITLIST  [Feature C]
    // ---------------------------------------------------------------
    void showWaitlist() {
        queue< pair<int,User> > tmp = waitlistQueue;
        cout << "\n--- Waitlist Queue ---\n";
        if (tmp.empty()) { cout << "Waitlist is empty.\n"; return; }
        int pos = 1;
        while (!tmp.empty()) {
            cout << pos++ << ". Event#" << tmp.front().first
                 << "  | " << tmp.front().second.name
                 << "  | Booking ID: " << tmp.front().second.booking_id << "\n";
            tmp.pop();
        }
    }

    // ---------------------------------------------------------------
    //  NEXT EVENT  [MinHeap]
    // ---------------------------------------------------------------
    void nextEvent() {
        if (minHeap.empty()) { cout << "No scheduled events.\n"; return; }
        cout << "\n[MinHeap] Next shortest-duration event:\n";
        printEvent(minHeap.top());
    }

    // ---------------------------------------------------------------
    //  ALL HEAP CONTENTS
    // ---------------------------------------------------------------
    void showHeap() { minHeap.display(); }

    // ---------------------------------------------------------------
    //  SORT BY GUESTS  [QuickSort]
    // ---------------------------------------------------------------
    void sortByGuests() {
        if (cnt == 0) { cout << "No events to sort.\n"; return; }
        quickSort(Events, 0, cnt - 1);
        hashTable.rebuild(Events, cnt);
        cout << "\n[QuickSort] Events sorted by Guest count:\n";
        for (int i = 0; i < cnt; i++) printEvent(Events[i]);
    }

    // ---------------------------------------------------------------
    //  SORT BY DURATION  [MergeSort]
    // ---------------------------------------------------------------
    void sortByDuration() {
        if (cnt == 0) { cout << "No events to sort.\n"; return; }
        mergeSort(Events, 0, cnt - 1);
        hashTable.rebuild(Events, cnt);
        cout << "\n[MergeSort] Events sorted by Duration:\n";
        for (int i = 0; i < cnt; i++) printEvent(Events[i]);
    }

    // ---------------------------------------------------------------
    //  BINARY SEARCH
    // ---------------------------------------------------------------
    void binarySearchEvent() {
        int target;
        cout << "Enter Event Number to search: "; cin >> target;

        Event temp[MAX_EVENTS];
        int   tempCnt = cnt;
        for (int i = 0; i < cnt; i++) temp[i] = Events[i];
        sortByEventNum(temp, tempCnt);

        int idx = binarySearch(temp, tempCnt, target);
        if (idx == -1) cout << "Event#" << target << " not found.\n";
        else { cout << "[Binary Search] Event found:\n"; printEvent(temp[idx]); }
    }

    // ---------------------------------------------------------------
    //  SHOW HASH TABLE
    // ---------------------------------------------------------------
    void showHashTable() { hashTable.display(); }

    // ---------------------------------------------------------------
    //  SHOW AVL TREE
    // ---------------------------------------------------------------
    void showAVLTree() { avlTree.display(); }

    // ---------------------------------------------------------------
    //  SYSTEM REPORT
    // ---------------------------------------------------------------
    void systemReport() {
        int booked = 0, avail = 0;
        for (int i = 0; i < cnt; i++)
            Events[i].info == 1 ? booked++ : avail++;

        int availStaff = 0;
        for (int i = 0; i < staffCnt; i++)
            if (staffList[i].available) availStaff++;

        cout << "\n============ SYSTEM REPORT ============\n";
        cout << "  Total Events     : " << cnt                      << "\n";
        cout << "  Booked           : " << booked                   << "\n";
        cout << "  Available        : " << avail                    << "\n";
        cout << "  Queue Size       : " << registrationQueue.size() << "\n";
        cout << "  Waitlist Size    : " << waitlistQueue.size()     << "\n";
        cout << "  Undo Stack Depth : " << history.size()           << "\n";
        cout << "  Heap Size        : " << minHeap.size()           << "\n";
        cout << "  Total Staff      : " << staffCnt                 << "\n";
        cout << "  Available Staff  : " << availStaff               << "\n";
        avlTree.display();
        cout << "=======================================\n";
    }
};

// ================================================================
//  MAIN
// ================================================================
int main() {
    EventManager em;
    int opt;

    do {
        cout << "\n========== EVENT MANAGEMENT SYSTEM ==========\n";
        cout << "  1.  Add Event\n";
        cout << "  2.  Book Event\n";
        cout << "  3.  Show Available Events\n";
        cout << "  4.  Search by Name\n";
        cout << "  5.  Search by Booking ID          [BST]\n";
        cout << "  6.  Binary Search Event           [Binary Search]\n";
        cout << "  7.  Checkout & Generate Bill\n";
        cout << "  8.  Undo Last Booking             [Stack]\n";
        cout << "  9.  Registration Queue            [Queue]\n";
        cout << "  10. Next Scheduled Event          [MinHeap]\n";
        cout << "  11. All Scheduled Events          [Heap]\n";
        cout << "  12. Sort by Guests                [QuickSort]\n";
        cout << "  13. Sort by Duration              [MergeSort]\n";
        cout << "  14. Show Hash Table               [Hashing]\n";
        cout << "  15. Show AVL Tree                 [AVL]\n";
        cout << "  16. System Report\n";
        cout << "  --- NEW FEATURES ---\n";
        cout << "  17. Edit Event                    [Feature A]\n";
        cout << "  18. Cancel Booking (with Refund)  [Feature B]\n";
        cout << "  19. Join Waitlist                 [Feature C]\n";
        cout << "  20. Show Waitlist                 [Feature C]\n";
        cout << "  21. Check Venue Conflict          [Feature D]\n";
        cout << "  22. View All Bookings             [Feature E]\n";
        cout << "  23. Staff Management              [Feature F]\n";
        cout << "  24. Exit\n";
        cout << "==============================================\n";
        cout << "Choice: "; cin >> opt;

        switch(opt) {
            case  1: em.addEvent();           break;
            case  2: em.bookEvent();          break;
            case  3: em.showAvailable();      break;
            case  4: em.searchByName();       break;
            case  5: em.searchByBookingID();  break;
            case  6: em.binarySearchEvent();  break;
            case  7: em.checkOut();           break;
            case  8: em.undoBooking();        break;
            case  9: em.showQueue();          break;
            case 10: em.nextEvent();          break;
            case 11: em.showHeap();           break;
            case 12: em.sortByGuests();       break;
            case 13: em.sortByDuration();     break;
            case 14: em.showHashTable();      break;
            case 15: em.showAVLTree();        break;
            case 16: em.systemReport();       break;
            case 17: em.editEvent();          break;
            case 18: em.cancelBooking();      break;
            case 19: em.joinWaitlist();       break;
            case 20: em.showWaitlist();       break;
            case 21: em.checkVenueConflict(); break;
            case 22: em.viewAllBookings();    break;
            case 23: em.staffMenu();          break;
            case 24: cout << "Goodbye!\n";    break;
            default: cout << "Invalid option!\n";
        }

    } while (opt != 24);

    return 0;
}
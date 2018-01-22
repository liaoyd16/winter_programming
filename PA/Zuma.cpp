
#include <assert.h>
#include <random>
#include <cstdio>
#include <cstdlib>

// #define MAXN 7000000
#define MAXN 50
#define MAXH 4
// #define P_1 2
#define __min(a, b) (((a)<(b)?(a):(b)))

class SList;

struct quadNode {
    friend class SList;
private:
    char val;
    int step;
    int pred, succ, up, bot;
public:
    quadNode(int init = -1) : step(init) {
        pred = succ = up = bot = -1;
    }
    void print() {
        printf("<%d=%c>", step, val);
    }
} pool[MAXN];

class SList {
    static quadNode* get_n_node(int n, char c = '\0') {
        quadNode *top = addr(pool[0].bot), *cut = top;
        for (int i = 1; i <= n; ++i) {
            cut->val = c;
            cut = addr(cut->bot);
        }
        pool[0].bot = SList::rank(cut); top->up = -1;
        pool[cut->up].bot = -1;  cut->up = 0;
        return top;
    }
    static void return_n_node(quadNode* node) {
        
        quadNode *top = node;
        while(addr(top->bot)) {
            top->pred = top->succ =  -1;
            top = addr(top->bot);
        }
        top->pred = top->succ = -1;
        
        quadNode *cut = addr(pool[0].bot);
        cut->up = rank(node);
        node->bot = rank(cut);
        top->up = 0;
        addr(0)->bot = rank(top);
    }
    static void connect(quadNode* node, quadNode *left, quadNode *right) {
        node->pred = rank(left);
        node->succ = rank(right);
        left->succ = rank(node);
        right->pred = rank(node);
    }
    static void connect(quadNode *pred, quadNode *succ) {
        pred->succ = rank(succ);
        succ->pred = rank(pred);
    }
    inline static int rank(quadNode* node) { return node-&pool[0]; }
    inline static quadNode* addr(int rank) { return rank>=0 ? &pool[rank] : NULL; }
    
    static quadNode* toBottom(quadNode* node) {
        quadNode* ans = node;
        while(ans->bot > 0) ans = &pool[ans->bot];
        return ans;
    }
    static quadNode* find_upper_pred(quadNode* node, int& leftstep);
    static quadNode* find_upper_succ(quadNode* node, int& rightstep);
    static void update_steps(quadNode* newly);
    static void elim_from(quadNode* mid);
    static void elim_segment(quadNode* prev, quadNode* next);
    static void print_tower(quadNode* qnode) {
        for(; qnode; qnode = addr(qnode->up)) {
            qnode->print();
            printf("\n");
        }
        printf("\n");
    }
    
    // private:
public:
    quadNode *header, *trailer;
    quadNode *hit;
    void search(int key);
public:
    SList();
    void insert(int rank, char bead);
    // bool report();
    void print();
} skiplist;

int main() {
    //test SList:
    //initial integrity
    skiplist.print(); printf("\n");
    
    //search
    //printf("search: "); skiplist.search(10);
    //skiplist.hit->print(); printf("\n");
    
    //trivial insertion
    // skiplist.insert(1, 'A');
    // skiplist.print();
    // skiplist.insert(0, 'A');
    // skiplist.print();
    // skiplist.insert(2, 'B');
    // skiplist.print();
    // skiplist.insert(3, 'A');
    // skiplist.print();
    
    //nontrivial
    /*
     ACCBA
     5
     1 B
     0 A
     2 B
     4 C
     0 A
     
     ABCCBA
     AABCCBA
     AABBCCBA
     -
     A
     */
    
    skiplist.insert(0, 'A');
    skiplist.print(); printf("\n");
    skiplist.insert(1, 'C');
    skiplist.print(); printf("\n");
    skiplist.insert(2, 'C');
    skiplist.print(); printf("\n");
    skiplist.insert(3, 'B');
    skiplist.print(); printf("\n");
    skiplist.insert(4, 'A');
    skiplist.print(); printf("\n");
    
    skiplist.insert(1, 'B');
    skiplist.print(); printf("\n");
    skiplist.insert(0, 'A');
    skiplist.print(); printf("\n");
    skiplist.insert(2, 'B');
    skiplist.print(); printf("\n");
    skiplist.insert(4, 'C');
    skiplist.print(); printf("\n");
    skiplist.insert(0, 'A');
    skiplist.print(); printf("\n");
    
    return 0;
}

std::knuth_b generator;
std::geometric_distribution<int> distribution(0.5);
int georand() {
    int ans = -1;
    srand((unsigned)clock());
    generator.seed(rand()%10000);
    ans = distribution(generator)+1;
    return __min(ans, MAXH);
}


void SList::elim_segment(quadNode* prev, quadNode* next) {
    quadNode* run = addr(prev->succ), *tgt = run;
    
    while(run!=next) {
        run = addr(run->succ);
        return_n_node(tgt);
        tgt = run;
    }
    
    int leftstep = 0, rightstep = 1;
    for (; prev && next; prev = find_upper_pred(prev, leftstep),
         next = find_upper_succ(next, rightstep)) {
        //connect
        connect(prev, next);
        //update step
        prev->step = rightstep + leftstep;
    }
}

void SList::elim_from(quadNode* bottom) {
    quadNode* prev, *next;
    while(true) {
        prev = addr(bottom->pred), next = addr(bottom->succ);
        int cnt = 1;
        while(prev>0 && prev->val==bottom->val) {
            prev = addr(prev->pred);
            cnt ++;
        }
        while(next>0 && next->val==bottom->val) {
            next = addr(next->succ);
            cnt ++;
        }
        if(cnt >= 3) {
            elim_segment(prev, next);
            bottom = next;
        }
        else break;
    }
}

quadNode* SList::find_upper_pred(quadNode* curr_pred, int& leftstep) {
    while(curr_pred->up < 0) {
        leftstep += curr_pred->step;
        curr_pred = addr(curr_pred->pred);
        if(!curr_pred) return NULL;
    }
    return addr(curr_pred->up);
}

quadNode* SList::find_upper_succ(quadNode* curr_succ, int& rightstep) {
    while(curr_succ->up < 0) {
        curr_succ = addr(curr_succ->succ);
        rightstep += curr_succ->step;
        // assert(curr_succ);
        if(!curr_succ) return NULL;
    }
    return addr(curr_succ->up);
}

void SList::insert(int rank, char bead) {
    search(rank);
    
    quadNode *back = toBottom(hit), *front = addr(back->pred);
    
    //randomize height
    int h = georand();
    //new tower
    quadNode *bottom = toBottom(get_n_node(h, bead)), *runup = bottom;
    
    int leftstep = 1, rightstep = 1;
    for (; runup; runup = addr(runup->up)) {
        connect(runup, front, back); //connect
        
        front->step = leftstep;
        runup->step = rightstep;
        // if(runup->up > 0) {			 //upgrade front & back
        front = find_upper_pred(front, leftstep);
        back = find_upper_succ(back, rightstep);
        // }
    }
    int dummy;
    for(; front; front = find_upper_pred(front, dummy)) {
        front->step ++;
    }
    
    elim_from(bottom);
    return;
}

void SList::search(int rank) {
    int cnt = -1;
    hit = header;
    while(cnt < rank) {
        if(cnt + hit->step > rank) {
            if(hit->bot < 0) {
                hit = addr(hit->succ);
                break;
            }
            else hit = addr(hit->bot);
        } else {
            cnt += hit->step;
            hit = addr(hit->succ);
        }
    }
}

SList::SList() {
    //unused structure
    pool[0].bot = 1;
    pool[MAXN-1].up = MAXN - 2;
    for (int i = 1; i < MAXN-1; ++i) {
        pool[i].up = i-1;
        pool[i].bot = i+1;
    }
    
    //skiplist skel.
    header = get_n_node(MAXH);
    trailer = get_n_node(MAXH);
    
    ////
    int j = 0;
    for (quadNode* r = header, *p = trailer; r&&p ; r = addr(r->bot), p = addr(p->bot)) {
        r->val = '0'+j;
        p->val = '0'+j++;
    }
    ////
    
    quadNode *front = header, *back = trailer;
    front->step = 1, back->step = 0;
    for (int i = 1; i <= MAXH; ++i, 
         front = addr(front->bot), back = addr(back->bot))
    {
        front->succ = rank(back); back->pred = rank(front);
        front->step = 1;  back->step = 0;
    }
}

void SList::print() {
    //skiplist:
    for (quadNode *bottom = toBottom(header); bottom; bottom = addr(bottom->succ)) {
        for (quadNode* vert = bottom; vert; vert = addr(vert->up)) {
            vert->print();
        } printf("\n");
    }
}

struct intNode {
	int _data;
	intNode* succ;
	intNode(int data_) : _data(data_) {
		succ = nullptr;
	}
};

int atoi(char *a, int alen);

struct Long {
private:
	bool _sign;
	intNode _radix, *last;
	int _len;
public:
	static void copy_list(intNode& dest, const intNode& src);
	static void connect(intNode* pred, intNode* succ) { pred->succ = succ; }

public:
	Long(char *longchar) { //每9个10进制位压到一个intNode中
		int len = strlen(longchar);
		int segment;
		for(int end = len-1; end >= 0; end -= 9) {
			segment = 0;
			//every 9 digits: [len-9/0, len-1]
			for(int dgt = 0; dgt < 9; dgt ++) {
				segment += int(longchar[end-dgt]-'0') * pow_10(dgt ++);
			}
			connect(last = last->succ, new intNode(segment));
		}
	}
	Long(const Long& rhs) {
		this->_sign = rhs->_sign;
		copy_list(rhs._radix, this->_radix);
	}
	~Long() {
		intNode *run = radix.succ, *pred;
		while(run) {
			pred = run;
			run = run->succ;
			delete pred;
		}
	}
	Long& operator+ (const Long& rhs) {

	}
	Long& operator- (const Long& rhs);
	Long& operator* (const Long& rhs);

};
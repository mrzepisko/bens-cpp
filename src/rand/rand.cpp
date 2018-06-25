#include <iostream>

#define DBG true

namespace rnd {
    struct TestResults;

    class LCG {
        private:
            int _increment;
            int _multiplier;
            int _seed;
            int _modulus;
        public:
            LCG(int m, int a, int c, int s) :
                _increment(c),
                _multiplier(a),
                _modulus(m),
                _seed(s) {}

            int next() {
                int rtrn = _seed;
                _seed = (_multiplier * _seed + _increment) % _modulus;
                return rtrn;
            }
    };

    class LCGTester {
        private:
            static int min(int x, int y);
            static int max(int x, int y);
        public:
            static TestResults test(LCG lcg);
            
    };

    struct TestResults {
        public:    
            int min;
            int max;
            int periodLength;

            TestResults() { }
            TestResults(int mn, int mx, int pl) 
                : min(mn), max(mx), periodLength(pl) { }

            void print() {
                std::cout << "Result:"
                    << "\n\tlength:\t" << periodLength
                    << "\n\tmin:\t" << min
                    << "\n\tmax:\t" << max
                    << std::endl;
            }
    };
}

int main() {
    int m = 1024 *128 ;    //modulus
    int a = 13;      //multiplier
    int c = 7;      //increment
    int s = 1;      //seed

    rnd::LCG lcg(m, a, c, s);
    rnd::TestResults test = rnd::LCGTester::test(lcg);
    test.print();
    return 0;
}

rnd::TestResults rnd::LCGTester::test(rnd::LCG lcg) {
#if DBG
    char chr[5] = { '|', '/', '-', '\\', }; 
#endif
    int steps = 0;
    int first = lcg.next();
    int min = first;
    int max = first;
    int current;
    do {
        current = lcg.next();
        min = rnd::LCGTester::min(min, current);
        max = rnd::LCGTester::max(max, current);
        steps++;
#if DBG
        std::cout << "Processing " << chr[steps % 5] << "                     " << "\r";
        std::cout.flush();
#endif
    } while (first != current);
#if DBG
    std::cout << "                                                     \r";
    std::cout.flush();
#endif
    return TestResults(min, max, steps);
}

int rnd::LCGTester::min(int x, int y) {
    return x > y ? y : x;
}

int rnd::LCGTester::max(int x, int y) {
    return x > y ? x : y;
}

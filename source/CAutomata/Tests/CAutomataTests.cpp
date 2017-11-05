//
// Created by qua on 05.11.17.
//

#include "CAutomataTests.h"

namespace CAutomataTests {

// tests for '1'
    void runTest1() {

        std::cout << "Running tests on:\n";
        std::cout << "tests for '1'\n";
        std::cout << "'''''''''''''''''''''''''''''''''''\n";

        CAutomata whatever0('1');
        whatever0.PrintAutomata();

    }

// tests for '+'
// regular expression: "a+b+c"
// regular exp in RPN: "ab+c+"
    void runTest2() {

        std::cout << "Running tests on:\n";
        std::cout << "tests for '+'\n";
        std::cout << "regular expression: \"a+b+c\"\n";
        std::cout << "regular exp in RPN: \"ab+c+\"\n";
        std::cout << "'''''''''''''''''''''''''''''''''''\n";

        CAutomata whatever0('a');;
        whatever0.PrintAutomata();

        CAutomata whatever1('b');
        whatever1.PrintAutomata();

        CAutomata whatever2(&whatever0, &whatever1, '+');
        whatever2.PrintAutomata();

        CAutomata whatever3('c');
        whatever3.PrintAutomata();

        CAutomata whatever4(&whatever2, &whatever3, '+');
        whatever4.PrintAutomata();

    }

// tests for '.'
// regular expression: "a.b.c"
// regular exp in RPN: "ab.c."
    void runTest3() {

        std::cout << "Running tests on:\n";
        std::cout << "tests for '.'\n";
        std::cout << "regular expression: \"a.b.c\"\n";
        std::cout << "regular exp in RPN: \"ab.c.\"\n";
        std::cout << "'''''''''''''''''''''''''''''''''''\n";

        CAutomata whatever0('a');
        whatever0.PrintAutomata();

        CAutomata whatever1('b');
        whatever1.PrintAutomata();

        CAutomata whatever2(&whatever0, &whatever1, '.');
        whatever2.PrintAutomata();

        CAutomata whatever3('c');
        whatever3.PrintAutomata();

        CAutomata whatever4(&whatever2, &whatever3, '.');
        whatever4.PrintAutomata();
    }

// tests for '+ . +'
// regular expression: "(a+b).c+a"
// regular exp in RPN: "ab+c.a+"
    void runTest4() {

        std::cout << "Running tests on:\n";
        std::cout << "tests for '+ . +'\n";
        std::cout << "regular expression: \"(a+b).c+a\"\n";
        std::cout << "regular exp in RPN: \"ab+c.a+\"\n";
        std::cout << "'''''''''''''''''''''''''''''''''''\n";

        CAutomata whatever0('a');
        whatever0.PrintAutomata();

        CAutomata whatever1('b');
        whatever1.PrintAutomata();

        CAutomata whatever2(&whatever0, &whatever1, '+');
        whatever2.PrintAutomata();

        CAutomata whatever3('c');
        whatever3.PrintAutomata();

        CAutomata whatever4(&whatever2, &whatever3, '.');
        whatever4.PrintAutomata();

        CAutomata whatever5('a');
        whatever5.PrintAutomata();

        CAutomata whatever6(&whatever4, &whatever5, '+');
        whatever6.PrintAutomata();

    }

// tests for '*'
// regular expression: "a*"
// regular exp in RPN: "a*"
    void runTest5() {

        std::cout << "Running tests on:\n";
        std::cout << "tests for '*'\n";
        std::cout << "regular expression: \"a*\"\n";
        std::cout << "regular exp in RPN: \"a*\"\n";
        std::cout << "'''''''''''''''''''''''''''''''''''\n";

        CAutomata whatever0('a');
        whatever0.PrintAutomata();

        CAutomata whatever1(&whatever0, '*');
        whatever1.PrintAutomata();

    }

// tests for '+ . *'
// regular expression: "((a+b).c)*"
// regular exp in RPN: "ab+c.*"
    void runTest6() {

        std::cout << "Running tests on:\n";
        std::cout << "tests for '+ . +'\n";
        std::cout << "regular expression: \"((a+b).c)*\"\n";
        std::cout << "regular exp in RPN: \"ab+c.*\"\n";
        std::cout << "'''''''''''''''''''''''''''''''''''\n";

        CAutomata whatever0('a');
        whatever0.PrintAutomata();

        CAutomata whatever1('b');
        whatever1.PrintAutomata();

        CAutomata whatever2(&whatever0, &whatever1, '+');
        whatever2.PrintAutomata();

        CAutomata whatever3('c');
        whatever3.PrintAutomata();

        CAutomata whatever4(&whatever2, &whatever3, '.');
        whatever4.PrintAutomata();

        CAutomata whatever6(&whatever4, '*');
        whatever6.PrintAutomata();

    }

    void runTests() {

        bool on = true;

        while (on) {
            std::cout << "\n\n";
            int option;
            std::cin >> option;
            switch (option) {
                case -1: {
                    std::cout << "\n1 for '1'";
                    std::cout << "\n2 for '+'";
                    std::cout << "\n3 for '.'";
                    std::cout << "\n4 for '+ . +'";
                    std::cout << "\n5 for '*'";
                    std::cout << "\n6 for '+ . *'";
                    break;
                }
                case 0: {
                    for (int i = 0; i < 4; ++i) std::cout << "\n\n\n\n";
                    break;
                }
                case 1: {
                    runTest1();
                    break;
                }
                case 2: {
                    runTest2();
                    break;
                }
                case 3: {
                    runTest3();
                    break;
                }
                case 4: {
                    runTest4();
                    break;
                }
                case 5: {
                    runTest5();
                    break;
                }
                case 6: {
                    runTest6();
                    break;
                }
                default: {
                    on = false;
                }
            }
        }
    }
}

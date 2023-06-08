#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>
using namespace std;

const int nclas = 2; // Максимальна кількість уроків на день
const int nday = 5; // Кількість днів в тижні
const int nlesson = 5; // Максимальна кількість уроків на день
const int nsubject = 6; // Кількість різних уроків
const int nteacher = 6; // Кількість різних вчителів

struct slesson {
    int subject;
    int teacher;
};
struct sday {
    slesson lesson[nlesson];
};
struct sclas {
    sday day[nday];
};
struct srozclad {
    sclas clas[nclas];
};

srozclad getrandomrozclad() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> randsubject(0, nsubject);
    uniform_int_distribution<> randteacher(0, nteacher);
    srozclad randomrozclad;
    for (int i = 0; i < nclas; ++i) {
        for (int j = 0; j < nday; ++j) {
            for (int z = 0; z < nlesson; ++z) {
                randomrozclad.clas[i].day[j].lesson[z].subject = randsubject(gen);
                randomrozclad.clas[i].day[j].lesson[z].teacher = randteacher(gen);
            }
        }
    }
    return randomrozclad;
}

int check(srozclad& rozclad) {
    int check = 0;
    for (int j = 0; j < nday; ++j) {
        for (int z = 0; z < nlesson; ++z) {
            if (rozclad.clas[0].day[j].lesson[z].subject == rozclad.clas[1].day[j].lesson[z].subject) {
                check++;
            }
            if (rozclad.clas[0].day[j].lesson[z].teacher == rozclad.clas[1].day[j].lesson[z].teacher) {
                check++;
            }
        }
    }
    return check;
}

srozclad marge(srozclad& gen1, srozclad& gen2) {
    srozclad marged;
    for (int i = 0; i < nclas; ++i) {
        for (int j = 0; j < nday; ++j) {
            for (int z = 0; z < nlesson; ++z) {
                marged.clas[i].day[j].lesson[z].subject = gen1.clas[i].day[j].lesson[z].subject;
                marged.clas[i].day[j].lesson[z].teacher = gen2.clas[i].day[j].lesson[z].teacher;
            }
        }
    }
    return marged;
}

srozclad set(srozclad& rozclad) {
    srozclad setrozclad;
    for (int i = 0; i < nclas; ++i) {
        for (int j = 0; j < nday; ++j) {
            for (int z = 0; z < nlesson; ++z) {
                setrozclad.clas[i].day[j].lesson[z].subject = rozclad.clas[i].day[j].lesson[z].subject;
                setrozclad.clas[i].day[j].lesson[z].teacher = rozclad.clas[i].day[j].lesson[z].teacher;
            }
        }
    }
    return setrozclad;
}

srozclad getoptimalrozclad() {
    srozclad optimalrozclad = getrandomrozclad();
    bool optimized = false;
    const int ngen = 100;
    const int nelit = ngen / 2;
    srozclad gen[ngen];
    srozclad elite[nelit];
    for (int i = 0; i < ngen; i++) {
        gen[i] = getrandomrozclad();
    }
    for (int i = 0; i < ngen; i++) {
        if (check(gen[i]) == 0) {
            optimized = true;
            optimalrozclad = set(gen[i]);
        }
    }
    //int generations = 1000;
    //for (int i = 0; i < generations; i++) {
    while (optimized == false) {
        for (int i = 0; i < ngen / 2; i++) {
            if (check(gen[i]) < check(gen[ngen - i - 1])) {
                elite[i] = set(gen[i]);
            }
            else {
                elite[i] = set(gen[ngen - i - 1]);
            }
        }
        for (int i = 0; i < ngen / 2; i += 2) {
            gen[i] = marge(elite[i], elite[i + 1]);
            gen[i + 1] = marge(elite[i + 1], elite[i]);
        }
        for (int i = 0; i < ngen / 2; i++) {
            gen[ngen - i - 1] = getrandomrozclad();
        }
        for (int i = 0; i < ngen; i++) {
            if (check(gen[i]) == 0) {
                optimized = true;
                optimalrozclad = set(gen[i]);
            }
        }
        /*for (int i = 0; i < ngen; i++) {
            if (check(optimalrozclad) > check(gen[i])) {
                optimalrozclad = set(gen[i]);
            }
        }*/
    }
    return optimalrozclad;
}

void printrozclad(srozclad& rozclad) {
    for (int i = 0; i < nclas; ++i) {
        cout << " clas " << i + 1 << endl;
        for (int j = 0; j < nday; ++j) {
            cout << " day " << j + 1 << endl;
            for (int z = 0; z < nlesson; ++z) {
                cout << " lesson " << z + 1 << " - subject " << rozclad.clas[i].day[j].lesson[z].subject + 1 << " in class " << rozclad.clas[i].day[j].lesson[z].subject + 1 << " - teacher " << rozclad.clas[i].day[j].lesson[z].teacher + 1 << endl;
            }
        }
    }
}

int main() {

    srozclad optimalrozclad = getoptimalrozclad();

    printrozclad(optimalrozclad);

    return 0;
}
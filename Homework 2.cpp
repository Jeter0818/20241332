#include <iostream>
#include <cmath>
using namespace std;

class Term {
    friend class Polynomial;
    float coef; 
    int exp;    

public:
    Term() : coef(0), exp(0) {}

    Term(float c, int e) : coef(c), exp(e) {}

    float getCoef() const { return coef; }
    int getExp() const { return exp; }

    void setCoef(float c) { coef = c; }
    void setExp(int e) { exp = e; }
};

class Polynomial {
public:
    Polynomial();              
    ~Polynomial();            
    Polynomial Add(const Polynomial& poly) const;  
    Polynomial Mult(const Polynomial& poly) const; 
    float Eval(float x) const; 

     
    friend istream& operator>>(istream& in, Polynomial& poly);
    friend ostream& operator<<(ostream& out, const Polynomial& poly);

private:
    Term* termArray;  
    int capacity;     
    int terms;        

    void EnsureCapacity(int newCapacity);  
};
 
Polynomial::Polynomial() : termArray(new Term[10]), capacity(10), terms(0) {}

Polynomial::~Polynomial() {
    delete[] termArray;
}

void Polynomial::EnsureCapacity(int newCapacity) {
    if (newCapacity > capacity) {
        Term* newArray = new Term[newCapacity];
        for (int i = 0; i < terms; i++) {
            newArray[i] = termArray[i];
        }
        delete[] termArray;
        termArray = newArray;
        capacity = newCapacity;
    }
}

Polynomial Polynomial::Add(const Polynomial& poly) const {
    Polynomial result;
    result.EnsureCapacity(terms + poly.terms);

    int i = 0, j = 0;
    while (i < terms && j < poly.terms) {
        if (termArray[i].getExp() == poly.termArray[j].getExp()) {
            float sumCoef = termArray[i].getCoef() + poly.termArray[j].getCoef();
            if (sumCoef != 0) {
                result.termArray[result.terms++] = Term(sumCoef, termArray[i].getExp());
            }
            i++;
            j++;
        }
        else if (termArray[i].getExp() > poly.termArray[j].getExp()) {
            result.termArray[result.terms++] = termArray[i];
            i++;
        }
        else {
            result.termArray[result.terms++] = poly.termArray[j];
            j++;
        }
    }

    while (i < terms) {
        result.termArray[result.terms++] = termArray[i++];
    }
    while (j < poly.terms) {
        result.termArray[result.terms++] = poly.termArray[j++];
    }

    return result;
}

Polynomial Polynomial::Mult(const Polynomial& poly) const {
    Polynomial result;

    for (int i = 0; i < terms; i++) {
        for (int j = 0; j < poly.terms; j++) {
            float coef = termArray[i].getCoef() * poly.termArray[j].getCoef();
            int exp = termArray[i].getExp() + poly.termArray[j].getExp();

            bool found = false;
            for (int k = 0; k < result.terms; k++) {
                if (result.termArray[k].getExp() == exp) {
                    result.termArray[k].setCoef(result.termArray[k].getCoef() + coef);
                    found = true;
                    break;
                }
            }

            if (!found) {
                result.EnsureCapacity(result.terms + 1);
                result.termArray[result.terms++] = Term(coef, exp);
            }
        }
    }

    return result;
}

float Polynomial::Eval(float x) const {
    float result = 0;
    for (int i = 0; i < terms; i++) {
        result += termArray[i].getCoef() * pow(x, termArray[i].getExp());
    }
    return result;
}

istream& operator>>(istream& in, Polynomial& poly) {
    cout << "�п�J�D�s�����ƶq�G";
    in >> poly.terms;

    poly.EnsureCapacity(poly.terms);
    for (int i = 0; i < poly.terms; i++) {
        float coef;
        int exp;
        cout << "�п�J�� " << i + 1 << " �����Y�ƻP���ơ]�H�Ů���j�^�G";
        in >> coef >> exp;
        poly.termArray[i] = Term(coef, exp);
    }
    return in;
}

ostream& operator<<(ostream& out, const Polynomial& poly) {
    for (int i = 0; i < poly.terms; i++) {
        if (i > 0 && poly.termArray[i].getCoef() > 0) out << " + ";
        out << poly.termArray[i].getCoef() << "x^" << poly.termArray[i].getExp();
    }
    return out;
}

int main() {
    Polynomial p1, p2;

    cout << "��J�Ĥ@�Ӧh�����G" << endl;
    cin >> p1;
    cout << "��J�ĤG�Ӧh�����G" << endl;
    cin >> p2;

    Polynomial sum = p1.Add(p2);
    Polynomial product = p1.Mult(p2);

    cout << "�Ĥ@�Ӧh�������G" << p1 << endl;
    cout << "�ĤG�Ӧh�������G" << p2 << endl;
    cout << "��Ӧh�������M���G" << sum << endl;
    cout << "��Ӧh�������n���G" << product << endl;

    float x;
    cout << "�п�J���D�Ȫ� x�G";
    cin >> x;

    cout << "�Ĥ@�Ӧh�����b x = " << x << " ���Ȭ��G" << p1.Eval(x) << endl;
    cout << "�ĤG�Ӧh�����b x = " << x << " ���Ȭ��G" << p2.Eval(x) << endl;

    return 0;
}

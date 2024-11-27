#include <iostream>
#include <cmath>
using namespace std;

// Term ���O
class Term {
    friend class Polynomial; // �� Polynomial �i�H�X�� Term ���p������
private:
    float coef; // �Y��
    int exp;    // ����

public:
    // �w�]�غc�禡
    Term() : coef(0), exp(0) {}

    // �ۭq�غc�禡
    Term(float c, int e) : coef(c), exp(e) {}

    // Getter ��k
    float getCoef() const { return coef; }
    int getExp() const { return exp; }

    // Setter ��k
    void setCoef(float c) { coef = c; }
    void setExp(int e) { exp = e; }
};

// Polynomial ���O
class Polynomial {
public:
    Polynomial();              // �w�]�غc�l
    ~Polynomial();             // �Ѻc�l
    Polynomial Add(const Polynomial& poly) const;  // �h�����ۥ[
    Polynomial Mult(const Polynomial& poly) const; // �h�����ۭ�
    float Eval(float x) const; // �h�����D��

    // �B��l�h��
    friend istream& operator>>(istream& in, Polynomial& poly);
    friend ostream& operator<<(ostream& out, const Polynomial& poly);

private:
    Term* termArray; // �x�s�D�s�����ʺA�}�C
    int capacity;    // �ʺA�}�C���e�q
    int terms;       // �D�s�����ƶq

    void EnsureCapacity(int newCapacity); // �T�O�ʺA�}�C���e�q����
};

// �w�]�غc�l
Polynomial::Polynomial() : termArray(new Term[10]), capacity(10), terms(0) {}

// �Ѻc�l
Polynomial::~Polynomial() {
    delete[] termArray;
}

// �T�O�e�q����
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

// �h�����ۥ[
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

// �h�����ۭ�
Polynomial Polynomial::Mult(const Polynomial& poly) const {
    Polynomial result;

    for (int i = 0; i < terms; i++) {
        for (int j = 0; j < poly.terms; j++) {
            float coef = termArray[i].getCoef() * poly.termArray[j].getCoef();
            int exp = termArray[i].getExp() + poly.termArray[j].getExp();

            // ��M�O�_�w���ۦP������
            bool found = false;
            for (int k = 0; k < result.terms; k++) {
                if (result.termArray[k].getExp() == exp) {
                    result.termArray[k].setCoef(result.termArray[k].getCoef() + coef);
                    found = true;
                    break;
                }
            }

            // �Y�S���ۦP���ƪ����A�s�W�@��
            if (!found) {
                result.EnsureCapacity(result.terms + 1);
                result.termArray[result.terms++] = Term(coef, exp);
            }
        }
    }

    return result;
}

// �h�����D��
float Polynomial::Eval(float x) const {
    float result = 0;
    for (int i = 0; i < terms; i++) {
        result += termArray[i].getCoef() * pow(x, termArray[i].getExp());
    }
    return result;
}

// ��J�B��l�h��
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

// ��X�B��l�h��
ostream& operator<<(ostream& out, const Polynomial& poly) {
    for (int i = 0; i < poly.terms; i++) {
        if (i > 0 && poly.termArray[i].getCoef() > 0) out << " + ";
        out << poly.termArray[i].getCoef() << "x^" << poly.termArray[i].getExp();
    }
    return out;
}

// �D�{������
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

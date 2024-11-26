#include <iostream>
#include <vector>
#include <cmath> // �Ω� pow ���

using namespace std;

// �N�y���O
class Term {
    friend class Polynomial;

private:
    float coef; // �Y��
    int exp;    // ����
};

// �h�������O
class Polynomial {
public:
    Polynomial();                            // �w�]�غc�l
    Polynomial Add(const Polynomial& poly); // �h�����ۥ[
    Polynomial Mult(const Polynomial& poly);// �h�����ۭ�
    float Eval(float x);                     // �h�����D��

    // ��J�P��X�B��l�h��
    friend istream& operator>>(istream& in, Polynomial& poly);
    friend ostream& operator<<(ostream& out, const Polynomial& poly);

private:
    vector<Term> termArray; // �x�s�D�s�����V�q
    int terms;              // �D�s���ƶq
};

// �w�]�غc�l
Polynomial::Polynomial() : terms(0) {}

// �h�����ۥ[
Polynomial Polynomial::Add(const Polynomial& poly) {
    Polynomial result;
    int i = 0, j = 0;

    while (i < terms && j < poly.terms) {
        if (termArray[i].exp == poly.termArray[j].exp) {
            float sum = termArray[i].coef + poly.termArray[j].coef;
            if (sum != 0) {
                result.termArray.push_back({ sum, termArray[i].exp });
            }
            i++;
            j++;
        }
        else if (termArray[i].exp > poly.termArray[j].exp) {
            result.termArray.push_back(termArray[i++]);
        }
        else {
            result.termArray.push_back(poly.termArray[j++]);
        }
    }

    // �B�z�Ѿl��
    while (i < terms) result.termArray.push_back(termArray[i++]);
    while (j < poly.terms) result.termArray.push_back(poly.termArray[j++]);

    result.terms = result.termArray.size();
    return result;
}

// �h�����ۭ�
Polynomial Polynomial::Mult(const Polynomial& poly) {
    Polynomial result;

    for (int i = 0; i < terms; ++i) {
        for (int j = 0; j < poly.terms; ++j) {
            float coef = termArray[i].coef * poly.termArray[j].coef;
            int exp = termArray[i].exp + poly.termArray[j].exp;

            // �N���G�����J���G�h������
            bool merged = false;
            for (auto& term : result.termArray) {
                if (term.exp == exp) {
                    term.coef += coef;
                    merged = true;
                    break;
                }
            }

            if (!merged) {
                result.termArray.push_back({ coef, exp });
            }
        }
    }

    result.terms = result.termArray.size();
    return result;
}

// �h�����D��
float Polynomial::Eval(float x) {
    float result = 0;
    for (const auto& term : termArray) {
        result += term.coef * pow(x, term.exp);
    }
    return result;
}

// ��J�B��l�h��
istream& operator>>(istream& in, Polynomial& poly) {
    int n;
    cout << "�п�J���ơG";
    in >> n;

    poly.termArray.clear();
    poly.terms = n;

    for (int i = 0; i < n; ++i) {
        Term term;
        cout << "��J�Y�ƻP���ơG";
        in >> term.coef >> term.exp;
        poly.termArray.push_back(term);
    }

    return in;
}

// ��X�B��l�h��
ostream& operator<<(ostream& out, const Polynomial& poly) {
    for (int i = 0; i < poly.terms; ++i) {
        if (i > 0 && poly.termArray[i].coef > 0) out << " + ";
        out << poly.termArray[i].coef << "x^" << poly.termArray[i].exp;
    }
    return out;
}
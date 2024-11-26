#include <iostream>
#include <vector>
#include <cmath> // 用於 pow 函數

using namespace std;

// 術語類別
class Term {
    friend class Polynomial;

private:
    float coef; // 係數
    int exp;    // 指數
};

// 多項式類別
class Polynomial {
public:
    Polynomial();                            // 預設建構子
    Polynomial Add(const Polynomial& poly); // 多項式相加
    Polynomial Mult(const Polynomial& poly);// 多項式相乘
    float Eval(float x);                     // 多項式求值

    // 輸入與輸出運算子多載
    friend istream& operator>>(istream& in, Polynomial& poly);
    friend ostream& operator<<(ostream& out, const Polynomial& poly);

private:
    vector<Term> termArray; // 儲存非零項的向量
    int terms;              // 非零項數量
};

// 預設建構子
Polynomial::Polynomial() : terms(0) {}

// 多項式相加
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

    // 處理剩餘項
    while (i < terms) result.termArray.push_back(termArray[i++]);
    while (j < poly.terms) result.termArray.push_back(poly.termArray[j++]);

    result.terms = result.termArray.size();
    return result;
}

// 多項式相乘
Polynomial Polynomial::Mult(const Polynomial& poly) {
    Polynomial result;

    for (int i = 0; i < terms; ++i) {
        for (int j = 0; j < poly.terms; ++j) {
            float coef = termArray[i].coef * poly.termArray[j].coef;
            int exp = termArray[i].exp + poly.termArray[j].exp;

            // 將結果項插入結果多項式中
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

// 多項式求值
float Polynomial::Eval(float x) {
    float result = 0;
    for (const auto& term : termArray) {
        result += term.coef * pow(x, term.exp);
    }
    return result;
}

// 輸入運算子多載
istream& operator>>(istream& in, Polynomial& poly) {
    int n;
    cout << "請輸入項數：";
    in >> n;

    poly.termArray.clear();
    poly.terms = n;

    for (int i = 0; i < n; ++i) {
        Term term;
        cout << "輸入係數與指數：";
        in >> term.coef >> term.exp;
        poly.termArray.push_back(term);
    }

    return in;
}

// 輸出運算子多載
ostream& operator<<(ostream& out, const Polynomial& poly) {
    for (int i = 0; i < poly.terms; ++i) {
        if (i > 0 && poly.termArray[i].coef > 0) out << " + ";
        out << poly.termArray[i].coef << "x^" << poly.termArray[i].exp;
    }
    return out;
}
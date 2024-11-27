#include <iostream>
#include <cmath>
using namespace std;

// Term 類別
class Term {
    friend class Polynomial; // 讓 Polynomial 可以訪問 Term 的私有成員
private:
    float coef; // 係數
    int exp;    // 指數

public:
    // 預設建構函式
    Term() : coef(0), exp(0) {}

    // 自訂建構函式
    Term(float c, int e) : coef(c), exp(e) {}

    // Getter 方法
    float getCoef() const { return coef; }
    int getExp() const { return exp; }

    // Setter 方法
    void setCoef(float c) { coef = c; }
    void setExp(int e) { exp = e; }
};

// Polynomial 類別
class Polynomial {
public:
    Polynomial();              // 預設建構子
    ~Polynomial();             // 解構子
    Polynomial Add(const Polynomial& poly) const;  // 多項式相加
    Polynomial Mult(const Polynomial& poly) const; // 多項式相乘
    float Eval(float x) const; // 多項式求值

    // 運算子多載
    friend istream& operator>>(istream& in, Polynomial& poly);
    friend ostream& operator<<(ostream& out, const Polynomial& poly);

private:
    Term* termArray; // 儲存非零項的動態陣列
    int capacity;    // 動態陣列的容量
    int terms;       // 非零項的數量

    void EnsureCapacity(int newCapacity); // 確保動態陣列的容量足夠
};

// 預設建構子
Polynomial::Polynomial() : termArray(new Term[10]), capacity(10), terms(0) {}

// 解構子
Polynomial::~Polynomial() {
    delete[] termArray;
}

// 確保容量足夠
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

// 多項式相加
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

// 多項式相乘
Polynomial Polynomial::Mult(const Polynomial& poly) const {
    Polynomial result;

    for (int i = 0; i < terms; i++) {
        for (int j = 0; j < poly.terms; j++) {
            float coef = termArray[i].getCoef() * poly.termArray[j].getCoef();
            int exp = termArray[i].getExp() + poly.termArray[j].getExp();

            // 找尋是否已有相同的指數
            bool found = false;
            for (int k = 0; k < result.terms; k++) {
                if (result.termArray[k].getExp() == exp) {
                    result.termArray[k].setCoef(result.termArray[k].getCoef() + coef);
                    found = true;
                    break;
                }
            }

            // 若沒有相同指數的項，新增一項
            if (!found) {
                result.EnsureCapacity(result.terms + 1);
                result.termArray[result.terms++] = Term(coef, exp);
            }
        }
    }

    return result;
}

// 多項式求值
float Polynomial::Eval(float x) const {
    float result = 0;
    for (int i = 0; i < terms; i++) {
        result += termArray[i].getCoef() * pow(x, termArray[i].getExp());
    }
    return result;
}

// 輸入運算子多載
istream& operator>>(istream& in, Polynomial& poly) {
    cout << "請輸入非零項的數量：";
    in >> poly.terms;

    poly.EnsureCapacity(poly.terms);
    for (int i = 0; i < poly.terms; i++) {
        float coef;
        int exp;
        cout << "請輸入第 " << i + 1 << " 項的係數與指數（以空格分隔）：";
        in >> coef >> exp;
        poly.termArray[i] = Term(coef, exp);
    }
    return in;
}

// 輸出運算子多載
ostream& operator<<(ostream& out, const Polynomial& poly) {
    for (int i = 0; i < poly.terms; i++) {
        if (i > 0 && poly.termArray[i].getCoef() > 0) out << " + ";
        out << poly.termArray[i].getCoef() << "x^" << poly.termArray[i].getExp();
    }
    return out;
}

// 主程式測試
int main() {
    Polynomial p1, p2;

    cout << "輸入第一個多項式：" << endl;
    cin >> p1;
    cout << "輸入第二個多項式：" << endl;
    cin >> p2;

    Polynomial sum = p1.Add(p2);
    Polynomial product = p1.Mult(p2);

    cout << "第一個多項式為：" << p1 << endl;
    cout << "第二個多項式為：" << p2 << endl;
    cout << "兩個多項式的和為：" << sum << endl;
    cout << "兩個多項式的積為：" << product << endl;

    float x;
    cout << "請輸入欲求值的 x：";
    cin >> x;

    cout << "第一個多項式在 x = " << x << " 的值為：" << p1.Eval(x) << endl;
    cout << "第二個多項式在 x = " << x << " 的值為：" << p2.Eval(x) << endl;

    return 0;
}

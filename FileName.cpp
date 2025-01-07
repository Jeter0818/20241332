#include <iostream>
#include <cmath>
using namespace std;

// �w�q�`�I���c
struct Node {
    int coef;  // �Y��
    int exp;   // ����
    Node* next; // �U�@�Ӹ`�I����

    Node(int c = 0, int e = 0, Node* n = nullptr) : coef(c), exp(e), next(n) {}
};

// �w�q Polynomial ���O
class Polynomial {
private:
    Node* head; // �Y���I (��������Y���I)

public:
    // �w�]�c�y���
    Polynomial() {
        head = new Node(); // �إ��Y���I
        head->next = head; // ��l�Ƭ��������
    }

    // �ƻs�c�y���
    Polynomial(const Polynomial& a) {
        head = new Node();
        head->next = head;
        Node* current = a.head->next;
        while (current != a.head) {
            addTerm(current->coef, current->exp);
            current = current->next;
        }
    }

    // ��ȹB���
    const Polynomial& operator=(const Polynomial& a) {
        if (this != &a) {
            clear();
            Node* current = a.head->next;
            while (current != a.head) {
                addTerm(current->coef, current->exp);
                current = current->next;
            }
        }
        return *this;
    }

    // �R�c���
    ~Polynomial() {
        clear();
        delete head;
    }

    // ��J�h����
    friend istream& operator>>(istream& is, Polynomial& x) {
        int n; // ����
        is >> n;
        for (int i = 0; i < n; i++) {
            int coef, exp;
            is >> coef >> exp;
            x.addTerm(coef, exp);
        }
        return is;
    }

    // ��X�h����
    friend ostream& operator<<(ostream& os, const Polynomial& x) {
        Node* current = x.head->next;
        bool first = true;
        while (current != x.head) {
            if (!first) os << " ";
            os << current->coef << "x^" << current->exp;
            first = false;
            current = current->next;
        }
        return os;
    }

    // �[�k�B���
    Polynomial operator+(const Polynomial& b) const {
        Polynomial result;
        Node* p1 = head->next;
        Node* p2 = b.head->next;

        while (p1 != head && p2 != b.head) {
            if (p1->exp > p2->exp) {
                result.addTerm(p1->coef, p1->exp);
                p1 = p1->next;
            }
            else if (p1->exp < p2->exp) {
                result.addTerm(p2->coef, p2->exp);
                p2 = p2->next;
            }
            else {
                result.addTerm(p1->coef + p2->coef, p1->exp);
                p1 = p1->next;
                p2 = p2->next;
            }
        }

        while (p1 != head) {
            result.addTerm(p1->coef, p1->exp);
            p1 = p1->next;
        }
        while (p2 != b.head) {
            result.addTerm(p2->coef, p2->exp);
            p2 = p2->next;
        }

        return result;
    }

    // ��k�B���
    Polynomial operator-(const Polynomial& b) const {
        Polynomial result;
        Node* p1 = head->next;
        Node* p2 = b.head->next;

        while (p1 != head && p2 != b.head) {
            if (p1->exp > p2->exp) {
                result.addTerm(p1->coef, p1->exp);
                p1 = p1->next;
            }
            else if (p1->exp < p2->exp) {
                result.addTerm(-p2->coef, p2->exp);
                p2 = p2->next;
            }
            else {
                result.addTerm(p1->coef - p2->coef, p1->exp);
                p1 = p1->next;
                p2 = p2->next;
            }
        }

        while (p1 != head) {
            result.addTerm(p1->coef, p1->exp);
            p1 = p1->next;
        }
        while (p2 != b.head) {
            result.addTerm(-p2->coef, p2->exp);
            p2 = p2->next;
        }

        return result;
    }

    // ���k�B���
    Polynomial operator*(const Polynomial& b) const {
        Polynomial result;
        Node* p1 = head->next;
        while (p1 != head) {
            Node* p2 = b.head->next;
            while (p2 != b.head) {
                result.addTerm(p1->coef * p2->coef, p1->exp + p2->exp);
                p2 = p2->next;
            }
            p1 = p1->next;
        }
        return result;
    }

    // �D�Ȩ��
    float Evaluate(float x) const {
        float result = 0;
        Node* current = head->next;
        while (current != head) {
            result += current->coef * pow(x, current->exp);
            current = current->next;
        }
        return result;
    }

private:
    // �K�[�@����h������
    void addTerm(int coef, int exp) {
        if (coef == 0) return;

        Node* prev = head;
        Node* current = head->next;
        while (current != head && current->exp > exp) {
            prev = current;
            current = current->next;
        }

        if (current != head && current->exp == exp) {
            current->coef += coef;
            if (current->coef == 0) {
                prev->next = current->next;
                delete current;
            }
        }
        else {
            Node* newNode = new Node(coef, exp, current);
            prev->next = newNode;
        }
    }

    // �M�Ŧh����
    void clear() {
        Node* current = head->next;
        while (current != head) {
            Node* tmp = current;
            current = current->next;
            delete tmp;
        }
        head->next = head;
    }
};

int main() {
    Polynomial p1, p2;
    cout << "Enter first polynomial: ";
    cin >> p1;
    cout << "Enter second polynomial: ";
    cin >> p2;

    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;

    Polynomial sum = p1 + p2;
    Polynomial diff = p1 - p2;
    Polynomial prod = p1 * p2;

    cout << "p1 + p2: " << sum << endl;
    cout << "p1 - p2: " << diff << endl;
    cout << "p1 * p2: " << prod << endl;

    float x;
    cout << "Enter a value for x: ";
    cin >> x;

    cout << "p1 evaluated at x = " << x << ": " << p1.Evaluate(x) << endl;
    cout << "p2 evaluated at x = " << x << ": " << p2.Evaluate(x) << endl;

    return 0;
}

//#include <fstream>
//#include <string>
//#include <chrono>
//
//using namespace std;
//enum COLOR{
//    BLACK,
//    RED
//};
//
//class Node {
//public:
//    int value;
//    Node *left;
//    Node *right;
//    Node *parent;
//    COLOR color;
//    ~Node() {
//    }
//    void DeleteAll(){
//        if(left != NULL) left->DeleteAll();
//        if(right != NULL) right->DeleteAll();
//        delete(this);
//    }
//    Node() {}
//    Node(int value) : value(value) {
//        left = NULL;
//        right = NULL;
//        parent = NULL;
//        color = BLACK;
//    }
//    Node(int value, Node* par) : value(value) {
//        left = NULL;
//        right = NULL;
//        parent = par;
//    }
//
//    Node* grandparent(Node *n)
//    {
//        if ((n != NULL) && (n->parent != NULL))
//            return n->parent->parent;
//        else
//            return NULL;
//    }
//    Node* uncle(Node *n)
//    {
//        Node *g = grandparent(n);
//        if (g == NULL)
//            return NULL; // No grandparent means no uncle
//        if (n->parent == g->left)
//            return g->right;
//        else
//            return g->left;
//    }
//    Node* sibling(Node *n)
//    {
//        if (n == n->parent->left)
//            return n->parent->right;
//        else
//            return n->parent->left;
//    }
//    void rotate_left(Node *n)
//    {
//        Node *pivot = n->right;
//
//        pivot->parent = n->parent; /* при этом, возможно, pivot становится корнем дерева */
//        if (n->parent != NULL) {
//            if (n->parent->left==n)
//                n->parent->left = pivot;
//            else
//                n->parent->right = pivot;
//        }
//
//        n->right = pivot->left;
//        if (pivot->left != NULL)
//            pivot->left->parent = n;
//
//        n->parent = pivot;
//        pivot->left = n;
//    }
//    void rotate_right(Node *n)
//    {
//        Node *pivot = n->left;
//
//        pivot->parent = n->parent; /* при этом, возможно, pivot становится корнем дерева */
//        if (n->parent != NULL) {
//            if (n->parent->left==n)
//                n->parent->left = pivot;
//            else
//                n->parent->right = pivot;
//        }
//
//        n->left = pivot->right;
//        if (pivot->right != NULL)
//            pivot->right->parent = n;
//
//        n->parent = pivot;
//        pivot->right = n;
//    }
//    void insert_cases(Node *n)
//    {
//        if (n->parent == NULL)
//            n->color = BLACK;
//        else if (n->parent->color == BLACK)
//            return; /* Tree is still valid */
//        else{
//            Node *u = uncle(n), *g;
//
//            if ((u != NULL) && (u->color == RED)) {
//                n->parent->color = BLACK;
//                u->color = BLACK;
//                g = grandparent(n);
//                g->color = RED;
//                insert_cases(g);
//            } else {
//                Node *g = grandparent(n);
//
//                if ((n == n->parent->right) && (n->parent == g->left)) {
//                    rotate_left(n->parent);
//                    n = n->left;
//                } else if ((n == n->parent->left) && (n->parent == g->right)) {
//                    rotate_right(n->parent);
//                    n = n->right;
//                }
//
//                n->parent->color = BLACK;
//                g->color = RED;
//                if ((n == n->parent->left) && (n->parent == g->left)) {
//                    rotate_right(g);
//                } else { /* (n == n->parent->right) && (n->parent == g->right) */
//                    rotate_left(g);
//                }
//            }
//        }
//
//    }
//    void replace_node(Node* n, Node* child) {
//        child->parent = n->parent;
//        if (n == n->parent->left) {
//            n->parent->left = child;
//        } else {
//            n->parent->right = child;
//        }
//    }
//
//    void delete_one_child(Node *n)
//    {
//        Node *child = (n->right != NULL) ? n->left : n->right;
//
//        replace_node(n, child);
//        if (n->color == BLACK) {
//            if (child->color == RED)
//                child->color = BLACK;
//            else
//                delete_case1(child);
//        }
//        free(n);
//    }
//    void delete_case1(Node *n)
//    {
//        if (n->parent != NULL)
//            delete_case2(n);
//    }
//    void delete_case2(Node *n)
//    {
//        Node *s = sibling(n);
//
//        if (s->color == RED) {
//            n->parent->color = RED;
//            s->color = BLACK;
//            if (n == n->parent->left)
//                rotate_left(n->parent);
//            else
//                rotate_right(n->parent);
//        }
//        delete_case3(n);
//    }
//    void delete_case3(Node *n)
//    {
//        Node *s = sibling(n);
//
//        if ((n->parent->color == BLACK) &&
//            (s->color == BLACK) &&
//            (s->left->color == BLACK) &&
//            (s->right->color == BLACK)) {
//            s->color = RED;
//            delete_case1(n->parent);
//        } else
//            delete_case4(n);
//    }
//    void delete_case4(Node *n)
//    {
//        Node *s = sibling(n);
//
//        if ((n->parent->color == RED) &&
//            (s->color == BLACK) &&
//            (s->left->color == BLACK) &&
//            (s->right->color == BLACK)) {
//            s->color = RED;
//            n->parent->color = BLACK;
//        } else
//            delete_case5(n);
//    }
//    void delete_case5(Node *n)
//    {
//        Node *s = sibling(n);
//
//        if  (s->color == BLACK) { /* this if statement is trivial,
//due to case 2 (even though case 2 changed the sibling to a sibling's child,
//the sibling's child can't be red, since no red parent can have a red child). */
///* the following statements just force the red to be on the left of the left of the parent,
//   or right of the right, so case six will rotate correctly. */
//            if ((n == n->parent->left) &&
//                (s->right->color == BLACK) &&
//                (s->left->color == RED)) { /* this last test is trivial too due to cases 2-4. */
//                s->color = RED;
//                s->left->color = BLACK;
//                rotate_right(s);
//            } else if ((n == n->parent->right) &&
//                       (s->left->color == BLACK) &&
//                       (s->right->color == RED)) {/* this last test is trivial too due to cases 2-4. */
//                s->color = RED;
//                s->right->color = BLACK;
//                rotate_left(s);
//            }
//        }
//        delete_case6(n);
//    }
//    void delete_case6(Node *n)
//    {
//        Node *s = sibling(n);
//
//        s->color = n->parent->color;
//        n->parent->color = BLACK;
//
//        if (n == n->parent->left) {
//            s->right->color = BLACK;
//            rotate_left(n->parent);
//        } else {
//            s->left->color = BLACK;
//            rotate_right(n->parent);
//        }
//    }
//
//    void Add(int val) {
//        if (val < value) {
//            if (left == NULL) {
//                left = new Node(val, this);
//                insert_cases(left);
//            } else {
//                left->Add(val);
//            }
//        }
//        if (val > value) {
//            if (right == NULL) {
//                right = new Node(val, this);
//            } else {
//                right->Add(val);
//                insert_cases(right);
//            }
//        }
//    }
//    bool isInSet(int val) {
//        if (val == value)
//            return true;
//        if (val < value && left != NULL)
//            return left->isInSet(val);
//        if (val > value && right != NULL)
//            return right->isInSet(val);
//        return false;
//    }
//    Node* Leftest()
//    {
//        if(left == NULL)
//            return this;
//        return left->Leftest();
//    }
//    void Delete(int val)
//    {
//        if (val == value)
//        {
//            if(left == NULL && right == NULL)
//            {
//                if(parent!=NULL) {
//                    if (parent->left->value == val) parent->left = NULL;
//                    else if (parent->right->value == val) parent->right = NULL;
//                }
//                delete (this);
//                return;
//            } else
//            if(left == NULL && right != NULL)
//            {
//                value = right->value;
//                left = right->left;
//                Node* _right = right->right;
//                delete(right);
//
//                right = _right;
//            } else
//            if(left != NULL && right == NULL)
//            {
//                value = left->value;
//                right = left->right;
//                Node* _left = left->left;
//                delete(left);
//                left = _left;
//            } else
//            if(left != NULL && right != NULL)
//            {
//                Node* closest = right->Leftest();
//                value = closest->value;
//                closest->Delete(value);
//
//            }
//
//        }
//        else
//        if (val < value && left != NULL)
//            left->Delete(val);
//        else
//        if (val > value && right != NULL)
//            right->Delete(val);
//    };
//};
//
//class Set {
//
//public:
//    Node *root;
//
//    Set() {
//        root = NULL;
//    }
//    ~Set(){
//        root->DeleteAll();
//        delete(root);
//    }
//};
//
//int main() {
//    ifstream fin;
//    ofstream fout;
//    fin.open("set.in");
//    fout.open("set.out");
//    ios_base::sync_with_stdio(false);
//    Set mySet;
//    while (!fin.eof()) {
//        string command;
//        int val;
//
//        fin >> command;
//        fin >> val;
//
//        if (command.compare("insert") == 0) {
//            if (mySet.root == NULL)
//                mySet.root = new Node(val);
//            else {
//                mySet.root->Add(val);
//            }
//        } else
//        if (command.compare("exists") == 0) {
//            if (mySet.root == NULL)
//                fout << "false\n";
//            else {
//                fout << (mySet.root->isInSet(val) ? "true" : "false") << "\n";
//            }
//        } else
//        if (command.compare("delete") == 0) {
//            if (mySet.root != NULL)
//            {
//                if(mySet.root->left == NULL)
//                    if(mySet.root->right == NULL)
//                        if(mySet.root->value == val) {
//                            mySet.root->Delete(val);
//                            mySet.root == NULL;
//                            continue;
//                        }
//
//                mySet.root->Delete(val);
//            }
//        }
//    }
//    fin.close();
//    fout.close();
//    return 0;
//}
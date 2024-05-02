#include <iostream>
#include <queue>
#include <stack>
#include <omp.h>
using namespace std;

class Node {
    public:
        int data;
        Node* left;
        Node* right;
        
        Node(int data) {
            this->data = data;
            this->left = NULL;
            this->right = NULL;
        }
};

class Tree {
    public:
        Node* insert(Node* root, int data) {
            if (!root) {
                root = new Node(data);
                return root;
            }
            queue<Node*> q;
            q.push(root);
            while (!q.empty()) {
                Node* cur = q.front();
                q.pop();
                if (!cur->left) {
                    cur->left = new Node(data);
                    return root;
                } else {
                    q.push(cur->left);
                }
                
                if (!cur->right) {
                    cur->right = new Node(data);
                    return root;
                } else {
                    q.push(cur->right);
                }
            }
            return NULL;
        }
        
        void bfs(Node* root) {
            if (!root) {
                cout << "Tree is empty" << endl;
                return;
            }
            queue<Node*> q;
            q.push(root);
            
            while (!q.empty()) {
                
                #pragma omp parallel for
                for (int i = 0; i < q.size(); i++) {
                    Node* cur;
                    
                    #pragma omp critical
                    {
                        cur = q.front();
                        q.pop();
                        cout << cur->data << " ";
                    }
                    
                    #pragma omp critical
                    {
                        if (cur->left)
                            q.push(cur->left);
                        
                        if (cur->right)
                            q.push(cur->right);
                    }
                }
            }
            cout << endl;
        }
        
        void dfs(Node* root) {
            stack<Node*> st;
            st.push(root);
            while (!st.empty()) {
                #pragma omp parallel for
                for (int i = 0; i < st.size(); i++) {
                    Node* cur = st.top();
                    st.pop();
                    cout << cur->data << " ";
                    
                    if (cur->left)
                        st.push(cur->left);
                        
                    if (cur->right)
                        st.push(cur->right);
                }
            }
            cout << endl;
        }
};


int main()
{
    Node* root = NULL;
    Tree t;
    root = t.insert(root, 10);
    root = t.insert(root, 20);
    root = t.insert(root, 30);
    root = t.insert(root, 40);
    
   double start, end;

   start = omp_get_wtime();
    t.bfs(root);
   end = omp_get_wtime();
   cout << "Parallel BFS running duration: " << (end - start) << endl;
   
    start = omp_get_wtime();
     t.dfs(root);
    end = omp_get_wtime();
    cout << "Parallel DFS running duration: " << (end - start) << endl;
    
    return 0;
}